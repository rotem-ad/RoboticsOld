/*
 * Main.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map/Map.h"
#include "STC/STC.h"
#include "Settings.h"
#include <iostream>

int main() {
	// Map Init
	Map map(Settings::MAP_RESOLUTION, Settings::ROBOT_SIZE);

	// Load map from image file
	const char *filePath = "roboticLabMap.png";
	map.loadMapFromFile(filePath);

	// Map inflation
	map.inflateObstacles();
	//map.printMap();
	//map.printMap();

	map.buildFineGrid();
	map.buildCoarseGrid();
	//map.printGrid(map.getFineGrid());
	Position startPos;
	startPos.first = 6;
	startPos.second = 17;
	STC stc(map, startPos);
	stc.printPath();
	map.convertPathToGridGraph(stc.getPath());
	map.addPathToFile("roboticLabMapnew1.png",stc.getPath());
	map.drawPointsInfile("roboticLabMapnew2.png",map.getGridGraph());
	return 0;
}


