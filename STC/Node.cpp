/*
 * Node.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#include "Node.h"

Node::Node(int row, int col) : row(row), col(col), visited(false) {
	neighborsInSpanningTree.resize(4);
}

Position Node::getPosition() {
	Position position;
	ifExistWall = false;
	position.first = row;
	position.second = col;
	return position;
}

bool Node::isIfExistWall() const {
		return ifExistWall;
	}

void Node::setIfExistWall(bool ifExistWall) {
		this->ifExistWall = ifExistWall;
	}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

