#include "filterDialog.h"
#include "ui_filterDialog.h"

#include "lowpassFilter.h"
#include "highpassFilter.h"
#include "signalWindow.h"
#include "hammingWindow.h"
#include "blackmanWindow.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    ui->filterComboBox->addItem("Lowpass");
    ui->filterComboBox->addItem("Highpass");

    ui->windowComboBox->addItem("Rectangular");
    ui->windowComboBox->addItem("Hamming");
    ui->windowComboBox->addItem("Blackman");
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::reset()
{
    ui->filterProgressBar->setMinimum(0);
    ui->filterProgressBar->setMaximum(1);
    ui->filterProgressBar->setValue(0);
}

void FilterDialog::assignSignalBatch(SignalBatch::WeakPtr signalBatch)
{
    _signalBatch = signalBatch;
}

void FilterDialog::on_filterButton_clicked()
{
    if (!_signalBatch)
        return;

    FilterWindow* window;
    unsigned int halfLength = ui->halfLengthSpinBox->value();
    switch (ui->windowComboBox->currentIndex())
    {
    case 0:
        window = new FilterWindow(halfLength * 2 + 1);
        break;
    case 1:
        window = new HammingWindow(halfLength * 2 + 1);
        break;
    case 2:
        window = new BlackmanWindow(halfLength * 2 + 1);
        break;
    }

    SignalFilter* filter = nullptr;
    double cutoffFreq = ui->cutoffFrequencySpinBox->value();

    unsigned processedIdx = 0;
    ui->filterProgressBar->setMinimum(0);
    ui->filterProgressBar->setMaximum(_signalBatch->dataSignals().size());
    ui->filterProgressBar->setValue(processedIdx);

    for (SignalData::Ptr signalData : _signalBatch->dataSignals())
    {
        switch (ui->filterComboBox->currentIndex())
        {
        case 0:
            filter = new LowpassFilter(halfLength, cutoffFreq, signalData->samplingFreq());
            break;
        case 1:
            filter = new HighpassFilter(halfLength, cutoffFreq, signalData->samplingFreq());
            break;
        }

        filter->process(signalData, *window);
        ui->filterProgressBar->setValue(++processedIdx);

        delete filter;
        filter = nullptr;
    }

    delete window;
    window = nullptr;

    emit dataFiltered();
}

void FilterDialog::on_closeButton_clicked()
{
    this->close();
}
