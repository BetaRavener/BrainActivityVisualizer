#ifndef SIGNAL_READER_H
#define SIGNAL_READER_H

#include "signalRecord.h"
#include "edflib.h"

#include <string>
#include <vector>

class SignalFileReader
{
public:
    SignalFileReader();
    ~SignalFileReader();

    void open(std::string path);
    void close();
    bool isOpened();

    const std::vector<SignalRecord*>& records();

private:
    edf_hdr_struct _edfHeader;
    std::vector<SignalRecord*> _records;

    bool _opened;
};

#endif
