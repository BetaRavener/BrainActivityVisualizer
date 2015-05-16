// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

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
        throw std::runtime_error(std::string("Failed to open file.\nReason: ") +
                                 edfErrorToString(_edfHeader.filetype));

    if (_edfHeader.file_duration < 0)
        _edfHeader.file_duration = -_edfHeader.file_duration;

    if (_edfHeader.datarecord_duration < 0)
        _edfHeader.datarecord_duration = -_edfHeader.datarecord_duration;

    for (int i = 0; i < _edfHeader.edfsignals; i++)
    {
        // Ignore unlabeled signals
        if ((std::string(_edfHeader.signalparam[i].label)).compare(""))
        {
            _records.push_back(SignalRecord::create(&_edfHeader, i));
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

std::string SignalFileReader::edfErrorToString(int errorCode)
{
    switch(errorCode)
    {
    case EDFLIB_MALLOC_ERROR:
        return "Internal error";
    case EDFLIB_NO_SUCH_FILE_OR_DIRECTORY:
        return "No such file";
    case EDFLIB_FILE_CONTAINS_FORMAT_ERRORS:
        return "File contains format errors";
    case EDFLIB_MAXFILES_REACHED:
        return "Internal error";
    case EDFLIB_FILE_READ_ERROR:
        return "Read error";
    case EDFLIB_FILE_ALREADY_OPENED:
        return "File already opened";
    case EDFLIB_FILETYPE_ERROR:
        return "File type error";
    case EDFLIB_FILE_WRITE_ERROR:
        return "File write error";
    case EDFLIB_NUMBER_OF_SIGNALS_INVALID:
        return "Number of signals is invalid";
    case EDFLIB_FILE_IS_DISCONTINUOUS:
        return "File is discontinuous";
    case EDFLIB_INVALID_READ_ANNOTS_VALUE:
        return "Internal error";
    default:
        return "Unknown";
    }
}
