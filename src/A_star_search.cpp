

#include "A_star_search.h"
#include <assert.h>
#include <queue>          // std::priority_queue


AStarSearch::AStarSearch(Map & _map) : GraphSearch(_map)
{
//	GraphSearch(_map);
//	searchMap = *_map;
	Sclosed.clear();
	Poptimal.clear();
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
	Start.setId(column + row*searchMap.getColumn());

	row = floor(goal.x/searchMap.getResolution());
	column = floor(goal.y/searchMap.getResolution());
	Node Goal(row,column);
	Goal.setId(column + row*searchMap.getColumn());

	Node searchMapNode[searchMap.getRow()][searchMap.getColumn()];

	// Discretize the map in a set of node
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

	// Initialize
	Start.setCost(0.0);
	expectedCost = manDist(Start,Goal);
	Start.setExpectedCost(expectedCost);

//	Start.setPreviousNode(& NULL);		???

	// finish = Goal not in Sclosed
	Node nNext(1,1);

	Sopen.push(Start);
	// We need this list in order to keep track of the node that are already in Sopen
	SopenList.push_front(Start.getId());


	//Start A*
	while(not Sopen.empty() and not finish)
	{
		// Get the node with lowest expected coast
		nNext = costQueue.top();
		// Remove the node from the list
		costQueue.pop();
		// Add the node to the Sclosed list
		Sclosed.push_front(nNext);

		//Check if we are finish
		if ( (nNext.getRow() == Goal.getRow()) and (nNext.getColumn() == Goal.getColumn()) )
		{
			finish = true;
			while(not true)
			{
				//TODO
			}
		}
		else
		{
			for(int r = -1; r <= 1; r++)
			{
				for(int c = -1; c <= 1; c++)
				{
					// Update the neighbors' expected cost

					Node nNeighbor(nNext.getRow() + r, nNext.getColumn() + c);

					// first check if we are in the grid or outside
					if( (0 < (nNeighbor.getColumn() )) and ((nNeighbor.getColumn() ) < searchMap.getColumn()) and
						(0 < (nNeighbor.getRow() ))    and ((nNeighbor.getRow() )    < searchMap.getRow()) )
					{
						// Check if the neighbors node are free
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
//							    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> Sopen;

//								  it = find (myvector.begin(), myvector.end(), 30);
//								  if (it != myvector.end())
//								    std::cout << "Element found in myvector: " << *it << '\n';
//								  else
//								    std::cout << "Element not found in myints\n";
//
								if(std::find(SopenList.begin(), SopenList.end(), nNeighbor.getId()) != SopenList.end())
									isInOpen = true;

								if(not isInOpen)
								{
									// ?? non so bene cosa fanno loro (*)
									nNeighbor.setCost(nNext.getCost() + 1);
									nNeighbor.setExpectedCost(nNeighbor.getCost() + manDist(nNeighbor, Goal));
									nNeighbor.setPreviousNode(nNext);
									Sopen.push(nNeighbor);
									SopenList.push_front(nNeighbor.getId());
								}
								else
								{
									double gCostTmp;
									gCostTmp = nNext.getCost() + 1;
									if(gCostTmp < nNeighbor.getCost() )
									{
										nNeighbor.setCost(gCostTmp);
										nNeighbor.setExpectedCost(nNeighbor.getCost() + manDist(nNeighbor,Goal) );
										nNeighbor.setPreviousNode(nNext);
									}
								}




								//if
							}


						}

					}


				}


			}
		}
	}
}

		//(1) Check if n

		// Here choose if we want the 4 or 8 method

		// Four method
//		for (int i = 0; i < 4; i++)
//		{
//			if costQueue.top() > Node
//		}
//	}
//





int AStarSearch::manDist(Node Current, Node Goal)
{
	return abs(Current.getRow() - Goal.getRow()) + abs(Current.getColumn() - Goal.getColumn());
}



//empty()
//size()
//front()
//push_back()
//pop_back()

