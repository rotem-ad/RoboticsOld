/*
 * Settings.h
 *
 *  Created on: Jan 4, 2016
 *      Author: colman
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <math.h>
#include <string>
using namespace std;

class Settings {
public:
public:

	/** Connection Settings **/
	//static const string HOST = "localhost"; //host address
	static const int PORT = 6665; //port

	/** Constants **/
	static const float ROBOT_SIZE = 0.3; //size of robot in meters
	static const float MAP_RESOLUTION = 0.025; //resolution of the map
	static const int MAP_WIDTH = 550; //map width in pixels
	static const int MAP_HEIGHT = 380; //map height in pixels

	/** Not used so far.. **/
	static const float CELL_SIZE = 0.05; //size of one cell in map
	static const float SAFE_RANGE = 0.95; //the distance from obstacle
	//static const float WALL_RANGE = 0.6;
	static const float OPEN_PATH_RANGE = 3.0;
	static const int STATE_FREE = 0;
	static const int STATE_OCCUPIED = 1;
	static const int STATE_UNKNOWN = 2;
	static const int STATE_ROBOT = 3;
	static const int INITIAL_PARTICLES = 10;
	static const float TRUST_TRESHOLD = 0.6; //if belief is grater than this value it is ok!!
	static const float NORMAL_ACCURATE_ANGLE = 0.5;
	static const float RAND_COEFFICIENT = 0.2;
	static const double MOVEMENT_SPEED = 0.05;
	static const int LASER_INDEXES = 666; //robot angle in radians = 240/0.36 = 666
	static const double LASER_MAX_DISTANCE = 4.095; //configuration of robot - taken from web site
	static const double LASER_ANGLE = 240.0; //configuration of robot - taken from web site
	static const double MINIMUM_RADIAN = 60 / .36; //minimum range to check in radians
	static const double INITIAL_BELIEF = 1.0; //initial belief value
	static const double RADIAN_FACTOR = 0.36; //factor for converting degrees to radians

	/** Static Methods **/

	//calculated test map array size height
	static int MAP_ROWS() {
		return ((int) (MAP_HEIGHT / MAP_RESOLUTION));
	};

	 //calculated test map array size height
	static int MAP_COLS() {
		return ((int) (MAP_WIDTH / MAP_RESOLUTION));
	};

	static double getAngel(int laserIndex, double yaw) {

		double angel;
		angel = M_PI * (laserIndex - 120.0 + yaw) / 180.0;
		return angel;
	}

	//find the current cell location on the map
	//assume the robot is in the middle of the map
	static int getRobotInitXPos(double xRob) {
		  return  (int)(xRob / MAP_RESOLUTION + MAP_COLS() / 2);
	}

	static int getRobotInitYPos(double yRob) {
			  return  (int)(yRob / MAP_RESOLUTION + MAP_ROWS() / 2);
	}

	Settings();
	virtual ~Settings();
};

#endif /* SETTINGS_H_ */
