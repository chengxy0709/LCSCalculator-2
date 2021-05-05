#!/usr/bin/python3
#   This script provides a class AlgModManager for managing algorithm modules,
# for example, adding, removing, disabling and enabling. You can use the below
# instructions for your purpose:
#   
#     1. cd /your project path/scripts/
#     2. ./alg-mod-manager.py 
#     3. cd - && make 
#
#   In addition, the global variable "BASEPATH" refer to your project path, so, 
# you should check whether it is correct for your project.
#
# Author: chengxy
# Email:  xycheng19@gmail.com
# Date:   2021/4/29 : 9.55


import os
import re
import sys
import shutil

marks = {
    'route' : 'Register Mark',
    'routehf' : 'Alg Module Header',
    'makefile' : 'Makefile Mark'
}

BASEPATH = os.path.join( os.getcwd() , '../' )

class AlgModManager:

    def __init__(self, base_path = './'):
        self.base_path = base_path

    # return the position after mark start and the position before mark end 
    def __find_mark(self, filepath, mark):
        pos = [-1, -1]
        with open( filepath, mode = 'r' ) as f:
            
            line = f.readline()
            mark_cnt = 0

            while line and mark_cnt != 2 :
                if line.find(mark) != -1:
                    mark_cnt += 1 # 1 for mark start; 2 for mark end
                    if mark_cnt == 1:
                        pos[0] = f.tell()
                    else:
                        pos[1] = f.tell() - len(line) - 1

                line = f.readline()

            return pos


    def __insert_content(self, filepath, content, pos):
        with open( filepath, mode = 'r+' ) as f:
            f.seek(pos)
            rest = f.read()
            f.seek(pos)
            f.write(content + rest)

    
    def __delete_content_in_line(self, filepath, rcontent, pos = None):
        lines = []
        rest = ''
        with open( filepath, mode = 'r' ) as f:
            if not pos:
                rest = f.read()
            else:
                line = f.readline()
                while line :
                    if f.tell() < pos[0] and f.tell() > pos[1]:
                        lines.append(line)
                    else:
                        if re.search(rcontent , line):
                            rest = f.read()
                            break    
                        else:
                            lines.append(line)
                    line = f.readline()

        with open( filepath, mode = 'w' ) as f:
            for line in lines:
                f.write(line)
            f.write(rest)


    def __make_alg_mod_h(self, filepath, alg_name):
        with open(filepath, mode = 'w+') as f:
            content = '#ifndef %s_H\n' % alg_name.upper()
            content += '#define %s_H\n\n' % alg_name.upper()
            content += '#include <ostream>\n#include <iostream>\n#include <fstream>\n'
            content += '#include <string>\n#include <vector>\n\n#include "errdef.h"\n#include "point.h"\n\nusing namespace std;\n\n'
            content += 'void %s_help_func();\n' % alg_name
            content += 'int %s_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params);\n' % alg_name
            content += '\n\n#endif //%s_H\n' % alg_name.upper()
            f.write(content)


    def __make_alg_mod_cpp(self, filepath, alg_name):
        with open(filepath, mode = 'w+') as f:
            content = '#include \"%s.h\"\n\n' % alg_name
            content += 'void %s_help_func(){\n\n}\n' % alg_name
            content += 'int %s_exe_func(vector<string>& seqs, string& alphabet_set, ostream& os, string params){\n\n\treturn NORMAL_EXIT;\n\n}\n' % alg_name
            f.write(content)


    def __make_alg_mod_mk(self, filepath, alg_name):
        with open(filepath, mode = 'w+') as f:
            content = 'objs += alg-%s/%s.o' % (alg_name, alg_name)
            f.write(content)


    def check_mod_route(self, route_path, alg_name):

        mark = marks['route']
        pos = self.__find_mark(route_path, mark)
        if pos[0] > 0 and pos[1] >= pos[0]:
            with open( route_path, mode = 'r' ) as route_cpp:
                info = ''
                route_cpp.seek(pos[0])
                while route_cpp.tell() <= pos[1]:
                    info += route_cpp.readline()
                if re.search(r'\"\s*' + alg_name + r'\s*\"' , info):
                    return True
                else:
                    return False

        else:
            raise Exception('route file error')

        return False


    def get_all_alg_mod(self):
        alg_mods = []
        for filename in os.listdir(self.base_path):
            if re.match(r'alg-*', filename):
                alg_mods.append(filename.split('-')[1])
        return alg_mods


    # This function doesn't check whether alg_name is in route
    def add_alg_mod_route( self, cpp_path, h_path, alg_name ):

        content = '\t{"%s", %s_exe_func, %s_help_func},\n' % (alg_name, alg_name, alg_name)
        self.__insert_content(cpp_path, content, self.__find_mark(cpp_path, marks['route'])[0])
        content = '#include \"%s.h\"\n' % alg_name
        self.__insert_content(h_path, content, self.__find_mark(h_path, marks['routehf'])[0])
        

    # This function doesn't check whether alg_name is in makefile
    def add_alg_mod_makefile( self, makefile_path, alg_name ):
        content = 'include ./alg-%s/config.mk\n' % alg_name
        self.__insert_content(makefile_path, content, self.__find_mark(makefile_path, marks['makefile'])[0])
    

    # This function doesn't check whether alg_name is in route
    def rm_alg_mod_route(self, cpp_path, h_path, alg_name ):

        rcontent = r'\"\s*' + alg_name + r'\s*\"'
        self.__delete_content_in_line(cpp_path, rcontent, self.__find_mark(cpp_path, marks['route']))
        rcontent = alg_name + r'\.h'
        self.__delete_content_in_line(h_path, rcontent, self.__find_mark(h_path, marks['routehf']))


    # This function doesn't check whether alg_name is in makefile
    def rm_alg_mod_makefile( self, makefile_path, alg_name ):

        rcontent = r'alg-' + alg_name + r'/'
        self.__delete_content_in_line(makefile_path, rcontent, self.__find_mark(makefile_path, marks['makefile']))


    def add_alg_mod( self, alg_name ):
        
        if self.check_mod_route( os.path.join(self.base_path, "common/route.cpp"), alg_name ) or \
           os.path.exists(os.path.join(self.base_path, 'alg-%s' % alg_name)):
            print(alg_name + ' has already been added.')
        
        else:
            self.add_alg_mod_route( os.path.join(self.base_path, "common/route.cpp"), 
                                    os.path.join(self.base_path, "include/route.h"), 
                                    alg_name )
            self.add_alg_mod_makefile( os.path.join(self.base_path, "Makefile"), alg_name )
            # make a directory for th algotithm module
            folder = os.path.join(self.base_path, 'alg-%s' % alg_name)
            if not os.path.exists(folder):
                os.makedirs(folder)
                self.__make_alg_mod_h(os.path.join(self.base_path, 'include/%s.h' % alg_name), alg_name)
                self.__make_alg_mod_cpp(os.path.join(folder, '%s.cpp' % alg_name), alg_name)
                self.__make_alg_mod_mk(os.path.join(folder, 'config.mk'), alg_name)
            else:
                raise Exception('can\'t make directory for %s' % alg_name)
            print(alg_name + ' has been added.')


    def rm_alg_mod( self, alg_name ):
        
        if self.check_mod_route( os.path.join(self.base_path, "common/route.cpp"), alg_name ) or \
           os.path.exists(os.path.join(self.base_path, 'alg-%s' % alg_name)):
            ok = input('please input [yes] for confirming the operation that will remove all infomation and files about %s > ' % alg_name)
            if ok == 'yes':
                try:
                    self.rm_alg_mod_route( os.path.join(self.base_path, "common/route.cpp"), 
                                       os.path.join(self.base_path, "include/route.h"), 
                                       alg_name )
                    self.rm_alg_mod_makefile( os.path.join(self.base_path, "Makefile"), alg_name )
                except Exception:
                    pass
                if os.path.exists(os.path.join(self.base_path, 'include/%s.h' % alg_name)):
                    os.remove(os.path.join(self.base_path, 'include/%s.h' % alg_name))
                if os.path.exists(os.path.join(self.base_path, 'alg-%s' % alg_name)):
                    shutil.rmtree(os.path.join(self.base_path, 'alg-%s' % alg_name))
                print(alg_name + ' has been removed.')
            else:
                print('operation has been canceled')
        
        else:
            print(alg_name + ' doesn\'t exist.')


    def enable_alg_mod( self, alg_name ):

        if self.check_mod_route( os.path.join(self.base_path, "common/route.cpp"), alg_name ):
            print(alg_name + ' has already been enabled.')
        
        else:
            self.add_alg_mod_route( os.path.join(self.base_path, "common/route.cpp"), 
                                    os.path.join(self.base_path, "include/route.h"), 
                                    alg_name )
            self.add_alg_mod_makefile( os.path.join(self.base_path, "Makefile"), alg_name )
            print(alg_name + ' has been enabled.')


    def disable_alg_mod( self, alg_name ):

        if self.check_mod_route( os.path.join(self.base_path, "common/route.cpp"), alg_name ):
            self.rm_alg_mod_route( os.path.join(self.base_path, "common/route.cpp"), 
                                os.path.join(self.base_path, "include/route.h"), 
                                alg_name )
            self.rm_alg_mod_makefile( os.path.join(self.base_path, "Makefile"), alg_name )
            print(alg_name + ' has been disabled.')
        
        else:
            print(alg_name + ' has already been disabled or doesn\'t exist.')


def Usage():
    print('Usage:\n')
    print(' ' * 4 + './alg-mod-manager.py [active] [alg_mod]\n')
    print(' ' * 4 + '[active]:')
    print(' ' * 8 + 'disable  ------------  don\'t contain alg_mod during making')
    print(' ' * 8 + 'enable   ------------  contain alg_mod during making')
    print(' ' * 8 + 'add      ------------  add a basic frame for alg_mod')
    print(' ' * 8 + 'remove   ------------  clean all content and files about alg_mod')
    print(' ' * 4 + 'alg_mod:')
    for alg_mod in AlgModManager(BASEPATH).get_all_alg_mod():
        print(' ' * 8 + alg_mod)
    print('\n')

def main(argv):
    manager = AlgModManager(BASEPATH)

    if len(argv) == 1:
        Usage()

    else:
        if argv[1] == 'add':
            if len(argv) == 3:
                manager.add_alg_mod(argv[2])
            else:
                Usage()

        elif argv[1] == 'remove':
            if len(argv) == 3:
                manager.rm_alg_mod(argv[2])
            else:
                Usage()

        elif argv[1] == 'disable':
            if len(argv) == 3:
                manager.disable_alg_mod(argv[2])
            else:
                Usage()

        elif argv[1] == 'enable':
            if len(argv) == 3:
                manager.enable_alg_mod(argv[2])
            else:
                Usage()

        else:
            Usage()


if __name__ == "__main__":
    main(sys.argv)


     


