/*
 * String.cpp
 *
 *  Created on: 11 nov. 2008
 *      Author: nicolas
 */

#include "String.h"
//#include Shell.h"
#include <sextant/memoire/Memoire.h>
#include <sextant/memoire/op_memoire.h>

extern Memoire *InterfaceMemoire;

String::String() {
}

String::String(char* s) {
	size_t size = 0;

	for (int i = 0; s[i] != '\0'; i++) {
		size++;
	}
	size++;
	string = (char*) InterfaceMemoire->malloc(size);
	memcpy(string, s, size);
}

String::String(int i){
	int numb_chars=0;
	char buffer[256];
	char inv_buffer[256];
	int j=0;

	int i_modulo=0;

	if(i < 0) {
		inv_buffer[j]='-';
		j++;
	}

	if (i==0) {
		buffer[numb_chars]=48;
		numb_chars++;
	}

	while(i != 0)
	   {
	       i_modulo = i % 10;
	       i = i / 10;
	       i_modulo += 48;     /* Conversion int -> ASCII */
	       buffer[numb_chars]=i_modulo;
	       numb_chars++;
	   }

	for (int k=0;k<numb_chars;k++) {
		inv_buffer[j]=buffer[numb_chars-(k+1)];
		j++;
	}

	inv_buffer[j]='\0';
	j++;
	string = (char*) InterfaceMemoire->malloc(j);
	memcpy(string, inv_buffer, j);
}

char* String::getString() {
	return string;
}

extern EcranV* ecranV;

bool String::isEqual(String aTester) {
	int i = 0;
	for(int e=0;e<6;e++)
		ecranV[e].miniprintf(
				"comparaison entre %s et %s donne %i comme dernier indice",
				this->string,
				aTester.string, i);
	while (aTester.string[i] != '\0'
			&& string[i] != '\0'
					&& aTester.string[i]== string[i])
		i++;


	return aTester.string[i] == string[i];
}

int String::strlen(char* ch) {
	int i;
	for (i = 0; ch[i] != '\0'; i++)
		;
	return i;
}

void String::strcpy(char* dest, char* src, int sizeDest) {
	int i;
	for (i = 0; i < sizeDest - 1 && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}

void String::strcat(char* dest, char* src, int sizeDest) {

	int i;
	for (i = 0; i < sizeDest - 1 && dest[i] != '\0'; i++)
		;
	for (int j = 0; i < sizeDest - 1 && src[j] != '\0'; i++, j++) {
		dest[i] = src[j];
	}
	dest[i] = '\0';
}

bool String::strcmp(char* ch1, char* ch2) {

	int lg1 = strlen(ch1);
	int lg2 = strlen(ch2);

	if (lg1 != lg2)
		return false;
	else {
		int i;
		for (i = 0; i < lg1 && ch1[i] == ch2[i]; i++)
			;
		if (i == lg1)
			return true;
		else
			return false;
	}
}

String* tab[32];

//Renvoie un tableau de mots initialement separes par le caractere sep dans la String de depart.
String** String::split(char sep) {
	int i = 0;
	int debutMot = 0;
	int index = 0;

	do{
		while(string[i]!=sep&&string[i]!='\0'){
			i++;
		}
		tab[index]=strcut(debutMot,i-1);

		i++;
		debutMot=i;
		index++;
	}while(string[i-1]!='\0');

	for (int j=index;j<32;j++) tab[j]=new String("");

	return tab;
}

String* String::strcut(int debut, int fin) {
	char buffer[256];
	int i = 0;
	for(i = 0; i <= fin-debut; i++) {
		buffer[i]=string[debut+i];
	}
	buffer[i]='\0';
	String* s = new String(buffer);
	return s;
}

String* String::format(char *string, int size) {
	char buffer[256];
	int stringsize = String::strlen(string);
	int i = 0;

	for(i = 0; ((i < size) && (i < stringsize)); i++) {
		buffer[i]=string[i];
	}
	if (size>stringsize)
		for (;i<size;i++)
			buffer[i]=' ';

	buffer[i]='\0';
	String* s = new String(buffer);
	return s;
}


int String::atoi(String *str) {
	char* s=str->getString();

	int num=0,flag=0;

	for(int i=0;i<=strlen(s);i++)
	{
		if(s[i] >= '0' && s[i] <= '9')
              num = num * 10 + s[i] -'0';

		else if(s[0] == '-' && i==0)
			flag =1;
		else
			break;
	}
	if(flag == 1)
		num = num * -1;
	//printf("%d",num);
	return num;
}













