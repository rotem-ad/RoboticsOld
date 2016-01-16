/*
 * Driver.h
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "Robot.h"
#include <vector>
using namespace std;

typedef pair<double,double> Position;
typedef vector<Position> Path;

class Driver {

private:
	const double linearSpeed = 0.6;
	const double linearTolerance = 0.01;

	Robot &robot;
	Position currPos;
	void getCurrentPos();
	void moveToNextPos(Position targetPos);
	void turnToNewDirection(double targetAngle);

public:
	Driver(Robot &robot);
	void moveRobot(Path &path);
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
