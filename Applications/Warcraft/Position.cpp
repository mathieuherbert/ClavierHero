/*
 * Position.cpp
 *
 *  Created on: 13 dec. 2010
 *      Author: Frederic
 */

#include "Position.h"

Position::Position(int x,int y):x(x),y(y){}

Position::Position(Position *position):x(position->x),y(position->y){}

bool Position::egal(Position *pos){
	return x==pos->x&&y==pos->y;
}
