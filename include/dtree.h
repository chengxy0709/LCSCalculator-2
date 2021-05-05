#ifndef DTREE_H
#define DTREE_H

#include <iostream>
#include <string.h>

#include "point.h"

struct DtreeNode{

    Point<CordType> *D;   // lower bound
    Point<CordType> *A;   // upper bound

    struct DtreeNode **child;  // child array

};

class Dtree{

public:
    Dtree(){ d = 0; root = NULL; }
    Dtree(int d){
        root = NULL;
        if(d > 0) this->d = d;
        else std::cerr << "d must be a integer!" << std::endl;
    }
    ~Dtree();

    void setD(int d){this->d = d;}

    bool Search(Point<CordType> *p, DtreeNode *R = NULL);
    void Insert(Point<CordType> *p, DtreeNode *R = NULL);
    void traverse(DtreeNode *R = NULL);

    DtreeNode* getRoot() const{return root;}

private:
    DtreeNode* createDtNode(Point<CordType> *p);
    
    int d;
    DtreeNode *root;

};

#endif // DTREE_H
