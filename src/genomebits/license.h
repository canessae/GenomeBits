#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>
#include <QWidget>

#include "ui_license.h"

class License : public QDialog
{
    Q_OBJECT
public:
    License(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    Ui::License *ui;
};

#endif // LICENSE_H
