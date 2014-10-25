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


// Compute a path between start and goal
nav_msgs::Path computePath(geometry_msgs::Point start, geometry_msgs::Point goal)
{
  nav_msgs::Path path;

  ROS_INFO("path from (%f, %f, %f) to (%f, %f, %f)", start.x, start.y, start.z, goal.x, goal.y, goal.z);

  // Set the header and initialize the poses array
  path.header.stamp = ros::Time::now();
  path.header.frame_id = "map";
  path.poses = std::vector<geometry_msgs::PoseStamped>(2); // ho creato un mex di dimensione 2

  // Set start as the first pose
  path.poses[0].header.stamp = path.header.stamp;
  path.poses[0].header.frame_id = path.header.frame_id;
  path.poses[0].pose.position = start;

  // Set goal as the second pose
  path.poses[1].header.stamp = path.header.stamp;
  path.poses[1].header.frame_id = path.header.frame_id;
  path.poses[1].pose.position = goal;

  return path;
}



int main(int argc, char **argv)
{
  // Initialize the node
  ros::init(argc, argv, "path_planner");

  double robotRadius;
  robotRadius = 0.06; //[m]
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
    Node a1(12,12);
//    Node a2(12,23);
//    a1.cost = 1;
//    a2.cost = 333;
//    std::priority_queue<Node, std::vector<Node>, CompareNodeCost> costQueue;
//    costQueue.push(a1);
//    costQueue.push(a2);
//    std::cout << costQueue.top().cost << std::endl;
//    costQueue.pop();
//    std::cout << costQueue.top().cost << std::endl;
  ////  std::vector<int> asd;



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

    if(gridMap.isUpToDate() and not gridMap.isAlreadyInflated())
    {
//        ROS_INFO("Before inflate");
//        gridMap.inflate();
//        ROS_INFO("After inflate");
//        Node nodo(12,13);
        AStarSearch Astar(gridMap);

    }




    // Update the start and the goal
    start = goal;
    goal.x += goalIncrement;


    // Publish the path
    pathPublisher.publish(computePath(start, goal));
    loop_rate.sleep();


    inflatedMapPublisher.publish(gridMap.getMap());



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
