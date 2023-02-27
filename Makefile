CC = g++

BASEFLAGS = -Wall -std=c++20
DEBUG_FLAGS = -DDEBUG -g
LIBS = -lwiringPi

EXE = photodiode_reader singleended_test

ADSLIB = /home/bbst/bbst/Adafruit_ADS1X15_RPi/

release: CFLAGS = $(BASEFLAGS)
release: $(EXE)

debug: CFLAGS = $(BASEFLAGS) $(DEBUG_FLAGS)
debug: $(EXE)

$(EXE): $@.cpp $(ADSLIB)Adafruit_ADS1015.cpp $(ADSLIB)Adafruit_ADS1015.h
	$(CC) $(CFLAGS) -o $@ $@.cpp $(ADSLIB)Adafruit_ADS1015.cpp -I $(ADSLIB) $(LIBS)

clean:
	rm -f $(EXE)