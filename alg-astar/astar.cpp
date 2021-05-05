#include <sstream>
#include "astar.h"

static bool opt = false;
static int maxlen = 0;
static int optlen = 0; // the length of the best solution

ASTAR::ASTAR(vector<string>& seqs, string& alphabets){

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    phash_init(seqs.size(), 1000000);
    this->seqs = seqs;
    SucTabs = cal_suc_tabs(seqs, cmap);
    ScoreTabs = cal_score_tabs(seqs);

}

void ASTAR::run(){

    queue_type Q;
    HashSet nodes;
    Point<CordType> *p0 = new Point<CordType>(g_point_size, false, 0);

    PSETATTR(p0, new AstarAttr(UpperBound_by_ScoreTabs(p0, ScoreTabs), 0, UpperBound_by_ScoreTabs(p0, ScoreTabs), NULL));
    Q.push(p0);
    nodes.insert(p0);

    while (!opt){

        // pop a point from Qs_i
        int level;
        Point<CordType> *point = Q.top();

        Q.pop();
        level = ATTR(AstarAttr, point)->g;
        // calculate a point
        //cout << num << ": ";
        //point->print(g_point_size, '\t');
        //cout << "f: "  << ATTR(PAstarAttr, point)->f << " g: " << ATTR(PAstarAttr, point)->g << " ex: " \
        //     << ATTR(PAstarAttr, point)->ex << " segnum: " << ATTR(PAstarAttr, point)->segnum << endl; 
        for(int i = 0; i < SucTabs[0].size(); i++){
            Point<CordType> *suc = successor(point, SucTabs, i);
            if(suc){
                auto q = nodes.insert(suc);
                if (q.second) { // a new point
                    int ex = UpperBound_by_ScoreTabs(suc, ScoreTabs);
                    AstarAttr *sucAttr = new AstarAttr(level + ex + 1, level + 1, ex, point);
                    PSETATTR(suc, sucAttr);
                    Q.push(suc);
                }
                else {
                    Point<CordType> *ep = *(q.first);
                    if(level + 1 > ATTR(AstarAttr, ep)->g){
                        ATTR(AstarAttr, ep)->g = level + 1;
                        ATTR(AstarAttr, ep)->f = level + 1 + ATTR(AstarAttr, ep)->h;
                        ATTR(AstarAttr, ep)->parent = point;
                        Q.push(ep);
                    }
                    delete suc;
                }
            }
        }
        if(ATTR(AstarAttr, point)->h == 0){ // a completed point
            opt = true;
            find_lcs(point);
        }

    }

    cout << "Q : " << Q.size() << endl;
    cout << "h : " << nodes.size() << endl;

}

int ASTAR::find_lcs( Point<CordType>* p ) {
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
        else return PARAM_ERR;
    }

    return NORMAL_EXIT;

}

void astar_help_func(){

	cout << endl;
    cout << "Information for ASTAR:\n" << endl;
    cout << "Description:" << endl;
    cout << "\t" << endl;
    cout << "commmand:" << endl;
    cout << "\tLCSCalculator -A astar [-i input][-o output][-a alphabets][-e \"[l]\"]" << endl;
    cout << "someelse parameters:" << endl;
    cout << "\tl: the length of the optimal solution(unknown as default)." << endl;
    cout << endl;

}

int astar_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	ASTAR astar(seqs, alphabet_set);
	string lcs;
	optlen = 0;

	if(getparams(params) != NORMAL_EXIT){
		cout << "extra parameters error." << endl;
		return PARAM_ERR;
	}

	clock_t start_t, end_t;

	start_t = clock();

	astar.run();

	end_t = clock();

	lcs = astar.get_lcs();
	os << "Result(by " << "astar" << "):\n";
	os << "time(us) : " << end_t - start_t << "\n";
	os << "the length of lcs : " << lcs.length() << "\n";
	os << "a lcs : " << lcs << "\n";
	return 0;

	return NORMAL_EXIT;

}
