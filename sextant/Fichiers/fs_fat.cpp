/* Copyright (C) 2007 Anthoine Bourgeois

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
#include "fs_fat.h"

extern struct ide_controller ide_controllers[MAX_IDE_CONTROLLERS];//Les disques dur détectés
struct fat_data_structure data_struct;//Les informations de la FAT

/**
 * Calcul de l'adresse disque d'après le numéro de cluster. Les clusters 0 et 1 n'existent pas (convention, 0 = cluster vide).
 * Le numéro du premier cluster est donc 2.
 */
static luoffset_t find_addr(ui32_t num) {
	return (num-2) * data_struct.SecPerClus + data_struct.FirstDataSector;
}

/**
 * Calcul le numéro du cluster d'après l'adresse disque (l'adresse disque est un numéro de secteur).
 */
static ui32_t find_cluster_num(luoffset_t addr) {
	return (((ui32_t)addr - data_struct.FirstDataSector) / data_struct.SecPerClus + 2);
}

/**
 * Cherche le numéro du dernier cluster.
 */
static sextant_ret_t find_last_cluster(/*OUT*/ui32_t* num_last_cluster) {
	ui32_t num_clus = 2;
	ui32_t buffer = data_struct.fat_table[num_clus - 2];
	while(buffer != data_struct.EndOfCluster) {
		num_clus = buffer;
		buffer = data_struct.fat_table[num_clus - 2];
	}
	*num_last_cluster = num_clus;
	return SEXTANT_OK;
}

/**
 * Cherche le premier cluster libre dans la FAT.
 */
static sextant_ret_t find_free_cluster(/*OUT*/ui32_t* num_free_cluster) {
	ui32_t num_clus=2;
	ui32_t buffer = data_struct.fat_table[num_clus - 2];
	while(buffer != 0 && num_clus < data_struct.CountOfClusters+2) {
		num_clus ++;
		buffer = data_struct.fat_table[num_clus - 2];
	}
	if(num_clus >= data_struct.CountOfClusters+2)
		return -SEXTANT_ERROR;
	*num_free_cluster = num_clus;
	return SEXTANT_OK;
}

/**
 * Ajout d'un nouveau cluster. Si le paramètre prec_clus existe, l'ajout se fait à la suite du cluster
 * numéro prec_clus ; sinon le cluster est ajouter en fin de liste.
 */
static ui32_t add_new_cluster(ui32_t* num_clus,ui32_t prec_clus=NULL) {
	ui32_t num_last_cluster;
	find_free_cluster(num_clus);
	if(*num_clus != 2)//Si ce n'est pas le premier cluster
		if(prec_clus == NULL) {
			find_last_cluster(&num_last_cluster);
			data_struct.fat_table[num_last_cluster - 2] = *num_clus;
		}
		else
			data_struct.fat_table[prec_clus - 2] = *num_clus;
	data_struct.fat_table[*num_clus - 2] = data_struct.EndOfCluster;
	return SEXTANT_OK;
}

/**
 * Ajout d'un nouveau cluster contenant les données du buffer buf.
 * La taille est exprimée en octets.
 */
static sextant_ret_t set_cluster_value(vaddr_t buf,int taille,ui32_t prec_clus=NULL) {
	int nb_cluster = taille / data_struct.BytsPerClus + 1;
	for(int i=0;i<nb_cluster;i++) {
		ui32_t num_clus;
		add_new_cluster(&num_clus,prec_clus);
		if(prec_clus != NULL)
			prec_clus = num_clus;
		vaddr_t addr_clus = find_addr(num_clus);
		for(int secteur=0,lg=data_struct.BytsPerSec,offset=0;secteur < data_struct.SecPerClus && taille>0;secteur++) {
			ide_write_device(&ide_controllers[0].devices[1],buf + offset,addr_clus + secteur,lg);
			offset += lg;
			taille -= lg;
		}
	}
	return SEXTANT_OK;
}

/**
 * Réécrit le cluster à l'adresse addr_block avec les données du buffer buf.
 */
static sextant_ret_t rewrite_cluster(vaddr_t buf,int taille,luoffset_t addr_block) {
	int nb_cluster = taille / data_struct.BytsPerClus + 1;
	ui32_t num_clus = find_cluster_num(addr_block);
	for(int i=0;i<nb_cluster;i++) {
		for(int secteur=0,lg=data_struct.BytsPerSec,offset=0;secteur < data_struct.SecPerClus && taille>0;secteur++) {
			ide_write_device(&ide_controllers[0].devices[1],buf + offset,addr_block + secteur,lg);
			offset += lg;
			taille -= lg;
		}
		num_clus = data_struct.fat_table[num_clus-2];
	}
	return SEXTANT_OK;
}

/**
 * Création du répertoire racine nommé "root" permettant de stocker des fichiers.
 */
static void create_directory_root(struct fat_directory* dir) {
	ui32_t* mon_clus = (ui32_t*)malloc(sizeof(ui32_t));
	char* name = "root";

	dir->DIR_Attr = ATTR_DIRECTORY;//La structure est un répertoire
	dir->DIR_FileSize = 0;
	find_free_cluster(mon_clus);
	dir->addr_block = find_addr(*mon_clus);
	String::strcpy(dir->DIR_Name,name,String::strlen(name)+1);
	for(int i = 0; i< MAX_FILS;i++)
		dir->fils[i] = 0;//0 signifie l'absence de fils.
	set_cluster_value((vaddr_t)dir,sizeof(struct fat_directory));
}

/**
 * Retourne la taille du fichier. La fin du fichier est marquée par le caractère EOF.
 * Taille maximale d'un fichier est de 4 Go.
 */
static ui32_t ficlen(char* buf) {
	ui32_t len;
	for(len = 0;buf[len] != EOF && len < 4294967295;len++);
	if(len >= 4294967295)
		return 0;
	else
		return len;
}

/**
 * Ajoute un fils d'adresse disque moi au père d'adresse disque addr_p.
 */
static sextant_ret_t add_fils(luoffset_t addr_p,luoffset_t moi) {
	int i;
	struct fat_directory p;
	ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)&p,addr_p,sizeof(struct fat_directory));
	for(i = 0;p.fils[i] != 0 && i< MAX_FILS;i++);
	if(i == MAX_FILS)//Trop de fils : un répertoire peut contenir au maximum 20 fichiers.
		return SEXTANT_ERROR;
	else {
		p.fils[i] = moi;
		rewrite_cluster((vaddr_t)&p,sizeof(struct fat_directory),p.addr_block);
		return SEXTANT_OK;
	}
}

/**
 * Retrouve le fichier de nom name.
 */
static luoffset_t get_file(char* name,/*OUT*/struct fat_directory* file) {
	ui32_t i;
	bool compare = false;//Vrai quand le fichier de nom name a été trouvé dans le répertoire racine
	struct fat_directory root;
	ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)&root,32,sizeof(struct fat_directory));
	for(i = 0;i< MAX_FILS && !compare && root.fils[i]!=0;i++) {
		ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)file,root.fils[i],sizeof(struct fat_directory));
		compare = String::strcmp(file->DIR_Name,name);
	}
	if(compare)
		return root.fils[i];
	else
		return SEXTANT_ERROR;
}

/**
 * Création d'un fichier de nom name dans le répertoire racine.
 */
sextant_ret_t create_file(char* name) {
	char buffer = EOF;//Contenu du fichier. Le fichier vide contient seulement le caractère de fin de fichier.
	struct fat_directory* dir =(struct fat_directory*)malloc(sizeof(struct fat_directory));
	ui32_t* mon_clus = (ui32_t*)malloc(sizeof(struct fat_directory));
	if(String::strlen(name)+1 > MAX_FILE_LENGTH) {//Nom du fichier trop long
		free((vaddr_t)dir);
		return SEXTANT_ERROR;
	}
	if(get_file(name,dir) != SEXTANT_ERROR) {//Si le fichier est déjà créé, on arrête tout !
		free((vaddr_t)dir);
		return SEXTANT_ERROR;
	}
	dir->DIR_Attr = ATTR_FILE;//La structure est un fichier
	dir->DIR_FileSize = 1;//Contient le caractère EOF
	find_free_cluster(mon_clus);
	dir->addr_data = find_addr(*mon_clus);//Les données du fichier commenceront au cluster numéro mon_clus
	set_cluster_value((vaddr_t)&buffer,dir->DIR_FileSize);
	find_free_cluster(mon_clus);
	dir->addr_block = find_addr(*mon_clus);//L'adresse disque du fichier qu'on vient de créer
	free((vaddr_t)mon_clus);
	String::strcpy(dir->DIR_Name,name,String::strlen(name)+1);
	dir->parent = find_addr(2);//Le fichier est dans le répertoire racine se trouvant dans le premier cluster.
	add_fils(dir->parent,dir->addr_block);
	set_cluster_value((vaddr_t)dir,sizeof(struct fat_directory));//Ecriture du fichier sur le disque
	free((vaddr_t)dir);
	return SEXTANT_OK;
}

/**
 * Supprime tous les fichiers de la structure FAT (Formatage).
 * Ecriture d'un booléen dans le secteur 0 du disque. Ce booléen permet de savoir s'il faut recréer une structure
 * FAT ou s'il faut en récupérer une déjà écrite sur le disque.
 */
static void fat_clear() {
	bool* zero = (bool*)malloc(sizeof(bool));
	*zero = false;
	ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)zero,0,512);
}

/**
 * Initialisation de la structure FAT.
 */
static sextant_ret_t fat_mount(bool* formate) {
	/* Set fat system */
	data_struct.BytsPerSec = IDE_BLK_SIZE;//Nombre d'octets par secteur = nombre d'octets d'un secteur disque
	data_struct.SecPerClus = 32;
	data_struct.BytsPerClus = data_struct.BytsPerSec * data_struct.SecPerClus;
	data_struct.RsvdSecCnt = 0;
	data_struct.NumFATs = 2;//On écrit deux fois la table, sécurité si secteur défectueux
	data_struct.TotSec32 = ide_controllers[0].devices[1].blocks;//Nombre de secteur présent sur le disque
	data_struct.RootClus = 2;//Numéro du cluster du répertoire racine
	data_struct.CountOfClusters = data_struct.TotSec32 / data_struct.SecPerClus;//Nombre de cluster disponible dans la FAT
	data_struct.fat_table = (ui32_t*)malloc(sizeof(ui32_t)*data_struct.CountOfClusters);//Table de la liste des clusters
	data_struct.FATSz32 = sizeof(ui32_t)*data_struct.CountOfClusters + sizeof(struct fat_data_structure)
			+ data_struct.BytsPerSec;//Premier secteur est reserve (detection de la Fat)
	data_struct.FirstDataSector = data_struct.SecPerClus;//adresse disque du début des données. Premier cluster est réservé pour le répertoire racine
	//On reserve i clusters pour la structure Fat
	for(int i=1;(i*data_struct.BytsPerClus) < (data_struct.NumFATs * data_struct.FATSz32);i++) {
		data_struct.CountOfClusters = data_struct.TotSec32 / data_struct.SecPerClus - i;
		data_struct.FirstDataSector = data_struct.SecPerClus * i;
	}
	data_struct.FAT_Type = FAT32;
	data_struct.EndOfCluster = EOC;

	//Initialisation de la liste des clusters
	struct stock_tab* tintin = (struct stock_tab*)malloc(sizeof(struct stock_tab));
	for(unsigned int i=0; i < data_struct.CountOfClusters;i++)
		data_struct.fat_table[i] = 0;//Initialise tous les clusters à vide
	//Creation du repertoire racine
	struct fat_directory* root = (struct fat_directory*)malloc(sizeof(struct fat_directory));
	create_directory_root(root);
	//Ecriture des information de la fat
	*formate = true;//Une table FAT est présente sur le disque.
	//Le secteur 0 contient le booléen permettant de savoir si une table FAT est présente
	int secteur = 0;
	ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)formate,secteur,data_struct.BytsPerSec);
	secteur++;
	//Le secteur 1 contient la structure FAT permettant de retrouver les fichiers écrits sur le disque
	ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)&data_struct,secteur,data_struct.BytsPerSec);
	secteur++;
	//L'écriture sur le secteur 2 ne fonctionne pas ???? alors on écrit en 3.
	secteur = 3;
	int offset = 0;
	int taille = sizeof(ui32_t)*data_struct.CountOfClusters;//Taille de la liste des clusters
	//Ecriture de la liste des clusters.
	while(offset < taille) {
		/* Un secteur fait 512 octets. Une adresse de cluster est sur 4 octets. Un secteur contient donc
		 * 128 adresses des clusters */
		for(int i=0;i<128;i++)
			tintin->tab[i] = data_struct.fat_table[offset/4 + i];
		if(SEXTANT_OK != ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)tintin,secteur,data_struct.BytsPerSec))
			return -SEXTANT_ERROR;
		offset +=data_struct.BytsPerSec;
		secteur++;
	}
	free((vaddr_t)tintin);
	free((vaddr_t)root);
	return SEXTANT_OK;
}

struct fat_directory* fopen(char* nom_fic) {
	struct fat_directory* file = (struct fat_directory*)malloc(sizeof(struct fat_directory));
	if(get_file(nom_fic,file)== SEXTANT_ERROR)
		return NULL;
	file->offset = 0;//Déplacement à l'intérieur du fichier lors d'une lecture
	return file;
}

void fclose(struct fat_directory* fic) {
	free((vaddr_t)fic);
}

void fwrite(struct fat_directory* file,char* chaine,int taille) {
	char buf[data_struct.BytsPerSec];
	int i=0,j,libre_sec=0,nb_sec;
	char a_ecrire[taille+1];

	/* La copie permet d'ajouter le caractère fin de fichier sans écrire après l'adresse chaine + taille. Par exemple,
	 * lors d'un swap, l'adresse chaine correspond à une adresse RAM. Ecrire au delà de la taille entraîne donc
	 * l'écriture dans une zone mémoire */
	String::strcpy(a_ecrire,chaine,taille);
	a_ecrire[taille++] = EOF;
	buf[i]=1;
	luoffset_t addr_data = file->addr_data;
	while(buf[i] != EOF){//Lecture du fichier jusqu'à la fin. Ajout en fin de fichier !
		for(nb_sec=0;nb_sec < data_struct.SecPerClus && buf[i] != EOF;nb_sec++) {
			ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)buf,addr_data + nb_sec,data_struct.BytsPerSec);
			for(i=0;buf[i]!=EOF && i<data_struct.BytsPerSec;i++);
		}
	}
	nb_sec--;//On va réécrire le même secteur
	libre_sec = data_struct.BytsPerSec - i;//Calcul de la place libre dans le secteur qui vient d'être lu.
	if(libre_sec > 0) {//On remplit le dernier secteur lu
		for(j=0;j < libre_sec && taille > 0;j++,i++,taille--)
			buf[i] = a_ecrire[j];
		ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)buf,addr_data + nb_sec,data_struct.BytsPerSec);
		nb_sec++;
	}
	//On remplit le cluster
	for(;nb_sec < data_struct.SecPerClus && taille > 0;nb_sec++) {
		ide_write_device(&ide_controllers[0].devices[1],(vaddr_t)a_ecrire + j,addr_data + nb_sec,data_struct.BytsPerSec);
		j += data_struct.BytsPerSec;
		taille -= data_struct.BytsPerSec;
	}
	if(taille > 0) {//Allocation d'un nouveau cluster, beaucoup de choses à écrire
		set_cluster_value((vaddr_t)a_ecrire+j,taille,find_cluster_num(addr_data));
	}
}

void fread(struct fat_directory* file,/*OUT*/char* lu,int taille) {
	char buf[data_struct.BytsPerSec];
	int ind = 0;

	buf[ind]=1;
	lu[0] = '\0';
	luoffset_t addr_data = file->addr_data;
	ui32_t num_clus = find_cluster_num(file->addr_data);
	luoffset_t add_sector = file->offset / data_struct.BytsPerSec;
	while(buf[ind] != EOF && taille > 0) {
		for(int sec=0;sec < data_struct.SecPerClus && buf[ind] != EOF && taille > 0;sec++) {//Recherche EOF dans tous les secteurs du cluster
			ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)buf,addr_data + add_sector + sec,data_struct.BytsPerSec);
			for(ind = 0;buf[ind]!=EOF && ind < data_struct.BytsPerSec;ind++);
			taille -= ind;
			String::strcat(lu,buf,String::strlen(lu) + ind+1);
		}
		num_clus = data_struct.fat_table[num_clus-2];
		addr_data = find_addr(num_clus);
	}
	int offset_char = file->offset - add_sector * data_struct.BytsPerSec;
	if((ui32_t)String::strlen(lu) > offset_char) {//Décalage plus grand que le nombre de caractères présents dans le fichier
		int i;
		for(i=0;lu[i+offset_char] != '\0';i++)
			lu[i] = lu[i + offset_char];
		lu[i] = lu[i + offset_char];
	}
	else
		lu[0] = '\0';
}

void fseek(struct fat_directory* fic,int deplacement) {
	fic->offset += deplacement;
}

void fat_setup(bool clear) {
	bool* formate = (bool*)malloc(sizeof(bool));//Indicateur de formatage du disque
	struct stock_tab* milou = (struct stock_tab*)malloc(sizeof(struct stock_tab));//Permet la récupération de la table
	int secteur = 0;

	if(clear)//Réinitialisation du système de fichier
		fat_clear();//Supprime la structure Fat en place
	ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)formate,secteur,512);
	secteur++;
	if(!*formate)//Pas de table FAT, on en crée une
		fat_mount(formate);
	else {//On recupere les infos de la FAT
		ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)&data_struct,secteur,sizeof(struct fat_data_structure));
		secteur++;
		ui32_t taille = sizeof(ui32_t)*data_struct.CountOfClusters;
		data_struct.fat_table = (ui32_t*)malloc(taille);
		secteur = 3;//En 2 ca ne marche pas ???
		for(ui32_t offset = 0;offset < taille;offset+=512,secteur++) {
			ide_read_device(&ide_controllers[0].devices[1],(vaddr_t)milou,secteur,512);
			for(int i=0;i<128 && data_struct.CountOfClusters > (offset/4 + i);i++) {
				data_struct.fat_table[offset/4 + i] = milou->tab[i];
			}
		}
	}
}
