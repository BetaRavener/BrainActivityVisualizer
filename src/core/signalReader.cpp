#include "signalReader.h"
#include <stdexcept>

SignalFileReader::SignalFileReader() :
    _opened(false)
{

}

SignalFileReader::~SignalFileReader()
{
    if (_opened)
        close();
}

void SignalFileReader::open(std::string path)
{
    if (_opened)
        close();

    int result = edfopen_file_readonly(path.c_str(), &_edfHeader, EDFLIB_DO_NOT_READ_ANNOTATIONS);

    if (result < 0)
        throw std::runtime_error("Failed to open file.");

    for (int i = 0; i < _edfHeader.datarecords_in_file; i++)
    {
        // Ignore unlabeled signals
        if ((std::string(_edfHeader.signalparam[i].label)).compare(""))
        {
            _records.push_back(new SignalRecord(_edfHeader.handle, i, &(_edfHeader.signalparam[i])));
        }
    }

    _opened = true;
}

void SignalFileReader::close()
{
    for (SignalRecord* record : _records)
    {
        delete record;
    }

    _records.clear();
    edfclose_file(_edfHeader.handle);

    _opened = false;
}

bool SignalFileReader::isOpened()
{
    return _opened;
}

const std::vector<SignalRecord*>& SignalFileReader::records()
{
    return _records;
}
