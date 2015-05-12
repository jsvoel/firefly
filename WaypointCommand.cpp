/* 
 * File:   WaypointCommand.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 14:31
 */

#include "WaypointCommand.h"

WaypointCommand::WaypointCommand(Comport* comport)
: LLPCommand(comport, "Waypoint Command"),
Waypoint(0, 0, 0, 0) {
}

WaypointCommand::WaypointCommand(const WaypointCommand& orig) {
}

WaypointCommand::~WaypointCommand() {
}

