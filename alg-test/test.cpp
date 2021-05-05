#include "test.h"
#include "tool.h"
#include "quickdp.h"

void test_help_func(){

}
int test_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	// for your test

	// test for point.h
	// Point<CordType> *p1 = new Point<CordType>(3);
	// Point<CordType> *p2 = new Point<CordType>({1,2,3});
	// Point<CordType> *p3 = new Point<CordType>(3, true, 10);

	// vector<Point<CordType>*> vec;
	// vec.push_back(p1);
	// vec.push_back(p2);
	// vec.push_back(p3);

	// psprint< vector<Point<CordType>*> >(vec, 3, 2);


	// test for tool.cpp
	// use a simple case in main.cpp
	// unordered_map<char, int> alpha_map = build_alphabet_map(alphabet_set);
	// for(auto item : alpha_map){
	// 	cout << item.first << " : " << item.second << endl;
	// }

	// cout << "Successor Tables" << endl;
	// vector< vector< vector<int> > > SucTabs =  cal_suc_tabs(seqs, alpha_map, true);
	// Point<CordType> *p = new Point<CordType>({2,3,1});
	// Point<CordType> *suc = successor(p, SucTabs, alpha_map['G']);
	// p->print();
	// suc->print();
	// cout << "is suc the successor of p ? " << is_successor(suc, p) << endl;
	// cout << "is suc the immediate successor of p ? " << is_immediate_successor(suc, p, SucTabs) << endl;

	// cout << "Count Tables" << endl;
	// vector< vector< vector<int> > > CountTabs =  cal_count_tabs(seqs, alpha_map, true);
	// Point<CordType> *p = new Point<CordType>({3,4,3});
	// p->print();
	// cout << "evaluate by CountTabs: " << UpperBound_by_CountTabs(p, CountTabs) << endl;
	
	// cout << "Score Tables" << endl;
	// vector< vector< vector<int> > > ScoreTabs =  cal_score_tabs(seqs);
	// for (auto& ScoreTab : ScoreTabs)
	// {
	// 	for(auto& line : ScoreTab){
	// 		for(auto item : line){
	// 			cout << item << '\t';
	// 		}
	// 		cout << endl;
	// 	}
	// 	cout << endl;
	// }
	// Point<CordType> *p = new Point<CordType>({3,4,3});
	// p->print();
	// cout << "evaluate by ScoreTabs: " << UpperBound_by_ScoreTabs(p, ScoreTabs) << endl;

	// vector<Point<CordType>*> vec;
	// for(int i = 0; i < 10; i++){
	// 	vec.push_back(new Point<CordType>(3, true, 10));
	// }
	// psprint< vector<Point<CordType>*> >(vec, 3);
	// cout << "median, dim 1 : " << Qmedian(vec, 1) << endl;
	// cout << "max, dim 1 : " << vmax(vec, 1) << endl;
	// vector<Point<CordType>*> vec1;
	// for(int i = 0; i < 10; i++){
	// 	vec1.push_back(new Point<CordType>(3, true, 10));
	// }
	// Qsort(vec, 0, vec.size() - 1, 1);
	// Qsort(vec1, 0, vec1.size() - 1, 1);
	// cout << "after sort:" << endl;
	// psprint< vector<Point<CordType>*> >(vec, 3);
	// auto vecs = mergeSortedVecter(vec, vec1, 1);
	// cout << "sorted vec1:" << endl;
	// psprint< vector<Point<CordType>*> >(vec1, 3);
	// cout << "vec + vec1 :" << endl;
	// psprint< vector<Point<CordType>*> >(vecs, 3);
	// vec1.push_back(new Point<CordType>({8, 7, 9}));
	// Qsort(vec1, 0, vec1.size() - 1, 1);
	// vecs = mergeSortedSet(vec, vec1, 1);
	// psprint< vector<Point<CordType>*> >(vec1, 3);
	// psprint< vector<Point<CordType>*> >(vecs, 3);

	// test for QuickDP's Minima
	// vector< Point<CordType>* > vec;
	// g_point_size = 4;
	// for(int i = 0; i < 20; i++){
	// 	vec.push_back(new Point<CordType>(g_point_size, true, 20));
	// }
	// psprint(vec, 4);
	// auto res = QUICKDP().Minima(vec, 4);
	// psprint(res, 4);

	return NORMAL_EXIT;

}
