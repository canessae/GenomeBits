#include "showtext.h"
#include "ui_showtext.h"

ShowText::ShowText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowText)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
}

ShowText::~ShowText()
{
    delete ui;
}

bool ShowText::loadTxtFile(QString filename, int columns)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    this->filename = filename;

    QTextStream stream(&file);
    ui->textEdit->setText(stream.readAll());
    ui->textEdit->setLineWrapMode(QTextEdit::FixedColumnWidth);
    ui->textEdit->setLineWrapColumnOrWidth(columns);
    ui->textEdit->setMinimumWidth(ui->textEdit->document()->idealWidth() +
                                  ui->textEdit->contentsMargins().left() +
                                  ui->textEdit->contentsMargins().right());

    file.close();
    return true;
}

void ShowText::on_pushButton_clicked()
{
    QString saveFilename = QFileDialog::getSaveFileName(NULL, "Save file as");
    if (saveFilename.isEmpty())
        return;

    QFile::copy(filename, saveFilename);
}
