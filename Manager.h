/*
 * Manager.h
 *
 *  Created on: Jan 12, 2016
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_


#include "Robot.h"
#include "Behavior/Behavior.h"

class Manager {
private:
    Robot *_robot;
    Behavior *_currBehavior;
public:
    Manager(Robot *robot, Behavior *startBehavior);
    void run();
    virtual ~Manager();
};

#endif /* MANAGER_H_ */

