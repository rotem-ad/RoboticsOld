/*
 * Map.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map.h"
#include <iostream>

Map::Map(float mapResolution, float robotSize) :
	mapResolution(mapResolution), robotSize(robotSize) {
	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = 0.3 * robotSizeInCells;
	cout<<"inflation radius "<< inflationRadius<<endl;

}

void Map::loadMapFromFile(const char* filePath) {
	lodepng::decode(image, mapWidth, mapHeight, filePath);
	fineMapWidth = mapWidth/robotSizeInCells;
	fineMapHeight = mapHeight/robotSizeInCells;
	cout << "map size: " << mapWidth << "," << mapHeight << endl;

	map.resize(mapHeight);
	for (int i = 0; i < mapHeight; i++)
		map[i].resize(mapWidth);

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}


}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printMap() const {
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			cout << (inflateMap[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::printGrid(const Grid &grid) const {
	int rows = grid.size();
	int cols = grid[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (grid[i][j] ? "*" : " ");
		}
		cout << endl;
	}

	 rows = coarseGrid.size();
		 cols = coarseGrid[0].size();

	for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << (coarseGrid[i][j] ? "*" : " ");
			}
			cout << endl;
		}


}

void Map::inflateObstacles(){

	inflateMap.resize(mapHeight);
		for (int i = 0; i < mapHeight; i++){
			inflateMap[i].resize(mapWidth);
		}


	for (int i = 0; i < mapHeight; i++) {
			for (int j = 0; j < mapWidth; j++) {
				if(map[i][j]){
					inflate(i,j);
				}
			}
		}

}

void Map::inflate(int i , int j){

	for (int k=i-inflationRadius;k<i+inflationRadius;k++){
		for(int m=j-inflationRadius;m<j+inflationRadius;m++){
			if(m < 0 || k < 0 || k >= mapHeight || m >= mapWidth ){
				continue;
			}else{
				// Mark this cell as occupied in inflateMap
				inflateMap[k][m]= true;
				// Draw black color in corresponding image
				int c = (k * mapWidth + m) * 4;
				image[c] = 0;
				image[c + 1] = 0;
				image[c + 2] = 0;

			}
		}
	}
}

vector<vector<bool> > Map::getInflateMap(){
	return inflateMap;
}

void Map::writeinflateObstacles(vector<vector<bool> > map){

	lodepng::encode("robotic2.png",image,mapWidth,mapHeight);
}

void Map::buildFineGrid(){

	int fineGridCells = mapHeight/robotSizeInCells;
	int fineGridWidth = mapWidth/robotSizeInCells;
	fineGrid.resize(fineGridCells);
	for (int i = 0; i < fineGridCells; i++){
		fineGrid[i].resize(fineGridWidth);
	}

    int flag = false;


    for(int i = 0;i<fineGridCells;i++){
    	for(int j = 0 ;j<fineGridWidth;j++){
    		flag = false;
    		for(int m=i*robotSizeInCells;m < i * robotSizeInCells +robotSizeInCells;m++ ){
    			for(int z=j *robotSizeInCells;z< j * robotSizeInCells +robotSizeInCells;z++ ){
    				if(inflateMap[m][z] == true){
    					flag = true;
    					break;
    				}
    			}
    		}
    		fineGrid[i][j]= flag;
    	}
    }

}

void Map::buildCoarseGrid(){

		int fineGridCells = mapHeight/(robotSizeInCells*2);
		coarseMapHeight = fineGridCells;
		int fineGridWidth = mapWidth/(robotSizeInCells*2);
		coarseMapWidth= fineGridWidth;
		coarseGrid.resize(fineGridCells);
		for (int i = 0; i < fineGridCells; i++){
			coarseGrid[i].resize(fineGridWidth);
		}

	    int fleg = false;


	    for(int i = 0;i<fineGridCells;i++){
	    	for(int j = 0 ;j<fineGridWidth;j++){
	    		fleg = false;
	    		for(int m=i*(robotSizeInCells*2);m < i * (robotSizeInCells*2) +(robotSizeInCells*2);m++ ){
	    			for(int z=j *(robotSizeInCells*2);z< j * (robotSizeInCells*2) +(robotSizeInCells*2);z++ ){
	    				if(inflateMap[m][z] == true){
	    					fleg = true;
	    					break;
	    				}
	    			}
	    		}
	    		coarseGrid[i][j]= fleg;
	    	}
	    }

}

void Map::addPathToFile(char* filePath , vector<vector<Node *> > graph,int Width,int Hight) {
	gridGraph.resize(fineMapHeight);
		for(int k=0;k<fineMapHeight;k++){
			gridGraph[k].resize(fineMapWidth);
		}
		this->originalGraph = graph;

		for(int z = 0;z<Hight;z++){
			for(int l= 0;l<Width;l++){
				if (graph[z][l] != NULL) {
					for (int k=0;k<4;k++) {
						if (graph[z][l]->neighborsInSpanningTree[k] != NULL) {
						   	int i = graph[z][l]->getPosition().first;
							int j = graph[z][l]->getPosition().second;
							//convert the row to the original map row that was read from the image
							i  = ((i+0.5) * robotSizeInCells * 2);
							//convert the row to the original map column that was read from the image
							j = ((j+0.5) * robotSizeInCells * 2);

							int i1 = graph[z][l]->neighborsInSpanningTree[k]->getPosition().first ;
							int j1 = graph[z][l]->neighborsInSpanningTree[k]->getPosition().second;
							////convert the row to the original map row that was read from the image
							i1 = ((i1+0.5) * robotSizeInCells * 2);
							////convert the row to the original map column that was read from the image
							j1 = ((j1+0.5) * robotSizeInCells * 2);
							//check how we need to move on row or column
							//UP
							if(j<j1 && i == i1){
								for (int m = j; m < j1; m++) {
									calcGridGraphindex(i,m);
									gridGraph[a][b] = new Node(a,b);
									gridGraph[a][b]->setIfExistWall(true);
									gridGraph[a+1][b] = new Node(a+1,b);
									gridGraph[a+1][b]->setIfExistWall(true);
									cout<<endl;
									int c = (i * mapWidth + m) * 4;
								    image[c] = 255;
									image[c + 1] = 0;
									image[c + 2] = 0;
									cout<<a<<","<<b<<endl;

								}
//								gridGraph[a+1][b+1] = new Node(a+1,b+1);
//								gridGraph[a+1][b+1]->setIfExistWall(true);
//								gridGraph[a+2][b+1] = new Node(a+2,b+1);
//								gridGraph[a+2][b+1]->setIfExistWall(true);



							//check how we need to move on row or column
							//DOWN
							}else if(j>j1 && i == i1){
								for (int m =j1 ; m < j; m++) {
									calcGridGraphindex(i,m);
									gridGraph[a][b+1] = new Node(a,b+1);
									gridGraph[a][b+1]->setIfExistWall(true);
									gridGraph[a+1][b+1] = new Node(a+1,b+1);
									gridGraph[a+1][b+1]->setIfExistWall(true);
									int c = (i * mapWidth + m) * 4;
									image[c] = 255;
									image[c + 1] = 0;
									image[c + 2] = 0;
									}

//								gridGraph[a+1][b+2] = new Node(a+1,b+2);
//								gridGraph[a+1][b+2]->setIfExistWall(true);
//								gridGraph[a+2][b+2] = new Node(a+2,b+2);
//								gridGraph[a+2][b+2]->setIfExistWall(true);
							//check how we need to move on row or column
							//LEFT
							}else if(j == j1 && i > i1){
								for (int m =i1 ; m < i; m++) {
									calcGridGraphindex(m,j);
									gridGraph[a+1][b] = new Node(a+1,b);
									gridGraph[a+1][b]->setIfExistWall(true);
									gridGraph[a+1][b+1] = new Node(a+1,b+1);
									gridGraph[a+1][b+1]->setIfExistWall(true);
									int c = (m * mapWidth + j) * 4;
									image[c] = 255;
									image[c + 1] = 0;
									image[c + 2] = 0;
									}
//								gridGraph[a+2][b+1] = new Node(a+2,b+1);
//								gridGraph[a+2][b+1]->setIfExistWall(true);
//								gridGraph[a+2][b+2] = new Node(a+2,b+2);
//								gridGraph[a+2][b+2]->setIfExistWall(true);

							//check how we need to move on row or column
							//RIGHT
							}else if(j == j1 && i < i1){
								for (int m =i ; m < i1; m++) {
									calcGridGraphindex(m,j);
									gridGraph[a][b] = new Node(a,b);
									gridGraph[a][b]->setIfExistWall(true);
									gridGraph[a][b+1] = new Node(a,b+1);
									gridGraph[a][b+1]->setIfExistWall(true);
									int c = (m * mapWidth + j) * 4;
									image[c] = 255;
									image[c + 1] = 0;
									image[c + 2] = 0;
									}
//								gridGraph[a+1][b+1] = new Node(a+1,b+1);
//								gridGraph[a+1][b+1]->setIfExistWall(true);
//								gridGraph[a+1][b+2] = new Node(a+1,b+2);
//								gridGraph[a+1][b+2]->setIfExistWall(true);
							}
							cout << "(" << graph[z][l]->getPosition().first << "," << graph[z][l]->getPosition().second << ")";
							cout << " -> ";
							cout << "(" << graph[z][l]->neighborsInSpanningTree[k]->getPosition().first << "," << graph[z][l]->neighborsInSpanningTree[k]->getPosition().second << ")" << endl;
						}
					}

				}

			}
		}
		cout<<"save to image done"<<endl;
		lodepng::encode(filePath, image, mapWidth, mapHeight);
}

void Map::calcGridGraphindex(int i,int j){

	this->a = (((i-robotSizeInCells)/robotSizeInCells));
	this->b=(((j-robotSizeInCells)/robotSizeInCells));

}

void Map::addPathToFile1(char* filePath , vector<vector<Node *> > graph,int Width,int Hight) {
		for(int z = 0;z<fineMapHeight;z++){
			for(int l= 0;l<fineMapWidth;l++){
				if (graph[z][l] != NULL) {
					int i = graph[z][l]->getPosition().first;
					int j = graph[z][l]->getPosition().second;
					i  = ((i + 0.5) * robotSizeInCells);
					//convert the row to the original map column that was read from the image
					j = ((j+ 0.5) * robotSizeInCells);


					int c = (i * (mapWidth) + j) * 4;
					image[c] = 0;
					image[c + 1] = 0;
					image[c + 2] = 255;

					cout<<i<<","<<j<<endl;



				}

			}
		}
		lodepng::encode(filePath, image, mapWidth, mapHeight);
}

const Grid& Map::getFineGrid() const {
	return this->fineGrid;
}

const Grid& Map::getCoarseGrid() const{
	return this->coarseGrid;
	}


Map::~Map() {
	// TODO Auto-generated destructor stub
}

