/*
 * graph_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 *      Note: Abstracted Class that afford the use of graph algorithm
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_

#include <queue>
#include "path_planner.h"
#include "Node.h"


class GraphSearch : public PathPlanner
{
public:

	// Constructor and destructor
	GraphSearch(Map & _map);
	virtual ~GraphSearch();

	//Abstract function to find the optimal path between two node
	virtual void findPath(geometry_msgs::Point start, geometry_msgs::Point goal) = 0;

protected:
	// Priority queue that will always put on the top the node with the smallest expected cost
	  std::priority_queue<Node, std::vector<Node>, CompareNodeCost> costQueue;

private:
};



#endif /* MAFILIPP_PATH_PLANNING_SRC_GRAPH_SEARCH_H_ */
