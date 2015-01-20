CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		record.o csv2bin.o

LIBS =

TARGET =	csv2bin.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
