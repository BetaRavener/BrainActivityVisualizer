#ifndef ELECTRODEWINDOW3D_H
#define ELECTRODEWINDOW3D_H

#include <QDialog>
#include "electrodeView3D.h"

namespace Ui {
class ElectrodeWindow3D;
}

class ElectrodeWindow3D : public QDialog
{
    Q_OBJECT

public:
    explicit ElectrodeWindow3D(QWidget *parent = 0);
    ~ElectrodeWindow3D();

    ElectrodeView3D* electrodeView();

private:
    Ui::ElectrodeWindow3D *ui;
};

#endif // ELECTRODEWINDOW3D_H
