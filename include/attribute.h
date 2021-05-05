#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "point.h"

struct AttrPri
{
    // from large to small
    bool operator () (const Point<CordType>* a, const Point<CordType>* b){

        return ATTRINT(a) > ATTRINT(b);
    
    }

};

struct AstarAttr{
    int f;
    int g;
    int h;
    Point<CordType>* parent;
    AstarAttr() : f(0),g(0),h(0),parent(NULL){}
    AstarAttr(int f, int g, int h, Point<CordType>* parent = NULL) : f(f),g(g),h(h),parent(parent){}
};

struct AstarAttrPri
{
    // from large to small
    bool operator () (const Point<CordType>* a, const Point<CordType>* b){

        return ATTR(AstarAttr, a)->f > ATTR(AstarAttr, b)->f;
    
    }

};

struct AstarAttrPriInv
{
    // from small to large
    bool operator () (const Point<CordType>* a, const Point<CordType>* b){

        return ATTR(AstarAttr, a)->f < ATTR(AstarAttr, b)->f;
    
    }

};

struct AstarAttrPrih
{
    // from large to small
    bool operator () (const Point<CordType>* a, const Point<CordType>* b){

        return ATTR(AstarAttr, a)->h > ATTR(AstarAttr, b)->h;
    
    }

};

struct HASAttr{
    int f;
    int g;
    double k; // k-norm
    double EX; // expected length
    Point<CordType>* parent;
    int flag1;
    int flag2;
    HASAttr() : f(0),g(0),k(0),EX(0),parent(NULL){}
    HASAttr(int f, int g, double k, double EX, Point<CordType>* parent = NULL)
        : f(f),g(g),k(k),EX(EX),parent(parent){}
};

struct HASAttrPriFI{
    bool operator () (const Point<CordType>* a, const Point<CordType>* b) const{
        if(ATTR(HASAttr, a)->f < ATTR(HASAttr, b)->f){
            return true;
        }
        // same priority, do these steps to break this tie
        else if(ATTR(HASAttr, a)->f == ATTR(HASAttr, b)->f){
            // using level infomation
            if(ATTR(HASAttr, a)->g < ATTR(HASAttr, b)->g){
                return true; // bigger level
            }
            else if(ATTR(HASAttr, a)->g > ATTR(HASAttr, b)->g){
                return false;
            }
            else{ // using the second method, k(v)
                return ATTR(HASAttr, a)->k < ATTR(HASAttr, b)->k;
            }
        }
        else{
            return false;
        }
    }
};

struct HASAttrPriFD{
    bool operator () (const Point<CordType>* a, const Point<CordType>* b) const{
        if(ATTR(HASAttr, a)->f > ATTR(HASAttr, b)->f){
            return true;
        }
        // same priority, do these steps to break this tie
        else if(ATTR(HASAttr, a)->f == ATTR(HASAttr, b)->f){
            // using level infomation
            if(ATTR(HASAttr, a)->g > ATTR(HASAttr, b)->g){
                return true; // bigger level
            }
            else if(ATTR(HASAttr, a)->g < ATTR(HASAttr, b)->g){
                return false;
            }
            else{ // using the second method, k(v)
                return ATTR(HASAttr, a)->k > ATTR(HASAttr, b)->k;
            }
        }
        else{
            return false;
        }
    }
};

struct HASAttrPriEX{
    bool operator () (const Point<CordType>* a, const Point<CordType>* b) const{
        if(ATTR(HASAttr, a)->EX < ATTR(HASAttr, b)->EX){
            return true;
        }
        else{
            return false;
        }
    }
};

struct HASAttrPrih{
    bool operator () (const Point<CordType>* a, const Point<CordType>* b) const{
        return (ATTR(HASAttr, a)->f - ATTR(HASAttr, a)->g) > (ATTR(HASAttr, b)->f - ATTR(HASAttr, b)->g);
    }
};

#endif