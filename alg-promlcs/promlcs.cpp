#include <sstream>
#include "promlcs.h"

static int scnum = 1; // The number of calculating point in a single iteration

class Layer{

public:
    Layer(int d){dtree.setD(d);order = 0;}
    ~Layer(){
        while(!priq.empty()){
            delete priq.top();
            priq.pop();
        }
    }

    void setOrder(int ord){order = ord;}
    int getOrder() const {return order;}
    void addpriq(Point<CordType> *p){priq.push(p);}
    Point<CordType>* rmpriq(){
        Point<CordType> *p = priq.top();
        priq.pop();
        return p;
    }
    bool addDtree(Point<CordType> *p){
        if(dtree.Search(p, dtree.getRoot())){
            dtree.Insert(p, dtree.getRoot());
            return true;
        }
        else return false;
    }
    bool isPriqEmpty(){return priq.empty();}
    void printInfo(){
        cout << priq.size() << endl;
        //dtree.traverse(dtree.getRoot());
    }

private:
    priority_queue<Point<CordType>*, vector< Point<CordType>* >, AttrPri> priq;
    int order;
    Dtree dtree;

};

PROMLCS::PROMLCS(vector<string> seqs, string alphabets)
 : seqs(seqs),alphaSize(alphabets.length())
{

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    SucTabs = cal_suc_tabs(seqs, cmap);
    SU = cal_count_tabs(seqs, cmap);

}

void PROMLCS::run(){

    list<Layer*> layers;
    list<Layer*>::iterator lbeginIter;
    list<Layer*>::iterator lendIter;
    list<Layer*>::iterator curIter;

    int Lapp = 0;

    Point<CordType> *p = new Point<CordType>(seqs.size(), false, 0);
    Layer *layer = new Layer(seqs.size());

    SETATTRINT(p, 0);
    layer->addpriq(p);

    layers.push_back(layer);
    lbeginIter = layers.begin();
    curIter = layers.begin();
    lendIter = layers.begin();

    Lapp = 0;

    while(1){
        int m = 0;
        Layer *cur = *curIter;
        auto cur_next = curIter;
        cur_next++;
        while(!cur->isPriqEmpty()){
            p = cur->rmpriq();
            if(cal_g_val(p, cur->getOrder()) > Lapp && cur->addDtree(p)){
                m++;
                for(int i = 0; i < alphaSize; ++i){
                    Point<CordType> *suc = successor(p, SucTabs, i);
                    if(suc){
                        if(curIter == lendIter){
                            layer = new Layer(seqs.size());
                            layer->setOrder(cur->getOrder() + 1);
                            layers.push_back(layer);
                            Lapp++;
                            lendIter++;
                            cur_next = lendIter;
                        }
                        (*cur_next)->addpriq(suc);
                    }
                }
            }
            else{
                delete p;    // be careful of this statement.
                            // Don't delete a point that has already been stored in d-tree.
            }
            if(m == scnum){
                break;
            }   
        }
        if(lbeginIter == lendIter){
            break;
        }   
        if(curIter == lbeginIter && cur->isPriqEmpty()){
            lbeginIter++;
        }   
        if(curIter != lendIter){
            curIter++;
        }   
        else{
            break;
            curIter = lbeginIter;
        }
    //    cout << "cur: " << (*curIter)->getOrder() << endl;
    //    cout << "begin: " << (*lbeginIter)->getOrder() << endl;
    //    cout << "end: " << (*lendIter)->getOrder() << endl;
    }
    
    cout << "The length of LCS is " << Lapp << " ." << endl;

    // free memory
    for(auto& l : layers){
        delete l;
    }

}

int getparams(string& params){

    istringstream is(params);
    string opt;

    while(is >> opt){
        if(opt == "s") is >> scnum;
        else return PARAM_ERR;
    }

    return NORMAL_EXIT;

}

void promlcs_help_func(){

    cout << endl;
    cout << "Information for PROMLCS:\n" << endl;
    cout << "Description:" << endl;
    cout << "\tThis algorithm is re-implemented according to the article  \"A New Progressive Algorithm for a Multiple \
Longest Common Subsequences Problem and Its Efficient Parallelization. And this program only calculates the length of \
the optimal solution in a single iteration. You can specify the number of points calculated in sub iteration by using \
parameter s." << endl;
    cout << "commmand:" << endl;
    cout << "\tLCSCalculator -A promlcs [-i input][-o output][-a alphabets][-e \"[s]\"]" << endl;
    cout << endl;

}
int promlcs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){
 
	if(getparams(params) != NORMAL_EXIT){
		cout << "extra parameters error." << endl;
		return PARAM_ERR;
	}

	PROMLCS promlcs(seqs, alphabet_set);
	clock_t start_t, end_t;

	start_t = clock();
	promlcs.run();
	end_t = clock();
	os << "time(us) : " << end_t - start_t << "\n";

	return NORMAL_EXIT;

}
