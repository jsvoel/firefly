/* 
 * File:   Comport.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 12:48
 */

#ifndef COMPORT_H
#define	COMPORT_H

#include <boost/asio/serial_port.hpp>
#include <time.h>
#include <string>
#include <iostream>

class Comport {
public:
    Comport(const char* port, int baudrate);
    virtual ~Comport();
    
    bool Open();
    void Close();
    bool Write(const char* buffer, int size);
    int Read(char* buffer, int size, int timeout, int retrycount);
private:
    boost::asio::io_service ioser_;
    boost::asio::serial_port port_;
    std::string device_;
};

#endif	/* COMPORT_H */

