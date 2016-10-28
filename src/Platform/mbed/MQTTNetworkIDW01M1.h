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

#ifndef _MQTTNETWORKIDW01M1_h
#define _MQTTNETWORKIDW01M1_h

#include "mbed.h"
#include "TCPSocket.h"

/**
* Networking class for use with MQTTClient.
* @param Interface A network interface class with the methods: init, connect and disconnect.
*/
template<class Interface>
class MQTTNetwork
{
public:
    /**
    * Construct the network interface.
    * @param[in] interface The network interface to use
    */
    MQTTNetwork(Interface& interface) : _interface(interface), _connected(false) {
        _socket.open(&_interface);
    }
      
    /**
    * Connect the network interface.
    * @param[in] hostname Host for connection
    * @param[in] port Port for connection
    * @param[in] timeout_ms Timeout for the read operation, in milliseconds
    * @return 0 on success, -1 on failure.
    */
    int connect(char* hostname, int port, int timeout_ms = 1000) {
        //_socket.set_blocking(false);
        _socket.set_timeout(timeout_ms);
        int ret = _socket.connect(hostname, port);
        _connected = (ret == 0);
        return ret;
    }
    
    /**
    * Disconnect the network interface.
    * @return true if disconnect was successful, false otherwise
    */
    bool disconnect()
    {  
        _connected = false;
        return _socket.close();
    }

    /**
    * Check if connected.
    * @return true if connected, false otherwise
    */
    bool connected()
    {
        return _connected;
    }
    
    /**
    * Read data from the network.
    * @param[out] buffer Buffer that receives the data
    * @param[in] len Buffer length
    * @param[in] timeout_ms Timeout for the read operation, in milliseconds
    * @return Number of bytes read, or a negative value if there was an error
    */
    int read(unsigned char* buffer, int len, int timeout_ms) {
        _socket.set_timeout(timeout_ms);
        return _socket.recv((char*)buffer, len);
    }
    
    /**
    * Write data to the network.
    * @param[in] buffer Buffer that contains data to write
    * @param[in] len Number of bytes to write
    * @param[in] timeout_ms Timeout for the write operation, in milliseconds
    * @return Number of bytes written, or a negative value if there was an error
    */
    int write(unsigned char* buffer, int len, int timeout_ms) {
        _socket.set_timeout(timeout_ms);
        return _socket.send((char*)buffer, len);
    }   

private:
    Interface& _interface;
    TCPSocket _socket;
    bool _connected;
};

#endif