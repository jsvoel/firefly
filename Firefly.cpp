/* 
 * File:   Firefly.cpp
 * Author: johannes
 * 
 * Created on 27. April 2015, 12:27
 */

#include "Firefly.h"

Firefly* Firefly::instance_ = 0;

Firefly::Firefly()
: comport_(COMPORT, BAUDRATE) {
    strategy_ = 0;
    if (comport_.Open() == false) {
        std::cout << "Couldn't open comport: " << COMPORT << std::endl;
    }
}


Firefly::~Firefly() {
}

Firefly* Firefly::getInstance() {
    if (instance_ == 0) {
        instance_ = new Firefly();
        if (instance_ == 0) {
            std::cout << "Couldn't create instance of Firefly" << std::endl;
        }
    }
    return instance_;
}

void Firefly::start() {
    std::cout << "Fyling " << waypoints_.size() << " Waypoints:" << std::endl;
    for (std::vector<Waypoint*>::iterator it(waypoints_.begin()); it != waypoints_.end(); ++it) {
        std::cout << (*it)->latitude_ << " " << (*it)->longitude_ << std::endl;
    }
}

void Firefly::stop() {

}

void Firefly::clearRoute() {
    if (strategy_ != 0) {
        delete strategy_;
        strategy_ = 0;
    }
    for (std::vector<Waypoint*>::iterator it(waypoints_.begin()); it != waypoints_.end(); ++it) {
        delete *it;
    }
    waypoints_.clear();
}

void Firefly::setRouteStrategy(RouteStrategy *rs) {
    if (strategy_ != 0) {
        delete strategy_;
    }
    strategy_ = rs;
}

void Firefly::pushWaypoint(Waypoint* wp) {
    waypoints_.push_back(wp);
}

/*
void Firefly::getLocation(LocationData &data) {
#ifdef MOCKUP
    data.latitude = 495222300; // Luisenplatz
    data.longitude = 83904000;
    data.height = 1000000; // heigh in milimeter -> 100m
    data.heading = 105000; // heading in degree * 1000 -> 105*
#else
    // actual sensor readings
#endif
}
*/