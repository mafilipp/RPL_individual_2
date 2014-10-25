/*
 * path_planner.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_
#define MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_

#include <geometry_msgs/Point.h>
#include "map.h"


class PathPlanner
{
public:
	PathPlanner(Map & _map);
//	PathPlanner(geometry_msgs::Point _start, geometry_msgs::Point _goal);
	~PathPlanner();
	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;
	//...
protected:
//	geometry_msgs::Point start, goal;
	Map searchMap;

private:
};


#endif /* MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_ */
