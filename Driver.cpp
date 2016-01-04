/*
 * Driver.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Driver.h"

namespace lodepng {

Driver::Driver(Robot &robot) : robot(robot) {
	// TODO Auto-generated constructor stub

}

void Driver::moveToNextPos(Position targetPos){

	robot.setSpeed(linearSpeed,0);
	robot.read();
	double x = robot.getXPos();
	double y = robot.getYPos();

	while (abs(x- targetPos.first) > 10 * linearTolerance ||
			abs(y - targetPos.second) > 10 *linearTolerance ){

		robot.read();
		x = robot.getXPos();
		y = robot.getYPos();

	}
	robot.setSpeed(0.1 * linearSpeed,0);
}


Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

} /* namespace lodepng */
