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
namespace lodepng {

class Driver {

private:
	const double linearSpeed = 0.8;
	const double linearTolerance = 0.01;

	Robot &robot;
	void moveToNextPos(Position targetPos);
	void turnToNewDirection(double targetAngle);

public:
	Driver(Robot &robot);
	void moveRobot(Path &path);
	virtual ~Driver();
};

} /* namespace lodepng */

#endif /* DRIVER_H_ */
