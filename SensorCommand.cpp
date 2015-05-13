/* 
 * File:   SensorCommand.cpp
 * Author: johannes
 * 
 * Created on 13. Mai 2015, 03:12
 */

#include "SensorCommand.h"
#include "Firefly.h"

SensorCommand::SensorCommand(const char* description,
        char* answerbuffer, int answersize, char descriptor, unsigned short packetbit) {

    commanddescription_ = description;
    request_[0] = '>';
    request_[1] = '*';
    request_[2] = '>';
    request_[3] = 'p';
    request_[4] = (packetbit>>8) & 0xFF;
    request_[5] = packetbit & 0xFF;
    answerbuffer_ = answerbuffer;
    answersize_ = answersize;
    descriptor_ = descriptor;
}

SensorCommand::~SensorCommand() {
}

void SensorCommand::execute() {
    std::stringstream ss;
    int answerbytes = 0;
    unsigned short packetlength;
    unsigned short crc;
    char readbuffer[8];
    
    Comport* pcom = Firefly::getInstance()->getComport();
    
    if (pcom->Write(request_, 6) == false) {
        ss << "Couldn't write command request of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }
    
    answerbytes = pcom->Read(readbuffer, 8, 10, 10);
    if(answerbytes != 8) {
        ss << "Startstring incomplete of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());   
    }
    
    packetlength = short((short(readbuffer[3])<<8)|readbuffer[4]);
    if(readbuffer[5] != descriptor_ || packetlength != answersize_){
        ss << "Wrong packet descriptor or packet length of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }
    
    answerbytes = pcom->Read(answerbuffer_, answersize_, 10, 10);
    if(answerbytes != answersize_) {
        ss << "Packet data incomplete of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }
    
    answerbytes = pcom->Read(readbuffer, 5, 10, 10);
    if(answerbytes != 5) {
        ss << "Endstring incomplete of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }
    
    crc = short((short(readbuffer[0])<<8)|readbuffer[1]);
    if(crc != crc16((void*)answerbuffer_, answersize_)){
        ss << "CRC invalid of: " << commanddescription_ << std::endl;
        throw std::runtime_error(ss.str());
    }
}

unsigned short SensorCommand::crc16(void* data, unsigned short cnt) {
    unsigned short crc = 0xff;
    unsigned char * ptr = (unsigned char *) data;
    int i;

    for (i = 0; i < cnt; i++) {
        crc = crc_update(crc, *ptr);
        ptr++;
    }
    return crc;
}