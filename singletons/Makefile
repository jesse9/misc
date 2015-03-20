##############################
# Makefile
#  Created on: Mar 19, 2015
#      Author: Xing
##############################

CXX		= g++
LD		= gcc
OPT     = -O0 -g
INCS	= -I./include
LIBPATH = -L.
LIBS    = -lstdc++
CXXFLAG = $(OPT) $(INCS) -std=c++11
LDFLAG	= $(OPT) $(LIBPATH)

SRCS 	= $(wildcard *.cpp)
DEPS 	= $(SRCS:.cpp=.d)
OBJS 	= $(SRCS:.cpp=.o)
EXES 	= $(SRCS:.cpp=.exe)
TARGET  = $(EXES)

all: $(TARGET)

$(EXES): %.exe: %.o
	$(LD) $(LDFLAG) $< -o $@ $(LIBS)

$(OBJS): %.o: %.cpp %.d
	$(CXX) $(CXXFLAG) -c $< -o $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

$(DEPS): %.d: %.cpp
	$(CXX) -MM $(CXXFLAG) $< > $@

.PHONY: clean
clean:
	-rm -f $(TARGET) $(OBJS) $(DEPS)
