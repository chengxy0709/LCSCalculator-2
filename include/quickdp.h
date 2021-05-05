#ifndef QUICKDP_H
#define QUICKDP_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "errdef.h"
#include "point.h"
#include "phash.h"
#include "tool.h"

using namespace std;

class QUICKDP{

public:
    QUICKDP(){}
    QUICKDP(vector<string> seqs, string alphabets);
    ~QUICKDP(){}

    vector< Point<CordType>* > Minima(vector< Point<CordType>* >& points, int dim);
    void run();
    string get_lcs() const {return lcs;}

private:
    inline bool analyze_points(vector< Point<CordType>* >& points, int dim);
    vector<Point<CordType>*> Divide(vector< Point<CordType>* >& points, int d);
    vector<Point<CordType>*> Union(vector< Point<CordType>* >& points, int d);
    inline int CharIndex(const Point<CordType> *p){return cmap[seqs[0][p->cord[0] - 1]];}

    vector<string> seqs;
    unordered_map<char, int> cmap;
    int alphaSize;
    vector< vector< vector<int> > > SucTabs;
    string lcs;

};

void quickdp_help_func();
int quickdp_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //QUICKDP_H
