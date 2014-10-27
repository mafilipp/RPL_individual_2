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

	///
//	   void setProgram(clsProgram *x) { programEnrolled=x; }
//	   clsProgram *getProgram() const { return programEnrolled; }


    bool operator==(const Node& n1)
     {
        if( (n1.m_row == m_row) and (n1.m_column == m_column))
        	return true;
        else
        	return false;
     }

//	const Node*& getPreviousNode() const { // mi crea un pointer che pointa al pointer
//		return m_previousNode;
//	}
//
//	void setPreviousNode(const Node*& previousNode) {
//		m_previousNode = previousNode;
//	}

//    Node operator=(Node other) {
//    	this -> column = other.column;
//    	this -> row = other.row;
//    	this -> id = other.id;
//    	this -> cost = other.cost;
//    	this -> expectedCost = other.expectedCost;
//    	this -> previousNode = other.previousNode;
//    	this -> occupied = other.occupied;
//
//        return *this;
//    }


private:
	int m_row;
	int m_column;
	int m_id;
	double m_cost;
	double m_expectedCost;
	Node * m_previousNode;
	bool m_occupied;


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
