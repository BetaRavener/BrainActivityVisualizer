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

    std::vector<SignalRecord::Ptr> records();

private:
    edf_hdr_struct _edfHeader;
    std::vector<SignalRecord::Ptr> _records;

    bool _opened;
};

#endif
