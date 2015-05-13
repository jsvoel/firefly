/* 
 * File:   NavigationCommand.h
 * Author: johannes
 *
 * Created on 13. Mai 2015, 03:12
 */

#ifndef NAVIGATIONCOMMAND_H
#define	NAVIGATIONCOMMAND_H

#include <stdexcept>
#include <sstream>

class Comport;

class NavigationCommand {
public:
    NavigationCommand(const char* description, char request, char descriptor);
    virtual ~NavigationCommand();

    virtual void execute();
private:
    virtual void sendWaypoint(Comport* pcom) {
    }
    
    const char* commanddescription_;
    char request_[5];
    char descriptor_;
};

class GotoCommand : public NavigationCommand {
public:

    GotoCommand() : NavigationCommand("Goto Command", 'g', 0x25) {
    }
};

class LaunchCommand : public NavigationCommand {
public:

    LaunchCommand() : NavigationCommand("Launch Command", 'l', 0x26) {
    }
};

class EndCommand : public NavigationCommand {
public:

    EndCommand() : NavigationCommand("End Flight Command", 'e', 0x27) {
    }
};

struct WAYPOINT {
    //always set to 1
    unsigned char wp_number;
    //don't care
    unsigned char dummy_1;
    unsigned short dummy_2;
    //see WPPROP defines below
    unsigned char properties;
    //max. speed to travel to waypoint in % (default 100)
    unsigned char max_speed;
    //time to stay at a waypoint (XYZ) in 1/100th s  
    unsigned short time;
    //position accuracy to consider a waypoint reached in mm (default: 2500 (= 2.5 m))
    unsigned short pos_acc;
    //chksum = 0xAAAA + wp.yaw + wp.height + wp.time + wp.X + wp.Y + wp.max_speed + wp.pos_acc + wp.properties + wp.wp_number;
    short chksum;
    //waypoint coordinates in mm // longitude in abs coords
    int X;
    //waypoint coordinates in mm  // latitude in abs coords 
    int Y;
    //Desired heading at waypoint
    int yaw;
    //height over 0 reference in mm
    int height;
};

#define WPPROP_ABSCOORDS 0x01 //if set waypoint is interpreted as absolute coordinates, else relative coords
#define WPPROP_HEIGHTENABLED 0x02 //set new height at waypoint
#define WPPROP_YAWENABLED 0x04 //set new yaw-angle at waypoint(not yet implemented)
#define WPPROP_AUTOMATICGOTO 0x10 //if set, vehicle will not wait for a goto command, but goto this waypoint directly

class WaypointCommand : public NavigationCommand {
public:
    WaypointCommand();
    
    void setAbsolute(int latitude, int longitude, int height);
    void setRelative(int X, int Y, int height);
private:
    void sendWaypoint(Comport* pcom);
    void checksum();
    
    WAYPOINT wp_;
};

#endif	/* NAVIGATIONCOMMAND_H */

