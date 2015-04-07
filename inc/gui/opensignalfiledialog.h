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

class OpenSignalFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenSignalFileDialog(QWidget *parent = 0);
    ~OpenSignalFileDialog();

    void setElectrodeMap(ElectrodeMap* electrodeMap);

    SignalBatch::Ptr getResult();

public slots:
    void electrodeMapChanged();

private slots:
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
