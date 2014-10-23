/*
 * Node.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#include "Node.h"
#include <limits>

Node::Node(int row, int column) {
	this->row = row;
	this->column = column;
	this->cost = std::numeric_limits<int>::max(); // Set initial cost to inf
	this->previousNode = NULL;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

int Node::getColumn() const {
	return column;
}

void Node::setColumn(int column) {
	this->column = column;
}

double Node::getCost() const {
	return cost;
}

void Node::setCost(double cost) {
	this->cost = cost;
}


// Eclipse> perche const e perche this_ come lo uso qui?
//const Node*& Node::getPreviousNode() const {
//	return previousNode;
//}
//
//void Node::setPreviousNode(const Node*& previousNode) {
//	this->previousNode = previousNode;
//}


Node * Node::getPreviousNode()
{
	return previousNode;
}

void Node::setPreviousNode(Node &_previousNode)
{
	*previousNode = _previousNode;
}

//////

int Node::getRow() const {
	return row;
}

void Node::setRow(int row) {
	this->row = row;
}
