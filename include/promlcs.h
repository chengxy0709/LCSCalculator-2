#ifndef PROMLCS_H
#define PROMLCS_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <list>

#include "errdef.h"
#include "point.h"
#include "tool.h"
#include "dtree.h"
#include "attribute.h"

using namespace std;

class PROMLCS{

public:
    PROMLCS(vector<string> seqs, string alphabets);
    ~PROMLCS(){}

    void run();
    string get_lcs() const{return lcs;}

private:
    int cal_g_val(Point<CordType> *p, int order){return UpperBound_by_CountTabs(p, SU) + order;}

    vector<string> seqs;
    int alphaSize;
    vector< vector< vector<int> > > SucTabs;
    vector< vector< vector<int> > > SU; // for estimating the upper bound of a local LCS
    string lcs;

};


void promlcs_help_func();
int promlcs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //PROMLCS_H
