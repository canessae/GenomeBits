#include "genomehelp.h"

/////////////////////////////////////////////////////////////
//                  EYA TEXT BROWSER                       //
/////////////////////////////////////////////////////////////
GenomeTextBrowser::GenomeTextBrowser(QWidget *parent, QHelpEngine *engine)
	:QTextBrowser(parent)
{
    helpEngine = engine;
}

GenomeTextBrowser::~GenomeTextBrowser()
{
}

QVariant GenomeTextBrowser::loadResource(int type, const QUrl &name)
{
	qDebug("url=%s",qPrintable(name.toString()));
	if (name.scheme() == "qthelp")
		return QVariant(helpEngine->fileData(name));
	else
		return QTextBrowser::loadResource(type, name);
}

/////////////////////////////////////////////////////////////
//                   GENOMEBITS HELP                       //
/////////////////////////////////////////////////////////////
GenomeHelp::GenomeHelp(QWidget *parent, Qt::WindowFlags f)
	:QWidget(parent,f)
{
    QString collection = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    QDir().mkpath(collection);
    collection.append("genomebits.qhc");
    setWindowTitle(collection);
	mainLayout=new QHBoxLayout;

	//Init variables
	//Before helpEngine, after browserWidget!!
    helpEngine=new QHelpEngine(collection, this);
    helpEngine->setupData();
    if (helpEngine->registerDocumentation("/opt/genomebits/bin/manual.qch"))
        qDebug("Registered documentation");
    else
        qDebug("Error while registering documentation");
    contentWidget = helpEngine->contentWidget();
    browserWidget=new GenomeTextBrowser(this, helpEngine);
    browserWidget->setSource(QUrl("qthelp://genomebits.org.genomebits.1.0/doc/index.html"));

	//Layout
	mainLayout->addWidget(contentWidget,1);
	mainLayout->addWidget(browserWidget,4);
	setLayout(mainLayout);

	//Connections
    connect(contentWidget, &QHelpContentWidget::linkActivated,
            this, &GenomeHelp::slotLinkActivated);

    qDebug("GenomeHelp::GenomeHelp");
}

GenomeHelp::~GenomeHelp()
{
    qDebug("GenomeHelp::~GenomeHelp");
}

void GenomeHelp::slotLinkActivated(const QUrl &link)
{
	browserWidget->setSource(link);
}
