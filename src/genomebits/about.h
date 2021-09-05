#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QWidget>

#include "ui_about.h"

class About: public QDialog
{
    Q_OBJECT
public:
    About(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    Ui::About *ui;
};

#endif // ABOUT_H
