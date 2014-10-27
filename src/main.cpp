#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include "map.h"
#include "path_planner.h"
#include "graph_search.h"
#include "A_star_search.h"
#include "Node.h"

#include <queue>
#include <vector>

using namespace std;



// Callback function for map messages
void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  ROS_INFO("I read a map!");
}


//// Compute a path between start and goal
//nav_msgs::Path computePath(geometry_msgs::Point start, geometry_msgs::Point goal)
//{
//  nav_msgs::Path path;
//
//  ROS_INFO("path from (%f, %f, %f) to (%f, %f, %f)", start.x, start.y, start.z, goal.x, goal.y, goal.z);
//
//  // Set the header and initialize the poses array
//  path.header.stamp = ros::Time::now();
//  path.header.frame_id = "map";
//  path.poses = std::vector<geometry_msgs::PoseStamped>(2); // ho creato un mex di dimensione 2
//
//  // Set start as the first pose
//  path.poses[0].header.stamp = path.header.stamp;
//  path.poses[0].header.frame_id = path.header.frame_id;
//  path.poses[0].pose.position = start;
//
//  // Set goal as the second pose
//  path.poses[1].header.stamp = path.header.stamp;
//  path.poses[1].header.frame_id = path.header.frame_id;
//  path.poses[1].pose.position = goal;
//
//  return path;
//}



int main(int argc, char **argv)
{
  // Initialize the node
  ros::init(argc, argv, "path_planner");

  double robotRadius;
  robotRadius = 0.03; //[m]
  Map gridMap(robotRadius);

  ros::NodeHandle n;

  // Set publisher and subscriber
  ros::Subscriber mapSubscriber = n.subscribe<nav_msgs::OccupancyGrid>("/map", 1000, mapCallback);
  ros::Subscriber mapSubscriberCallback = n.subscribe<nav_msgs::OccupancyGrid>("/map", 1000, &Map::mapCallback, &gridMap);

  ros::Publisher inflatedMapPublisher = n.advertise<nav_msgs::OccupancyGrid>("/inflatedMap",10);
  ros::Publisher pathPublisher = n.advertise<nav_msgs::Path>("/path", 10);


//  //Get the time and store it in the time variable.
//  // This to be sure that the map is up to date with the callback
//  ros::Time time = ros::Time::now();
//  //Wait a duration of one second.
//  ros::Duration d = ros::Duration(1, 0);
//  d.sleep();





  // Ask to the user for the desired robot radius


  // Define variable

  //  execte function mapCallback with the object gridMap

  // Inflate the gridMap with the robot radius

  //  AStarSearch aStarPlanner(...);
//  aStarPlanner.setPublisher(pathPublisher);

  /////////////////////////// Test for pick out the node with major cost
//    Node a1(12,12);
//    Node a2(12,12);
//
//    bool h;
//    h = a1 == a2;
//    a1.cost = 1;
//    a2.cost = 333;
//    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> costQueue;
//    costQueue.push(a1);
//    costQueue.push(a2);
//    std::cout << costQueue.top().cost << std::endl;
//    costQueue.pop();
//    std::cout << costQueue.top().cost << std::endl;
  ////  std::vector<int> asd;

bool PathComputed = false;
  Node asd(12,12);
  Node aa(11,11);
  Node as(13,13);
//  Node* ciao = new Node(12,12);
//  asd.setPreviousNode(&aa);
//  int ccc = asd.getPreviousNode()->getColumn();
//  as.setPreviousNode(asd.getPreviousNode());
//  int cici = aa.getPreviousNode()->getColumn();

  ros::Rate loop_rate(1);

  // Initialize start, goal, and goal increment
  geometry_msgs::Point start, goal;
  double goalIncrement = 0.1;
  start.x = start.y = start.z = 0.0;
  goal.x = goal.y = goal.z = 0.0;

  while (ros::ok() && goal.x < 2.0)
  {
    ros::spinOnce();

//    while(not gridMap.isUpToDate())
//    {
//  	  // Wait
//    }
//    std::list<int> ilist;
//    ilist.push_back(1);
//    ilist.push_back(2);
//    ilist.push_back(3);
//
//	if(std::find(ilist.begin(), ilist.end(), 1) != ilist.end())
//		            	 ROS_INFO("asd true");
//					else
//						ROS_INFO("asd false");


//    std::list<int>::iterator findIter = std::find(ilist.begin(), ilist.end(), 1);
//
//    ROS_INFO("valore it = ",*findIter);
//
//    std::list<int> my_list;
//    //...
//    int some_value = 12;
//    std::list<int>::iterator iter = std::find (my_list.begin(), my_list.end(), some_value);
//    // now variable iter either represents valid iterator pointing to the found element,
    // or it will be equal to my_list.end()


//            std::list<int> lista;
//            lista.push_back(3);
//            lista.push_back(2);
//            lista.push_back(7);
//            lista.push_back(15);
//
//            std::vector<int>::iterator it;
//
//             it = std::find(lista.begin(), lista.end(), 30);
//
//             if (it != lista.end())
//            	 ROS_INFO("true");
//			else
//				ROS_INFO("false");
//
//
//             ROS_INFO("valore it = ",*it)

//    Node asd(12,12);
//    Node asd1(13,13);
//    Node asd2(14,14);
//    Node asd3(15,15);
//
//
//
//
//    asd2.setPreviousNode(&asd1);
//    asd1.setPreviousNode(&asd);
//    asd.setPreviousNode(&asd3);
//    asd2 = *asd1.getPreviousNode();
//    asd1 = *asd2.getPreviousNode();
//    ROS_INFO("15 = %d", asd1.getColumn());

//    asd = asd1;
//    ROS_INFO("13 = %d",asd.getColumn());

//    ROS_INFO("12 = %d", asd2.getPreviousNode() ->getPreviousNode() ->getColumn());



    if(gridMap.isUpToDate() and not gridMap.isAlreadyInflated() and not PathComputed)
    {
//        ROS_INFO("Before inflate");
        gridMap.inflate();
        inflatedMapPublisher.publish(gridMap.getMap());

//        ROS_INFO("After inflate");
//        Node nodo(12,13);


        geometry_msgs::Point Start;
        geometry_msgs::Point Goal;

        Start.x = 1.8;//0*gridMap.getResolution();
        Start.y = 0.2;//3*gridMap.getResolution();
        Goal.x  = 0.2;//3*gridMap.getResolution();
        Goal.y  = 1.8;//3*gridMap.getResolution();

        AStarSearch Astar(gridMap, pathPublisher);
//        std::list<int> lista;
//        lista.push_back(3);
//        lista.push_back(2);
//        lista.push_back(7);
//        lista.push_back(15);
//
//
//        Astar.setPoptimal(lista);

//        Astar.findPath(Start, Goal);
//
////        ROS_INFO("Noi siamo qua %d", Astar.getPoptimal().empty()); // esce che è empty
//
//        pathPublisher.publish(Astar.computePath());
        PathComputed = true;

        ////////////

        geometry_msgs::Point s1, s2, s3, s4;

         s1.x = 1.8;
         s1.y = 0.2;

         s2.x = 1.8;
         s2.y =  1.8;

         s3.x = 0.2,
         s3.y = 1.8;

         s4.x = 0.2;
         s4.y = 2;
        Astar.findPath(s1, s2);
        pathPublisher.publish(Astar.computePath());
        Astar.findPath(s2, s3);
        pathPublisher.publish(Astar.computePath());
        Astar.findPath(s3, s4);
        pathPublisher.publish(Astar.computePath());
        /////////////////


    }




    // Update the start and the goal
    start = goal;
    goal.x += goalIncrement;


    // Publish the path
    loop_rate.sleep();





  }


  return 0;
}

//Da mettere da qualche parte:
//...

//  ros::Subscriber mapSubscriber = n.subscribe<nav_msgs::OccupancyGrid>("/map", 1000, &gridMap::mapCallback, &gridMap);
//  ros::Publisher pathPublisher = n.advertise<nav_msgs::Path>("/path", 1000, true);

//
//  aStarPlanner.setPublisher(pathPublisher);
//...


/////////////////////////// Test for pick out the node with major cost
//  Node a1(12,12);
//  Node a2(12,23);
//  a1.cost = 1;
//  a2.cost = 333;
//  std::priority_queue<Node, std::vector<Node>, CompareNodeCost> costQueue;
//  costQueue.push(a1);
//  costQueue.push(a2);
//  std::cout << costQueue.top().cost << std::endl;
//  costQueue.pop();
//  std::cout << costQueue.top().cost << std::endl;
////  std::vector<int> asd;
//////////////////////////7
