/*
 * A_star_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_A_STAR__SEARCH_H_

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>

#include <geometry_msgs/Point.h>
#include "graph_search.h"
#include "Node.h"
//#include "map.h"


class AStarSearch : public GraphSearch
{
public: 
	AStarSearch(Map & _map, ros::Publisher _pathPublisher);
//	AStarSearch(geometry_msgs::Point _start, geometry_msgs::Point _goal);
	~AStarSearch();
	void findPath(geometry_msgs::Point start, geometry_msgs::Point goal);
	//Compute the manatthan distance between where we are and the goal

	int manDist(Node Current, Node Goal);

	nav_msgs::Path computePath();

	void publishPathRviz(std::list<int> Poptimal);

	const ros::Publisher& getPathPublisher() const;
	void setPathPublisher(const ros::Publisher& pathPublisher);
	const std::list<int>& getPoptimal() const;
	void setPoptimal(const std::list<int>& poptimal);
	const std::list<Node>& getSclosed() const;
	void setSclosed(const std::list<Node>& sclosed);
	const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& getSopen() const;
	void setSopen(
			const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& sopen);
	const std::list<int>& getSopenList() const;
	void setSopenList(const std::list<int>& sopenList);

protected:
	std::list<Node> Sclosed;
	std::list<int> Poptimal;
	std::list<int> SopenList;
	std::queue<Node> PoptimalQueue;
    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> Sopen;

private:
	ros::Publisher pathPublisher;

};

#endif /* MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_ */
