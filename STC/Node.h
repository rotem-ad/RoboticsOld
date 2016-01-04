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


public:
	bool visited;
	vector<Node *> neighborsInSpanningTree;

	Node(int row, int col);
	virtual ~Node();
	Position getPosition();
	bool isVisited();
};

#endif /* NODE_H_ */
