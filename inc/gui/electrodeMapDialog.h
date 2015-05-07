#ifndef ELECTRODEMAPDIALOG_H
#define ELECTRODEMAPDIALOG_H

#include <QDialog>
#include "electrodeMap.h"

namespace Ui {
class ElectrodeMapDialog;
}

class ElectrodeMapDialog : public QDialog
{
    Q_OBJECT

signals:
    void electrodeMapImported();

public:
    explicit ElectrodeMapDialog(QWidget *parent = 0);
    ~ElectrodeMapDialog();

    void assignElectrodeMap(ElectrodeMap* electrodeMap);

private slots:
    void on_importButton_clicked();

    void on_exportButton_clicked();

    void on_import3DButton_clicked();

private:
    Ui::ElectrodeMapDialog *ui;
    ElectrodeMap* _electrodeMap;
};

#endif // ELECTRODEMAPDIALOG_H
