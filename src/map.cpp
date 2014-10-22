/*
 * map.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#include "map.h"
#include <assert.h>

Map::Map(double robotSize)
{
	assert(robotSize>=0); // Ensure that the robot size is non-negative
	m_robotSize = robotSize;		//...
}

Map::Map(nav_msgs::OccupancyGrid map, double robotSize)
{
	//...
}

Map::~Map()
{
	//...
}

//...

void Map::inflate()
{
	if( m_robotSize > 0 )
	{
		//...
	}
}

//...

void Map::setRobotSize(double robotSize)
{
	assert(robotSize >= 0); // Ensure that the robot size is non-negative
	m_robotSize = robotSize;
}

double Map::getRobotSize()
{
	return m_robotSize;
}


