#include <sstream>
#include "mlcsapp.h"

static int constc = 20;
static int constk = 2000;

MLCSAPP::MLCSAPP(vector<string>& seqs, string& alphabets){

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    phash_init(seqs.size(), 1000000);
    this->seqs = seqs;
    SucTabs = cal_suc_tabs(seqs, cmap);
    ScoreTabs = cal_score_tabs(seqs);

}

int MLCSAPP::find_lcs( Point<CordType>* p ) {
    while(p->cord[0] != 0){
        lcs = seqs[0][p->cord[0] - 1] + lcs;
        p = ATTR(AstarAttr, p)->parent;
    }
    return lcs.length();
}

void MLCSAPP::run(){

    HashSet nodeset(constk);
    vector< vector< Point<CordType>* > > trash;
    Point<CordType> *p0 = new Point<CordType>(seqs.size(), false, 0);
    bool flag = true;
    int iter = 0;

    PSETATTR(p0, new AstarAttr(UpperBound_by_ScoreTabs(p0, ScoreTabs), 0, UpperBound_by_ScoreTabs(p0, ScoreTabs)));
    nodeset.insert(p0);

    while(nodeset.size() > 0) {
        vector< Point<CordType>* > nodeset_t;
        int maxf = 0;

        for(auto& p : nodeset){
            if(ATTR(AstarAttr, p)->f > maxf) maxf = ATTR(AstarAttr, p)->f;
        }
        for(auto& p : nodeset){
            if(ATTR(AstarAttr, p)->f >= (maxf - constc)){
                nodeset_t.push_back(p);
            }
            else{
                delete ATTR(AstarAttr, p);
                delete p;
            }
        }

        sort(nodeset_t.begin(), nodeset_t.end(), AstarAttrPri());
        if(nodeset_t.size() > constk){
            for(unsigned int i = nodeset_t.size() - 1; i > constk; i--){
                delete ATTR(AstarAttr, nodeset_t.back());
                delete nodeset_t.back();
                nodeset_t.pop_back();
            }
        }

        trash.push_back(nodeset_t);
        nodeset.clear();
        flag = true;
        for(auto& p : nodeset_t){
            if (ATTR(AstarAttr, p)->h != 0) { // h(p) != 0
                flag = false;
            }

            for(int i = 0; i < SucTabs[0].size(); i++) {
                Point<CordType> *suc = successor(p, SucTabs, i);
                if(suc){
                   auto q = nodeset.find(suc);
                    if (q != nodeset.end()) { //node is already in node set
                        AstarAttr *sucAttr = ATTR(AstarAttr, (*q));
                        if ( sucAttr->g < ATTR(AstarAttr, p)->g + 1) {
                            sucAttr->parent = p;
                            sucAttr->g = ATTR(AstarAttr, p)->g + 1;
                            sucAttr->f = sucAttr->g + sucAttr->h;
                        }
                        delete suc;
                    }
                    else {
						int ex = UpperBound_by_ScoreTabs(suc, ScoreTabs);
                        PSETATTR(suc, new AstarAttr(ATTR(AstarAttr, p)->g + 1 + ex, ATTR(AstarAttr, p)->g + 1, ex, p));
                        nodeset.insert(suc);
                    }
                }
            }
        }
        iter++;
        if(flag || nodeset.size() == 0) break;
    }

    find_lcs(trash.back()[0]);
    // trash.back()[0]->print(seqs.size());
    for(auto& vec : trash){
        for(auto& p : vec){
            delete ATTR(AstarAttr, p);
        }
    }
    cout << "loop: " << iter << endl;

}

MLCSAPP::~MLCSAPP(){

}

static int getparams(string& params){

    istringstream is(params);
    string opt;

    while(is >> opt){
        if(opt == "k") is >> constk;
        else if(opt == "c") is >> constc;
        else return PARAM_ERR;
    }

    return NORMAL_EXIT;

}

void mlcsapp_help_func(){

	cout << endl;
    cout << "Information for MLCSAPP:\n" << endl;
    cout << "Description:" << endl;
    cout << "\tThis algorithm is re-implemented according to the article  \"A Fast Heuristic Search Algorithm for Finding \
the Longest Common Subsequence of Multiple Strings\". This is a variant for A* algorithm." << endl;
    cout << "commmand:" << endl;
    cout << "\tLCSCalculator -A mlcsapp [-i input][-o output][-a alphabets][-e \"[k|c]\"]" << endl;
    cout << "someelse parameters:" << endl;
    cout << "\tk: The number of points maintained in the algorithm." << endl;
    cout << "\tc: The difference between the level of the best point and the level of the worst point." << endl;
    cout << endl;

}
int mlcsapp_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	if(getparams(params) == PARAM_ERR){
		cout << "extra parameter error" << endl;
		return PARAM_ERR;
	}
	else if (getparams(params) != NORMAL_EXIT)
	{
		return UNEXPECTED_ERR;
	}
	

	MLCSAPP mlcsapp(seqs, alphabet_set);
	string lcs;
	clock_t start_t, end_t;

	start_t = clock();
	mlcsapp.run();
	end_t = clock();
	lcs = mlcsapp.get_lcs();
	os << "Result(by " << "mlcsapp" << "):\n";
	os << "time(us) : " << end_t - start_t << "\n";
	os << "the length of lcs : " << lcs.length() << "\n";
	os << "a lcs : " << lcs << "\n";

	os << "checking result ...\t";
	if(result_check(seqs, lcs)){
		os << "ok" << endl;
	}
	else{
		os << "false" << endl;
	}

	return NORMAL_EXIT;

}
