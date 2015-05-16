// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODEWINDOW3D_H
#define ELECTRODEWINDOW3D_H

#include <QMainWindow>
#include "electrodeView3D.h"

namespace Ui {
class ElectrodeWindow3D;
}

/**
 * @brief The ElectrodeWindow3D class represents a window that has a 3D electrode view as main element.
 */
class ElectrodeWindow3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit ElectrodeWindow3D(QWidget *parent = 0);
    ~ElectrodeWindow3D();

    /**
     * @brief Getter.
     * @return Electrode view that is contained in the window.
     */
    ElectrodeView3D* electrodeView();

private slots:
    void on_resetViewButton_clicked();

    void on_showNamesCheckBox_toggled(bool checked);

private:
    Ui::ElectrodeWindow3D *ui;
};

#endif // ELECTRODEWINDOW3D_H
