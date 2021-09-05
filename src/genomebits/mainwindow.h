#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLocale>
#include <QDebug>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QToolBox>
#include <QVector>

#include "./ui_mainwindow.h"
#include "./ui_license.h"
#include "./ui_about.h"

#include "license.h"
#include "about.h"
#include "launchscripts.h"
#include "countrytreewidget.h"
#include "plottreewidget.h"
#include "processingstatus.h"
#include "genomemanual.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define STOP_BUTTON    "STOP"
#define RUN_BUTTON     "RUN"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotEnableTabs(QVector<bool>);
    void slotActionLicense();
    void slotActionAbout();
    void slotActionManual();
    void slotReadyReadStandardOutput(QString);
    void slotReadyReadStandardError(QString);
    void slotReadyReadMultipleStandardOutput(QString);
    void slotReadyReadMultipleStandardError(QString);
    void slotAllScriptsFinished(int, QProcess::ExitStatus);
    void slotFinishedScript(int);
    void slotFinishedMultipleScript(int);

    void on_pushButton_1a_clicked();
    void on_pushButton_1b_clicked();
    void on_pushButton_2a_clicked();
    void on_pushButton_2b_clicked();
    void on_pushButton_3a_clicked();
    void on_pushButton_3b_clicked();
    void on_pushButton_4a_clicked();
    void on_pushButton_4b_clicked();
    void on_pushButton_5a_clicked();
    void on_pushButton_5b_clicked();
    void on_pushButton_6a_clicked();
    void on_pushButton_6b_clicked();

    void on_runButton_clicked();

    void on_selectAllButton_clicked();
    void on_unselectAllButton_clicked();

    void on_cleanButton_1a_clicked();
    void on_cleanButton_1b_clicked();
    void on_cleanButton_2a_clicked();
    void on_cleanButton_2b_clicked();
    void on_cleanButton_3a_clicked();
    void on_cleanButton_3b_clicked();
    void on_cleanButton_4a_clicked();
    void on_cleanButton_4b_clicked();
    void on_cleanButton_5a_clicked();
    void on_cleanButton_5b_clicked();
    void on_cleanButton_6a_clicked();
    void on_cleanButton_6b_clicked();

    void on_runMultipleButton_clicked();

private:
    Ui::MainWindow *ui;
    License *license;
    About *about;
    GenomeManual *manual;
    LaunchScripts *script, *scriptMultiple;
    bool checkedVariants[6];
    ProcessingStatus status;
    void initCountries(QComboBox *);
    void on_pushButton_clicked(QLineEdit *);

};
#endif // MAINWINDOW_H
