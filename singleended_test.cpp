#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "Adafruit_ADS1015.h"

Adafruit_ADS1015 ads;

int main()
{
    uint16_t adc0, adc1, adc2, adc3;
    // float volts0, volts1, volts2, volts3;

    // int sadc0;

    ads.setGain(GAIN_ONE);

    /*if (!ads.begin())
    {
        std::cout << "Failed to initialize ADS." << std::endl;
        while (1)
            ;
    }*/

    ads.begin();

    while (true)
    {
        adc0 = ads.readADC_SingleEnded(0);
        adc1 = ads.readADC_SingleEnded(1);
        adc2 = ads.readADC_SingleEnded(2);
        adc3 = ads.readADC_SingleEnded(3);

        // volts0 = ads.computeVolts(adc0);
        // volts1 = ads.computeVolts(adc1);
        // volts2 = ads.computeVolts(adc2);
        // volts3 = ads.computeVolts(adc3);

        std::cout << std::showbase
                  << std::internal
                  << std::setfill('0');

        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "AIN0: " << std::hex << std::setw(6) << adc0 << std::endl; //"  " << volts0 << "V" << std::endl;
        std::cout << "AIN1: " << std::hex << std::setw(6) << adc1 << std::endl; //"  " << volts1 << "V" << std::endl;
        //std::cout << "AIN2: " << std::hex << std::setw(6) << adc2 << std::endl; //"  " << volts2 << "V" << std::endl;
        //std::cout << "AIN3: " << std::hex << std::setw(6) << adc3 << std::endl; //"  " << volts3 << "V" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
