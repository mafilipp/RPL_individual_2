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
#include "Node.h"
//#include "map.h"


class AStarSearch : public GraphSearch
{
public: 
	AStarSearch(Map & _map);
//	AStarSearch(geometry_msgs::Point _start, geometry_msgs::Point _goal);
	~AStarSearch();
	void findPath(geometry_msgs::Point start, geometry_msgs::Point goal);
	//Compute the manatthan distance between where we are and the goal
	int manDist(Node Current, Node Goal);


protected:
	std::list<Node> Sclosed;
	std::list<Node> Poptimal;
	std::list<int> SopenList;
    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> Sopen;

private:
	//...
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_ */
