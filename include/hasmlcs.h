#ifndef HASMLCS_H
#define HASMLCS_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "errdef.h"
#include "point.h"
#include "phash.h"
#include "tool.h"
#include "attribute.h"

using namespace std;

class HASMLCS{

public:
    HASMLCS(vector<string>& seqs, string& alphabets);
    ~HASMLCS(){

    }

    void run_for_BS();
    void run_for_ACS();
    string get_lcs() const {return lcs;}

private:

    int UB(Point<CordType>* p);
    void Filter(HashSet& Vext, int Kfilter);
    vector< Point<CordType>* > Reduce(HashSet& Vext, int beta);
    int find_lcs( Point<CordType>* p );

    template<class T>
    Point<CordType>* pop_valid1(T& Q){
        Point<CordType> *p = NULL;
        while(Q.size() > 0) {
            p = Q.top();
            Q.pop();
            if(ATTR(HASAttr, p)->flag1 == 0) break;
        }
        return (ATTR(HASAttr, p)->flag1 == 0) ? p : NULL;
    }

    template<class T>
    Point<CordType>* pop_valid2(T& Q, int level){
        Point<CordType> *p = NULL;
        while(Q.size() > 0) {
            p = Q.top();
            Q.pop();
            if(ATTR(HASAttr, p)->flag2 == level) break;
        }
        return (ATTR(HASAttr, p)->flag2 == level) ? p : NULL;
    }

    template<class T>
    int Qmax(T& Q){
        Point<CordType> *p = NULL;
        while(Q.size() > 0) {
            p = Q.top();
            if(ATTR(HASAttr, p)->flag1 == 0) break;
            Q.pop();
        }
        return (ATTR(HASAttr, p)->flag1 == 0) ? ATTR(HASAttr, p)->f : 0;
    }

    using queue_type1 = priority_queue<Point<CordType>*, vector<Point<CordType>*>, HASAttrPriFI>;
    using queue_type2 = priority_queue<Point<CordType>*, vector<Point<CordType>*>, HASAttrPriEX>;
    using queue_type3 = priority_queue<Point<CordType>*, vector<Point<CordType>*>, HASAttrPriFD>;

    vector< Point<CordType>* > ExpandNode(Point<CordType>* p, queue_type1& Q);
    vector< Point<CordType>* > ExpandNode(Point<CordType>* p, queue_type1& Q, vector<queue_type2>& Qlev);

    vector<string> seqs;
    vector< vector< vector<int> > > SucTabs;
    vector< vector< vector<int> > > ScoreTabs; // for estimating the length of a local LCS
    vector< vector< vector<int> > > CountTabs; // for estimating the length of a local LCS
    HashSet pset;
    vector< vector<double> > P; // pr table

    string lcs;

};


void hasmlcs_help_func();
int hasmlcs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //HASMLCS_H
