#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <signalBatch.h>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

signals:
    void dataFiltered();

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();

    void reset();
    void assignSignalBatch(SignalBatch::WeakPtr signalBatch);

private slots:

    void on_filterButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::FilterDialog *ui;
    SignalBatch::WeakPtr _signalBatch;
};

#endif // FILTERDIALOG_H
