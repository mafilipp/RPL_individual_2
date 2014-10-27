README 

-- Functionality
This Ros node afford to find an optimal path using A* algorithm, given a map from ros_server, and to publish the inflated map and the optimal path.


-- Usage
First start the ROS and rviz for the visualization (all in separate terminal):

	roscore

	rosrun rviz rviz

	rosrun path_planning path_planning

-> if you want to modify the configuration, like the target or the start position, go in main.cpp and modify the USER section	 

-- File/directory structure
In the roboscoop_app directory:
* path_planner: Abstract class that can be reused in the case of path planning task.
* graph_search: Abstract class that can be reused in the case of graph search algorithm.
* A_star_search: Here you can finde the funcion for inflate a map and given 2 or more point the A* algorithm implementation

-- Note for the instructor
I didn't use svn, but github for the commit, so if you are interested, please have a look at https://github.com/mafilipp/RPL_individual_2.
