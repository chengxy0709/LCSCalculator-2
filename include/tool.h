#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <math.h>

#include "point.h"

using namespace std;

// return a map for a alphabet set and index
unordered_map<char, int> build_alphabet_map(string& alphabets);

// return a successor table or tables
vector< vector<int> > cal_suc_tab(string& seq, unordered_map<char, int>& cmap, bool disp = false);
vector< vector< vector<int> > > cal_suc_tabs(vector<string>& seqs, unordered_map<char, int>& cmap, bool disp = false);

// return a count table or tables
vector< vector<int> > cal_count_tab(string& seq, unordered_map<char, int>& cmap, bool disp = false);
vector< vector< vector<int> > > cal_count_tabs(vector<string>& seqs, unordered_map<char, int>& cmap, bool disp = false);
// evaluate a point by count tables
int UpperBound_by_CountTabs(Point<CordType> *p, vector< vector< vector<int> > >& CountTabs);

// return a set of score tables
vector< vector< vector<int> > > cal_score_tabs(vector<string>& seqs);
// evaluate a point by score tables
int UpperBound_by_ScoreTabs(Point<CordType> *p, vector< vector< vector<int> > >& ScoreTabs);

// return a dist value
int cal_manhattan_dist(Point<CordType> *p);

// return the k-norm of a point
double cal_k_norm(vector<string>& seqs, const Point<CordType>* p, double k);

// return a pr table
vector< vector<double> > cal_pr_tab(int p, int q, int sigSize);

// evaluate a point by a Pr Table
double UpperBound_by_PrTab(const Point<CordType>* p, int sigSize, vector<string>& seqs, vector< vector<double> >& P);

// return a successor by using SucTables
Point<CordType>* successor(Point<CordType>* p, vector< vector< vector<int> > >& SucTabs, int i);
// is p the successor of q ? 
bool is_successor(Point<CordType>* p, Point<CordType>* q, int num = g_point_size);
// is p the immediate successor of q ? 
bool is_immediate_successor(Point<CordType>* p, Point<CordType>* q , vector< vector< vector<int> > >& SucTabs);

void Qsort(vector< Point<CordType>* >& arr, int low, int high, int dim);
int Qmedian(vector< Point<CordType>* >& arr, int dim);
int vmax(vector< Point<CordType>* >& arr, int dim);

// A and B are two sorted vectors in dim, and the function mergeSortedVecter can merge the two vectors
// by this order.
vector<Point<CordType>*> mergeSortedVecter(vector<Point<CordType>*>& A, vector<Point<CordType>*>& B, int dim);
// Compare with mergeSortedVecter, mergeSortedSet will not add twice for a point which [dim:last] part in A is equal to B 
vector<Point<CordType>*> mergeSortedSet(vector<Point<CordType>*>& A, vector<Point<CordType>*>& B, int dim, int pointsize = g_point_size);

#endif //TOOL_H