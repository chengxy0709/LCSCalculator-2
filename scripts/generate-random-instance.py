#!/usr/bin/python3
#   This script provides a class InstGenerator for generating a random test 
#instance. You can use th below instruction:
#   
#     1. cd /your project path/scripts/
#     2. ./generate-random-instance.py [option] [parameter] 
#
#   For more details, use ""./generate-random-instance.py -h".
#
# Author: chengxy
# Email:  xycheng19@gmail.com
# Date:   2021/4/30 : 9.40

import random
import datetime
import sys
import os
import getopt

alphabet_sets = ['ACGT', 
                 'ACDEFGHIKLMNPQRSTVWY']

class InstGenerator:

    def __init__(self, store_path = './example', seq_len = 0, seq_num = 0, alphabet_set = 'a'):
        self.store_path = store_path
        self.seq_len = seq_len
        self.seq_num = seq_num
        self.alphabet_set = alphabet_set
        random.seed(datetime.datetime.now().strftime('%Y%m%d%H%M%S'))

    def __gen_one_random_seq(self):
        seq = ''
        gap = len(self.alphabet_set) 
        for i in range(self.seq_len):
            seq += self.alphabet_set[random.randint(0, gap - 1)]
        return seq

    def generate_instance(self, store_path = None, seed = None):
        filepath = store_path if store_path else self.store_path
        filepath = os.path.join(filepath, 'random-%d-%d-%s' % (self.seq_num, self.seq_len, self.alphabet_set))
        if seed:
            filepath += '-' + str(seed)
        with open(filepath, mode = 'w+') as f:
            for i in range(self.seq_num):
                f.write(self.__gen_one_random_seq() + '\n')


def Usage():
    print("Usage:\n")
    print(" " * 4 + "./generate-random-instance.py [option] [parameter]")
    print(" " * 8 + "-p <path>:      -----  specify a folder store sequences.")
    print(" " * 8 + "-l <length>:    -----  the length of a sequence.")
    print(" " * 8 + "-n <num>        -----  the number of sequences.")
    print(" " * 8 + "-N <No>         -----  specify a existing alphabet set:")
    for i in range(len(alphabet_sets)):
        print(" " * 12, i, '. ', alphabet_sets[i])
    print(" " * 8 + "-a <alphabets>  -----  specify a unique alphabet set.")
    print(" " * 8 + "-c <count>      -----  specify the number of instances to generate.")



def main(argv):
    store_path = '../instances/'
    seq_len = 0
    seq_num = 0
    alphabet_set = 'a'
    count = 1
    try:
        opts, args = getopt.getopt(argv, 'hp:l:n:N:a:c:',['path=','length=','num=','No=','alphabet_set=','count='])
    except getopt.GetoptError:
        Usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            Usage()
            sys.exit()
        elif opt in ("-p", "--path"):
            store_path = arg
        elif opt in ("-l", "--length"):
            seq_len = int(arg)
        elif opt in ("-n", "--num"):
            seq_num = int(arg)
        elif opt in ("-N", "--No"):
            index = int(arg)
            if index < 0 or index >= len(alphabet_sets):
                Usage()
                sys.exit(2)
            else:
                alphabet_set = alphabet_sets[index]
        elif opt in ("-a", "--alphabet_set"):
            alphabet_set = arg
        elif opt in ("-c", "--count"):
            count = int(arg)
        else:
            pass

    if not os.path.exists(store_path):
        print('Please check your path to store instances.')
        sys.exit()

    generator = InstGenerator(store_path, seq_len, seq_num, alphabet_set)
    for i in range(count):
        generator.generate_instance(seed = i + 1)
    

if __name__ == "__main__":
    main(sys.argv[1:])