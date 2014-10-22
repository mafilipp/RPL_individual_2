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
	Node(int row_f, int column_f);
	// TODO: setter / getter

//private:
	int row, column;
	double cost;
	Node * previousNode;

};


class CompareNodeCost {
public:
    bool operator()(Node& N1, Node& N2)
    {
       if (N1.cost > N2.cost) return true;
       return false;
    }
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_NODE_H_ */
