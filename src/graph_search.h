/*
 * graph_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_

#include <queue>
#include "path_planner.h"
#include "Node.h"
//#include "map.h"



class GraphSearch : public PathPlanner
{
public:

	GraphSearch(Map & _map);
	//GraphSearch(geometry_msgs::Point start, geometry_msgs::Point goal);
	virtual ~GraphSearch();

	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;
	//...
protected:
	  std::priority_queue<Node, std::vector<Node>, CompareNodeCost> costQueue;

private:

//	  int * asd;
};



#endif /* MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_ */
