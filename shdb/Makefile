CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		record.o mergecsv.o csv2bin.o

LIBS =

TARGET =	mergecsv csv2bin

all:	$(TARGET)

mergecsv:	record.o mergecsv.o
	$(CXX) -o mergecsv record.o mergecsv.o $(LIBS)
	
csv2bin:	record.o csv2bin.o
	$(CXX) -o csv2bin record.o csv2bin.o $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
