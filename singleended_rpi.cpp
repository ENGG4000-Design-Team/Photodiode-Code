#include <iostream>
#include <chrono>

#include "Adafruit_ADS1015.h"

Adafruit_ADS1015 ads;

int main()
{
    uint16_t adc0, adc1, adc2, adc3;

    int sadc0;

    ads.setGain(GAIN_ONE);
    ads.begin();
    while (true)
    {
        adc0 = ads.readADC_SingleEnded(0);
        sadc0 = stastic_cast<int>(adc0);
        adc1 = ads.readADC_SingleEnded(1);
        adc2 = ads.readADC_SingleEnded(2);
        adc3 = ads.readADC_SingleEnded(3);
        std::cout << "\nadc0 = (" << sadc0 << ", " << sadc0 << "), adc1 = " << adc1 << ", adc2 = " << adc2 << ", adc3 = " << adc3 << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}