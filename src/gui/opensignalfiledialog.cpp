#include "opensignalfiledialog.h"
#include "ui_opensignalfiledialog.h"
#include "signalReader.h"
#include "electrodeMap.h"

#include <QFileDialog>
#include <QString>
#include <fstream>

OpenSignalFileDialog::OpenSignalFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenSignalFileDialog),
    _electrodeMap(nullptr)
{
    ui->setupUi(this);
    ui->assignElectrode->setEnabled(false);
}

OpenSignalFileDialog::~OpenSignalFileDialog()
{
    delete ui;
}

void OpenSignalFileDialog::setElectrodeMap(ElectrodeMap *electrodeMap)
{
    _electrodeMap = electrodeMap;
}

SignalBatch::Ptr OpenSignalFileDialog::getResult()
{
    std::vector<SignalData::Ptr> dataSignals;
    for (int i = 0; i < ui->chosenSignals->count(); i++)
    {
        SignalRecordItem* signalItem = (SignalRecordItem*)ui->chosenSignals->item(i);
        SignalData::Ptr signalData = signalItem->signalRecord()->load();
        signalData->electrode(_electrodeMap->electrode(signalItem->assignedElectrode().toStdString()));
        dataSignals.push_back(signalData);
    }

    return SignalBatch::create(std::move(dataSignals));
}

void OpenSignalFileDialog::electrodeMapChanged()
{
    clearAssignments();
}

void OpenSignalFileDialog::on_selectFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select EEG file", "data");
    if (path.isEmpty())
        return;

    ui->filePath->setText(path);
    _reader.open(path.toStdString());
    std::vector<SignalRecord::Ptr> records = _reader.records();

    ui->availableSignals->clear();
    ui->chosenSignals->clear();
    ui->availableElectrodes->clear();
    ui->assignElectrode->setEnabled(false);

    for (SignalRecord::Ptr record : records)
    {
        QListWidgetItem* item = new SignalRecordItem(record);
        ui->availableSignals->addItem(item);
    }

    initAvailableElectrodes();
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
        clearAssignment((SignalRecordItem*)selectedItem);
        ui->availableSignals->addItem(selectedItem);
    }
}

OpenSignalFileDialog::SignalRecordItem::SignalRecordItem(SignalRecord::Ptr signalRecord) :
    QListWidgetItem(QString::fromStdString(signalRecord->label())),
    _signalRecord(signalRecord),
    _assignedElectrode("")
{

}

SignalRecord::Ptr OpenSignalFileDialog::SignalRecordItem::signalRecord()
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
        clearAssignment(selected);
        QString electrodeName = ui->availableElectrodes->currentText();
        selected->assignedElectrode(electrodeName);
        ui->availableElectrodes->removeItem(ui->availableElectrodes->currentIndex());
        on_chosenSignals_itemSelectionChanged();
    }
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

    if (ui->chosenSignals->selectedItems().count() > 0)
    {
        ui->clear->setEnabled(true);
    }
    else
    {
        ui->clear->setEnabled(false);
    }
}

void OpenSignalFileDialog::on_buttonBox_accepted()
{

}

void OpenSignalFileDialog::on_autoAssign_clicked()
{
    clearAssignments();

    for (int i = 0; i < ui->chosenSignals->count(); i++)
    {
        auto signal = (SignalRecordItem*)ui->chosenSignals->item(i);
        QString label = QString::fromStdString(signal->signalRecord()->label());
        for (int j = 0; j < ui->availableElectrodes->count(); j++)
        {
            QString elName = ui->availableElectrodes->itemText(j);
            if (label == elName)
            {
                signal->assignedElectrode(elName);
                ui->availableElectrodes->removeItem(j);
            }
        }
    }

    on_chosenSignals_itemSelectionChanged();
}

void OpenSignalFileDialog::on_importAssignment_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select assignment file", "data", "Assignment (*.elass)");

    if (path == "")
        return;

    std::ifstream fin;

    fin.open(path.toStdString());
    if (fin.is_open())
    {
        clearAssignments();

        std::string inputSignalLabel, inputElName;
        while (true)
        {
            if (!(fin >> inputSignalLabel))
                break;
            if (!(fin >> inputElName))
                break;

            SignalRecordItem* searchedSignal = nullptr;
            for (int i = 0; i < ui->chosenSignals->count(); i++)
            {
                auto signal = (SignalRecordItem*)ui->chosenSignals->item(i);
                if (signal->signalRecord()->label() == inputSignalLabel)
                {
                    searchedSignal = signal;
                    break;
                }
            }

            if (searchedSignal)
            {
                int idx = ui->availableElectrodes->findText(QString::fromStdString(inputElName));
                if (idx >= 0)
                {
                    searchedSignal->assignedElectrode(ui->availableElectrodes->itemText(idx));
                    ui->availableElectrodes->removeItem(idx);
                }
            }
        }

        on_chosenSignals_itemSelectionChanged();
    }
}

void OpenSignalFileDialog::on_exportAssignment_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select assignment file", "data", "Assignment (*.elass)");

    if (path == "")
        return;

    std::ofstream fout;

    fout.open(path.toStdString());
    if (fout.is_open())
    {
        for (int i = 0; i < ui->chosenSignals->count(); i++)
        {
            auto signal = (SignalRecordItem*)ui->chosenSignals->item(i);
            auto elName = signal->assignedElectrode().toStdString();
            if (elName != "")
                fout << signal->signalRecord()->label() << " " << elName << std::endl;
        }
    }
}

void OpenSignalFileDialog::initAvailableElectrodes()
{
    ui->availableElectrodes->clear();

    for (std::string elName : _electrodeMap->allNames())
    {
        ui->availableElectrodes->addItem(QString::fromStdString(elName));
    }
}

void OpenSignalFileDialog::clearAssignment(OpenSignalFileDialog::SignalRecordItem *item)
{
    if (item->assignedElectrode() != "")
    {
        ui->availableElectrodes->addItem(item->assignedElectrode());
        item->assignedElectrode("");
    }
}

void OpenSignalFileDialog::clearAssignments()
{
    for (int i = 0; i < ui->chosenSignals->count(); i++)
    {
        auto item = (SignalRecordItem*)ui->chosenSignals->item(i);
        item->assignedElectrode("");
    }

    initAvailableElectrodes();
}

void OpenSignalFileDialog::on_clearAll_clicked()
{
    clearAssignments();
}

void OpenSignalFileDialog::on_clear_clicked()
{
    if (ui->chosenSignals->selectedItems().count() > 0)
    {
        auto selected = ui->chosenSignals->selectedItems();
        for (QListWidgetItem* selectedItem : selected)
        {
            clearAssignment((SignalRecordItem*)selectedItem);
        }
    }
}
