#ifndef SHOWTEXT_H
#define SHOWTEXT_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QString>

namespace Ui {
class ShowText;
}

class ShowText : public QWidget
{
    Q_OBJECT

public:
    explicit ShowText(QWidget *parent = nullptr);
    ~ShowText();
    bool loadTxtFile(QString filename, int columns = 80);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowText *ui;
    QString filename;
};

#endif // SHOWTEXT_H
