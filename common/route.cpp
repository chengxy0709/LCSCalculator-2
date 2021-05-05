#include "route.h"

int g_point_size = 0;

Router::Router(string filename, ostream& os, string algo, string alphasets, string params) 
     :instance_file_name(filename), os(os), alg_name(algo), alphabet_set(alphasets), alg_extra_params(params)
{
    
    ifstream f(instance_file_name);
    if(f.good()){
        string seq;
        while(!f.eof()){
            getline(f, seq);
            if(seq.size() > 1) seqs.push_back(seq);
        }
    }
        
}

void Router::connect(){
    
    int ret = ALG_NOT_FOUND;
    int i = 0;

    if(seqs.size() == 0){
        os << "Test Set is empty!\n";
        return;
    }
    else{
        os << "Test set:" << endl;
        for(int i = 0; i < seqs.size(); i++){
            os << seqs[i] << endl;
        }
        g_point_size = seqs.size();
    }

    i = 0;
    while( Alg_Module_Array[i].name != "" ) {

        if( Alg_Module_Array[i].name == alg_name ){
            ret = Alg_Module_Array[i].exe_func(seqs, alphabet_set, os, alg_extra_params);
        }

        i++;
    
    }

	if(ret == ALG_NOT_FOUND){
        os << "'" << alg_name << "' is undefined.\n";
    }
    else if(ret == NORMAL_EXIT){
        cout << "\n----------------------------\nDone!\n";
    }
    else{
        cout << "unexpected error\n";
    }
    
}

void Router::help_message(){
    
    int ret = ALG_NOT_FOUND;
    int i = 0;

    i = 0;
    while( Alg_Module_Array[i].name != "" ) {

        if( Alg_Module_Array[i].name == alg_name ){
            Alg_Module_Array[i].help_func();
            ret = NORMAL_EXIT;
        }

        i++;
    
    }

	if(ret == ALG_NOT_FOUND){
        os << "'" << alg_name << "' is undefined.\n";
    }
    
}


const Alg_Module Alg_Module_Array[MAX_MODULES_NUM] = {

// Register Mark Start
	{"bs", bs_exe_func, bs_help_func},
	{"astar", astar_exe_func, astar_help_func},
	{"hasmlcs", hasmlcs_exe_func, hasmlcs_help_func},
	{"promlcs", promlcs_exe_func, promlcs_help_func},
	{"quickdp", quickdp_exe_func, quickdp_help_func},
	{"topmlcs", topmlcs_exe_func, topmlcs_help_func},
	{"mlcsapp", mlcsapp_exe_func, mlcsapp_help_func},
	{"test", test_exe_func, test_help_func},
	{"example", example_exe_func, example_help_func},

// Register Mark End

};