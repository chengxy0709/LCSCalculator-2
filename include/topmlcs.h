#ifndef TOPMLCS_H
#define TOPMLCS_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <time.h>

#include "errdef.h"
#include "point.h"
#include "tool.h"
#include "phash.h"

using namespace std;

class TOPMLCS{

public:
    TOPMLCS(vector<string>& seqs, string& alphabets);
    ~TOPMLCS();

    void run();
    vector<string> get_mlcs() const {return mlcs;}

private:
    int construct_ICSG();
    int forward_top_sort(int maxIndex);
    void backward_top_sort(int maxlevel, int pinf_index);
    void find_mlcs(string& LCSRecord, int index);

    vector<string> seqs;
    vector<string> mlcs;
    vector< vector< vector<int> > > SucTabs;
    BiHashTable DM;
    vector<int> ID;
    vector<int> tlevel;
    vector< list<int> > precursor;
                                   
};

void topmlcs_help_func();
int topmlcs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //TOPMLCS_H
