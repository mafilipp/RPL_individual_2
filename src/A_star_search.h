/*
 * A_star_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_A_STAR__SEARCH_H_

#include <geometry_msgs/Point.h>
#include "graph_search.h"

class AStarSearch : public GraphSearch
{
public: 
	//...
	void findPath(geometry_msgs::Point start, geometry_msgs::Point goal);
	//...
protected:
	//...
private:
	//...
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_ */
