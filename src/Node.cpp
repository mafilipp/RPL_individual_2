/*
 * Node.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#include "Node.h"
#include <limits>

Node::Node(int row_f, int column_f) {
	int row = row_f;
	column = column_f;
	cost = std::numeric_limits<int>::max(); // Set initial cost to inf
	previousNode = NULL;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

