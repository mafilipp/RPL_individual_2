/*
 * path_planner.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_
#define MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_

#include <geometry_msgs/Point.h>

class PathPlanner
{
public:
	//...
	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;
	//...
protected:
	//...
private:
	geometry_msgs::Point start, goal;
};


#endif /* MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_ */
