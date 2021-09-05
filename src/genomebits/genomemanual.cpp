#include "genomemanual.h"
#include "ui_genomemanual.h"

GenomeManual::GenomeManual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenomeManual)
{
    ui->setupUi(this);
}

GenomeManual::~GenomeManual()
{
    delete ui;
}
