/*
 * String
 *
 *  Created on: 11 nov. 2008
 *      Author: nicolas
 */

#ifndef STRING_
#define STRING_

class String{

	char* string;

public:
	String();
	String(char* s);
	String(int i);
	char* getString();
	bool isEqual(String aTester);
	String** split(char sep);
	String* strcut(int debut, int fin);
	static bool strcmp(char*,char*);
	static int strlen(char*);
	static void strcpy(char*,char*,int);
	static void strcat(char* dest,char* src,int sizeDest);
	static String* format(char *string, int size);
	static int atoi(String *str);

};


#endif /* STRING_ */
