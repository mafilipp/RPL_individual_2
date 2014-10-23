/*
 * map.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_MAP_H_
#define MAFILIPP_PATH_PLANNING_SRC_MAP_H_

#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/Point.h>

class Map {
public:
	// Constructors and destructor
	Map(double robotSize = 0);
	Map(nav_msgs::OccupancyGrid map, double robotSize = 0);
	void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr &map);
	~Map();

	// inflate the current Map by the robot's radius
	void inflate();
//	int indx2DTo1D(int column, int row);
//	int indx1DTo2D(int indx);


	// Setters and getters

	const nav_msgs::OccupancyGrid& getMap() const;
	void setMap(const nav_msgs::OccupancyGrid& map);
	double getRobotSize() const;
	void setRobotSize(double robotSize);
	int getColumn() const;
	void setColumn(int column);
	int getRow() const;
	void setRow(int row);
	const geometry_msgs::Pose& getOrigin() const;
	void setOrigin(const geometry_msgs::Pose& origin);
	const int* getOriginPx() const;
	int getRadiusPx() const;
	void setRadiusPx(int radiusPx);
	float getResolution() const;
	void setResolution(float resolution);
	bool isUpToDate() const;
	void setUpToDate(bool upToDate);

private:
	double m_robotSize;
	nav_msgs::OccupancyGrid m_map;
	int nRow, nColumn;
	geometry_msgs::Pose origin;
	float resolution;
	int radiusPx;
	int originPx[2];
	bool upToDate;

};


#endif /* MAFILIPP_PATH_PLANNING_SRC_MAP_H_ */
