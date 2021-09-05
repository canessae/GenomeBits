#include "launchscripts.h"

LaunchScripts::LaunchScripts()
{
    proc = NULL;
    step = -1;
    runningScript = 0;
    multiple = false;
}

LaunchScripts::~LaunchScripts()
{
    if (proc)
        delete proc;
    proc = NULL;
}

bool LaunchScripts::prepareScript(bool conf[6])
{
    if (proc)
        delete proc;
    proc = new QProcess;
    runningScript = 0;
    multiple = false;

    connect(proc, &QProcess::readyReadStandardError, this, &LaunchScripts::slotReadStdError);
    connect(proc, &QProcess::readyReadStandardOutput, this, &LaunchScripts::slotReadStdOutput);
    connect(proc, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &LaunchScripts::slotFinished);

    proc->setWorkingDirectory(WORKPATH);
    step = -1;
    memcpy(this->conf, conf, sizeof(bool)*6);
    program = QString(PROGRAM);

    emit signalFinishedScript(runningScript); //send 0 for reset purpose

    return searchNextStep();
}

bool LaunchScripts::prepareMultipleScript()
{
    if (proc)
        delete proc;
    proc = new QProcess;
    runningScript = 0;
    multiple = true;
    args.clear();

    connect(proc, &QProcess::readyReadStandardError, this, &LaunchScripts::slotReadStdError);
    connect(proc, &QProcess::readyReadStandardOutput, this, &LaunchScripts::slotReadStdOutput);
    connect(proc, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &LaunchScripts::slotFinished);

    proc->setWorkingDirectory(WORKPATH);
    program = QString(PROGRAMM);

    emit signalFinishedScript(runningScript); //send 0 for reset purpose

    return true;
}

void LaunchScripts::startScript()
{
    qDebug("######## STARTING %d ########", step);
    proc->start(program, args);
}

//11=1a 12=1b
bool LaunchScripts::copyFastaFile(QString srcPath, int position)
{
    QString dstPath = CONFPATH;
    QString prefix;
    QString dstFilename;

    prefix = QString("%1-").arg(position/10);
    prefix += ((position&0x01)==1)?"a-":"b-";

    qDebug("fasta %s", qPrintable(srcPath));
    dstFilename = QFileInfo(srcPath).fileName();
    if (QFileInfo(srcPath).suffix().toUpper() == "FAS")
        dstFilename = QFileInfo(srcPath).baseName()+".fasta";

    return QFile::copy(srcPath, dstPath+QDir::separator()+prefix+dstFilename);
}

bool LaunchScripts::setTxtFile(QString country, int position)
{
    QString prefix = QString("%1-").arg(position/10);
    prefix += ((position&0x01)==1)?"a":"b";

    QFile file(CONFPATH+QDir::separator()+prefix+".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    //Replace spaces with underscore
    country.replace(" ", "_");
    int idx = 2*(position/10-1) + (position-position/10*10)-1;
    qDebug("%s idx: %d", qPrintable(country), idx);
    countries[idx] = country.toUpper();
    out << country.toUpper() << "\n";

    file.close();
    return true;
}

bool LaunchScripts::cleanConfigDir()
{
    QDir dir(CONFPATH);

    // Remove config file in x-inputs
    dir.setNameFilters(QStringList() << "*.txt" << "*.fasta");
    dir.setFilter(QDir::Files);

    for(const QString &dirFile: dir.entryList()) {
        dir.remove(dirFile);
    }

    // Remove output files
    dir = QDir(PLOTPATH);
    QList<QString> list = dir.entryList(QStringList() << "?-input");
    for(const QString &dirFile: list) {
        QString toRemove = dir.absolutePath()+QDir::separator()+dirFile+QDir::separator();
        clearDir(toRemove);
        qDebug("removing: %s", qPrintable(toRemove));
    }

    return true;
}

bool LaunchScripts::cleanAllPlotsDir()
{
    QDir rootDir(PLOTPATH);

    QList<QString> list = rootDir.entryList(QStringList() << "?-input-PLOTS");
    for(const QString &dirFile: list) {
        QString toRemove = rootDir.absolutePath()+QDir::separator()+dirFile+QDir::separator();
        clearDir(toRemove);
        qDebug("removing: %s", qPrintable(toRemove));
    }

    return true;
}

void LaunchScripts::clearDir(QString toRemove)
{
    QDir dir(toRemove);

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
    foreach( QString dirItem, dir.entryList() )
        dir.remove( dirItem );

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
    foreach( QString dirItem, dir.entryList() )
    {
        QDir subDir( dir.absoluteFilePath( dirItem ) );
        subDir.removeRecursively();
    }
}

void LaunchScripts::cancel()
{
    if (proc) {
        proc->kill();
        delete proc;
        proc = NULL;
        step = 7;
    }
}

QStringList LaunchScripts::getAllCountries()
{
    QStringList ret;

    for (int i=0; i<12; i++) {
        ret.append(QString(countries[i]));
        qDebug("getAllCountries: %s", qPrintable(ret.last()));
    }

    return ret;
}

bool LaunchScripts::searchNextStep()
{
    step++;
    args.clear();
    // Search for groupbox checked
    while (!(this->conf[step]) && step<6)
        step ++;
    // Use found checked groupbox if possible
    if (step<6 && this->conf[step])
        args.append(QString("%1").arg(step+1));
    else
        return false;

    runningScript++;
    return true;
}

void LaunchScripts::slotReadStdError()
{
    QString msg = proc->readAllStandardError();

    emit signalSendToTextEdit(msg);
}

void LaunchScripts::slotReadStdOutput()
{
    QString msg = proc->readAllStandardOutput();

    emit signalSendToTextEdit(msg);
}

void LaunchScripts::slotFinished(int code, QProcess::ExitStatus status)
{
    qDebug("Finished %d", code);
    emit signalSendToTextEdit("Script execution completed.");
    if (multiple)
        runningScript = 1;
    emit signalFinishedScript(runningScript);
    if (!searchNextStep() || multiple)
        emit signalFinished(code, status);
    else {
        startScript();
    }
}
