/* 
 * File:   SensorCommand.h
 * Author: johannes
 *
 * Created on 13. Mai 2015, 03:12
 */

#ifndef SENSORCOMMAND_H
#define	SENSORCOMMAND_H

#include <stdexcept>
#include <sstream>

class SensorCommand {
public:
    SensorCommand(const char* description, char* answerbuffer, int answersize,
            char descriptor, unsigned short packetbit);
    virtual ~SensorCommand();

    virtual void execute();
private:
    unsigned short crc_update(unsigned short crc, unsigned char data);
    unsigned short crc16(void* data, unsigned short cnt);

    const char* commanddescription_;
    char request_[6];
    char* answerbuffer_;
    int answersize_;
    char descriptor_;
};

inline unsigned short SensorCommand::crc_update(unsigned short crc, unsigned char data) {
    data ^= (crc & 0xff);
    data ^= data << 4;
    return ((((unsigned short) data << 8) | ((crc >> 8)&0xff))
            ^ (unsigned char) (data >> 4) ^ ((unsigned short) data << 3));
}

struct GPS_DATA {
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
};

class GPSDataCommand : public SensorCommand {
public:

    GPSDataCommand() : SensorCommand("GPS Data Request", (char*) &data, sizeof (data), 0x23, 0x080) {
    }

    GPS_DATA data;
};

#endif	/* SENSORCOMMAND_H */

