/* 
 * File:   LocationData.h
 * Author: johannes
 *
 * Created on 27. April 2015, 12:52
 */

#ifndef LOCATIONDATA_H
#define	LOCATIONDATA_H

class LocationData {
public:
    LocationData();
    virtual ~LocationData();
    
    int latitude; // latitude in degree * 10^7
    int longitude; // lonitude in degree * 10^7
    int height; // height in mm
    int heading; // heading in degree * 1000
};

#endif	/* LOCATIONDATA_H */

