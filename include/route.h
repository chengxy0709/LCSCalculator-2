#ifndef ROUTE_H
#define ROUTE_H

#include <functional>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "errdef.h"

// Alg Module Header Start
#include "bs.h"
#include "astar.h"
#include "hasmlcs.h"
#include "promlcs.h"
#include "quickdp.h"
#include "topmlcs.h"
#include "mlcsapp.h"
#include "test.h"
#include "example.h"

// Alg Module Header End

using namespace std;

class Router{
    
public:
    Router(string algo, ostream& os) : alg_name(algo), os(os) {

    }

    Router(vector<string> seqs, ostream& os, string algo, string alphasets, string params)
     :seqs(seqs), os(os), alg_name(algo), alphabet_set(alphasets), alg_extra_params(params)
    {

    }
    
    Router(string filename, ostream& os, string algo, string alphasets, string params);
    
    ~Router(){}
    
    void connect();
    void help_message();
    
private:
    vector<string> seqs;
    string instance_file_name;
    ostream& os;
    string alg_name;
    string alphabet_set;
    string alg_extra_params;

};

typedef function<int(vector<string>&, string&, ostream&, string)> ExeFunc;
typedef function<void(void)> HelpFunc;

struct Alg_Module{

    string name;
    ExeFunc exe_func;
    HelpFunc help_func;

};

#define MAX_MODULES_NUM 128

extern const Alg_Module Alg_Module_Array[MAX_MODULES_NUM];

#endif //ROUTE_H