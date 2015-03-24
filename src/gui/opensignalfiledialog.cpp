#include "opensignalfiledialog.h"
#include "ui_opensignalfiledialog.h"
#include "signalReader.h"
#include "electrodeMap.h"

#include <QFileDialog>
#include <QString>

OpenSignalFileDialog::OpenSignalFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenSignalFileDialog)
{
    ui->setupUi(this);
    ui->assignElectrode->setEnabled(false);
}

OpenSignalFileDialog::~OpenSignalFileDialog()
{
    delete ui;
}

std::vector<std::pair<std::string, SignalRecord *>> OpenSignalFileDialog::getResult()
{
    std::vector<std::pair<std::string, SignalRecord *>> result;
    for (int i = 0; i < ui->chosenSignals->count(); i++)
    {
        SignalRecordItem* signalItem = (SignalRecordItem*)ui->chosenSignals->item(i);
        result.push_back(std::pair<std::string, SignalRecord *>(
                             signalItem->assignedElectrode().toStdString(),
                             signalItem->signalRecord()));
    }

    return result;
}

void OpenSignalFileDialog::on_selectFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select EEG file", "data");
    if (path.isEmpty())
        return;

    ui->filePath->setText(path);
    _reader.open(path.toStdString());
    const std::vector<SignalRecord*>& records = _reader.records();

    ui->availableSignals->clear();
    ui->chosenSignals->clear();
    ui->availableElectrodes->clear();
    ui->assignElectrode->setEnabled(false);

    for (SignalRecord* record : records)
    {
        QListWidgetItem* item = new SignalRecordItem(record);
        ui->availableSignals->addItem(item);
    }

    for (std::string elName : ElectrodeMap::allNames())
    {
        ui->availableElectrodes->addItem(QString::fromStdString(elName));
    }
}

void OpenSignalFileDialog::on_addSignal_clicked()
{
    auto selected = ui->availableSignals->selectedItems();
    for (QListWidgetItem* selectedItem : selected)
    {
        ui->availableSignals->takeItem(ui->availableSignals->row(selectedItem));
        ui->chosenSignals->addItem(selectedItem);
    }
}

void OpenSignalFileDialog::on_removeSignal_clicked()
{
    auto selected = ui->chosenSignals->selectedItems();
    for (QListWidgetItem* selectedItem : selected)
    {
        ui->chosenSignals->takeItem(ui->chosenSignals->row(selectedItem));
        ui->availableSignals->addItem(selectedItem);
    }
}

OpenSignalFileDialog::SignalRecordItem::SignalRecordItem(SignalRecord *signalRecord) :
    QListWidgetItem(QString::fromStdString(signalRecord->label())),
    _signalRecord(signalRecord),
    _assignedElectrode("")
{

}

SignalRecord* OpenSignalFileDialog::SignalRecordItem::signalRecord()
{
    return _signalRecord;
}

QString OpenSignalFileDialog::SignalRecordItem::assignedElectrode()
{
    return _assignedElectrode;
}

void OpenSignalFileDialog::SignalRecordItem::assignedElectrode(QString name)
{
    _assignedElectrode = name;
}

void OpenSignalFileDialog::on_assignElectrode_clicked()
{
    if (ui->chosenSignals->selectedItems().count() == 1)
    {
        auto selected = (SignalRecordItem*)ui->chosenSignals->selectedItems()[0];
        QString electrodeName = ui->availableElectrodes->currentText();
        selected->assignedElectrode(electrodeName);
        ui->assignedElectrodeLabel->setText(electrodeName != "" ? electrodeName : "None");
    }
}

void OpenSignalFileDialog::on_chosenSignals_itemClicked(QListWidgetItem *item)
{

}

void OpenSignalFileDialog::on_chosenSignals_clicked(const QModelIndex &index)
{

}

void OpenSignalFileDialog::on_chosenSignals_itemSelectionChanged()
{
    if (ui->chosenSignals->selectedItems().count() == 1)
    {
        auto selected = (SignalRecordItem*)ui->chosenSignals->selectedItems()[0];
        QString electrodeName = selected->assignedElectrode();
        ui->assignedElectrodeLabel->setText(electrodeName != "" ? electrodeName : "None");
        ui->assignElectrode->setEnabled(true);
    }
    else
    {
        ui->assignedElectrodeLabel->setText("None");
        ui->assignElectrode->setEnabled(false);
    }
}

void OpenSignalFileDialog::on_buttonBox_accepted()
{

}
