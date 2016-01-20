/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "../STC/Node.h"
#include "lodepng.h"
#include <vector>
using namespace std;
typedef vector<vector<bool> > Grid;
class Map {
private:
	vector<unsigned char> image;
	vector<unsigned char> Gridimage;
	vector<vector<Node *> > gridGraph;
	vector<vector<Node *> > originalGraph;
	Grid map;
	Grid inflateMap;
	//original Map size
	unsigned int mapWidth;
	unsigned int mapHeight;
	//grid Map size
	unsigned int fineMapWidth;
	unsigned int fineMapHeight;
	//coarse Map size
	unsigned int coarseMapWidth;
	unsigned int coarseMapHeight;
	//Converter from coarse to grid
	int a,b;
	float mapResolution;
	float robotSize;
	//size of the robot in pixels
	int robotSizeInCells;
	//the inflation of the map
	int inflationRadius;
	Grid fineGrid; // each cell in the size of the robot
	Grid coarseGrid; // each cell in the size 2x2 of the fine grid cell

	bool checkIfCellIsOccupied(int i, int j);
	void inflate(int i , int j);

public:
	/**
	 * constructor
	 */
	Map(float mapResolution, float robotSize);
	/**
	 * load map from file
	 */
	void loadMapFromFile(const char* filePath);
	void drawPointsInfile(char* filePath , vector<vector<Node *> > graph);
	void addPathToFile(char* filePath ,vector<Node *> path);
	void convertPathToGridGraph(vector<Node *> path);
	void inflateObstacles();
	void printMap() const;
	void printGrid(const Grid &grid) const;
	vector<vector<bool> > getInflateMap();
	void writeinflateObstacles(vector<vector<bool> > map);
	void buildFineGrid();
	void buildCoarseGrid();
	void buildPath(vector<vector<Node *> > graph,int Width,int Hight);
	void calcGridGraphindex(int i,int j);
	virtual ~Map();

	const Grid& getFineGrid() const;
	const Grid& getCoarseGrid()const;

	const vector<vector<Node*> >& getGridGraph() const {
		return gridGraph;
	}

	void setGridGraph(const vector<vector<Node*> >& gridGraph) {
		this->gridGraph = gridGraph;
	}
};

#endif /* MAP_H_ */
