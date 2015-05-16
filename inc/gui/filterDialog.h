// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <signalBatch.h>

namespace Ui {
class FilterDialog;
}

/**
 * @brief The FilterDialog class represents a dialog which exposes the signal filtering methods to the user.
 */
class FilterDialog : public QDialog
{
    Q_OBJECT

signals:
    /**
     * @brief Signal fires when the data has been successfully filtered.
     */
    void dataFiltered();

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();

    /**
     * @brief Resets the dialog to default state.
     */
    void reset();

    /**
     * @brief Assigns signal batch that will serve as data source for filtering.
     * @param signalBatch A group of signals which can be filtered.
     */
    void assignSignalBatch(SignalBatch::WeakPtr signalBatch);

private slots:

    void on_filterButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::FilterDialog *ui;
    SignalBatch::WeakPtr _signalBatch;
};

#endif // FILTERDIALOG_H
