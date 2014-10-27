/*
 * Node.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#include "Node.h"
#include <limits>
#include<ros/ros.h>

Node::Node()
{
	m_row=0;
	m_column=0;
	m_id=0;

	m_cost = std::numeric_limits<int>::max(); // Set initial cost to inf
	m_expectedCost = std::numeric_limits<int>::max(); // Set initial cost to inf
	m_occupied = false;

	m_previousNode = NULL;
}
Node::Node(int row, int column) {
	m_row = row;
	m_column = column;
	m_cost = std::numeric_limits<int>::max(); // Set initial cost to inf
	m_expectedCost = std::numeric_limits<int>::max(); // Set initial cost to inf
	m_occupied = false;
//	this->previousNode = NULL;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
//	delete m_previousNode; delete è la memoria che voglio liberare creata col new

}

int Node::getColumn() const {
	return m_column;
}

void Node::setColumn(int column) {
	m_column = column;
}

double Node::getCost() const {
	return m_cost;
}

void Node::setCost(double cost) {
	m_cost = cost;
}


// Eclipse> perche const e perche this_ come lo uso qui?
//const Node*& Node::getPreviousNode() const {
//	return previousNode;
//}
//
//void Node::setPreviousNode(const Node*& previousNode) {
//	this->previousNode = previousNode;
//}


Node * Node::getPreviousNode() const
{
	return m_previousNode;
}

void Node::setPreviousNode(Node *_previousNode)
{
//	ROS_INFO("prima");
	m_previousNode = _previousNode;
//	std::cout << "  m_previsouNode: " << m_previousNode->getRow() << " " << m_previousNode->getColumn() << std::endl;
//	ROS_INFO("dopo");

}

//void setProgram(clsProgram *x) { programEnrolled=x; }
//clsProgram *getProgram() const { return programEnrolled; }
//////

int Node::getRow() const {
	return m_row;
}

void Node::setRow(int row) {
	m_row = row;
}

double Node::getExpectedCost() const {
	return m_expectedCost;
}

void Node::setExpectedCost(double expectedCost) {
	m_expectedCost = expectedCost;
}

bool Node::isOccupied() const {
	return m_occupied;
}

void Node::setOccupied(bool occupied) {
	m_occupied = occupied;
}

int Node::getId() const {
	return m_id;
}

void Node::setId(int id) {
	m_id = id;
}
