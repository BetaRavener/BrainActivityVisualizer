// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "mainwindow.h"

#include <QApplication>
#include <QtGui/QScreen>
#include <QtGui/QSurface>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
