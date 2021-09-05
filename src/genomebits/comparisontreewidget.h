#ifndef COMPARISONTREEWIDGET_H
#define COMPARISONTREEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <aspectratiopixmaplabel.h>
#include <QDir>
#include <QTimer>

#define COMPARISON_PATH      "../scripts"
#define PAPER_PATH           "../doc"

class ComparisonTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ComparisonTreeWidget(QWidget *parent = NULL);

private:
    void displayPng(QString filename);

private slots:
    void slotItemDoubleClicked(QTreeWidgetItem *item, int column);
    void slotTimer();
};

#endif // COMPARISONTREEWIDGET_H
