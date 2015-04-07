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
            _records.push_back(SignalRecord::create(_edfHeader.handle, i, &(_edfHeader.signalparam[i]), _edfHeader.file_duration));
        }
    }

    _opened = true;
}

void SignalFileReader::close()
{
    _records.clear();
    edfclose_file(_edfHeader.handle);

    _opened = false;
}

bool SignalFileReader::isOpened()
{
    return _opened;
}

std::vector<SignalRecord::Ptr> SignalFileReader::records()
{
    return _records;
}
