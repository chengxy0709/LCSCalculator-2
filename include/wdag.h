#ifndef WDAG_H
#define WDAG_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>

#include "errdef.h"
#include "point.h"
#include "phash.h"
#include "tool.h"

using namespace std;

class WDAG{

public:
    WDAG(vector<string>& seqs, string alphabets);
    ~WDAG(){}

    void run();
    vector<string> get_mlcs() const {return mlcs;}

private:
    void cal_nums_and_merge_char();
    void cal_weights();
    int  weight(int p, int k);
    void construct_WDAG();
    void determine_levels();
    void GetMLCS(string& LCSRecord, int index);

    vector<string> seqs;
    vector<string> seqms;
    vector<string> mlcs;
    vector< vector< vector<int> > > SucTabs;
    vector< vector<int> > nums;
    vector< vector< vector<int> > > Weights;

    BiHashTable DM;
    vector< list<int> > Edge;
    vector<int> Indegree;
    vector<int> Level;
    vector< list<int> > precursor;

};

void wdag_help_func();
int wdag_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //WDAG_H
