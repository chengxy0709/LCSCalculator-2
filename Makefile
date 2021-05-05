CPPFLAGS += -std=c++11
CPPFLAGS += -fpermissive
CPPFLAGS += -I ${shell pwd}/include/

CC = g++
AR = ar
LD = ld

.DEFAULT_GOAL := all

objs += main.o
include ./common/config.mk
include ./utils/config.mk

# Makefile Mark Start
include ./alg-bs/config.mk
include ./alg-astar/config.mk
include ./alg-hasmlcs/config.mk
include ./alg-promlcs/config.mk
include ./alg-quickdp/config.mk
include ./alg-topmlcs/config.mk
include ./alg-mlcsapp/config.mk
include ./alg-test/config.mk
include ./alg-example/config.mk

# Makefile Mark End

target = LCSCalculator

$(target): $(objs)
	$(CC) -o $(target) $(objs) 
%.o : %.cpp
	$(CC) $(CPPFLAGS) -o $@ $< -c

all: $(target)

clean:
	for i in `ls` ; do \
		if [[ $$i == alg-* ]]; then \
    		cd $$i && rm -rf *.o && cd .. ; \
		fi ; \
	done
	cd common; rm -rf *.o; cd ..
	cd utils; rm -rf *.o; cd ..
	rm -rf *.o $(target)
