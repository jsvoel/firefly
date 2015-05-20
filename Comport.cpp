/* 
 * File:   Comport.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 12:48
 */

#include "Comport.h"

Comport::Comport(const char* port, int baudrate)
: port_(ioser_, port) {
    port_.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
    device_ = port;
}

Comport::~Comport() {
}

bool Comport::Open() {
    bool ret = false;
    port_.open(device_);
    ret = port_.is_open();
    return ret;
}

void Comport::Close() {
    port_.close();
}

bool Comport::Write(const char* buffer, int size) {
    bool ret = false;
    int index = 0;
    try {
        while (index < size) {
            index = port_.write_some(boost::asio::buffer(&buffer[index], size - index));
        }
    } catch (boost::system::system_error &e) {
        std::cerr << "Boost Exception on write some!" << std::endl << e.what() << std::endl;
    }
    if (index == size) {
        ret = true;
    }
    return ret;
}

int Comport::Read(char* buffer, int size, int timeout, int retrycount) {
    int index = 0;
    timespec reqt, remt;

    reqt.tv_sec = 0;
    reqt.tv_nsec = timeout * 1000 * 1000;
    nanosleep(&reqt, &remt);
    try {
        while (index < size && retrycount > -1) {
            index = port_.read_some(boost::asio::buffer(&buffer[index], size - index));
            if (index < size) {
                nanosleep(&reqt, &remt);
                retrycount--;
            }
        }
    } catch (boost::system::system_error &e) {
        std::cerr << "Boost Exception on read some!" << std::endl << e.what() << std::endl;
    }
    return index;
}

