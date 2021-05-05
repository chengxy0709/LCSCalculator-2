#ifndef TEST_H
#define TEST_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "errdef.h"
#include "point.h"

using namespace std;

void test_help_func();
int test_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);


#endif //TEST_H
