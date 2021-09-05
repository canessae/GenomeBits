#include "comparisontreewidget.h"

ComparisonTreeWidget::ComparisonTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, &ComparisonTreeWidget::itemDoubleClicked, this, &ComparisonTreeWidget::slotItemDoubleClicked);

    QTimer::singleShot(200, this, &ComparisonTreeWidget::slotTimer);
}

void ComparisonTreeWidget::slotTimer()
{
    header()->setStretchLastSection(true);
    expandAll();
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    qApp->processEvents();
    header()->setSectionResizeMode(0, QHeaderView::Interactive);
}

void ComparisonTreeWidget::displayPng(QString filename)
{
    AspectRatioPixmapLabel *widget = new AspectRatioPixmapLabel();
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle(QFileInfo(filename).fileName());
    widget->setPixmap(QPixmap(filename));
    widget->show();
}

void ComparisonTreeWidget::slotItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString filename;
    qDebug("item double clicked: %s %d", qPrintable(item->text(1)), column);

    if (item->text(0) == "Paper:") { //static file
        filename = QDir(PAPER_PATH).absolutePath()+QDir::separator()+item->text(1);
        displayPng(filename);
    }
    else if (QFileInfo(item->text(1)).suffix() == "png") { //dynamic file
        filename = QDir(COMPARISON_PATH).absolutePath()+QDir::separator()+item->text(1);
        displayPng(filename);
    }
}
