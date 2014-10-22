/*
 * graph_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_

#include "path_planner.h"

class GraphSearch : public PathPlanner
{
public:
	//...
	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;
	//...
protected:
	//...
private:
	//...
};



#endif /* MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_ */
