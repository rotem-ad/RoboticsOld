/*
 * Node.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

typedef pair<int, int> Position;

class Node {
private:
	int row, col;
	bool ifExistWall;


public:
	bool visited;
	vector<Node *> neighborsInSpanningTree;

	Node(int row, int col);
	virtual ~Node();
	Position getPosition();
	bool isVisited();
	/**
	 * check if we have a wall
	 */
	bool isIfExistWall() const ;
	void setIfExistWall(bool ifExistWall);
};

#endif /* NODE_H_ */
