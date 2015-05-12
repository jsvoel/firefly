/* 
 * File:   WaypointCommand.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 14:31
 */

#ifndef WAYPOINTCOMMAND_H
#define	WAYPOINTCOMMAND_H

#include "Waypoint.h"
#include "LLPCommand.h"

class WaypointCommand : public LLPCommand {
public:
    WaypointCommand(Comport* comport);
    WaypointCommand(const WaypointCommand& orig);
    virtual ~WaypointCommand();
    
    bool execute();
    void setCoordinates(int latitude, int longitude, int height, int yaw, bool isAbsolute = true);
private:
    Waypoint wp_;
};

#endif	/* WAYPOINTCOMMAND_H */

