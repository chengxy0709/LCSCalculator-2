#ifndef ASTAR_H
#define ASTAR_H

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

class ASTAR{

public:
    ASTAR(vector<string>& seqs, string& alphabets);
    ~ASTAR(){

    }

    void run();
    string get_lcs() const {return lcs;}

    using queue_type = priority_queue<Point<CordType>*, vector<Point<CordType>*>, AstarAttrPriInv>;
private:

    int find_lcs( Point<CordType>* p );

    vector<string> seqs;
    vector< vector< vector<int> > > SucTabs;
    vector< vector< vector<int> > > ScoreTabs;
    string lcs;

};

void astar_help_func();
int astar_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //ASTAR_H
