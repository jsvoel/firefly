/* 
 * File:   GPSData.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 20:17
 */

#ifndef GPSDATA_H
#define	GPSDATA_H

class GPSData {
public:
    char start[8];
   //latitude/longitude in deg * 10^7
    int latitude;
    int longitude;
    //GPS height in mm
    int height;
    //speed in x (E/W) and y(N/S) in mm/s
    int speed_x;
    int speed_y;
    //GPS heading in deg * 1000
    int heading;
    //accuracy estimates in mm and mm/s
    unsigned int horizontal_accuracy;
    unsigned int vertical_accuracy;
    unsigned int speed_accuracy;
    //number of satellite vehicles used in NAV solution
    unsigned int numSV;
    // GPS status information; 0x03 = valid GPS fix
    int status;
    char end[5];
};

#endif	/* GPSDATA_H */

