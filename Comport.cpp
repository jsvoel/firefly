/* 
 * File:   Comport.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 12:48
 */

#include "Comport.h"

Comport::Comport(const char* port, speed_t baudrate) {
    port_ = port;
    baudrate_ = baudrate;
    filed_ = -1;
}

Comport::Comport(const Comport& orig) {
}

Comport::~Comport() {
}

bool Comport::open() {
    bool ret = false;
    // Initializing the Serial Port
    filed_ = open(port_, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
    if (filed_ != -1) {
        struct termios port_settings; // structure to store the port settings in
        cfsetispeed(&port_settings, baudrate_); // set baud rates
        port_settings.c_cflag = baudrate_ | CS8 | CREAD | CLOCAL;
        port_settings.c_iflag = IGNPAR;
        port_settings.c_oflag = 0;
        port_settings.c_lflag = 0;
        tcsetattr(filed_, TCSANOW, &port_settings); // apply the settings to the port
        ret = true;
    }
    return ret;
}

void Comport::close() {
    close(filed_);
}

bool Comport::write(const char* buffer, int size) {
    bool ret = false;
    int written = write(filed_, buffer, size);
    fsync(filed_);
    if (written == size) {
        ret = true;
    }
    return ret;
}

int Comport::read(char* buffer, int size, int timeout) {
    int remaining = size;
    int index = 0;
    timespec reqt, remt;

    reqt.tv_sec = 0;
    reqt.tv_nsec = timeout * 1000 * 1000;
    nanosleep(&reqt, &remt);

    while (remaining > 0) {
        index = read(filed_, &buffer[index], size - index);
        remaining -= index;
        if (remaining > 0) {
            nanosleep(&reqt, &remt);
        }
    }
    return remaining;
}
