/* 
 * File:   WaypointCommand.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 14:31
 */

#include "WaypointCommand.h"
#include "Comport.h"

WaypointCommand::WaypointCommand(Comport* comport)
: LLPCommand(comport, "Waypoint Command"),
wp_(0, 0, 0, 0) {
    this->initiator_[0] = '>';
    this->initiator_[1] = '*';
    this->initiator_[2] = '>';
    this->initiator_[3] = 'w';
    this->initiator_[4] = 's';
    this->initiatorsize_ = 5;
    this->commandbuffer_ = (char*) &wp_;
    this->commandsize_ = sizeof (wp_);
    this->answerbuffer_ = new char[6];
    this->answerbuffer_[5] = 0;
    this->answersize_ = 5;
}


WaypointCommand::~WaypointCommand() {

}

bool WaypointCommand::execute() {
    bool ret = false;
    if (LLPCommand::execute() == true) {
        ret = true;
        std::cout << "Waypoint set: " << this->answerbuffer_ << std::endl;
    }
    return ret;
}

void WaypointCommand::setCoordinates(int latitude, int longitude, int height, int yaw, bool isAbsolute) {
    wp_.latitude_ = latitude;
    wp_.longitude_ = longitude;
    wp_.height_ = height;
    wp_.yaw_ = yaw;
    if (isAbsolute) {
        wp_.properties_ = WPPROP_ABSCOORDS | WPPROP_HEIGHTENABLED | WPPROP_AUTOMATICGOTO;
    } else {
        wp_.properties_ = WPPROP_HEIGHTENABLED | WPPROP_AUTOMATICGOTO;
    }
    wp_.chksum_ = wp_.getChecksum();
}

