#include "wdag.h"

WDAG::WDAG(vector<string>& seqs, string alphabets):seqs(seqs){

    unordered_map<char, int> cmap = build_alphabet_map(alphabets);
    phash_init(seqs.size());
    cal_nums_and_merge_char();
    SucTabs = cal_suc_tabs(seqms, cmap);
    cal_weights();

}

void WDAG::cal_nums_and_merge_char(){

    for(int i = 0; i < seqs.size(); i++){
        int now = 0;
        nums.push_back(vector<int>{1});
        seqms.push_back(string());
        seqms[i] += seqs[i][now];
        for(int j = 1; j < seqs[i].length(); j++){
            if(seqs[i][j] == seqms[i][now]){
                nums[i][now]++;
            }
            else{
                nums[i].push_back(1);
                seqms[i] += seqs[i][j];
                now++;
            }
        }
    }

    /*cout << "nums:\n";
    for(auto& vec : nums){
        for(auto v : vec){
            cout << v << "\t";
        }
        cout << endl;
    }*/

}
void WDAG::cal_weights(){

    for(int i = 0; i < seqms.size(); i++){
        int len = seqms[i].length();
        Weights.push_back(vector< vector<int> >(len + 1, vector<int>(len + 1, 0)));
        for(int j = 1; j <= len; j++) Weights[i][0][j] = 1;
        for(int j = 1; j <= len; j++){
            int sum = 0;
            for(int k = j; k < len; k++){
                if(seqms[i][k - 1] == seqms[i][j - 1]) sum += nums[i][k - 1];
                Weights[i][j][k + 1] = sum;
            }
        }
    }

    /*cout << "Weight:\n";
    for(auto& W : Weights){
        for(auto& vec : W){
            for(auto v : vec){
                cout << v << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }*/

}

int  WDAG::weight(int p, int k){
    Point<CordType> *pp = DM.at(p);
    Point<CordType> *kk = DM.at(k);
    int res = INT32_MAX;
    if(k == 1){ // Inf Point
        int sum = 0;
        for(int i = 0; i < seqms.size(); i++){
            sum = 0;
            for(int j = pp->cord[i] - 1; j < nums[i].size(); j++){
                if(seqms[i][j] == seqms[i][pp->cord[i] - 1])
                    sum += nums[i][j];
            }
            if(sum < res) res = sum;
        }
    }
    else{
        for(int i = 0; i < seqms.size(); i++){
            if(Weights[i][pp->cord[i]][kk->cord[i]] < res)
                res = Weights[i][pp->cord[i]][kk->cord[i]];
        }
    }
    return res;
}

void WDAG::run(){

    string LCSRecord;
    cout << "Constructing WDAG..." << endl;
    construct_WDAG();
    cout << "The number of points : " << DM.size() << endl;
    cout << "Calculating the level of each point..." << endl;
    determine_levels();
    cout << "Generating MLCS..." << endl;
    GetMLCS(LCSRecord, 1);
    for(auto& lcs : mlcs){
        reverse(lcs.begin(), lcs.end());
    }

}

void WDAG::GetMLCS(string& LCSRecord, int index){

    if(index == 0){
        mlcs.push_back(LCSRecord.substr(0, LCSRecord.length() - 1));
        return;
    }

    for(auto p : precursor[index]){
        Point<CordType> *q = DM.at(p);
        int w = weight(p, index);
        for(int i = 0; i < w; i++)
            LCSRecord += seqms[0][q->cord[0] - 1];
        GetMLCS(LCSRecord, p);
        LCSRecord = LCSRecord.substr(0, LCSRecord.length() - w);
    }

}
void WDAG::construct_WDAG(){

    queue<int> Q;
    Point<CordType> *p = new Point<CordType>(seqms.size(), false, 0);
    int InfIndex = 0;

    DM.insert(p);
    Q.push(DM.at(p));
    Indegree.push_back(0);
    p = new Point<CordType>(seqms.size(), false, seqms[0].length() + 2);
    DM.insert(p);
    Indegree.push_back(0);
    InfIndex = DM.at(p);
    Edge = vector< list<int> >(DM.size(), list<int>());

    while(!Q.empty()){
        int index = Q.front();
        bool hasSuc = false;
        p = DM.at(index);
        for(int i = 0; i < SucTabs[0].size(); i++){
            Point<CordType> *suc = successor(p, SucTabs, i);
            if(suc){
                bool flag = DM.insert(suc);
                int index_t = DM.at(suc);
                Edge[index].push_back(index_t);
                if(flag) {
                    Q.push(index_t);
                    Indegree.push_back(1);
                }
                else{
                    Indegree[index_t]++;
                    delete suc;
                }
                hasSuc = true;
            }
        }
        if(hasSuc)
            Edge.resize(DM.size());
        else{
            Edge[index].push_back(InfIndex);
            Indegree[InfIndex]++;
        }
        Q.pop();
    }

}

void WDAG::determine_levels(){

    queue<int> Q;

    Q.push(0);
    Level = vector<int>(DM.size(), 0);
    precursor = vector< list<int> >(DM.size(), list<int>());

    while(!Q.empty()){
        int p = Q.front();
        for(auto& k : Edge[p]){
            int w = weight(p, k);
            if(Level[p] + w > Level[k]){
                precursor[k].clear();
                precursor[k].push_back(p);
                Level[k] = Level[p] + w;
            }
            else if(Level[p] + w == Level[k]){
                precursor[k].push_back(p);
            }
            Indegree[k]--;
            if(Indegree[k] == 0) Q.push(k);
        }
        Q.pop();
    }

}

void wdag_help_func(){

}
int wdag_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){

	return NORMAL_EXIT;

}
