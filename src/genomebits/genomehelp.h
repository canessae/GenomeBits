#ifndef OPENEYA_HELP
#define OPENEYA_HELP

#include <QString>
#include <QWidget>
#include <QTextBrowser>
#include <QtHelp/QHelpEngine>
#include <QLayout>
#include <QVariant>
#include <QtHelp/QHelpContentWidget>
#include <QDir>
#include <QStandardPaths>

/*!
	\brief Help browser class

    This class displays the help of genomebits: is provides
	the way to navigate inside the hyperlinks.
*/
class GenomeTextBrowser:public QTextBrowser
{
	Q_OBJECT
public:
    GenomeTextBrowser(QWidget *parent=0, QHelpEngine *engine=0);
    ~GenomeTextBrowser();
	virtual QVariant loadResource(int, const QUrl &);
private:
	QHelpEngine *helpEngine;
};

class GenomeHelp: public QWidget
{
	Q_OBJECT
public:
    GenomeHelp(QWidget *parent=0, Qt::WindowFlags f=0);
    ~GenomeHelp();
private:
    GenomeTextBrowser *browserWidget;
	QHelpContentWidget *contentWidget;
	QHBoxLayout *mainLayout;
	QHelpEngine *helpEngine;
private slots:
	void slotLinkActivated(const QUrl &);
};

#endif
