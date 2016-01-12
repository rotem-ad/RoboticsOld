/*
 * Behavior.h
 *
 *  Created on: Jan 12, 2016
 *      Author: colman
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot.h"
#include "../Settings.h"
#include <vector>

using namespace std;

class Behavior {
private:
	vector<Behavior *> _nextBehaviors;

protected:
    Robot *_robot;

public:
    virtual bool startCond() = 0;
    virtual bool stopCond() = 0;
    virtual void action() = 0;

    //void addNext(Behavior* next);
    Behavior* addNext(Behavior *beh);
    Behavior* selectNext();

    Behavior(Robot *robot);
    virtual ~Behavior();
};

#endif /* BEHAVIOR_H_ */
