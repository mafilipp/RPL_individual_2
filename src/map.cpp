/*
 * map.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#include "map.h"
#include <assert.h>
#include <ros/ros.h>


Map::Map(double robotSize)
{
	assert(robotSize>=0); // Ensure that the robot size is non-negative
	m_robotSize = robotSize;		//...
	upToDate = 0;

}

Map::Map(nav_msgs::OccupancyGrid map, double robotSize)
{
	assert(robotSize>=0); // Ensure that the robot size is non-negative
	m_robotSize = robotSize;

	//Create the map
	nColumn = map.info.height;
	nRow = map.info.width;
	m_map = map;
	origin = map.info.origin;
	resolution = map.info.resolution;
	radiusPx = m_robotSize/resolution; //[cell]
	if (radiusPx % 2 == 0)
			radiusPx += 1; // In order to inflate the map we need a odd filter
	upToDate = 1;
	alreadyInflated = false;
}

Map::~Map()
{
	//delete m_map;
}

void Map::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr &map)
{
	//Create the map
	ROS_INFO("callback");

	m_map = *map;
	nColumn = m_map.info.height;
	nRow = m_map.info.width;
	origin = m_map.info.origin;
	resolution = m_map.info.resolution;
	radiusPx = m_robotSize/resolution; //[cell]
	upToDate = true;
	if (radiusPx % 2 == 0)
			radiusPx += 1; // In order to inflate the map we need a odd filter
	ROS_INFO("Element Map correctly updated");
}
//...

//Remember
//array[3][4] = [row] [column]
//[0][0]  [0][1]  [0][2]  [0][3]  [0][4]
//[1][0]  [1][1]  [1][2]  [1][3]  [1][4]
//[2][0]  [2][1]  [2][2]  [2][3]  [2][4]
void Map::inflate()
{
	if( m_robotSize > 0 and upToDate and not alreadyInflated)
	{

		Map inflatedMap(m_map,m_robotSize);

		ROS_INFO("nColumn = %d", inflatedMap.nColumn);

		ROS_INFO("resolution = %f", inflatedMap.resolution);

		ROS_INFO("radius = %d", inflatedMap.radiusPx);

		// Create the dimension that we want to add to the original image due to the boundary condition needed for the filtering
		int dimAdded = (radiusPx-1)/2; // We know that the radius is odd

		ROS_INFO("added = %d", dimAdded);

		// Generate a map as a matrix, not an array. Here we add some space
		int FilterCalcMap[nRow + 2*dimAdded] [nColumn + 2*dimAdded];

		// Initialize
		for(int r = 0; r < nRow + 2*dimAdded; r++)
		{
			for(int c = 0; c < nColumn + 2*dimAdded; c++) // No need to do -1 since the array start at 0
			{
				FilterCalcMap[r][c] = 0;
			}
		}
		// Populate

		for(int r = dimAdded; r < nRow + dimAdded; r++)
		{
			for(int c = dimAdded; c < nColumn + dimAdded; c++) // No need to do -1 since the array start at 0
			{
				FilterCalcMap[r][c] = m_map.data[(c - dimAdded) + (r - dimAdded)*nColumn];
			}
		}

		int inflatedFiltredMap[nRow][nColumn];
		// Populate with the original data

		for(int r = 0; r < nRow; r++)
		{
			for(int c = 0; c < nColumn; c++)
			{
				inflatedFiltredMap[r][c] = m_map.data[c + r*nColumn];

			}
		}
		 // Create the filter kernel
		int kernel[radiusPx][radiusPx];
//		 double* a = new int[n]; // Don't forget to delete [] a; when you're done!


		// Populate the kernel in a circle way
//		for(int c = 0; c >= radiusPx - 1; c++)
//		{
//			for(int r = 0; r >= radiusPx - 1; r++)
//			{
//				if()
//					kernel[c][r] = 1;
//				else
//					kernel[c][r] = 0;
//			}
//		}
		// make it all occupied


		for(int r = 0; r < radiusPx; r++)
		{
			for(int c = 0; c < radiusPx; c++)
			{
					kernel[r][c] = 1;
			}
		}

// ok Fino a qui
		// Filter the image
//		for(int r = dimAdded; r < nRow + dimAdded; r++)
//		{
//			for(int c = dimAdded; c < nColumn + dimAdded; c++)
//			{
//
//				bool touch = false;
//
//				for (int rF = 0; rF < radiusPx; rF++)
//				{
//					for (int cF = 0; cF < radiusPx; cF++)
//					{
//
//						if((kernel[rF][cF] > 0) && (FilterCalcMap[r + rF][c + cF] > 0))
//						{
//							touch = true;
//							break;
//						}
//
//					}
//				}
//
//				if (touch)
//				{
//					inflatedFiltredMap[c - dimAdded][r - dimAdded] = 100;
//				}
//			}
		for(int r = 0; r < nRow + dimAdded; r++)
		{
			for(int c = 0; c < nColumn + dimAdded; c++)
			{

				bool touch = false;

				for (int rF = 0; rF < radiusPx; rF++)
				{
					for (int cF = 0; cF < radiusPx; cF++)
					{

						if((kernel[rF][cF] > 0) && (FilterCalcMap[r + rF][c + cF] > 0))
						{
							touch = true;
//							break;
						}

					}
				}

				if (touch)
				{
					inflatedFiltredMap[r][c] = 60;
				}
			}
		}
		// Reconvert the inflated map in a data array

//		ROS_INFO("asdasd");



		for(int r = 0; r < nRow; r++)
		{
			for(int c = 0; c < nColumn; c++)
			{
//			ROS_INFO("1212121212");

				m_map.data[c + r*nColumn]  = inflatedFiltredMap[r][c];
//				  ROS_INFO("%d",m_map.data[c + r*nColumn]);

			}
		}
		  ROS_INFO("Pass inflate");

	alreadyInflated = true;



	}
}

//...

//int Map::indx2DTo1D(int column, int row)
//{
//	return column + row * (nColumn - 1);
//}
//int Map::indx1DTo2D(int indx)
//{
//	return ;
//}
//
// Setters and getters

void Map::setRobotSize(double robotSize)
{
	assert(robotSize >= 0); // Ensure that the robot size is non-negative
	m_robotSize = robotSize;
}

double Map::getRobotSize() const {
	return m_robotSize;
}

const nav_msgs::OccupancyGrid& Map::getMap() const {
	return m_map;
}

void Map::setMap(const nav_msgs::OccupancyGrid& map) {
	m_map = map;
}

int Map::getColumn() const {
	return nColumn;
}

void Map::setColumn(int column) {
	nColumn = column;
}

int Map::getRow() const {
	return nRow;
}

void Map::setRow(int row) {
	nRow = row;
}

const geometry_msgs::Pose& Map::getOrigin() const {
	return origin;
}

void Map::setOrigin(const geometry_msgs::Pose& origin) {
	this->origin = origin;
}

const int* Map::getOriginPx() const {
	return originPx;
}

int Map::getRadiusPx() const {
	return radiusPx;
}

void Map::setRadiusPx(int radiusPx) {
	this->radiusPx = radiusPx;
}

float Map::getResolution() const {
	return resolution;
}

void Map::setResolution(float resolution) {
	this->resolution = resolution;
}

bool Map::isUpToDate() const {
	return upToDate;
}

void Map::setUpToDate(bool upToDate) {
	this->upToDate = upToDate;
}
