#include "topmlcs.h"

TOPMLCS::TOPMLCS(vector<string>& seqs, string& alphabets){

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    phash_init(seqs.size());
    SucTabs = cal_suc_tabs(seqs, cmap);
    this->seqs = seqs;

}

int TOPMLCS::construct_ICSG(){

    Point<CordType> *p0 = new Point<CordType>(SucTabs.size(), false, 0);
    queue< Point<CordType>* > Q;
    int index = 0;

    Q.push(p0);
    DM.insert(p0);
    ID.push_back(0);

    while(!Q.empty()){
        Point<CordType> *p = Q.front();
        for(int i = 0; i < SucTabs[0].size(); ++i){
            Point<CordType> *suc = successor(p, SucTabs, i);
            if(suc){
                if(DM.insert(suc)){
                    Q.push(suc);
                    ID.push_back(1);
                }
                else{
                    int index_t = DM.at(suc);
                    ID[index_t] = ID[index_t] + 1;
                    delete suc;
                }
            }
        }
        Q.pop();
        index++;
    }

    Point<CordType> *pinf = new Point<CordType>(SucTabs.size(), false, -1);
    DM.insert(pinf);

    return DM.size();

}

int TOPMLCS::forward_top_sort(int maxIndex){

    vector<int> D{0};
    tlevel = vector<int>(maxIndex, 0);
    precursor = vector< list<int> >(maxIndex, list<int>());

    int k = 0;

    while(D.size()){
        vector<int> Dt;
        for(auto index : D){
            bool hasSuccessor = false;
            Point<CordType> *p = DM.at(index);
            for(int i = 0; i < SucTabs[0].size(); ++i){
                Point<CordType> *suc = successor(p, SucTabs, i);
                if(suc){
                    int index_t = DM.at(suc);
                    hasSuccessor = true;
                    tlevel[index_t] = k + 1;
                    if(is_immediate_successor(suc, p, SucTabs)){
                        precursor[index_t].push_back(index);
                    }
                    ID[index_t] = ID[index_t] - 1;
                    if(ID[index_t] == 0){
                        Dt.push_back(index_t);
                    }
                    delete suc;
                }
            }
            if(!hasSuccessor){
                precursor[maxIndex - 1].push_back(index);
            }
        }
        k = k + 1;
        D = Dt;
    }
    tlevel[maxIndex - 1] = k;

    return k - 1;

}



void TOPMLCS::backward_top_sort(int maxlevel, int pinf_index){

    vector<int> D{pinf_index};
    int k = 0;

    while(D.size() != 0){
        vector<int> Dt;
        for(auto q : D){
            for(auto p = precursor[q].begin(); p != precursor[q].end();){
                if(tlevel[*p] + k != maxlevel){
                    p = precursor[q].erase(p);
                }
                else{
                    Dt.push_back(*p);
                    p++;
                }
            }
        }
        D = Dt;
        k = k + 1;
    }

}
void TOPMLCS::run(){

    int maxIndex, maxlevel;
    string LCSRecord;

    maxIndex = construct_ICSG();
    cout << "The number of points Generated is " << maxIndex << " ." << endl;
    maxlevel = forward_top_sort(maxIndex);
    cout << "The maximal level of points is " << maxlevel << " ." << endl;
    backward_top_sort(maxlevel, maxIndex - 1);
    cout << "Generating MLCS..." << endl;
    find_mlcs(LCSRecord, maxIndex - 1);
    for(string& lcs : mlcs){
        reverse(lcs.begin(), lcs.end());
    }

}

void TOPMLCS::find_mlcs(string& LCSRecord, int index){

    if(index == 0){
        mlcs.push_back(LCSRecord.substr(0, LCSRecord.length() - 1));
        return;
    }

    for(auto p : precursor[index]){
        Point<CordType> *q = DM.at(p);
        LCSRecord += seqs[0][q->cord[0] - 1];
        find_mlcs(LCSRecord, p);
        LCSRecord = LCSRecord.substr(0, LCSRecord.length() - 1);
    }

}

TOPMLCS::~TOPMLCS(){


}

void topmlcs_help_func(){

	cout << endl;
    cout << "Information for TOPMLCS:\n" << endl;
    cout << "Description:" << endl;
    cout << "\tThis algorithm is re-implemented according to the article  \"A Novel Fast and Memory Efficient Parallel \
MLCS Algorithm for Long and Large-Scale Sequences Alignments\"." << endl;
    cout << "commmand:" << endl;
    cout << "\tLCSCalculator -A topmlcs [-i input][-o output][-a alphabets]" << endl;
    cout << endl;

}

int topmlcs_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	TOPMLCS topmlcs(seqs, alphabet_set);
    vector<string> mlcs;
    clock_t start_t, end_t;

	start_t = clock();
	topmlcs.run();
	end_t = clock();
	mlcs = topmlcs.get_mlcs();
	os << "Result(by " << "topmlcs" << "):\n";
	os << "time(us) : " << end_t - start_t << "\n";
	os << "the length of lcs : " << mlcs[0].length() << "\n";
	os << "all lcs : \n";
	for(int i = 0; i < mlcs.size(); i++){
		os << i << " : " << mlcs[i] << "\n";
	}

	return NORMAL_EXIT;

}
