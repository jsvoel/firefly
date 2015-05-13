/* 
 * File:   NavigationCommand.cpp
 * Author: johannes
 * 
 * Created on 13. Mai 2015, 03:12
 */

#include "Firefly.h"
#include "NavigationCommand.h"


NavigationCommand::NavigationCommand(const char* description, char request, char descriptor) {
    commanddescription_ = description;
    request_[0] = '>';
    request_[1] = '*';
    request_[2] = '>';
    request_[3] = 'w';
    request_[4] = request;
    descriptor_ = descriptor;
}

NavigationCommand::~NavigationCommand() {
}

void NavigationCommand::execute() {
    std::stringstream ss;
    int answerbytes = 0;
    char readbuffer[5];

    Comport* pcom = Firefly::getInstance()->getComport();

    if (pcom->Write(request_, 5) == false) {
        ss << "Couldn't write command request of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }

    sendWaypoint(pcom);

    answerbytes = pcom->Read(readbuffer, 5, 10, 10);
    if (answerbytes != 5) {
        ss << "Acknowledge incomplete of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }

    if (readbuffer[0] != '>' || readbuffer[1] != 'a' || readbuffer[2] != descriptor_
            || readbuffer[3] != 'a' || readbuffer[4] != '<') {
        ss << "Acknowledge incorrect of: " << commanddescription_ << std::endl;
        ss.put(readbuffer[0]);
        ss.put(readbuffer[1]);
        ss.put(readbuffer[2]);
        ss.put(readbuffer[3]);
        ss.put(readbuffer[4]);
        ss << std::endl;
        throw std::runtime_error(ss.str());
    }
}

WaypointCommand::WaypointCommand() : NavigationCommand("Waypoint Command", 's', 0x24) {
    wp_.wp_number = 1;
    wp_.properties = WPPROP_HEIGHTENABLED | WPPROP_AUTOMATICGOTO;
    wp_.max_speed = 20;
    wp_.time = 500;
    wp_.pos_acc = 2500;
    wp_.X = 0;
    wp_.Y = 0;
    wp_.yaw = 0;
    wp_.height = 10000;
    
    checksum();
}

void WaypointCommand::setAbsolute(int latitude, int longitude, int height){
    wp_.properties |= WPPROP_ABSCOORDS;
    wp_.X = longitude;
    wp_.Y = latitude;
    wp_.height = height * 1000;
    checksum();
}

void WaypointCommand::setRelative(int X, int Y, int height){
    wp_.properties &= ~WPPROP_ABSCOORDS;
    wp_.X = X * 1000;
    wp_.Y = Y * 1000;
    wp_.height = height * 1000;
    checksum();
}

void WaypointCommand::sendWaypoint(Comport* pcom) {
    std::stringstream ss;
    
    if (pcom->Write((char*)&wp_, sizeof(WAYPOINT)) == false) {
        ss << "Couldn't write Waypointstructure" << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void WaypointCommand::checksum(){
    short chk = 0xAAAA;
    chk += wp_.yaw + wp_.height + wp_.time + wp_.X + wp_.Y + wp_.max_speed;
    chk += wp_.pos_acc + wp_.properties + wp_.wp_number;
    wp_.chksum = chk;
}