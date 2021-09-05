#ifndef GENOMEMANUAL_H
#define GENOMEMANUAL_H

#include <QWidget>

namespace Ui {
class GenomeManual;
}

class GenomeManual : public QWidget
{
    Q_OBJECT

public:
    explicit GenomeManual(QWidget *parent = nullptr);
    ~GenomeManual();

private:
    Ui::GenomeManual *ui;
};

#endif // GENOMEMANUAL_H
