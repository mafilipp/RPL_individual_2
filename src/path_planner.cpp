/*
 * path_planner.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 */

#include "path_planner.h"
#include <assert.h>


// Constructor and destructor
PathPlanner::PathPlanner(Map & _map)
{
	searchMap = _map;
}

PathPlanner::~PathPlanner()
{

}

