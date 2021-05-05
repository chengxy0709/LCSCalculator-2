#include "check.h"

// is test a subsequence of ori ?
bool is_subsequence( string& ori, string& test ){

    int i = 0, j = 0;
    while(i < ori.length() && j < test.length()){
        if(ori[i] == test[j]) {
            i++;
            j++;
        }
        else{
            i++;
        }
    }
    if(i >= ori.length() && j < test.length()){
        return false;
    }
    else{
        return true;
    }

}

int result_check( vector<string>& seqs, string& res ){

    for(auto& seq : seqs){
        if( !is_subsequence(seq, res) ){
            return false;
        }
        else{
            return true;
        }
    }

}