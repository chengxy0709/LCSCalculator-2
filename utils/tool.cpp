#include "tool.h"

unordered_map<char, int> build_alphabet_map(string& alphabets){
    unordered_map<char, int> cmap;
    for(int i = 0; i < alphabets.length(); i++){
        cmap.insert(make_pair(alphabets[i], i));
    }
    return cmap;
}

vector< vector<int> > cal_suc_tab(string& seq, unordered_map<char, int>& cmap, bool disp){
    int len = seq.length();
    vector< vector<int> > SucTab(cmap.size(), vector<int>(len + 1));

    // calculate successor table
    for (int i = 0; i < cmap.size(); i++) {
        SucTab[i][len] = -1;
    }

    for (int j = len - 1; j >= 0; j--) {
        for (int i = 0; i < cmap.size(); i++) {
            SucTab[i][j] = SucTab[i][j + 1];
        }
        SucTab[cmap[seq[j]]][j] = j + 1;
    }

    if(disp){
        cout << "\n  | \t\t";
        for(int i = 0; i < len; i++) cout << seq[i] << "\t";
        cout << endl;
        for(int i = 0; i < len + 2; i++) cout << "--" << "\t";
        cout << endl;
        for (auto m : cmap) {
            cout << m.first << " | \t";
            for (int j = 0; j <= len; j++) {
                cout << SucTab[m.second][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return SucTab;
}

vector< vector< vector<int> > > cal_suc_tabs(vector<string>& seqs, unordered_map<char, int>& cmap, bool disp){
    
    vector< vector< vector<int> > > SucTabs;
    for(auto& seq : seqs){
        SucTabs.push_back(cal_suc_tab(seq, cmap, disp));
    }
    return SucTabs;
    
}

vector< vector<int> > cal_count_tab(string& seq, unordered_map<char, int>& cmap, bool disp){
    int len = seq.length();
    vector< vector<int> > CountTab(cmap.size(), vector<int>(len + 1));

    // calculate alpha count table
    for (int i = 0; i < cmap.size(); i++) {
        CountTab[i][len] = 0;
    }

    for (int j = len - 1; j >= 0; j--) {
        for (int i = 0; i < cmap.size(); i++) {
            CountTab[i][j] = CountTab[i][j + 1];
        }
        CountTab[cmap[seq[j]]][j]++;
    }

    if(disp){
        cout << "\n  | \t\t";
        for(int i = 0; i < len; i++) cout << seq[i] << "\t";
        cout << endl;
        for(int i = 0; i < len + 2; i++) cout << "--" << "\t";
        cout << endl;
        for (auto m : cmap) {
            cout << m.first << " | \t";
            for (int j = 0; j <= len; j++) {
                cout << CountTab[m.second][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return CountTab;
}

vector< vector< vector<int> > > cal_count_tabs(vector<string>& seqs, unordered_map<char, int>& cmap, bool disp){
    
    vector< vector< vector<int> > > CountTabs;
    for(auto& seq : seqs){
        CountTabs.push_back(cal_count_tab(seq, cmap, disp));
    }
    return CountTabs;
    
}

int UpperBound_by_CountTabs(Point<CordType> *p, vector< vector< vector<int> > >& CountTabs){

    int ub = 0;

    for(int i = 0; i < CountTabs[0].size(); i++){
        int minval = INT32_MAX;
        for(int j = 0; j < CountTabs.size(); j++){
            minval = min(CountTabs[j][i][p->cord[j]], minval);
        }
        ub += minval;
    }

    return ub;

}

vector< vector< vector<int> > > cal_score_tabs(vector<string>& seqs){
    
    vector< vector< vector<int> > > ScoreTabs;

    for (int i = 0; i < (seqs.size() + 1) / 2; i++) {
        int i1 = i << 1;
        int i2 = 1+ (i << 1);
        if (i2 >= seqs.size()) i2 = 0;

        ScoreTabs.push_back(vector< vector<int> >(seqs[i1].length() + 1, vector<int>(seqs[i2].length() + 1, 0)));
        for (int x = seqs[i1].length() - 1; x >= 0; x--) {
            for (int y = seqs[i2].length() - 1; y >= 0; y--) {
                if (seqs[i1][x] == seqs[i2][y])
                    ScoreTabs[i][x][y] = ScoreTabs[i][x + 1][y + 1] + 1;
                else
                    ScoreTabs[i][x][y] = max(ScoreTabs[i][x+1][y], ScoreTabs[i][x][y+1]);
            }
        }

    }

    return ScoreTabs;
    
}

int UpperBound_by_ScoreTabs(Point<CordType> *p, vector< vector< vector<int> > >& ScoreTabs){

    int h = ScoreTabs[0][0][0];
    for (int i = 0; i < ScoreTabs.size(); i++) {
        int i1 = i << 1;
        int i2 = 1+ (i << 1);
        if (i2 >= g_point_size) i2 = 0;
        h = min(h, ScoreTabs[i][p->cord[i1]][p->cord[i2]]);
    }

    return h;
    
}

int cal_manhattan_dist(Point<CordType> *p){
    int sum = 0;
    for(int i = 0; i < g_point_size; ++i){
        sum += p->cord[i];
    }
    return sum;
}

double cal_k_norm(vector<string>& seqs, const Point<CordType>* p, double k){
    double res = 0;
    for(int i = 0; i < seqs.size(); i++){
        res += pow(seqs[i].length() - p->cord[i] + 1, k);
    }
    return pow(res, 1.0 / k);
}

vector< vector<double> > cal_pr_tab(int p, int q, int sigSize){

    vector< vector<double> > P = vector< vector<double> >(p, vector<double>(q, 0));
    for(int i = 0; i < p; i++){
        for(int j = 0; j < q; j++){
            if(i == 0) P[i][j] = 1;
            else if(i > j) P[i][j] = 0;
            else P[i][j] = (1.0 / sigSize) * P[i - 1][j - 1] + ((sigSize - 1) * 1.0 / sigSize) * P[i][j - 1];
        }
    }
    
    return P;

}

double UpperBound_by_PrTab(const Point<CordType>* p, int sigSize, vector<string>& seqs, vector< vector<double> >& P){
    double lmin = INT32_MAX;
    double res = 0;

    for(int i = 0; i < seqs.size(); i++){
        if(lmin > seqs[i].length() - p->cord[i] + 1)
            lmin = seqs[i].length() - p->cord[i] + 1;
    }
    for(int i = 1; i <= lmin; i++){
        double pr = 1.0;
        for(int j = 0; j < seqs.size(); j++){
            pr *= P[i][seqs[j].length() - p->cord[j] + 1];
        }
        res += pow(1 - pr, pow(sigSize, i));
    }
    return lmin - res;
}


Point<CordType>* successor(Point<CordType>* p, vector< vector< vector<int> > >& SucTabs, int i){
    Point<CordType>* q = new Point<CordType>(SucTabs.size());

    for(unsigned int j = 0; j < SucTabs.size(); ++j){
        q->cord[j] = SucTabs[j][i][p->cord[j]];
        if(q->cord[j] < 0){ // dominants do not exists.
            delete q;
            return NULL;
        }
    }

    return q;
}

bool is_successor(Point<CordType>* p, Point<CordType>* q, int num){
    bool flag = false;
    for(int i = 0; i < num; i++){
        if(p->cord[i] != q->cord[i]){ 
            flag = true;
            if(p->cord[i] < q->cord[i]) return false;
        }
    }
    return flag;
}

bool is_immediate_successor(Point<CordType>* p, Point<CordType>* q , vector< vector< vector<int> > >& SucTabs){

    for(int i = 0; i < SucTabs[0].size(); i++){
        Point<CordType> *suc = successor(q, SucTabs, i);
        if(suc){
            if(is_successor(p, suc, SucTabs.size())){
                delete suc;
                return false;
            }
            delete suc;
        }
    }
    return true;

}

void Qsort(vector< Point<CordType>* >& arr, int low, int high, int dim){
    if (high <= low) return;
    int i = low;
    int j = high + 1;
    int key = arr[low]->cord[dim];
    while (true)
    {
        while (arr[++i]->cord[dim] < key)
        {
            if (i == high){
                break;
            }
        }
        while (arr[--j]->cord[dim] > key)
        {
            if (j == low){
                break;
            }
        }
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[j], arr[low]);
    Qsort(arr, low, j - 1, dim);
    Qsort(arr, j + 1, high, dim);
}

// find k-th number in a sorted arr
int Qselect(vector< Point<CordType>* >& arr, int k, int dim){

    if (arr.size() <= 1){
        return arr[0]->cord[dim];
    }

    int pivot = arr[arr.size()/2]->cord[dim];
    vector<Point<CordType>*> first;
    vector<Point<CordType>*> last;
    vector<Point<CordType>*> pivots;

    for(auto p : arr){
        if(p->cord[dim] < pivot){
            first.push_back(p);
        }
        else if(p->cord[dim] > pivot){
            last.push_back(p);
        }
        else{
            pivots.push_back(p);
        }
    }

    if(first.size() > k){
        return Qselect(first, k, dim);
    }
    else if(first.size() + pivots.size() > k){
        return pivot;
    }
    else{
        return Qselect(last, k - first.size() - pivots.size(), dim);
    }

}
int Qmedian(vector< Point<CordType>* >& arr, int dim){

    if(arr.size() % 2 == 0){
        return (Qselect(arr, arr.size() / 2 - 1, dim) + Qselect(arr, arr.size() / 2, dim)) / 2;
    }
    else{
        return Qselect(arr, arr.size() / 2, dim);
    }

}

int vmax(vector< Point<CordType>* >& arr, int dim){
    int res = arr[0]->cord[dim];
    for(auto p : arr){
        if(p->cord[dim] > res) res = p->cord[dim];
    }
    return res;
}

vector<Point<CordType>*> mergeSortedVecter(vector<Point<CordType>*>& A, vector<Point<CordType>*>& B, int dim){

    int i = 0, j = 0, k = 0;
    int M = A.size();
    int N = B.size();
    vector<Point<CordType>*> res(M + N);

    while(i < M && j < N){
        if(A[i]->cord[dim] < B[j]->cord[dim]){
            res[k++] = A[i++];
        }
        else if(A[i]->cord[dim] > B[j]->cord[dim]){
            res[k++] = B[j++];
        }
        else{
            res[k++] = A[i++];
            res[k++] = B[j++];
        }
    }

    while(j < N) res[k++] = B[j++];
    while(i < M) res[k++] = A[i++];

    return res;

}

vector<Point<CordType>*> mergeSortedSet(vector<Point<CordType>*>& A, vector<Point<CordType>*>& B, int dim, int pointsize){

    int i = 0, j = 0;
    int M = A.size();
    int N = B.size();
    vector<Point<CordType>*> res;

    while(i < M && j < N){
        if(A[i]->cord[dim] < B[j]->cord[dim]){
            res.push_back(A[i++]);
        }
        else if(A[i]->cord[dim] > B[j]->cord[dim]){
            res.push_back(B[j++]);
        }
        else{
            char flag = 0; // 0: A = B 1: A < B 2: A > B
            for(int k = dim + 1; k < pointsize; k++){
                if(A[i]->cord[k] < B[j]->cord[k]){flag = 1; break;}
                else if(A[i]->cord[k] > B[j]->cord[k]){flag = 2; break;}
            }
            if(flag == 1){
                res.push_back(A[i++]);
            }
            else if(flag == 2){
                res.push_back(B[j++]);
            }
            else{
                res.push_back(A[i++]);j++;
            }
        }
    }

    while(j < N) res.push_back(B[j++]);
    while(i < M) res.push_back(A[i++]);

    return res;

}

