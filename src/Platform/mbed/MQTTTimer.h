/*
The MIT License(MIT)

Cayenne MQTT Client Library
Copyright (c) 2016 myDevices

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files(the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _MQTTTIMER_h
#define _MQTTTIMER_h

#include "mbed.h"

/**
* Timer class for use with MQTTClient.
*/
class MQTTTimer : private Timer
{
public:
    /**
    * Construct a timer.
    */
    MQTTTimer() : interval_end_ms(0) {};

    /**
    * Construct a timer and start it.
    * @param[in] milliseconds Number of milliseconds to count down.
    */
    MQTTTimer(int milliseconds) { 
        countdown_ms(milliseconds);
    }
    
    /**
    * Start countdown.
    * @param[in] milliseconds Number of milliseconds to count down.
    */
    void countdown_ms(int milliseconds) {
        interval_end_ms = milliseconds;
        reset();
        start();
    }

    /**
    * Start countdown.
    * @param[in] seconds Number of seconds to count down.
    */
    void countdown(int seconds) {
        countdown_ms(seconds * 1000);
    }

    /**
    * Get the number of milliseconds left in countdown.
    * @return Number of milliseconds left.
    */
    int left_ms() {
        return interval_end_ms - read_ms();
    }

    /**
    * The countdown timer has expired.
    * @return true if countdown has expired, false otherwise.
    */
    bool expired() {
        return (interval_end_ms > 0L) && (read_ms() >= interval_end_ms);
    }
    
private:
    unsigned long interval_end_ms;
};

#endif