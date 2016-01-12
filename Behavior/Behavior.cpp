/*
 * Behavior.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: colman
 */

#include "Behavior.h"

Behavior::Behavior(Robot *robot) : _robot(robot){
	// TODO Auto-generated constructor stub
}

Behavior* Behavior::addNext(Behavior *beh) {
    _nextBehaviors.push_back(beh);
    return this;
}

Behavior *Behavior::selectNext() {
    for (int i = 0; i < _nextBehaviors.size(); i++)
    {
        if (_nextBehaviors[i]->startCond())
            return _nextBehaviors[i];
    }
    return NULL;
}

Behavior::~Behavior() {
	// TODO Auto-generated destructor stub
}
