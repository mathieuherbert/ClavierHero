#ifndef FS_FAT_H
#define FS_FAT_H

#include <lib/String.h>
#include <sextant/types.h>
//#include <memoire/memoire.h>
//#include <memoire/alloc.h>
#include <drivers/ide.h>
#include <drivers/ClavierV.h>
#include <drivers/EcranV.h>

#define ATTR_FILE		0x04
#define ATTR_DIRECTORY	0x10
#define MAX_FILS 		20
#define FAT32 			32
#define MAX_FILE_LENGTH 20
#define EOF 26

/**
 * @file fs_fat.h
 * @brief Gestion du syst�me de fichier FAT.
 */

/** FAT EOC (End Of Cluster) marker
 *
 * In this context the FAT refers to the cluster table.
 * When the cluster contains a end of file then the EOC marker is set in the
 * mapping of this cluster in the FAT.
 */
#define EOC   0x0FFFFFF8

/** Fat Directory/File entry structure
 *
 * There are only 2 nodes types in FAT: file and directory.
 */
struct fat_directory{
	ui32_t		DIR_Attr;					//Fichier ou répertoire
	char		DIR_Name[MAX_FILE_LENGTH];		/* Short name */
	/* File attributes */
	ui32_t  	DIR_FileSize;				//Taille du fichier en octets
	luoffset_t 	addr_block;					//Adresse physique de la description du fichier sur le disque
	luoffset_t 	parent;						//l'adresse disque du père dans la hiérarchie de la FAT
	ui32_t		addr_data;					//Adresse physique des données du fichier
	ui32_t		offset;						//déplacement dans les données du fichier
	luoffset_t 	fils[MAX_FILS];				//l'adresse disque des fils du fichier
} __attribute__ ((packed));

/** Fat data structure
 *
 * This structure is filled during the mount operation. These fields are
 * computed from BS/BPB like describe in the official specification. The
 * structure is fundamental for partition use in many VFS operations.
 */
struct fat_data_structure {
	ui32_t* fat_table;
	ui32_t	RootDirSectors;		/* Number of sectors in root directory */
	ui32_t	FirstDataSector;	/* First data sector */
	ui32_t	DataSec;		/* Number of data sector in the partition */
	ui32_t	CountOfClusters;	/* Number of cluster in the partition */
	ui32_t	FirstRootDirSecNum;	/* First sector of the root directory */
	ui32_t	FAT_Type;		/* FAT type */
	ui32_t	EndOfCluster;		/* End of cluster marker */
	ui32_t	BytsPerClus;
	ui16_t	BytsPerSec;	/* Count of bytes per sector: 512, 1024, 2048 or 4096 */
	ui8_t	SecPerClus;	/* Number of sectors per allocation unit: 1, 2, 4, 8, 16, 32, 64 or 128 */
	ui16_t	RsvdSecCnt;	/* Number of reserved sectors in the Reserved region of the volume */
	ui8_t	NumFATs;	/* The count of FAT data structures on the volume. */
	ui16_t	RootEntCnt;	/* For FAT32 volumes, this field must be set to 0. */
	ui32_t	TotSec32;	/* This field is the new 32-bit total count of sectors on the volume. */
	ui32_t	FATSz32;	/* This field is the FAT32 32-bit count of sectors occupied by ONE FAT */
	ui32_t	TotReserv;	/* This field is the FAT32 32-bit count of sectors occupied by ONE FAT */
	ui32_t	RootClus;	/* This is set to the cluster number of the first cluster of the root directory. */
} __attribute__ ((packed));

/**
 * Permet de stocker la table en memoire comme on l'ecrit sur le disque.
 */
struct stock_tab {
	ui32_t tab[128];
} __attribute__ ((packed));

/**
 * Creation d'un fichier.
 */
sextant_ret_t create_file(char* name);

/**
 * Ouverture d'un fichier.
 */
struct fat_directory* fopen(char* nom_fic);

/**
 * fermeture d'un fichier.
 */
void fclose(struct fat_directory* fic);

/**
 * Ecriture dans un fichier. Les données sont ajoutées en fin de fichier.
 */
void fwrite(struct fat_directory* file,char* a_ecrire,int taille);

/**
 * Lecture dans un fichier.
 */
void fread(struct fat_directory* file,char* lu,int taille);

/**
 * Modification de la position du curseur dans le fichier fic. Le curseur est placé à la position
 * debut du fichier + deplacement (en octet).Pris en charge seulement par la lecture.
 */
void fseek(struct fat_directory* fic,int deplacement);

/**
 * Initialisation du système de fichier FAT.
 */
void fat_setup(bool clear);

#endif
