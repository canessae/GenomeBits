#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("ICTP");
    app.setApplicationName("GenomeBits");
    app.setOrganizationDomain("genomebits.org");

    QPixmap pixmap(":/icons/Logo5.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    splash.showMessage(QString("Welcome to GenomeBits!"), Qt::AlignBottom|Qt::AlignCenter);

    MainWindow w;

    app.processEvents();
    QTimer::singleShot(3000, &splash, &QWidget::close);

    w.show();

    return app.exec();
}
