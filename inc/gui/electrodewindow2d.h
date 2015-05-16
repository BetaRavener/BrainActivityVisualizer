// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODEWINDOW2D_H
#define ELECTRODEWINDOW2D_H

#include <QMainWindow>
#include "electrodeView2D.h"

namespace Ui {
class ElectrodeWindow2D;
}

/**
 * @brief The ElectrodeWindow2D class represents a window that has a 2D electrode view as main element.
 */
class ElectrodeWindow2D : public QMainWindow
{
    Q_OBJECT

public:
    explicit ElectrodeWindow2D(QWidget *parent = 0);
    ~ElectrodeWindow2D();

    /**
     * @brief Getter.
     * @return Electrode view that is contained in the window.
     */
    ElectrodeView2D* electrodeView();

private slots:
    void on_resetViewButton_clicked();

    void on_showNamesCheckBox_toggled(bool checked);

private:
    Ui::ElectrodeWindow2D *ui;
};

#endif // ELECTRODEWINDOW2D_H
