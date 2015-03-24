#ifndef ELECTRODEWINDOW2D_H
#define ELECTRODEWINDOW2D_H

#include <QDialog>
#include "electrodeView2D.h"

namespace Ui {
class ElectrodeWindow2D;
}

class ElectrodeWindow2D : public QDialog
{
    Q_OBJECT

public:
    explicit ElectrodeWindow2D(QWidget *parent = 0);
    ~ElectrodeWindow2D();

    ElectrodeView2D* electrodeView();

private:
    Ui::ElectrodeWindow2D *ui;
};

#endif // ELECTRODEWINDOW2D_H
