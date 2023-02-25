CC = g++

BASEFLAGS = -Wall -std=c++20
DEBUG_FLAGS = -DDEBUG -g
LIBS = -lwiringPi

OBJS = singleended_rpi.o

EXE = singleended_rpi

ADSLIB = /home/bbst/bbst/Adafruit_ADS1X15_RPi/

release: CFLAGS = $(BASEFLAGS)
release: $(EXE)

debug: CFLAGS = $(BASEFLAGS) $(DEBUG_FLAGS)
debug: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

singleended_rpi.o: singleended_rpi.cpp $(ADSLIB)Adafruit_ADS1015.cpp $(ADSLIB)Adafruit_ADS1015.h
	$(CC) $(CFLAGS) -c singleended_rpi.cpp $(ADSLIB)Adafruit_ADS1015.cpp -I $(ADSLIB)

clean:
	rm -f $(OBJS)
	rm -f $(EXE)

run:
	./$(EXE)