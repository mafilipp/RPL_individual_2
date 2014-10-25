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
	m_robotSizePx = m_robotSize/resolution;
//	radiusPx = ceil(m_robotSize/resolution/2); //[cell]
//	if (radiusPx % 2 == 0)
//			radiusPx += 1; // In order to inflate the map we need a odd filter
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
//	double tmp = m_robotSize/resolution;
//	m_robotSizePx = ceil(tmp); // Always better to consider the robot with some tollerance
	m_robotSizePx = m_robotSize/resolution;
	upToDate = true;
//	radiusPx = ceil(m_robotSize/resolution/2); //[cell]
//	if (radiusPx % 2 == 0)
//			radiusPx += 1; // In order to inflate the map we need a odd filter
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
	if( m_robotSizePx > 1 and upToDate and not alreadyInflated) // >1 else it doesn't make sense to inflate
	{
		ROS_INFO("INFLATING!!");
		ROS_INFO("RobotSizePx = %d",m_robotSizePx);


		// Define the filter kernel
		int sizeKernel;
		bool whiteAngle = false;

		if (m_robotSizePx % 2 == 0)
		{
			sizeKernel = m_robotSizePx + 1;
			whiteAngle = true;
		}
		else
		{
			sizeKernel = m_robotSizePx;
		}
		ROS_INFO("Kernel size = %d",sizeKernel);




		// Create the filter kernel
		int kernel[sizeKernel][sizeKernel];


		// Populate
		for(int row = 0; row < sizeKernel; row++)
		{
			for(int column = 0; column < sizeKernel; column++)
			{
				kernel[row][column] = 100;
			}
		}


		int kernelCalc = floor(sizeKernel/2);
		ROS_INFO("kernelCalc = %d",kernelCalc);



		// Until here is right: the only problem is that if I give a m_robotSize = 0.08; 0.08/0.03 = 2 and not 2....

		// if robot dimension compared to filter small, make the angle free
		if(whiteAngle)
		{
			kernel[0][0] = 0;
			kernel[sizeKernel - 1][0] = 0;
			kernel[0][sizeKernel - 1] = 0;
			kernel[sizeKernel - 1][sizeKernel - 1] = 0;
		}

		for(int i = 0; i < sizeKernel; i++)
		{
			for(int j = 0; j < sizeKernel; j++)
			{
			ROS_INFO("Kernel Element = %d",kernel[i][j]);
			}
		}
		// Create inflated map
		Map inflatedMap(m_map,m_robotSize);

//		int rowMin, rowMax, columnMin, columnMax;
//		rowMin = 0;
//		rowMax = sizeKernel-1;
//		columnMin = 0;
//		columnMax = sizeKernel-1;
//		int idxRowMin, idxRowMax, idxColumnMin, idxColumnMax;

		// Make calculation
		for(int r = 0; r < nRow; r++)
		{
			for(int c = 0; c < nColumn; c++)
			{

//				ROS_INFO("r = %d,	c=%d	",r,c);
//
//				idxRowMin = -kernelCalc;
//				idxColumnMin = -kernelCalc;
//				idxRowMax = kernelCalc;
//				idxColumnMax = kernelCalc;

//				if (r - kernelCalc < rowMin)
//					idxRowMin = 0;
//				if (r + kernelCalc > rowMax)
//						idxRowMax = nRow -1;
//				if (c - kernelCalc < columnMin)
//					idxColumnMin = 0;
//				if (c + kernelCalc > columnMax)
//						idxColumnMax = nColumn -1;
//
//				// Calculation
//
//				for(int rF = idxRowMin; rF < idxRowMax; rF++ )
//				{
//					for(int cF = idxColumnMin; cF < idxColumnMax; cF++ )
//					{
//						if((m_map.data[getIndex(r+rF, c+cF)] > 0) and (kernel[rF][cF] > 0))
//						inflatedMap.m_map.data[c + r*nColumn] = 100;
//
//						ROS_INFO("r = %d,	c=%d	rF=%d	cF=%d",r,c,rF,cF);
//					}
//				}


				ROS_INFO("r = %d,	c=%d	",r,c);

//				idxRowMin = -kernelCalc;
//				idxColumnMin = -kernelCalc;
//				idxRowMax = kernelCalc;
//				idxColumnMax = kernelCalc;
//
//				if (r - kernelCalc < rowMin)
//					idxRowMin = 0;
//				if (r + kernelCalc > rowMax)
//						idxRowMax = nRow -1;
//				if (c - kernelCalc < columnMin)
//					idxColumnMin = 0;
//				if (c + kernelCalc > columnMax)
//						idxColumnMax = nColumn -1;

				// Calculation

				for(int rF = -kernelCalc; rF < kernelCalc; rF++)
				{
					for(int cF = -kernelCalc; cF < kernelCalc; cF++)
					{
						if((r + rF > 0) and (r + rF < nRow - 1) and (c + cF > 0) and (c + cF < nColumn - 1))
						{
							if((m_map.data[getIndex(r+rF, c+cF)] > 0) and (kernel[rF + kernelCalc][cF + kernelCalc] > 0))
							{
								inflatedMap.m_map.data[c + r*nColumn] = 100;
							}

							ROS_INFO("r = %d,	c=%d	rF=%d	cF=%d",r,c,rF,cF);
						}

					}
				}
			}
		}
		m_map = inflatedMap.m_map;
		alreadyInflated = true;
	}
}



int Map::getIndex(int row, int column)
{
	return row*nColumn + column;
}

//int Map::getIndex2Dfrom1D(int index, int lengthColumn)
//{
//	return row*nColumn + column;
//}
//
//int Map::getIndex1Dfrom2D(int row, int column, int lengthColumn)
//{
//	return row*lengthColumn + column;
//}
//

//		forSetters and getters

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

int Map::getM_robotSizePx() const {
	return m_robotSizePx;
}

void Map::setM_robotSizePx(int m_robotSizePx) {
	this->m_robotSizePx = m_robotSizePx;
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

bool Map::isAlreadyInflated() const {
	return alreadyInflated;
}

void Map::setAlreadyInflated(bool alreadyInflated) {
	this->alreadyInflated = alreadyInflated;
}
