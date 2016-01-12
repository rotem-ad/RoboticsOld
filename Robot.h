/*
 * Robot.h
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <string>
using namespace std;
using namespace PlayerCc;

class Robot {
private:
	PlayerClient *pc;
	Position2dProxy *pp;
	LaserProxy *lp;

public:
	Robot(string ip , int port);
	void setSpeed(double linearSpeed , double angularSpeed);
	double getXPos();
	double getYPos();
	double getYaw();
	void read();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
