#include <iostream>
#include <chrono>
#include <thread>

#include "Adafruit_ADS1015.h"

Adafruit_ADS1015 ads;

int main()
{
    int16_t adc0, adc1, adc2, adc3;
    float volts0, volts1, volts2, volts3;

    int sadc0;

    ads.setGain(GAIN_ONE);

    if (!ads.begin())
    {
        std::cout << "Failed to initialize ADS." << std::endl;
        while (1)
            ;
    }

    while (true)
    {

        adc0 = ads.readADC_SingleEnded(0);
        adc1 = ads.readADC_SingleEnded(1);
        adc2 = ads.readADC_SingleEnded(2);
        adc3 = ads.readADC_SingleEnded(3);

        volts0 = ads.computeVolts(adc0);
        volts1 = ads.computeVolts(adc1);
        volts2 = ads.computeVolts(adc2);
        volts3 = ads.computeVolts(adc3);

        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "AIN0: " << adc0 << "  " << volts0 << "V" << std::endl;
        std::cout << "AIN1: " << adc1 << "  " << volts1 << "V" << std::endl;
        std::cout << "AIN2: " << adc2 << "  " << volts2 << "V" << std::endl;
        std::cout << "AIN3: " << adc3 << "  " << volts3 << "V" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}