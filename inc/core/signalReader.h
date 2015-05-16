// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SIGNAL_READER_H
#define SIGNAL_READER_H

#include "signalRecord.h"
#include "edflib.h"

#include <string>
#include <vector>

/**
 * @brief The SignalFileReader class wraps the EDFlib library.
 */
class SignalFileReader
{
public:
    SignalFileReader();
    ~SignalFileReader();

    /**
     * @brief Opens an EDF signal source file.
     * @param path Path to the file.
     */
    void open(std::string path);

    /**
     * @brief Closes the opened file.
     */
    void close();

    /**
     * @brief Getter.
     * @return True if the file is opened.
     */
    bool isOpened();

    /**
     * @brief Getter.
     * @return All EDF data records read from the file.
     */
    std::vector<SignalRecord::Ptr> records();

private:
    std::string edfErrorToString(int errorCode);

    edf_hdr_struct _edfHeader;
    std::vector<SignalRecord::Ptr> _records;

    bool _opened;
};

#endif
