/*
 * Node.h
 *
 *  Created on: Oct 22, 2014
 *      Author: mafilipp
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_NODE_H_
#define MAFILIPP_PATH_PLANNING_SRC_NODE_H_

class Node {
public:
	// Constructor and Deconstructor

	Node(int row, int column);
	~Node();

	// Getters and setters
	int getColumn() const;
	void setColumn(int column);
	double getCost() const;
	void setCost(double cost);
	Node * getPreviousNode();
	void setPreviousNode(Node &_previousNode);
	int getRow() const;
	void setRow(int row);
	double getExpectedCost() const;
	void setExpectedCost(double expectedCost);

	///



private:
	int row, column;
	double cost;
	double expectedCost;
	Node * previousNode;

};


class CompareNodeCost {
public:
    bool operator()(Node& N1, Node& N2)
    {
       if (N1.getExpectedCost() > N2.getExpectedCost()) return true;
       return false;
    }
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_NODE_H_ */
