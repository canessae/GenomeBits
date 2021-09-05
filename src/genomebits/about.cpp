#include "about.h"

About::About(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent, f), ui(new Ui::About)
{
    ui->setupUi(this);
}
