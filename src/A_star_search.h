/*
 * A_star_search.h
 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 *      Note: Class that afford the use of A* for find the optimal path between two or more node
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_
#define MAFILIPP_PATH_PLANNING_SRC_A_STAR__SEARCH_H_

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Point.h>
#include "graph_search.h"
#include "Node.h"


class AStarSearch : public GraphSearch
{
public: 
	// Constructor and destructor
	AStarSearch(Map & _map, ros::Publisher _pathPublisher);
	~AStarSearch();

	// Function to find the optimal path between two node
	void findPath(geometry_msgs::Point start, geometry_msgs::Point goal);

	//Compute the manhattan distance between where we are and the goal (or more in general two point)
	int manDist(Node Current, Node Goal);

	//Compute the euclidean distance between where we are and the goal (or more in general two point)
	double euclideanDistance(Node Current, Node Goal);

	// Compute the optimal path found with the findPath function and put all the path in the nav_msgs Path
	nav_msgs::Path computePath();

	// Getters and Setters
	const ros::Publisher& getPathPublisher() const;
	void setPathPublisher(const ros::Publisher& pathPublisher);
	const std::list<int>& getPoptimal() const;
	void setPoptimal(const std::list<int>& poptimal);
	const std::list<Node>& getSclosed() const;
	void setSclosed(const std::list<Node>& sclosed);
	const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& getSopen() const;
	void setSopen( const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& sopen);
	const std::list<int>& getSopenList() const;
	void setSopenList(const std::list<int>& sopenList);
	int getMethodPoint() const;
	void setMethodPoint(int methodPoint);

protected:
	// Attribute
	std::list<Node> Sclosed; // List of the node that are in Sclosed
	std::list<int> Poptimal;
	std::list<int> SopenList; // List of the node (thanks to their ID) that are in the open List
	std::queue<Node> PoptimalQueue; // Queue that contain the optimal path
    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> Sopen; // Priority queue
    int MethodPoint; // 8 or 4, the method point that we want to use


private:
	ros::Publisher pathPublisher;

};

#endif /* MAFILIPP_PATH_PLANNING_SRC_A_STAR_SEARCH_H_ */
