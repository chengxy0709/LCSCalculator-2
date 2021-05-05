#ifndef MLCSAPP_H
#define MLCSAPP_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "errdef.h"
#include "point.h"
#include "phash.h"
#include "attribute.h"
#include "tool.h"
#include "check.h"

using namespace std;

class MLCSAPP{

public:
    MLCSAPP(vector<string>& seqs, string& alphabets);
    ~MLCSAPP();

    void run();
    string get_lcs() const {return lcs;}
private:
    void compute_score_tabs();
    void computeF(Point<CordType> *p);
    int find_lcs( Point<CordType>* p );

    vector<string> seqs;
    vector< vector< vector<int> > > SucTabs;
    vector< vector< vector<int> > > ScoreTabs; // for estimating the length of a local LCS
    string lcs;

};

void mlcsapp_help_func();
int mlcsapp_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //MLCSAPP_H
