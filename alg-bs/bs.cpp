#include <sstream>
#include "bs.h"

static bool opt = false;
static int maxlen = 0;
static int optlen = 0; // the length of the best solution

static int bw = 500;
static int kf = 10;

BS::BS(vector<string>& seqs, string& alphabets){

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    phash_init(seqs.size(), 1000000);
    this->seqs = seqs;
    SucTabs = cal_suc_tabs(seqs, cmap);
    ScoreTabs = cal_score_tabs(seqs);

}

void BS::run(){

    HashSet nodes;
    Point<CordType> *p0 = new Point<CordType>(g_point_size, false, 0);
    vector< Point<CordType>* > B;

    PSETATTR(p0, new AstarAttr(UpperBound_by_ScoreTabs(p0, ScoreTabs), 0, UpperBound_by_ScoreTabs(p0, ScoreTabs), NULL));
    nodes.insert(p0);
    B.push_back(p0);

    while (B.size() != 0){

        HashSet Vext;

        for(auto point : B){

            int level = ATTR(AstarAttr, point)->g;
            bool hasSuccessor = false;

            for(int i = 0; i < SucTabs[0].size(); i++){
                Point<CordType> *suc = successor(point, SucTabs, i);
                if(suc){
                    auto q = nodes.insert(suc);
                    hasSuccessor = true;
                    if (q.second) { // a new point
                        int ex = UpperBound_by_ScoreTabs(suc, ScoreTabs);
                        AstarAttr *sucAttr = new AstarAttr(level + ex + 1, level + 1, ex, point);
                        PSETATTR(suc, sucAttr);
                        Vext.insert(suc);
                    }
                    else {
                        Point<CordType> *ep = *(q.first);
                        if(level + 1 > ATTR(AstarAttr, ep)->g){
                            ATTR(AstarAttr, ep)->g = level + 1;
                            ATTR(AstarAttr, ep)->f = level + 1 + ATTR(AstarAttr, ep)->h;
                            ATTR(AstarAttr, ep)->parent = point;
                            Vext.insert(ep);
                        }
                        delete suc;
                    }
                }
            }
            if(!hasSuccessor){
                string lcs_t = lcs;
                lcs.clear();
                find_lcs(point);
                if(lcs.length() < lcs_t.length()){
                    lcs = lcs_t;
                }
            }
        }
        Filter(Vext, kf);
        B = Reduce(Vext, bw);
        //cout << num << ": ";
        //point->print(g_point_size, '\t');
        //cout << "f: "  << ATTR(PASAttr, point)->f << " g: " << ATTR(PASAttr, point)->g << " ex: " \
        //     << ATTR(PASAttr, point)->ex << " segnum: " << ATTR(PASAttr, point)->segnum << endl; 

    }

    cout << "h : " << nodes.size() << endl;

}

void BS::Filter(HashSet& Vext, int Kfilter){

    queue_type Q;

    for(auto p : Vext){
        if(Q.size() > Kfilter){
            Q.pop();
        }
        Q.push(p);
    }

    while(Q.size() > Kfilter) Q.pop();
    while(Q.size() > 0){
        auto i = Vext.begin();
        while(i != Vext.end() ){
            if(is_successor(*i, Q.top(), seqs.size())){
                i = Vext.erase(i);
            }
            else i++;
        }
        Q.pop();
    }

}

vector< Point<CordType>* > BS::Reduce(HashSet& Vext, int beta){

    vector< Point<CordType>* > res;

    if(beta > Vext.size()){
        res = vector< Point<CordType>* >(Vext.begin(), Vext.end());
    }
    else{
        res = vector< Point<CordType>* >(Vext.begin(), Vext.end());
        sort(res.begin(), res.end(), AstarAttrPrih());
        res.erase(res.begin() + beta, res.end());
    }

    return res;

}

int BS::find_lcs( Point<CordType>* p ) {
    while(p->cord[0] != 0){
        lcs = seqs[0][p->cord[0] - 1] + lcs;
        p = ATTR(AstarAttr, p)->parent;
    }
    return lcs.length();
}

static int getparams(string& params){

    istringstream is(params);
    string opt;

    while(is >> opt){
        if(opt == "l") is >> optlen;
        else if(opt == "b") is >> bw;
        else if(opt == "k") is >> kf;
        else return -1;
    }

    return 0;

}

void bs_help_func(){

	cout << endl;
    cout << "Information for BS:\n" << endl;
    cout << "Description:" << endl;
    cout << "\t" << endl;
    cout << "commmand:" << endl;
    cout << "\tLCSCalculator -A bs [-i input][-o output][-a alphabets][-e \"[l|b|k]\"]" << endl;
    cout << "someelse parameters:" << endl;
    cout << "\tl: the length of the optimal solution(unknown as default)." << endl;
	cout << "\tb: beta, beam size." << endl;
    cout << "\tk: Kfliter, the number of the best point in function 'Select'." << endl;
    cout << endl;

}
int bs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	BS bs(seqs, alphabet_set);
	string lcs;

	if(getparams(params) != NORMAL_EXIT){
		cout << "extra parameters error." << endl;
		return PARAM_ERR;
	}

	clock_t start_t, end_t;

	start_t = clock();

	bs.run();

	end_t = clock();

	lcs = bs.get_lcs();
	os << "Result(by " << "bs" << "):\n";
	os << "time(us) : " << end_t - start_t << "\n";
	os << "the length of lcs : " << lcs.length() << "\n";
	os << "a lcs : " << lcs << "\n";

	return NORMAL_EXIT;

}
