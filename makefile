OBJS = convert.o CreatePoly.o InfoPrint.o main.o OSMDiv.o OSMNode.o OSMRead.o OSMRelation.o OSMTopData.o OSMWay.o Point.o Polygon.o SQLCreate.o SVGCreate.o SVGItem.o XMLRead.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++0x
LFLAGS = -Wall $(DEBUG)
PROG_NAME = OSM2SQL

all : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PROG_NAME)
#	./$(PROG_NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	\rm *.o


