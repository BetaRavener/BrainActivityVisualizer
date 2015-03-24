#ifndef OPENSIGNALFILEDIALOG_H
#define OPENSIGNALFILEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "signalReader.h"

namespace Ui {
class OpenSignalFileDialog;
}

class OpenSignalFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenSignalFileDialog(QWidget *parent = 0);
    ~OpenSignalFileDialog();

    std::vector<std::pair<std::string, SignalRecord *> > getResult();

private slots:
    void on_selectFile_clicked();

    void on_addSignal_clicked();

    void on_removeSignal_clicked();

    void on_assignElectrode_clicked();

    void on_chosenSignals_itemClicked(QListWidgetItem *item);

    void on_chosenSignals_clicked(const QModelIndex &index);

    void on_chosenSignals_itemSelectionChanged();

    void on_buttonBox_accepted();

private:
    class SignalRecordItem : public QListWidgetItem
    {
    public:
        SignalRecordItem(SignalRecord* signalRecord);
        SignalRecord* signalRecord();

        QString assignedElectrode();
        void assignedElectrode(QString name);

    private:
        SignalRecord* _signalRecord;
        QString _assignedElectrode;
    };

    Ui::OpenSignalFileDialog *ui;
    SignalFileReader _reader;
};

#endif // OPENSIGNALFILEDIALOG_H
