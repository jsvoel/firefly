/* 
 * File:   Waypoint.h
 * Author: johannes
 *
 * Created on 27. April 2015, 12:35
 */

#ifndef WAYPOINT_H
#define	WAYPOINT_H


#define WPPROP_ABSCOORDS 0x01 //if set waypoint is interpreted as absolute coordinates, else relative coords
#define WPPROP_HEIGHTENABLED 0x02  //set new height at waypoint
#define WPPROP_YAWENABLED 0x04 //set new yaw-angle at waypoint(not yet implemented)
#define WPPROP_AUTOMATICGOTO 0x10 //if set, vehicle will not wait for a goto command, but goto this waypoint directly
#define WPPROP_CAM_TRIGGER 0x20 //if set, photo camera is triggered when waypoint is reached and time to stay is 80% up

class Waypoint {
    friend class Firefly;
    friend class WaypointCommand;
public:
    Waypoint(int latitude, int longitude, int height, int yaw);
    virtual ~Waypoint();
    
    short getChecksum();
private: 
    //always set to 1
    unsigned char wp_number_;
    //don't care
    unsigned char dummy_1_;
    unsigned short dummy_2_;
    //see WPPROP defines below
    unsigned char properties_;
    //max. speed to travel to waypoint in % (default 100)
    unsigned char max_speed_;
    //time to stay at a waypoint (XYZ) in 1/100th s  
    unsigned short time_;  
    //position accuracy to consider a waypoint reached in mm (default: 2500 (= 2.5 m))
    unsigned short pos_acc_; 
    //chksum = 0xAAAA + wp.yaw + wp.height + wp.time + wp.X + wp.Y + wp.max_speed + wp.pos_acc + wp.properties + wp.wp_number;
    short chksum_;
    //waypoint longitude in abs coords
    int longitude_;  
    //waypoint latitude in abs coords 
    int latitude_;  
    //Desired heading at waypoint
    int yaw_;
    //height over 0 reference in mm
    int height_;
};

#endif	/* WAYPOINT_H */

