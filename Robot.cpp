/*
 * Robot.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Robot.h"

namespace lodepng {

Robot::Robot(string ip , int port) {
	// TODO Auto-generated constructor stub
	pc = new PlayerClient(ip,port);
	pp = new Position2dProxy(pc);
	lp = new LaserProxy(pc);

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



Robot::~Robot() {
	// TODO Auto-generated destructor stub
}


} /* namespace lodepng */
