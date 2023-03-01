/*
 * photodiode_reader.cpp
 * Author: Ethan garnier
 */
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <vector>
#include <chrono>
#include <thread>

#include "Adafruit_ADS1015.h"
#include "wiringPi.h"

Adafruit_ADS1015 ads;

const int PHOTODIODE_ARRAY_X = 5;
const int PHOTODIODE_ARRAY_Y = 5;

// GPIO pins we are using to control multiplexer channels
int pins[4] = {1, 2, 3, 4};

// Map the multiplexer channel bits to the corresponding
// index on the photodiodes array below.
std::map<uint8_t, std::vector<int>> photodiodeIdx{
    {0x00, {0, 2}}, // 0b0000 corresponds to photodiode D1
    {0x01, {0, 4}}, // 0b0001 corresponds to photodiode D2
    {0x02, {2, 4}}, // 0b0010 corresponds to photodiode D3
    {0x03, {4, 4}}, // 0b0011 corresponds to photodiode D4
    {0x04, {4, 2}}, // 0b0100 corresponds to photodiode D5
    {0x05, {4, 0}}, // 0b0101 corresponds to photodiode D6
    {0x0A, {2, 0}}, // 0b1010 corresponds to photodiode D7
    {0x0B, {0, 0}}, // 0b1011 corresponds to photodiode D8
};

// Store photodiode readings in this array such that their
// index mimics their physical position on the photodiode board.
// Below is the exact indexing:
//      D1 => photodiodes[0][2]
//      D2 => photodiodes[0][4]
//      D3 => photodiodes[2][4]
//      D4 => photodiodes[4][4]
//      D5 => photodiodes[4][2]
//      D6 => photodiodes[4][0]
//      D7 => photodiodes[2][0]
//      D8 => photodiodes[0][0]
// All other values in between are zeros and disgarded in processing.
uint16_t photodiodes[PHOTODIODE_ARRAY_Y][PHOTODIODE_ARRAY_X] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};

// Print the photodiode matrix nicely
void printMat()
{
    std::cout << std::showbase
              << std::internal
              << std::setfill('0');

    std::cout << "-----------------------------------------------------------" << std::endl;

    for (const auto &row : photodiodes)
    {
        for (const auto &col : row)
        {
            std::cout << std::hex << std::setw(6) << col << " ";
        }
        std::cout << std::endl
                  << std::endl;
    }
}

// Find the maximum value in the photodiode matrix, as well
// as its position in the matrix.
void findMax(uint16_t &maxVal, std::vector<int> &maxPos)
{
    maxVal = 0x0000;
    for (int i = 0; i < PHOTODIODE_ARRAY_Y; i++)
    {
        auto rowMax = std::max_element(photodiodes[i], photodiodes[i] + PHOTODIODE_ARRAY_X);
        if (*rowMax > maxVal)
        {
            maxPos[0] = i;
            maxPos[1] = std::distance(photodiodes[i], rowMax);
            maxVal = *rowMax;
        }
    }
}

int main()
{
    // Setup wiringPi
    wiringPiSetup();
    for (const auto &pin : pins)
    {
        pinMode(pin, OUTPUT);
    }

    // Setup ADC
    ads.setGain(GAIN_ONE);
    ads.begin();

    std::vector<int> maxPos{0, 0};
    uint16_t maxVal = 0x0000;

    while (true)
    {
        for (const auto &[key, val] : photodiodeIdx)
        {
            // Write key to GPIO pins to select particular photodiode
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(pins[i], (key >> i) & 0x01);
            }

            // TODO: Is this needed?
            // Sleep for 1ms for good measuer
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            // Read value from adc and store in photodiodes matrix
            // TODO: Double check all values are coming from A0,
            // or else we need to keep track of that too
            photodiodes[val[0]][val[1]] = ads.readADC_SingleEnded(0);
        }

        // printMat();

        std::cout << "Brightest Photodiode: ";

        findMax(maxVal, maxPos);
        if (maxPos == photodiodeIdx.at(0x00))
        {
            std::cout << "D1";
        }
        else if (maxPos == photodiodeIdx.at(0x01))
        {
            std::cout << "D2";
        }
        else if (maxPos == photodiodeIdx.at(0x02))
        {
            std::cout << "D3";
        }
        else if (maxPos == photodiodeIdx.at(0x03))
        {
            std::cout << "D4";
        }
        else if (maxPos == photodiodeIdx.at(0x04))
        {
            std::cout << "D5";
        }
        else if (maxPos == photodiodeIdx.at(0x05))
        {
            std::cout << "D6";
        }
        else if (maxPos == photodiodeIdx.at(0x0A))
        {
            std::cout << "D7";
        }
        else if (maxPos == photodiodeIdx.at(0x0B))
        {
            std::cout << "D8";
        }
        else
        {
            std::cout << "NONE";
        }

        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
