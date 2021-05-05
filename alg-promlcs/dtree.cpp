#include "dtree.h"

bool Dtree::Search(Point<CordType> *p, DtreeNode *R){

    if(root == NULL){
        return true;
    }

    for(int i = 0; i < d; ++i){
        if(p->cord[i] < R->A->cord[i]){ // comparing with upper bound
            return true;
        }
    }

    int i = 0;
    for(i = 0; i < d; ++i){
        if(p->cord[i] < R->D->cord[i]){
            break;
        }
    }
    if(i == d) return false; // P is dominated by R.D

    //otherwise,search subtree
    for(int i = 0; i < d; ++i){
        if(R->child[i] == NULL) continue;
        if( !Search(p, R->child[i]) ) // P is dominated by a point in the i th subtree of R
            return false;
    }
    return true;

}

DtreeNode* Dtree::createDtNode(Point<CordType> *p){

    DtreeNode *node = new DtreeNode;
    node->D = p;
    node->A = new Point<CordType>(d, false, 0);
    for(int i = 0; i < d; i++){
        node->A->cord[i] = p->cord[i];
    }
    node->child = new DtreeNode* [d];
    for(int i = 0; i < d; ++i){
        node->child[i] = NULL;
    }

    return node;

}

void Dtree::Insert(Point<CordType> *p, DtreeNode *R){

    if(root == NULL){
        root = createDtNode(p);
        return;
    }

    for(int i = 0; i < d; ++i){
        if(p->cord[i] < R->A->cord[i]) // update upper bound
            R->A->cord[i] = p->cord[i];
    }

    int i = 0;
    for(i = 0; i < d; ++i){     // find a position that insert correctly
        if(p->cord[i] < R->D->cord[i])
            break;
    }

    if(R->child[i] == NULL){
        R->child[i] = createDtNode(p);
    }
    else{
        Insert(p, R->child[i]);
    }

}

void Dtree::traverse(DtreeNode *R){

    if(R == NULL)
        return;
    
    R->A->print(d, '|');
    R->D->print(d);

    for(int i = 0; i < d; ++i){
        traverse(R->child[i]);
    }

}

Dtree::~Dtree(){
    
    if(root == NULL)
        return;
    
    delete root->A;
    delete root->D;

    for(int i = 0; i < d; ++i){
        delete root->child[i];
    }
    delete root->child;
    
}
