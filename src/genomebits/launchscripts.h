#ifndef LAUNCHSCRIPTS_H
#define LAUNCHSCRIPTS_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>

#define PROGRAM     QString("./z0-run-data-LINUX.pl")
#define PROGRAMM    QString("./z1-ALL-run-4plots-LINUX.pl")
#define WORKPATH    QString("../scripts")
#define CONFPATH    QString("../scripts/x-inputs")
#define PLOTPATH    QString("../scripts/")

class LaunchScripts : public QObject
{
    Q_OBJECT
public:
    LaunchScripts();
    ~LaunchScripts();
    bool prepareScript(bool conf[6]);
    bool prepareMultipleScript();
    void startScript();
    bool copyFastaFile(QString path, int position);
    bool setTxtFile(QString country, int position);
    bool cleanConfigDir();
    bool cleanAllPlotsDir();
    void clearDir(QString toRemove);
    void cancel();
    int getCurrentStep() {return step;};
    QStringList getAllCountries();

private:
    QProcess *proc;
    QString program;
    QStringList args;
    QString countries[12];
    int step; //!< Steps index
    int runningScript; //!< The number of the running step for progressbar
    bool conf[6]; //!< Config of steps, max 6
    bool searchNextStep();
    bool multiple;

private slots:
    void slotReadStdError();
    void slotReadStdOutput();
    void slotFinished(int, QProcess::ExitStatus);

signals:
    void signalSendToTextEdit(QString);
    void signalFinished(int, QProcess::ExitStatus);
    void signalFinishedScript(int);
};

#endif // LAUNCHSCRIPTS_H
