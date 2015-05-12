/* 
 * File:   Firefly.h
 * Author: johannes
 *
 * Created on 27. April 2015, 12:27
 */

#ifndef FIREFLY_H
#define	FIREFLY_H

#include <vector>
#include <iostream>

#include "RouteStrategy.h"
#include "Waypoint.h"
#include "LocationData.h"
#include "Comport.h"

#define MOCKUP // instead of using real data, use mock data for testing the interface
#define COMPORT "/dev/ttyS3" // the port were the serial is to be opened
#define BAUDRATE B57600 // the baud rate it shall be set to

class Firefly {
public:
    virtual ~Firefly();
    
    static Firefly* getInstance();
    
    void start(); // start to fly the route using provided Waypoints and Strategy
    void stop(); // stop flight and land instantly
    
    void clearRoute(); // clear all waypoints and Strategy
    void setRouteStrategy(RouteStrategy *rs); // set the RouteStrategy
    void pushWaypoint(Waypoint* wp); // put a Waypoint into the List
    
    void getLocation(LocationData &data);
private:
    Firefly();
    Firefly(const Firefly& orig);
    
    static Firefly *instance_;
    
    Comport comport_;
    RouteStrategy *strategy_;
    std::vector<Waypoint*> waypoints_;
};

#endif	/* FIREFLY_H */

