#include "license.h"

License::License(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent, f), ui(new Ui::License)
{
    ui->setupUi(this);
}
