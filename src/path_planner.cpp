
#include "path_planner.h"
#include <assert.h>


PathPlanner::PathPlanner(Map & _map)
{
	searchMap = _map;
}

//PathPlanner::PathPlanner(geometry_msgs::Point _start, geometry_msgs::Point _goal)
//{
//	start = _start;
//	goal = _goal;
//}

PathPlanner::~PathPlanner()
{

}
//PathPlanner::findPath(geometry_msg::Point start, geometry_msgs::Point goal) = 0;
//{
//	//
//}
