/*
 * Position.h
 *
 *  Created on: 13 déc. 2010
 *      Author: Frédéric
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position{
public :
	int
	x,
	y;

	Position(int x,int y);
	Position(Position *position);

	bool egal(Position *pos);
};

#endif /* POSITION_H_ */
