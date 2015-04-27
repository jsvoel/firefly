/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 27. April 2015, 12:26
 */



#include "Firefly.h"


/*
 * 
 */
int main(int argc, char** argv) {
    
    Firefly::getInstance()->setRouteStrategy(new RouteStrategy());
    Firefly::getInstance()->pushWaypoint(new Waypoint(495222300, 83904000, 100000, 105000)); //Luisenplatz 100 Meter 105°
    Firefly::getInstance()->pushWaypoint(new Waypoint(498661560, 86415150, 150000, 85000)); // D14 150 Meter 85°
    Firefly::getInstance()->pushWaypoint(new Waypoint(498664880, 86420730, 30000, 270000)); // Albert Schweizer Anlage querweg 30 Meter 270°
    
    Firefly::getInstance()->start();
    
    Firefly::getInstance()->clearRoute();
    Firefly::getInstance()->start();
    
    std::cout << "------------------------" << std::endl;
    
    LocationData data;
    Firefly::getInstance()->getLocation(data);
    
    std::cout << data.latitude << " " << data.longitude << " " << data.height << " " << data.heading << std::endl;
            
    return 0;
}

