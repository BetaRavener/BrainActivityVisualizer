// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODEMAPDIALOG_H
#define ELECTRODEMAPDIALOG_H

#include <QDialog>
#include "electrodeMap.h"

namespace Ui {
class ElectrodeMapDialog;
}

/**
 * @brief The ElectrodeMapDialog class represents a dialog for importing and exporting electrode maps
 * and electrode positions
 */
class ElectrodeMapDialog : public QDialog
{
    Q_OBJECT

signals:
    /**
     * @brief Signal fires when new electrode map was imported.
     */
    void electrodeMapImported();

public:
    explicit ElectrodeMapDialog(QWidget *parent = 0);
    ~ElectrodeMapDialog();

    /**
     * @brief Assigns electrode map which the dialog will work with.
     * @param electrodeMap
     */
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
