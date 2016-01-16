/*
 * Driver.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Driver.h"

Driver::Driver(Robot &robot) : robot(robot) {
	// TODO Auto-generated constructor stub

}

void Driver::getCurrentPos() {
	robot.read();
	currPos.first = robot.getXPos();
	currPos.second = robot.getYPos();

	cout << "curr pos: " << currPos.first << "," << currPos.second << endl;
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

/*
void Driver::moveForward(Position targetPos) {
	getCurrentPos();

	robot.setSpeed(linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > 10 * linearTolerance ||
			abs(currPos.second - targetPos.second) > 10 * linearTolerance) {
		getCurrentPos();
	}

	// slow down before reaching the target
	robot.setSpeed(0.1 * linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > linearTolerance ||
		abs(currPos.second - targetPos.second) > linearTolerance) {		getCurrentPos();
	}
}

*/

void Driver::moveRobot(Path &path) {
	Position targetPos(2.475, -2.575);
	moveToNextPos(targetPos);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

