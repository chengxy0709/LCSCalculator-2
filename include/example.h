#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "errdef.h"

using namespace std;

void example_help_func();
int example_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //EXAMPLE_H
