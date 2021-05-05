# LCSCalculator-2
This is a new version for LCS Calculator that is used to calculate the longest common subsequence of several sequences.

## Introduction for directories
It is re-implemented for a specified algorithm in alg-*, such as topmlcs, A*, quickdp and so on. There are two directories that are unique. In alg-example, it is a simple example for using alg-mod-manager.py. And it is for testing functions in alg-test.

In scripts, some scripts are produced for knds of aims.

In common and utils, there are some functions and classes for re-implementing algorithm modules.

In include, there are some header files.

In instances, there are some instances for testing algorithm modules.

## compile and fun
You can use the below instructions to compile this project and run it:
```
$ git clone https://github.com/Limbing/LCSCalculator-2.git
$ cd LCSCalculator-2
$ make
$ ./LCSCalculator -A topmlcs 
```
## add your algorithm for your purpose
```
$ cd project-path/scripts
$ ./alg-mod-manager.py add [your algorithm]
```
## generate your instances
```
$ cd project-path/scripts
$ ./generate-random-instance.py -l [length] -n [num]
```

For more details about scripts, you can use the option [h].

For any question, you can contact my email address xycheng19@gmail.com
