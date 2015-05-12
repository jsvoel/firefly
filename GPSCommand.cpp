/* 
 * File:   GPSCommand.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 20:15
 */

#include "GPSCommand.h"

GPSCommand::GPSCommand(Comport* comport)
: LLPCommand(comport, "GPS Data Command") {
    this->initiator_[0] = '>';
    this->initiator_[1] = '*';
    this->initiator_[2] = '>';
    this->initiator_[3] = 'p';
    this->initiator_[4] = 0x00;
    this->initiator_[5] = 0x80;
    this->initiatorsize_ = 6;
    this->commandbuffer_ = 0;
    this->commandsize_ = 0;
    this->answerbuffer_ = (char*) &data_;
    this->answersize_ = sizeof(data_);
}
GPSCommand::GPSCommand(const GPSCommand& orig) {
}

GPSCommand::~GPSCommand() {
}

