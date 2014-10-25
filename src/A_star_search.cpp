

#include "A_star_search.h"
#include <assert.h>
#include <queue>          // std::priority_queue


AStarSearch::AStarSearch(Map & _map) : GraphSearch(_map)
{
//	GraphSearch(_map);
//	searchMap = *_map;
}
//AStarSearch::AStarSearch(geometry_msgs::Point _start, geometry_msgs::Point _goal)
//{
//	GraphSearch(_start, _goal);
//}
AStarSearch::~AStarSearch()
{

}

void AStarSearch::findPath(geometry_msgs::Point start, geometry_msgs::Point goal)
{

	// First determine the location that correspond to start and end
	int row, column;

	row = floor(start.x/searchMap.getResolution());
	column = floor(start.y/searchMap.getResolution());
	Node Start(row,column);

	row = floor(goal.x/searchMap.getResolution());
	column = floor(goal.y/searchMap.getResolution());
	Node Goal(row,column);

	// Start algorithm
	double expectedCost, cost;
	Start.setCost(0.0);
	expectedCost = manDist(Start,Goal);
	Start.setExpectedCost(expectedCost);


	costQueue.push(Start);

	//Start A*
	while(not costQueue.empty() and 1)
	{

	}



}

int AStarSearch::manDist(Node Current, Node Goal)
{
	return abs(Current.getRow() - Goal.getRow()) + abs(Current.getColumn() - Goal.getColumn());
}



//empty()
//size()
//front()
//push_back()
//pop_back()

