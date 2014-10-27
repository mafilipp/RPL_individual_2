

#include "A_star_search.h"
#include <assert.h>
#include <queue>          // std::priority_queue


AStarSearch::AStarSearch(Map & _map, ros::Publisher _pathPublisher) : GraphSearch(_map)
{
	Sclosed.clear();
	Poptimal.clear();
    pathPublisher = _pathPublisher;
}

 AStarSearch::~AStarSearch() // virtual e anche nella base classe, quelli delle classi sopra vengono chiamati direttamente
{

}

void AStarSearch::findPath(geometry_msgs::Point start, geometry_msgs::Point goal)
{

	// First determine the location that correspond to start and end
	int row, column;

	row = floor(start.x/searchMap.getResolution());
	column = floor(start.y/searchMap.getResolution());
	Node Start(row,column);
//	Node Start(3,0);
//	Start.setId(column + row*searchMap.getColumn());

	row = floor(goal.x/searchMap.getResolution());
	column = floor(goal.y/searchMap.getResolution());
	Node Goal(row,column);
//	Node Goal(3,3);
//	Goal.setId(column + row*searchMap.getColumn());

	Node Ncurrent(row,column); // ALLOCATA NELLA memoria stack (statica): RAM -> le cose che definiamo statiche-- faster
	//heap: tutta la ram a disposizione -> tanto spazio col new usiamo questa
	// se non c'e abbatanza ram si usa la virtual memory (HD)
	// pointer molto veloce perche punta solo alladres
	// heap è il valore
	Ncurrent = Goal;


	Node searchMapNode[searchMap.getRow()][searchMap.getColumn()];

	// Discretize the map in a set of node
	for(int r = 0; r < searchMap.getRow(); r++)
	{
		for(int c = 0; c < searchMap.getColumn(); c++)
		{
//			ROS_INFO("occupied %d",searchMap.getMap().data[searchMap.getIndex(r,c)]);
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


	Start.setPreviousNode(NULL);

	// finish = Goal not in Sclosed
	Node nNext(1,1);

	Sopen.push(Start);
	// We need this list in order to keep track of the node that are already in Sopen
	SopenList.push_front(Start.getId());


	//Start A*
	while(not Sopen.empty() and not finish)
		//if(std::find(SopenList.begin(), SopenList.end(), nNeighbor.getId()) != SopenList.end())
//		isInOpen = true;
	{
		// Get the node with lowest expected coast
		nNext = Sopen.top();

//		std::cout << "\nnNext: " << nNext.getRow() << " " << nNext.getColumn() << std::endl;
		// Remove the node from the list
		Sopen.pop();
		// Add the node to the Sclosed list
		Sclosed.push_front(nNext);

		//Check if we are finish
		if ( (nNext.getRow() == Goal.getRow()) and (nNext.getColumn() == Goal.getColumn()) )
		{
			finish = true;
			Ncurrent = nNext;

//			std::cout << "\n=== At Goal: " << Ncurrent.getRow() << " " << Ncurrent.getColumn() << std::endl;
//			std::cout << "\n previous: " << Ncurrent.getPreviousNode()->getRow() << " " << Ncurrent.getPreviousNode()->getColumn() << std::endl;
			while(Ncurrent.getPreviousNode() != NULL)// and Ncurrent.getPreviousNode()->getRow() != END.getColumn())
			{
//				Ncurrent = searchMapNode[Ncurrent.getRow()][Ncurrent.getColumn()];

//				ROS_INFO("sista per finire");
//				std::cout << "Ncurrent: " << Ncurrent.getRow() << " " << Ncurrent.getColumn() << std::endl;
//				ROS_INFO("sista per finire");
//				ROS_INFO("r = %d, c = %d", Ncurrent.getRow(), Ncurrent.getColumn());

//				Poptimal.push_back(Ncurrent.getId());
				PoptimalQueue.push(Ncurrent);
				Ncurrent = *(Ncurrent.getPreviousNode());



//			    Node asd(12,12);
//			    Node asd1(13,13);
//			    Node asd2(14,14);
//			    Node asd3(15,15);
//
//			    asd2.setPreviousNode(&asd1);
//			    asd1.setPreviousNode(&asd);
//			    asd.setPreviousNode(&asd3);
//			    asd2 = *asd1.getPreviousNode();
//			    asd1 = *asd2.getPreviousNode();
//			    ROS_INFO("15 = %d", asd1.getColumn());
			}
			if(!PoptimalQueue.empty()) PoptimalQueue.push(Ncurrent);
		}
		else
		{


			for(int r = -1; r <= 1; r++)
			{
				for(int c = -1; c <= 1; c++)
				{
					// Update the neighbors' expected cost

					if( (r == -1 and (c ==-1 or c==1 )) or (r == 1 and (c ==-1 or c==1 )) )
					{

					}
					else
						{
						Node nNeighbor(nNext.getRow() + r, nNext.getColumn() + c);

						// first check if we are in the grid or outside
						if( (0 <= (nNeighbor.getColumn() )) and ((nNeighbor.getColumn() ) < searchMap.getColumn()) and (0 <= (nNeighbor.getRow() ))    and ((nNeighbor.getRow() )    < searchMap.getRow()) )
						{
							nNeighbor = searchMapNode[nNext.getRow() + r][nNext.getColumn() + c];
							// Check if the neighbors node are free

							int neigh, search;
							neigh = nNeighbor.getId();
							search = searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getId();

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
									if(std::find(SopenList.begin(), SopenList.end(), nNeighbor.getId()) != SopenList.end()) //fulfilled if nNeighbor is in the list
										isInOpen = true;


									if(not isInOpen)
									{
										// ?? non so bene cosa fanno loro (*)
//										ROS_INFO("cost prima = %f", searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost());
//										ROS_INFO("Expectedcost prima = %f", searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getExpectedCost());

//										std::cout << "current node 1: " << nNext.getRow() + r << " " << nNext.getColumn() + c << std::endl;
//										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost() + 1);
										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(nNext.getCost() + 1);

										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost() + manDist(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c], Goal));
										searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& searchMapNode[nNext.getRow()][nNext.getColumn()]); //

//										ROS_INFO("cost = %f", searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getCost());
//										ROS_INFO("Expectedcost = %f", searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getExpectedCost());

										Sopen.push(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c]);
										SopenList.push_front(searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].getId());
//										ROS_INFO("Messo in open: r= %d, c = %d", nNext.getRow() + r, nNext.getColumn() + c);
									}
									else
									{
										double gCostTmp;
										gCostTmp = nNext.getCost() + 1;
										if(gCostTmp < nNeighbor.getCost() )
										{
//											std::cout << "current node 2: " << nNext.getRow() + r << " " << nNext.getColumn() + c << std::endl;
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setCost(gCostTmp);
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setExpectedCost(nNeighbor.getCost() + manDist(nNeighbor,Goal) );
											searchMapNode[nNext.getRow() + r][nNext.getColumn() + c].setPreviousNode(& nNext);
										}
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


// Compute a path between start and goal
nav_msgs::Path AStarSearch::computePath()
{
  nav_msgs::Path path;

//  ROS_INFO("path from (%f, %f, %f) to (%f, %f, %f)", start.x, start.y, start.z, goal.x, goal.y, goal.z);

  // Set the header and initialize the poses array
  path.header.stamp = ros::Time::now();
  path.header.frame_id = "map";
  path.poses = std::vector<geometry_msgs::PoseStamped>(PoptimalQueue.size()); // ho creato un mex di dimensione 2

  std::cout << "poptimal size: " << PoptimalQueue.size() << std::endl;

  // Set start as the first pose

  int i = 0;

//  for (std::list<int>::iterator it=Poptimal.begin(); it != Poptimal.end(); ++it)
//  {
  while(not PoptimalQueue.empty())

  {
	  ROS_INFO("in computePath");
//	  ROS_INFO("%d",*it);
	  geometry_msgs::Point point;

	  Node Nused(1,1);
	  int row, column;
	  ROS_INFO("before");

	  Nused = PoptimalQueue.front();

//		std::cout << "Nused: " << Nused.getRow() << " " << Nused.getColumn() << std::endl;


	  PoptimalQueue.pop();
	  ROS_INFO("after");

	  row = Nused.getRow() ;
	  column = Nused.getColumn();
	  point.x = column*searchMap.getResolution() + searchMap.getResolution()/2;
	  point.y =  row*searchMap.getResolution() + searchMap.getResolution()/2;
	  // + searchMap.getResolution() just for a better understanding and a better reppresentation in rviz
//	  ROS_INFO("after 1");

	  path.poses[i].header.stamp = path.header.stamp;
	  path.poses[i].header.frame_id = path.header.frame_id;
	  path.poses[i].pose.position = point;
//	  ROS_INFO("after 2");

	  i++;
  }
  return path;
}


void AStarSearch::publishPathRviz(std::list<int> Poptimal)
{
	  for (std::list<int>::iterator it=Poptimal.begin(); it != Poptimal.end(); ++it)
	  {
		  geometry_msgs::Point start;
		  geometry_msgs::Point goal;

//		  computePath(start, goal);
	  }
}

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
//empty()
//size()
//front()
//push_back()
//pop_back()

