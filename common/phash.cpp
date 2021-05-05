#include "phash.h"

int expendedfactor;
int pointsize;
vector<double> e;

void phash_init(int seqnum, int fac){

    double esum = 0;
    e = vector<double>(seqnum);
    for(int i = 0; i < seqnum; i++){
        unsigned int erand = rand();
        e[i] = 1.23456789 * i + (sqrt(erand) - (unsigned int)sqrt(erand) + 1);
        esum += e[i] * e[i];
    }
    esum = sqrt(esum);
    for(int i = 0; i < seqnum; i++){
        e[i] = e[i] / esum;
    }

    pointsize = seqnum;
    expendedfactor = fac;

}

vector<Point<CordType>*> set2vec(HashSet& pset){
    vector<Point<CordType>*> pvec;
    for(auto p : pset) pvec.push_back(p);
    return pvec;
}

bool Key_equal::operator() (const Point<CordType> *p1, const Point<CordType> *p2) const {
    for(int i = 0; i < pointsize; i++){
        if(p1->cord[i] != p2->cord[i]) return false;
    }
    return true;
}

int inline cal_hash_val(const Point<CordType> *p){
    double res = 0;
    for(int i = 0; i < pointsize; i++){
        res += e[i] * p->cord[i];
        res -= (int) res;
    }
    return (int)(res * expendedfactor);
}

size_t Hash_Function::operator() (const Point<CordType> *p) const{
    return (size_t)cal_hash_val(p);
}

BiHashTable::BiHashTable(int volume){

    if(volume < 0) volume = expendedfactor;
    Point2IndexTab = HashMap(volume);
    Index2PointTab.resize(volume);
    sz = 0;

}

bool BiHashTable::insert(Point<CordType> *p){
    auto res = Point2IndexTab.insert(make_pair(p, sz));
    if(res.second){
        if(sz < Index2PointTab.size())
            Index2PointTab[sz] = p;
        else
            Index2PointTab.push_back(p);
        sz++;
        return true;
    }
    else return false;
}

unsigned int BiHashTable::maxnum_in_each_bucket() const{
    unsigned int maxnum = 0;
    for(unsigned int i = 0; i < Point2IndexTab.bucket_count(); i++){
        if(Point2IndexTab.bucket_size(i) > maxnum)
            maxnum = Point2IndexTab.bucket_size(i);
    }
    return maxnum;
}

BiHashTable::~BiHashTable(){
    for(int i = 0; i < sz; i++){
        delete Index2PointTab[i];
    }
}
