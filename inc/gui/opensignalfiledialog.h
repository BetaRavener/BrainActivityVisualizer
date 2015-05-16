// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef OPENSIGNALFILEDIALOG_H
#define OPENSIGNALFILEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "signalReader.h"
#include "electrodeMap.h"
#include "signalBatch.h"

namespace Ui {
class OpenSignalFileDialog;
}

/**
 * @brief The OpenSignalFileDialog class represents a dialog used for setting the EEG data source.
 */
class OpenSignalFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenSignalFileDialog(QWidget *parent = 0);
    ~OpenSignalFileDialog();

    /**
     * @brief Setter.
     * @param electrodeMap Electrode map which is currently used by application.
     */
    void setElectrodeMap(ElectrodeMap* electrodeMap);

    /**
     * @brief Returns the user selected group of signals after the dialog was accepted.
     * @return Signal batch.
     */
    SignalBatch::Ptr getResult();

public slots:
    /**
     * @brief Slot used when electrode map changes.
     */
    void electrodeMapChanged();

private slots:
    /**
     * @brief Slot used when user wants to select a file.
     */
    void on_selectFile_clicked();

    void on_addSignal_clicked();

    void on_removeSignal_clicked();

    void on_assignElectrode_clicked();

    void on_chosenSignals_itemSelectionChanged();

    void on_buttonBox_accepted();

    void on_autoAssign_clicked();

    void on_importAssignment_clicked();

    void on_exportAssignment_clicked();

    void on_clearAll_clicked();

    void on_clear_clicked();

private:
    class SignalRecordItem : public QListWidgetItem
    {
    public:
        SignalRecordItem(SignalRecord::Ptr signalRecord);
        SignalRecord::Ptr signalRecord();

        QString assignedElectrode();
        void assignedElectrode(QString name);

    private:
        SignalRecord::Ptr _signalRecord;
        QString _assignedElectrode;
    };

    void initAvailableElectrodes();
    void clearAssignment(SignalRecordItem* item);
    void clearAssignments();

    Ui::OpenSignalFileDialog *ui;
    SignalFileReader _reader;
    ElectrodeMap* _electrodeMap;
};

#endif // OPENSIGNALFILEDIALOG_H
