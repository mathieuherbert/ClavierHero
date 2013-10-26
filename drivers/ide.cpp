/* Copyright (C) 2005  Thomas Petazzoni, David Decotigny

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.
 */

#include "ide.h"
/**
 * @file ide.c
 * Basic PIO IDE implementation based on the ATA standards
 * http://www.t13.org/
 */


/**
 * Busy-wait for a given time
 * @param delay Delay to wait
 * @todo Implement a calibration routine
 */
static void udelay(int delay) {
	for(int i = 0; i < (delay * 1000) ; i++) {
		i++;
		i--;
	}
}

/*struct ide_controller ide_controllers[MAX_IDE_CONTROLLERS] = {
		{
				0,
				IDE_CONTROLLER_0_BASE,
				IDE_CONTROLLER_0_IRQ,
				IDE_CTRL_NOT_PRESENT,
		}
};
*/

struct ide_controller ide_controllers[MAX_IDE_CONTROLLERS] = {
  {
    0,
    IDE_CONTROLLER_0_BASE,
    IDE_CONTROLLER_0_IRQ,
    IDE_CTRL_NOT_PRESENT,
  },
  {
    1,
    IDE_CONTROLLER_1_BASE,
    IDE_CONTROLLER_1_IRQ,
    IDE_CTRL_NOT_PRESENT,
  }
};

/*
 * Each IDE controller is controlled through a set of 9 I/O ports,
 * starting from a base address, which is different for each IDE
 * controller. On a standard PC with two onboard IDE controllers, the
 * I/O registers of the first controller start at 0x1F0
 * (IDE_CONTROLLER_0_BASE), the I/O registers of the second controller
 * start at 0x170 (IDE_CONTROLLER_1_BASE). These I/O registers are
 * 8-bits wide, and can be read using the inb() macro, and written
 * using the outb() macro.
 *
 * The first controller is generally known as "primary" controller,
 * and the second one is know as "secondary" controller. Each of them
 * can handle at most two devices : the "master" device and the
 * "slave" device.
 *
 * The registers can be used to issue commands and send data to the
 * IDE controller, for example to identify a device, to read or write
 * a device. Then are different ways of transmitting data to the IDE
 * controller :
 *
 * - program the IDE controller, send the data, and wait for the
 *   completion of the request. This method is called "polling".
 *
 * - program the IDE controller, send the data, block the current
 *   process and do something else. The completion of the request will
 *   be signaled asynchronously by an interrupt (IRQ), which will
 *   allow to restart the sleeping process.
 *
 * - program the IDE controller and the DMA controller. There's no
 *   need to transfer the data to the IDE controller : the DMA
 *   controller will do it. This allows to use the CPU to do something
 *   useful during the transfer of data between the main memory and
 *   the IDE controller.
 *
 * In this driver, we use the two first methods. The polling method is
 * used to fetch the identification of the devices, while the IRQ
 * method is used to read and write to devices.
 */


void ide_irq_handler (int irq_level) {
	int i;
	struct ide_controller *ctrl = (struct ide_controller*)NULL1;

	for(i = 0; i < MAX_IDE_CONTROLLERS ; i++) {
		if (ide_controllers[i].irq == irq_level) {
			ctrl = & ide_controllers[i];
			break;
		}
	}
}

sextant_ret_t  ide_get_device_info (struct ide_device *dev) {
	int devselect;
	ui16_t buffer[256];
	struct ide_device_info *info;
	int timeout, i;
	int status;
	if (dev->position == IDE_DEVICE_MASTER)
		devselect = ATA_D_MASTER;
	else
		devselect = ATA_D_SLAVE;
	/* Ask the controller to NOT send interrupts to acknowledge commands */
	ecrireOctet(ATA_A_nIEN | ATA_A_4BIT, dev->ctrl->ioaddr + ATA_DEVICE_CONTROL);
	udelay(1);
	/* Select the device (master or slave) */
	ecrireOctet(ATA_D_IBM | devselect, dev->ctrl->ioaddr + ATA_DRIVE);
	/* Send the IDENTIFY command */
	ecrireOctet(ATA_C_ATA_IDENTIFY, dev->ctrl->ioaddr + ATA_CMD);
	/* Wait for command completion (wait while busy bit is set) */
	for(timeout = 0; timeout < 30000; timeout++) 	{
		status = lireOctet(dev->ctrl->ioaddr + ATA_STATUS);
		if(!(status & ATA_S_BSY))
			break;
		udelay(1);
	}
	/* DRQ bit indicates that data is ready to be read.
	 * If it is not set after an IDENTIFY command, there is a problem */
	if(! (status & ATA_S_DRQ))
		return SEXTANT_ERROR;
	/* Read data from the controller buffer to a temporary buffer */
	for(i = 0; i < 256; i++)
		buffer[i] = lireMot(dev->ctrl->ioaddr + ATA_DATA);
	/* The buffer contains an information structure, defined by ATA specification.
	 * To ease its access, we use the previously defined ide_device_info structure. */
	info = (struct ide_device_info*) buffer;
	/* Fetch intersting informations from the structure */
	dev->heads   = info->nb_logical_heads;
	dev->cyls    = info->nb_logical_cylinders;
	dev->sectors = info->nb_logical_sectors;
	dev->support_lba = false;
	/* Determines if device supports LBA. The method is a bit ugly, but there's no other way */
	if (info->capabilities & (1 << 1)
			&& info->major_version
			&& (info->fields_valid & 1)
			&& (info->lba_capacity & 1))
		dev->support_lba = true;
	/* Determines the capacity of the device */
	if (dev->heads   == 16 && dev->sectors == 63 &&	dev->cyls    == 16383) {
		if (dev->support_lba)
			dev->blocks = info->lba_capacity;
		else
			return SEXTANT_ERROR;
	}
	else
		dev->blocks = dev->cyls * dev->sectors * dev->heads;
	return SEXTANT_OK;
}

static ide_device_type_t ide_probe_device(struct ide_device *dev) {
	int status;
	int devselect;
	if (dev->position == IDE_DEVICE_MASTER)
		devselect = ATA_D_MASTER;
	else
		devselect = ATA_D_SLAVE;
	/* Select the given device */
	ecrireOctet(ATA_D_IBM | devselect, dev->ctrl->ioaddr + ATA_DRIVE);
	/* Read the status of the device */
	status = lireOctet(dev->ctrl->ioaddr + ATA_STATUS);
	/* If status indicates a busy device, it means that there's no device */
	if (status & ATA_S_BSY)
		return IDE_DEVICE_NONE;
	/* If status indicates that drive is ready and drive has complete seeking, then we've got an hard drive */
	if (status & (ATA_S_DRDY | ATA_S_DSC))
		return IDE_DEVICE_HARDDISK;
	/* Detect CD-ROM drives by reading the cylinder low byte and cylinder high byte,
	 * and check if they match magic values */
	if(lireOctet(dev->ctrl->ioaddr + ATA_CYL_LSB) == ATAPI_MAGIC_LSB &&
			lireOctet(dev->ctrl->ioaddr + ATA_CYL_MSB) == ATAPI_MAGIC_MSB)
		return IDE_DEVICE_CDROM;
	return IDE_DEVICE_NONE;
}

static sextant_ret_t ide_probe_controller(struct ide_controller *ctrl) {
	bool hasdevice = false;
	sextant_ret_t ret = SEXTANT_OK;
	/* Master */
	ctrl->devices[0].id       = 0;
	ctrl->devices[0].position = IDE_DEVICE_MASTER;
	ctrl->devices[0].ctrl     = ctrl;
	ctrl->devices[0].type     = ide_probe_device (& ctrl->devices[0]);
	if (ctrl->devices[0].type == IDE_DEVICE_HARDDISK) {
		ret = ide_get_device_info (&ctrl->devices[0]);
		hasdevice = true;
	}
	/* Slave */
	ctrl->devices[1].id       = 1;
	ctrl->devices[1].position = IDE_DEVICE_SLAVE;
	ctrl->devices[1].ctrl     = ctrl;
	ctrl->devices[1].type     = ide_probe_device (& ctrl->devices[1]);
	if (ctrl->devices[1].type == IDE_DEVICE_HARDDISK) {
		ret = ide_get_device_info (& ctrl->devices[1]);
		hasdevice = true;
	}
	if (hasdevice)
		irq_set_routine (ctrl->irq, ide_irq_handler);
	return ret;
}

static sextant_ret_t ide_io_operation(struct ide_device *dev,vaddr_t buf, int block,bool iswrite,int lgg) {
	ui8_t cyl_lo, cyl_hi, sect, head, status;
	int devselect, i;
	int lg = lgg/2 + 1;
	if(block > dev->blocks)
		return -SEXTANT_ERROR;
	if (dev->position == IDE_DEVICE_MASTER)
		devselect = ATA_D_MASTER;
	else
		devselect = ATA_D_SLAVE;
	/* Compute the position of the block in the device in terms of cylinders, sectors and heads.
	 * As cylinders must be sent in two separate parts, we compute it that way. */
	if (dev->support_lba) {
		sect   = (block & 0xff);
		cyl_lo = (block >> 8) & 0xff;
		cyl_hi = (block >> 16) & 0xff;
		head   = ((block >> 24) & 0x7) | 0x40;
	} else {
		int cylinder = block / (dev->heads * dev->sectors);
		int temp = block % (dev->heads * dev->sectors);
		cyl_lo = cylinder & 0xff;
		cyl_hi = (cylinder >> 8) & 0xff;
		head   = temp / dev->sectors;
		sect   = (temp % dev->sectors) + 1;
	}
	/* Select device */
	ecrireOctet(ATA_D_IBM | devselect, dev->ctrl->ioaddr + ATA_DRIVE);
	udelay(100);
	/* Write to registers */
	ecrireOctet(ATA_A_4BIT, dev->ctrl->ioaddr + ATA_DEVICE_CONTROL);
	ecrireOctet(1,          dev->ctrl->ioaddr + ATA_ERROR);
	ecrireOctet(0,          dev->ctrl->ioaddr + ATA_PRECOMP);
	ecrireOctet(1,          dev->ctrl->ioaddr + ATA_SECTOR_COUNT);
	ecrireOctet(sect,       dev->ctrl->ioaddr + ATA_SECTOR_NUMBER);
	ecrireOctet(cyl_lo,     dev->ctrl->ioaddr + ATA_CYL_LSB);
	ecrireOctet(cyl_hi,     dev->ctrl->ioaddr + ATA_CYL_MSB);
	ecrireOctet((ATA_D_IBM | devselect | head),dev->ctrl->ioaddr + ATA_DRIVE);
	/* Send the command, either read or write */
	if (iswrite)
		ecrireOctet(ATA_C_WRITE, dev->ctrl->ioaddr + ATA_CMD);
	else
		ecrireOctet(ATA_C_READ, dev->ctrl->ioaddr + ATA_CMD);
	/* Wait for the device ready to transfer */
	do {
		udelay(1);
	} while(lireOctet(dev->ctrl->ioaddr + ATA_STATUS) & ATA_S_BSY);
	/* If an error was detected, stop here */
	if (lireOctet(dev->ctrl->ioaddr + ATA_STATUS) & ATA_S_ERROR)
		return -SEXTANT_ERROR;
	/* If it's a write I/O, transfer the contents of the buffer provided by the user to
	 * the controller internal buffer, so that the controller can write the data to the disk */
	if (iswrite) {
		/* Wait for the DRQ bit to be set */
		while((status & ATA_S_BSY) || !(status & ATA_S_DRQ)) {
			status = lireOctet(dev->ctrl->ioaddr + ATA_STATUS);
			if (status & ATA_S_ERROR) {
				return -SEXTANT_ERROR;
			}
		}
		/* Do the transfer to the device's buffer */
		ui16_t *buffer = (ui16_t *)buf;
		for (i = 0 ; i < lg ; i++)//Longueur
			ecrireMot(buffer[i], dev->ctrl->ioaddr + ATA_DATA);
		/* Wait for the device to have received all the data */
		while((status & ATA_S_BSY) || (status & ATA_S_DRQ)) {
			status = lireOctet(dev->ctrl->ioaddr + ATA_STATUS);
			if(status & ATA_S_ERROR) {
				return -SEXTANT_ERROR;
			}
		}
	}
	/* ATA specs tell to read the alternate status reg and ignore its result */
	lireOctet(dev->ctrl->ioaddr + ATA_ALTPORT);
	if (! iswrite) {
		/* Wait for the DRQ bit to be set */
		status = lireOctet(dev->ctrl->ioaddr + ATA_STATUS);
		if(status & ATA_S_ERROR) {
			return -SEXTANT_ERROR;
		}
		/* copy data from the controller internal buffer to the buffer provided by the user */
		ui16_t *buffer = (ui16_t *) buf;
		for (i = 0 ; i < lg ; i++)
			buffer[i] = lireMot(dev->ctrl->ioaddr + ATA_DATA);
		/* ATA specs tell to read the alternate status reg and ignore its result */
		lireOctet(dev->ctrl->ioaddr + ATA_ALTPORT);
	}
	/* If an error was detected, stop here */
	if (lireOctet(dev->ctrl->ioaddr + ATA_STATUS) & ATA_S_ERROR) {
		return -SEXTANT_ERROR;
	}
	/* Someone else can safely use devices on this controller for other requests */
	return SEXTANT_OK;
}

sextant_ret_t ide_read_device (struct ide_device *dev, vaddr_t dest_buf,luoffset_t block_offset,int lg) {
	return ide_io_operation(dev, dest_buf, block_offset,false,lg);
}

sextant_ret_t ide_write_device (struct ide_device* dev, vaddr_t src_buf, luoffset_t block_offset,int lg) {
	return ide_io_operation (dev, src_buf, block_offset,true,lg);
}

sextant_ret_t ide_subsystem_setup(EcranV* e) {
	sextant_ret_t ret;
	int i;
	e->afficherMot("Initialisation du pilote IDE\n");
for (i=0;i<2;i++) {
	ret = ide_probe_controller(&ide_controllers[i]);
	if(ret != SEXTANT_OK)
		e->miniprintf("Error while probing IDE controller %d\n",i);
	else  {
		e->miniprintf("Sur le controleur %d,\nEn master : ",i);
		switch(ide_controllers[i].devices[0].type) {
		case IDE_DEVICE_HARDDISK :
			e->afficherMot("detecting hard disk\n");
			break;
		case IDE_DEVICE_CDROM :
			e->afficherMot("detecting cd rom\n");
			break;
		case IDE_DEVICE_NONE :
			e->afficherMot("detecting none\n");
			break;
		}
		e->afficherMot("En esclave : ");
		switch(ide_controllers[i].devices[1].type) {
		case IDE_DEVICE_HARDDISK :
			e->afficherMot("detecting hard disk\n");
			break;
		case IDE_DEVICE_CDROM :
			e->afficherMot("detecting cd rom\n");
			break;
		case IDE_DEVICE_NONE :
			e->afficherMot("detecting none\n");
			break;
		}
	}
}
	return SEXTANT_OK;
}
