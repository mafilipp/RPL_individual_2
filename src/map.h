/*
 * map.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_MAP_H_
#define MAFILIPP_PATH_PLANNING_SRC_MAP_H_

#include <nav_msgs/OccupancyGrid.h>

class Map {
public:
	// Constructors and destructor
	Map(double robotSize = 0);
	Map(nav_msgs::OccupancyGrid map, double robotSize = 0);
	//...
	~Map();

	// inflate the current Map
	void inflate(); // Inflate the map by the robot's radius
	//...

	// Setters and getters
	void setRobotSize(double robotSize);
	double getRobotSize();
	//...

private:
	double m_robotSize;
	nav_msgs::OccupancyGrid m_map;
	int height, width;
	geometry_msgs::Pose initial_pose;
	float resolution;
	float radius_in_px;

	//...
};


#endif /* MAFILIPP_PATH_PLANNING_SRC_MAP_H_ */
