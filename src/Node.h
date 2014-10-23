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
	virtual ~Node();
	Node(int row, int column);

	// Getters and setters
	int getColumn() const;
	void setColumn(int column);
	double getCost() const;
	void setCost(double cost);
	Node * getPreviousNode();
	void setPreviousNode(Node &_previousNode);
	int getRow() const;
	void setRow(int row);
	///



private:
	int row, column;
	double cost;
	Node * previousNode;

};


class CompareNodeCost {
public:
    bool operator()(Node& N1, Node& N2)
    {
       if (N1.getCost() > N2.getCost()) return true;
       return false;
    }
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_NODE_H_ */
