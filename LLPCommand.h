/* 
 * File:   LLPCommand.h
 * Author: johannes
 *
 * Created on 12. Mai 2015, 13:43
 */

#ifndef LLPCOMMAND_H
#define	LLPCOMMAND_H

#include <iostream>

class Comport;

class LLPCommand {
public:
    LLPCommand(Comport* comport, const char* description);
    
    virtual ~LLPCommand();

    virtual bool execute();

private:
    unsigned short crc_update(unsigned short crc, unsigned char data);
    
    Comport* pcom_;
    const char* commanddescription_;
protected:
    unsigned short crc16(void* data, unsigned short cnt);
    char initiator_[6];
    int initiatorsize_;
    char* commandbuffer_;
    int commandsize_;
    char* answerbuffer_;
    int answersize_;
};

inline unsigned short LLPCommand::crc_update(unsigned short crc, unsigned char data) {
    data ^= (crc & 0xff);
    data ^= data << 4;
    return ((((unsigned short) data << 8) | ((crc >> 8)&0xff))
            ^ (unsigned char) (data >> 4) ^ ((unsigned short) data << 3));
}
#endif	/* LLPCOMMAND_H */

