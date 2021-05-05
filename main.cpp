#include <iostream>
#include <vector>
#include <malloc.h>
#include <unistd.h>
#include <fstream>

#include "route.h"

using namespace std;

#define ARG_ERR -1
#define ARG_EXE 0
#define ARG_HELP 1

struct Arguments
{
    string alg;
    string outputfile;
    string inputfile;
    string alphabet_set;
    string params;
};


static void Usage(){
    cout << "Usage:" << endl;
    cout << "-a <alphabet_set>    -----  specify a alphabet set of test sequences." << endl;
    cout << "-A <algorithm>       -----  select a algorithm from the below list:\n" << endl;
    int i = 0;
    while(Alg_Module_Array[i].name != ""){
        cout << "\t\t\t> " << Alg_Module_Array[i].name << endl;
        i++;
    }
    cout << endl;
    cout << "-o <outputfile>      -----  specify a output file." << endl; 
    cout << "-i <inputfile>       -----  specify a input file." << endl;
    cout << "-e <extra param>     -----  specify some extra parameters for a specified algorithm." << endl;
    cout << "-h <algorithm>       -----  print some help messages for a specified algorithm." << endl;
}

int getargs(int argc, char* argv[], Arguments& args);

int main(int argc, char* argv[]){
    
    Arguments args;
    vector<string> seqs{"ACTAGTGC", "TGCTAGCA", "CATGCGAT"}; // a simple case
    int ret = ARG_HELP;

    cout << endl;
    cout << "\t\t**********************************\n";
    cout << "\t\t*                                *\n";
    cout << "\t\t*        LCS   Calculator        *\n";
    cout << "\t\t*                                *\n";
    cout << "\t\t**********************************\n\n\n";

    ret = getargs(argc, argv, args);
    if(ret == ARG_ERR){
        cout << "parameters error." << endl;
        return -1;
    }
    else if(ret == ARG_HELP){
        Router router(args.alg, cout);
        router.help_message();
        return 0;
    }

    filebuf fb;
    ostream *os;
    if(args.outputfile.length() == 0){
        os = &cout;
    }
    else{
        filebuf fb;
        fb.open(args.outputfile, ios::out | ios::trunc);
        os = new ostream(&fb);
    }
    
    if(args.inputfile.length() == 0){
        Router router(seqs, *os, args.alg, args.alphabet_set, args.params);
        router.connect();
    }
    else
    {
        Router router(args.inputfile, *os, args.alg, args.alphabet_set, args.params);
        router.connect();
    }

    fb.close();

    return 0;

}

int getargs(int argc, char* argv[], Arguments& args){
    
    int ch;
    int flag = ARG_EXE;
    args.alphabet_set = "ACGT";
    args.alg = Alg_Module_Array[0].name;
    args.inputfile = "";
    args.outputfile = "";
    args.params = "";

    while((ch = getopt(argc, argv, "a:A:i:o:e:h:")) != -1){
        switch (ch)
        {
        case 'a':
            args.alphabet_set = optarg;
            break;
        case 'A':
            args.alg = optarg;
            break;
        case 'i':
            args.inputfile = optarg;
            break;
        case 'o':
            args.outputfile = optarg;
            break;
        case 'e':
            args.params = optarg;
            break;
        case 'h':
            args.alg = optarg;
            flag = ARG_HELP;
            break;
        default:
            Usage();
            flag = ARG_ERR;
        }
    }

    return flag;

}
