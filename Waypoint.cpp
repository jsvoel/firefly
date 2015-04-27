/* 
 * File:   Waypoint.cpp
 * Author: johannes
 * 
 * Created on 27. April 2015, 12:35
 */

#include "Waypoint.h"

#define WPPROP_ABSCOORDS 0x01 //if set waypoint is interpreted as absolute coordinates, else relative coords
#define WPPROP_HEIGHTENABLED 0x02  //set new height at waypoint
#define WPPROP_YAWENABLED 0x04 //set new yaw-angle at waypoint(not yet implemented)
#define WPPROP_AUTOMATICGOTO 0x10 //if set, vehicle will not wait for a goto command, but goto this waypoint directly
#define WPPROP_CAM_TRIGGER 0x20 //if set, photo camera is triggered when waypoint is reached and time to stay is 80% up

Waypoint::Waypoint(int latitude, int longitude, int height, int yaw){
    //always set to 1
    wp_number_ = 1;
    //see WPPROP defines below
    properties_ = WPPROP_ABSCOORDS | WPPROP_HEIGHTENABLED | WPPROP_AUTOMATICGOTO;
    //max. speed to travel to waypoint in % (default 100)
    max_speed_ = 10;
    //time to stay at a waypoint (XYZ) in 1/100th s  
    time_ = 500;  
    //position accuracy to consider a waypoint reached in mm (default: 2500 (= 2.5 m))
    pos_acc_ = 2500; 
    //waypoint longitude in abs coords
    longitude_ = longitude;  
    //waypoint latitude in abs coords 
    latitude_ = latitude;  
    //Desired heading at waypoint
    yaw_ = yaw;
    //height over 0 reference in mm
    height_ = height;
    
    short chksum_ = getChecksum();
}

Waypoint::~Waypoint() {
}

short Waypoint::getChecksum()
{
    //chksum = 0xAAAA + wp.yaw + wp.height + wp.time + wp.X + wp.Y + wp.max_speed + wp.pos_acc + wp.properties + wp.wp_number;
    short ret = 0xAAAA + yaw_ + height_ + time_ + longitude_ + latitude_ + max_speed_ + pos_acc_ + properties_ + wp_number_;
    return ret;
}

