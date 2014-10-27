/*
 * Node.h

 *
 *  Created on: Oct 22, 2014
 *      Author: Filippo Martinoni
 *      Note: Node that are used for the graph search. CompareNodeCost needed for the priority queue in order to sort the node with smaller expected cost.
 */

#ifndef MAFILIPP_PATH_PLANNING_SRC_NODE_H_
#define MAFILIPP_PATH_PLANNING_SRC_NODE_H_

class Node {
public:

	// Constructor and Destructors
	Node();
	Node(int row, int column);
	~Node();

	// Getters and setters
	int getColumn() const;
	void setColumn(int column);
	double getCost() const;
	void setCost(double cost);
	Node * getPreviousNode() const;
	void setPreviousNode(Node *_previousNode);
	int getRow() const;
	void setRow(int row);
	double getExpectedCost() const;
	void setExpectedCost(double expectedCost);
	bool isOccupied() const;
	void setOccupied(bool occupied);
	int getId() const;
	void setId(int id);

	// Operator overloading
    bool operator==(const Node& n1)
     {
        if( (n1.m_row == m_row) and (n1.m_column == m_column))
        	return true;
        else
        	return false;
     }

private:
    // Attribute
    int m_row;
	int m_column;
	int m_id;
	double m_cost;
	double m_expectedCost;
	Node * m_previousNode;
	bool m_occupied;


};

// used from priority queue
class CompareNodeCost {
public:
    bool operator()(Node& N1, Node& N2)
    {
       if (N1.getExpectedCost() > N2.getExpectedCost()) return true;
       return false;
    }
};

#endif /* MAFILIPP_PATH_PLANNING_SRC_NODE_H_ */
