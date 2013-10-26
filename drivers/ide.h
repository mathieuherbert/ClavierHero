/* Copyright (C) 2005  Thomas Petazzoni

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
#ifndef DRV_IDE_H
#define DRV_IDE_H

#include <sextant/types.h>
#include <hal/fonctionsES.h>
#include <sextant/interruptions/irq.h>
#include <drivers/EcranV.h>

#define IDE_CONTROLLER_0_BASE           0x1F0
#define IDE_CONTROLLER_1_BASE           0x170
#define IDE_CONTROLLER_0_IRQ            14
#define IDE_CONTROLLER_1_IRQ            15
/*
 * All defines below are relative to the base address of the I/O
 * registers (IDE_CONTROLLER_0_BASE and IDE_CONTROLLER_1_BASE)
 */

/**
 * Read/write register that allows to transfer the data to be written
 * or to fetch the read data from the IDE controller.
 */
#define ATA_DATA                        0x00

/**
 * Read only register that gives information about errors that occured
 * during operation
 */
#define ATA_ERROR                       0x01

/**
 * Write only register to set precompensation. It is in fact the same
 * register as the ATA_ERROR register. It simply has a different
 * behaviour when reading and writing it.
 */
#define ATA_PRECOMP                     0x01

/**
 * Write only register used to set the count of sectors on which the
 * request applies.
 */
#define ATA_SECTOR_COUNT                0x02

/**
 * Write only register used to set the number of the starting sector
 * of the request.
 */
#define ATA_SECTOR_NUMBER               0x03

/**
 * Write only register used to set the 8 lower bits of the starting
 * cylinder number of the request
 */
#define ATA_CYL_LSB                     0x04

/**
 * Write only register used to set the 8 higher bits of the starting
 * cylinder number of the request
 */
#define ATA_CYL_MSB                     0x05

/**
 * Write only register that allows to select whether the LBA mode
 * should be used, and to select whether the request concerns the
 * slave or master device.
 */
#define 		ATA_DRIVE               0x06
#define         ATA_D_IBM               0xa0    /* bits that must be set */
#define         ATA_D_LBA               0x40    /* use LBA ? */
#define         ATA_D_MASTER            0x00    /* select master */
#define         ATA_D_SLAVE             0x10    /* select slave */

/**
 * Read only register that contains the status of the controller. Each
 * bit of this register as a different signification.
 */
#define 		ATA_STATUS				0x07
#define         ATA_S_ERROR             0x01    /* error */
#define         ATA_S_INDEX             0x02    /* index */
#define         ATA_S_CORR              0x04    /* data corrected */
#define         ATA_S_DRQ               0x08    /* data request */
#define         ATA_S_DSC               0x10    /* drive Seek Completed */
#define         ATA_S_DWF               0x20    /* drive write fault */
#define         ATA_S_DRDY              0x40    /* drive ready */
#define         ATA_S_BSY               0x80    /* busy */

/**
 * Write only register used to set the command that the IDE controller
 * should process. In our driver, only ATA_C_ATA_IDENTIFY, ATA_C_READ
 * and ATA_C_WRITE are used.
 */
#define 		ATA_CMD					0x07
#define         ATA_C_ATA_IDENTIFY		0xec    /* get ATA params */
#define         ATA_C_ATAPI_IDENTIFY    0xa1    /* get ATAPI params*/
#define         ATA_C_READ              0x20    /* read command */
#define         ATA_C_WRITE             0x30    /* write command */
#define         ATA_C_READ_MULTI        0xc4    /* read multi command */
#define         ATA_C_WRITE_MULTI       0xc5    /* write multi command */
#define         ATA_C_SET_MULTI         0xc6    /* set multi size command */
#define         ATA_C_PACKET_CMD        0xa0    /* set multi size command */

/**
 * Read register that contains more information about the status of
 * the controller
 */
#define ATA_ALTPORT                     0x206   /* (R) alternate Status register */
/**
 * Write only register that allows to control the controller
 */
#define ATA_DEVICE_CONTROL              0x206   /* (W) device control
	register */
#define         ATA_A_nIEN              0x02    /* disable interrupts */
#define         ATA_A_RESET             0x04    /* RESET controller */
#define         ATA_A_4BIT              0x08    /* 4 head bits */
/** Magic numbers used to detect ATAPI devices */
#define ATAPI_MAGIC_LSB                 0x14
#define ATAPI_MAGIC_MSB                 0xeb
#define MAX_IDE_CONTROLLERS 			2
#define MAX_IDE_DEVICES     			2
#define IDE_BLK_SIZE        			512
#define IDE_DEVICE(ctrl,device) 		(((ctrl) * 2) + (device))
#define IDE_MINOR(ctrl,device)  		(IDE_DEVICE(ctrl,device)*16)
#define IDE_MAJOR            			1
/* This structure describe the informations returned by the Identify
   Device command (imposed by the ATA standard) */
struct ide_device_info {
	ui16_t general_config_info;      /* 0 */
	ui16_t nb_logical_cylinders;     /* 1 */
	ui16_t reserved1;                /* 2 */
	ui16_t nb_logical_heads;         /* 3 */
	ui16_t unformatted_bytes_track;  /* 4 */
	ui16_t unformatted_bytes_sector; /* 5 */
	ui16_t nb_logical_sectors;       /* 6 */
	ui16_t vendor1[3];               /* 7-9 */
	ui8_t  serial_number[20];        /* 10-19 */
	ui16_t buffer_type;              /* 20 */
	ui16_t buffer_size;              /* 21 */
	ui16_t ecc_bytes;                /* 22 */
	ui8_t  firmware_revision[8];     /* 23-26 */
	ui8_t  model_number[40];         /* 27-46 */
	ui8_t  max_multisect;            /* 47 */
	ui8_t  vendor2;
	ui16_t dword_io;                 /* 48 */
	ui8_t  vendor3;                  /* 49 */
	ui8_t  capabilities;
	ui16_t reserved2;                /* 50 */
	ui8_t  vendor4;                  /* 51 */
	ui8_t  pio_trans_mode;
	ui8_t  vendor5;                  /* 52 */
	ui8_t  dma_trans_mode;
	ui16_t fields_valid;             /* 53 */
	ui16_t cur_logical_cylinders;    /* 54 */
	ui16_t cur_logical_heads;        /* 55 */
	ui16_t cur_logical_sectors;      /* 56 */
	ui16_t capacity1;                /* 57 */
	ui16_t capacity0;                /* 58 */
	ui8_t  multsect;                 /* 59 */
	ui8_t  multsect_valid;
	ui32_t lba_capacity;             /* 60-61 */
	ui16_t dma_1word;                /* 62 */
	ui16_t dma_multiword;            /* 63 */
	ui16_t pio_modes;                /* 64 */
	ui16_t min_mword_dma;            /* 65 */
	ui16_t recommended_mword_dma;    /* 66 */
	ui16_t min_pio_cycle_time;       /* 67 */
	ui16_t min_pio_cycle_time_iordy; /* 68 */
	ui16_t reserved3[11];            /* 69-79 */
	ui16_t major_version;            /* 80 */
	ui16_t minor_version;            /* 81 */
	ui16_t command_sets1;            /* 82 */
	ui16_t command_sets2;            /* 83 dixit lk : b14 (smart enabled) */
	ui16_t reserved4[4];             /* 84-87 */
	ui16_t dma_ultra;                /* 88 dixit lk */
	ui16_t reserved5[37];            /* 89-125 */
	ui16_t last_lun;                 /* 126 */
	ui16_t reserved6;                /* 127 */
	ui16_t security;                 /* 128 */
	ui16_t reserved7[127];
} __attribute__((packed));

enum ide_device_type_t { IDE_DEVICE_NONE,IDE_DEVICE_HARDDISK,IDE_DEVICE_CDROM };
enum ideDevice { IDE_DEVICE_MASTER, IDE_DEVICE_SLAVE };
enum presence { IDE_CTRL_NOT_PRESENT, IDE_CTRL_PRESENT };


struct ide_controller;
struct ide_device {
	int id;
	ide_device_type_t type;
	ideDevice position;
	int cyls;
	int heads;
	int sectors;
	int blocks;
	bool support_lba;
	struct ide_controller *ctrl;
};

struct ide_controller {
	int id;
	int ioaddr;
	int irq;
	presence state;
	struct ide_device devices[MAX_IDE_DEVICES];
};
/***
 * Lecture du disque.
 ***/
sextant_ret_t ide_read_device(struct ide_device*, vaddr_t dest_buf,luoffset_t block_offset,int);
/***
 * Initialisation du driver ide.
 ***/
sextant_ret_t ide_subsystem_setup(EcranV*);
/***
 * Ecriture sur le disque.
 ***/
sextant_ret_t ide_write_device(struct ide_device*, vaddr_t src_buf, luoffset_t block_offset,int);

#endif
