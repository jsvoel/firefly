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
#include "Comport.h"

#define MOCKUP // instead of using real data, use mock data for testing the interface
#define COMPORT "/dev/ttyS3" // the port were the serial is to be opened
#define BAUDRATE B57600 // the baud rate it shall be set to

struct WAYPOINT;

class Firefly {
public:
    virtual ~Firefly();
    
    static Firefly* getInstance();
    
    void start(); // start to fly the route using provided Waypoints and Strategy
    void stop(); // stop flight and land instantly
    
    void clearRoute(); // clear all waypoints and Strategy
    void setRouteStrategy(RouteStrategy *rs); // set the RouteStrategy
    void pushWaypoint(WAYPOINT* wp); // put a Waypoint into the List
    
    //void getLocation(LocationData &data);
    Comport* getComport();
private:
    Firefly();
    
    static Firefly *instance_;
    
    Comport comport_;
    RouteStrategy *strategy_;
    std::vector<WAYPOINT*> waypoints_;
};

inline Comport* Firefly::getComport(){
    return &comport_;
}
#endif	/* FIREFLY_H */

