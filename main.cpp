/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 27. April 2015, 12:26
 */

#include <time.h>

#include "Firefly.h"
#include "GPSCommand.h"

/*
 * 
 */
int main(int argc, char** argv) {

    Comport port(COMPORT, BAUDRATE);
    GPSCommand gc(&port);

    timespec reqt, remt;

    reqt.tv_sec = 0;
    reqt.tv_nsec = 5000 * 1000 * 1000;

    while (true) {
        gc.execute();

        std::cout << gc.getData().latitude << " " << gc.getData().longitude << " " << gc.getData().height << " " << gc.getData().heading << std::endl;
        std::cout << "--------------------------------------------------------" << std::cout;
        nanosleep(&reqt, &remt);
    }
    return 0;
}

