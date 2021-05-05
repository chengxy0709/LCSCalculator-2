#ifndef BS_H
#define BS_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "errdef.h"
#include "point.h"
#include "tool.h"
#include "phash.h"
#include "attribute.h"

using namespace std;

class BS{

public:
    BS(vector<string>& seqs, string& alphabets);
    ~BS(){

    }

    void run();
    string get_lcs() const {return lcs;}

    using queue_type = priority_queue<Point<CordType>*, vector<Point<CordType>*>, AstarAttrPri>;
private:
    int find_lcs( Point<CordType>* p );

    vector<string> seqs;
    vector< vector< vector<int> > > SucTabs;
    vector< vector< vector<int> > > ScoreTabs;
    string lcs;

    void Filter(HashSet& Vext, int Kfilter);
    vector< Point<CordType>* > Reduce(HashSet& Vext, int beta);

};


void bs_help_func();
int bs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //BS_H
