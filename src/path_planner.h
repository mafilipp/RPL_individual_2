/*
 * path_planner.h
 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 *      Note: Class that give you the abstract instrument to perform a path search algorithm
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_
#define MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_

#include <geometry_msgs/Point.h>
#include "map.h"


class PathPlanner
{
public:
	// Constructor and destructor
	PathPlanner(Map & _map);
	~PathPlanner();

	//Abstract function to find the optimal path between two node
	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;

protected:
	// Map in which we are going to plan the path
	Map searchMap;

private:
};


#endif /* MAFILIPP_PATH_PLANNING_SRC_PATH_PLANNER_H_ */
