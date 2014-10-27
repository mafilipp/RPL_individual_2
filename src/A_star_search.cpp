/*
 * A_star_search.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 *      Note: implementation of A_star_search.h
 */

#include "A_star_search.h"
#include <assert.h>
#include <queue>

// Constructor and destructor
AStarSearch::AStarSearch(Map & _map, ros::Publisher _pathPublisher) : GraphSearch(_map)
{
	Sclosed.clear();
	Poptimal.clear();
    pathPublisher = _pathPublisher;
    MethodPoint = 4;
}

 AStarSearch::~AStarSearch()
{

}

// This function afford, given two point, to find the optimal way between them on a map grid (using A*)
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

	// Node used to get at the end the optimal path
	Node Ncurrent(row,column);
	Ncurrent = Goal;

	// Map formed from node, where every node corresponds to a cell in the map grid
	Node searchMapNode[searchMap.getRow()][searchMap.getColumn()];

	// Fill the node with the information coming from the map
	for(int r = 0; r < searchMap.getRow(); r++)
	{
		for(int c = 0; c < searchMap.getColumn(); c++)
		{
			searchMapNode[r][c].setColumn(c);
			searchMapNode[r][c].setRow(r);
			searchMapNode[r][c].setId(c + r*searchMap.getColumn());
			if(searchMap.getMap().data[searchMap.getIndex(r,c)] > 0)
				searchMapNode[r][c].setOccupied(true);
		}
	}

	// Start algorithm

	// Define variable
	double expectedCost, cost;
	bool finish = false;
	int method = 4;

	// Initialize Start
	Start.setCost(0.0);
	expectedCost = manDist(Start,Goal);
	Start.setExpectedCost(expectedCost);
	Start.setPreviousNode(NULL);

	Node nNext(1,1);

	Sopen.push(Start);

	// We need this list in order to keep track of the node that are already in Sopen
	SopenList.push_front(Start.getId());


	//Start A*
	while(not Sopen.empty() and not finish)
	{
		// Get the node with lowest expected cost
		nNext = Sopen.top();

		// Remove the node from the list
		Sopen.pop();

		// Add the node to the Sclosed list
		Sclosed.push_front(nNext);

		//Check if we are finish
		if ( (nNext.getRow() == Goal.getRow()) and (nNext.getColumn() == Goal.getColumn()) )
		{
			// Create the queue with all the optimal path
			finish = true;
			Ncurrent = nNext;
			while(Ncurrent.getPreviousNode() != NULL)
			{
				PoptimalQueue.push(Ncurrent);
				Ncurrent = *(Ncurrent.getPreviousNode());
			}
			if(!PoptimalQueue.empty())
				PoptimalQueue.push(Ncurrent);
		}
		else
		{
			for(int r = -1; r <= 1; r++)
			{
				for(int c = -1; c <= 1; c++)
				{
					if (MethodPoint == 4)
					{
						// Consider just 4 point

						if( (r == -1 and (c ==-1 or c==1 )) or (r == 1 and (c ==-1 or c==1 )) )
						{

						}
						else
						{
							Node nNeighbor(nNext.getRow() + r, nNext.getColumn() + c);

							// first check if we are in the grid or outside
							if( (0 <= (nNeighbor.getColumn() )) and ((nNeighbor.getColumn() ) < searchMap.getColumn()) and (0 <= (nNeighbor.getRow() ))    and ((nNeighbor.getRow() )    < searchMap.getRow()) )
							{
								// Check if the neighbors node are free or occupied
								nNeighbor = searchMapNode[nNext.getRow() + r][nNext.getColumn() + c];

								if(not nNeighbor.isOccupied())
								{
									bool isInSclosed = false;

									//Check if the node is in Sclose
									if(not Sclosed.empty())
									{
										for (std::list<Node>::iterator it = Sclosed.begin(); it != Sclosed.end(); it++)
										{
											if(*it == nNeighbor)
											{
												isInSclosed = true;
											}
										}
									}

									if(not isInSclosed)
									{
										// Check if nNeighbor is in Sopen
										bool isInOpen = false;

										if(std::find(SopenList.begin(), SopenList.end(), nNeighbor.getId()) != SopenList.end()) //fulfilled if nNeighbor is in the list
											isInOpen = true;


										if(not isInOpen)
										{
											// Update
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(nNext.getCost() + 1);
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost() + manDist(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c], Goal));
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& searchMapNode[nNext.getRow()][nNext.getColumn()]);

											Sopen.push(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c]);
											SopenList.push_front(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getId());
										}
										else
										{
											double gCostTmp;
											gCostTmp = nNext.getCost() + 1;
											if(gCostTmp < nNeighbor.getCost() )
											{
												searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(gCostTmp);
												searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(nNeighbor.getCost() + manDist(nNeighbor,Goal) );
												searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& nNext);
											}
										}

									}
								}
							}
						}
					}

					if (MethodPoint == 8)
					{

						Node nNeighbor(nNext.getRow() + r, nNext.getColumn() + c);

						// first check if we are in the grid or outside
						if( (0 <= (nNeighbor.getColumn() )) and ((nNeighbor.getColumn() ) < searchMap.getColumn()) and (0 <= (nNeighbor.getRow() ))    and ((nNeighbor.getRow() )    < searchMap.getRow()) )
						{
							// Check if the neighbors node are free or occupied
							nNeighbor = searchMapNode[nNext.getRow() + r][nNext.getColumn() + c];

							if(not nNeighbor.isOccupied())
							{
								bool isInSclosed = false;

								//Check if the node is in Sclose
								if(not Sclosed.empty())
								{
									for (std::list<Node>::iterator it = Sclosed.begin(); it != Sclosed.end(); it++)
									{
										if(*it == nNeighbor)
										{
											isInSclosed = true;
										}
									}
								}

								if(not isInSclosed)
								{
									// Check if nNeighbor is in Sopen
									bool isInOpen = false;

									if(std::find(SopenList.begin(), SopenList.end(), nNeighbor.getId()) != SopenList.end()) //fulfilled if nNeighbor is in the list
										isInOpen = true;


									if(not isInOpen)
									{
										// Update
										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(nNext.getCost() + 1);
										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost() + euclideanDistance(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c], Goal));
										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& searchMapNode[nNext.getRow()][nNext.getColumn()]);

										Sopen.push(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c]);
										SopenList.push_front(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getId());
									}
									else
									{
										double gCostTmp;
										gCostTmp = nNext.getCost() + 1;
										if(gCostTmp < nNeighbor.getCost() )
										{
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(gCostTmp);
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(nNeighbor.getCost() + euclideanDistance(nNeighbor,Goal) );
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& nNext);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// Check if the goal is unreachable
	if(Sopen.empty() and not finish)
		ROS_INFO("GOAL UNREACHABLE!!");
}


int AStarSearch::manDist(Node Current, Node Goal)
{
	return abs(Current.getRow() - Goal.getRow()) + abs(Current.getColumn() - Goal.getColumn());
}

double AStarSearch::euclideanDistance(Node Current, Node Goal)
{
	return sqrt(pow(Current.getRow() - Goal.getRow(),2) + pow(Current.getColumn() - Goal.getColumn(),2));
}

// Compute a path between start and goal
nav_msgs::Path AStarSearch::computePath()
{
  ROS_INFO("ComputePath");

  nav_msgs::Path path;

  // Set the header and initialize the poses array
  path.header.stamp = ros::Time::now();
  path.header.frame_id = "map";
  path.poses = std::vector<geometry_msgs::PoseStamped>(PoptimalQueue.size());

  int i = 0; // To set the message to the right place

  while(not PoptimalQueue.empty())
  {
	  geometry_msgs::Point point;
	  Node Nused(1,1);
	  int row, column;

	  Nused = PoptimalQueue.front(); //Extract the node from the queue
	  PoptimalQueue.pop();

	  row = Nused.getRow() ;
	  column = Nused.getColumn();
	  point.x = column*searchMap.getResolution();// + searchMap.getResolution()/2; //Uncomment to see better the trajectory in rviz
	  point.y =  row*searchMap.getResolution();// + searchMap.getResolution()/2;

	  path.poses[i].header.stamp = path.header.stamp;
	  path.poses[i].header.frame_id = path.header.frame_id;
	  path.poses[i].pose.position = point;

	  i++;
  }
  return path;
}



// Getters and Setters
const ros::Publisher& AStarSearch::getPathPublisher() const {
	return pathPublisher;
}

void AStarSearch::setPathPublisher(const ros::Publisher& pathPublisher) {
	this->pathPublisher = pathPublisher;
}

const std::list<int>& AStarSearch::getPoptimal() const {
	return Poptimal;
}

void AStarSearch::setPoptimal(const std::list<int>& poptimal) {
	Poptimal = poptimal;
}

const std::list<Node>& AStarSearch::getSclosed() const {
	return Sclosed;
}

void AStarSearch::setSclosed(const std::list<Node>& sclosed) {
	Sclosed = sclosed;
}

const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& AStarSearch::getSopen() const {
	return Sopen;
}

void AStarSearch::setSopen(
		const std::priority_queue<Node, std::vector<Node>, CompareNodeCost>& sopen) {
	Sopen = sopen;
}

const std::list<int>& AStarSearch::getSopenList() const {
	return SopenList;
}

void AStarSearch::setSopenList(const std::list<int>& sopenList) {
	SopenList = sopenList;
}

int AStarSearch::getMethodPoint() const {
	return MethodPoint;
}

void AStarSearch::setMethodPoint(int methodPoint) {
	MethodPoint = methodPoint;
}
