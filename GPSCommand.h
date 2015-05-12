/* 
 * File:   GPSCommand.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 20:15
 */

#ifndef GPSCOMMAND_H
#define	GPSCOMMAND_H

#include "LLPCommand.h"
#include "GPSData.h"

class GPSCommand : public LLPCommand {
public:
    GPSCommand(Comport* comport);
    GPSCommand(const GPSCommand& orig);
    virtual ~GPSCommand();
    
    
    
    GPSData& getData(){
        return data_;
    }
private:
    GPSData data_;
};

#endif	/* GPSCOMMAND_H */

