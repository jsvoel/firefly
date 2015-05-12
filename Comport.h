/* 
 * File:   Comport.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 12:48
 */

#ifndef COMPORT_H
#define	COMPORT_H

#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h>  // File control definitions
#include <termios.h> // POSIX terminal control definitions
#include <time.h>

class Comport {
public:
    Comport(const char* port, speed_t baudrate);
    Comport(const Comport& orig);
    virtual ~Comport();
    
    bool open();
    void close();
    bool write(const char* buffer, int size);
    int read(char* buffer, int size, int timeout, int retrycount);
private:
    const char* port_;
    speed_t baudrate_; // defined by bits/terminos.h
    int filed_;
};

#endif	/* COMPORT_H */

