/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 27. April 2015, 12:26
 */

#include <time.h>

#include "Firefly.h"
#include "SensorCommand.h"
#include "NavigationCommand.h"
/*
 * 
 */
int main(int argc, char** argv) {
    try{
    int count = 0;
    GPSDataCommand gps;
    LaunchCommand ln;
    WaypointCommand wp;
    EndCommand ed;

    timespec reqt, remt;

    reqt.tv_sec = 5;
    reqt.tv_nsec = 0;

    while (true) {
        gps.execute();

        std::cout << gps.data.latitude << " " << gps.data.longitude << " " << gps.data.height << " " << gps.data.heading << std::endl;
        std::cout << "--------------------------------------------------------" << std::cout;
        nanosleep(&reqt, &remt);
        count++;
        if(count > 5){
            break;
        }
    }
    
    
    /*
    std::cout << "Launching..." << std::endl;
    ln.execute();
    nanosleep(&reqt, &remt);
    
    std::cout << "Flying 10 x 10 x 10" << std::endl;
    wp.setRelative(10, 10, 10);
    //wp.setAbsolute(490000000, 80000000, 10);
    wp.execute();
    nanosleep(&reqt, &remt);
    
    std::cout << "Ending..." << std::endl;
    ed.execute();
    nanosleep(&reqt, &remt); 
     */
    }
    catch(std::runtime_error &e){
        std::cout << "Runtime error: " << e.what()  << std::endl;
    }
    catch(std::exception &e){
        std::cout << "Esception: " << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Uncaught Exception" << std::endl;
    }
    
    return 0;
}

