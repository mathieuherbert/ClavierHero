/*
 * mouse_handler.h
 *
 *  Created on: 16 nov. 2008
 *      Author: Marc Noblet
 */

#ifndef MOUSE_HANDLER_H_
#define MOUSE_HANDLER_H_

#define CLIC_G 1
#define CLIC_D 2

void mouse_handler(int irq);
inline void mouse_wait(unsigned char a_type);
inline void mouse_write(unsigned char a_write);
unsigned char mouse_read();
void mouse_install();

#endif /* MOUSE_HANDLER_H_ */
