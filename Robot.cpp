/*
 * Robot.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip , int port) {
	pc = new PlayerClient(ip,port);
	pp = new Position2dProxy(pc);
	lp = new LaserProxy(pc);

	// Set robot's odometry
	//pp->SetOdometry(2.175, -2.875, M_PI / 4);
}

void Robot:: setSpeed(double linearSpeed , double angularSpeed){
	pp->SetSpeed(linearSpeed,angularSpeed);
}

double Robot::getXPos(){
	return pp->GetXPos();
}
double Robot::getYPos(){
	return pp->GetYPos();
}
double Robot::getYaw(){
	return pp->GetYaw();
}
void Robot::read(){
	pc->Read();
}

// Robot's destructor
Robot::~Robot() {
	delete pp;
	delete lp;
	delete pc;
}
