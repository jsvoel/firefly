/* 
 * File:   LLPCommand.cpp
 * Author: johannes
 * 
 * Created on 12. Mai 2015, 13:43
 */

#include "LLPCommand.h"
#include "Comport.h"

LLPCommand::LLPCommand(Comport* comport, const char* description) {
    commanddescription_ = description;
    pcom_ = comport;
}

LLPCommand::LLPCommand(const LLPCommand& orig) {
}

LLPCommand::~LLPCommand() {
}

bool LLPCommand::execute() {
    bool ret = false;
    int answerbytes = 0;
    if (this->pcom_->write(initiator_, initiatorsize_) == false) {
        std::cout << "Couldn't write command initiator: " << commanddescription_ << std::endl;
    } else {
        if (pcom_->write(commandbuffer_, commandsize_) == false) {
            std::cout << "Couldn't write command " << commanddescription_ << std::endl;
        } else {
            if (answersize_ > 0) {
                answerbytes = pcom_->read(answerbuffer_, answersize_, 10, 10);
                if (answerbytes != 0) {
                    answerbytes = answersize_ - answerbytes;
                    std::cout << "LLP Answer unexpected:" << std::endl;
                    for (int i = 0; i < answerbytes; ++i) {
                        std::cout << answerbuffer_[i] << ' ';
                    }
                    std::cout << std::endl;
                    for (int i = 0; i < answerbytes; ++i) {
                        std::cout << std::hex << (int) answerbuffer_[i] << ' ';
                    }
                    std::cout << std::dec;
                } else {
                    ret = true;
                }
            } else {
                ret = true;
            }
        }
    }

    return ret;
}

unsigned short LLPCommand::crc16(void* data, unsigned short cnt) {
    unsigned short crc = 0xff;
    unsigned char * ptr = (unsigned char *) data;
    int i;

    for (i = 0; i < cnt; i++) {
        crc = crc_update(crc, *ptr);
        ptr++;
    }
    return crc;
}