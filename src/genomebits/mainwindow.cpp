#include "mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initCountries(ui->comboBox_1a);
    ui->comboBox_1a->setCurrentText("Italy"); //default
    initCountries(ui->comboBox_1b);
    initCountries(ui->comboBox_2a);
    initCountries(ui->comboBox_2b);
    initCountries(ui->comboBox_3a);
    initCountries(ui->comboBox_3b);
    initCountries(ui->comboBox_4a);
    initCountries(ui->comboBox_4b);
    initCountries(ui->comboBox_5a);
    initCountries(ui->comboBox_5b);
    initCountries(ui->comboBox_6a);
    initCountries(ui->comboBox_6b);

    ui->progressScript->setValue(0);

    license = NULL;
    about = NULL;
    manual = NULL;
    script = NULL;
    scriptMultiple = NULL;

    //Set the version number
    QString title = this->windowTitle()+" v";
    title += CURRVERSION;
    this->setWindowTitle(title);

    connect(&status, &ProcessingStatus::signalEnableTabs, this, &MainWindow::slotEnableTabs);
    status.init();
}

MainWindow::~MainWindow()
{
    delete ui;

    if (license)
        delete license;
    license = NULL;

    if (about)
        delete about;
    about = NULL;

    if (manual)
        delete manual;
    manual = NULL;

    if (script)
        delete script;
    script = NULL;
}


void MainWindow::on_pushButton_clicked(QLineEdit *lineEdit)
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Select FASTA file"), QString(), "FASTA files (*.fasta *.fas)");
    if (!fileName.isEmpty())
        lineEdit->setText(fileName);
}


void MainWindow::on_pushButton_1a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_1a);
}

void MainWindow::on_pushButton_1b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_1b);
}

void MainWindow::on_pushButton_2a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_2a);
}

void MainWindow::on_pushButton_2b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_2b);
}

void MainWindow::on_pushButton_3a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_3a);
}

void MainWindow::on_pushButton_3b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_3b);
}

void MainWindow::on_pushButton_4a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_4a);
}

void MainWindow::on_pushButton_4b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_4b);
}

void MainWindow::on_pushButton_5a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_5a);
}

void MainWindow::on_pushButton_5b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_5b);
}

void MainWindow::on_pushButton_6a_clicked()
{
    on_pushButton_clicked(ui->lineEdit_6a);
}

void MainWindow::on_pushButton_6b_clicked()
{
    on_pushButton_clicked(ui->lineEdit_6b);
}

void MainWindow::initCountries(QComboBox *combo)
{
    QStringList countries;

    countries << "None";
    for (int i = 1; i < QLocale::LastCountry-1; ++i)
    {
        countries << QLocale::countryToString((QLocale::Country)i);
    }
    combo->addItems(countries);
}

void MainWindow::slotEnableTabs(QVector<bool> s)
{
    for (int i=0; i<s.length(); i++)
        ui->tabs->setTabEnabled(i, s[i]);
}

void MainWindow::slotActionLicense()
{
    if (!license)
        license = new License(this);
    license->show();
}

void MainWindow::slotActionAbout()
{
    if (!about)
        about = new About(this);
    about->show();
}

void MainWindow::slotActionManual()
{
    qDebug("void MainWindow::slotActionManual()");
    if (!manual)
        manual = new GenomeManual;
    manual->show();
}

void MainWindow::slotReadyReadStandardOutput(QString msg)
{
    ui->outputScriptTextEdit->append(msg);
}

void MainWindow::slotReadyReadMultipleStandardOutput(QString msg)
{
    ui->outputScriptMultipleTextEdit->append(msg);
}

void MainWindow::slotReadyReadStandardError(QString msg)
{
    ui->outputScriptTextEdit->append(msg);
}

void MainWindow::slotReadyReadMultipleStandardError(QString msg)
{
    ui->outputScriptMultipleTextEdit->append(msg);
}

void MainWindow::slotAllScriptsFinished(int code, QProcess::ExitStatus status)
{
    if (sender() == script) { //this is for first run tab
        ui->runButton->setText(RUN_BUTTON);
        ui->runButton->setStyleSheet("background-color:yellow");
        //button enabled
        ui->runMultipleButton->setEnabled(true); //re-enable runmultiple
        this->status.slotRunSumsFinished(true);
        //store variants configuration in status class
        QVector<bool> variants(VARIANT_MAX, false);
        variants[0] = ui->groupBox_1->isChecked();
        variants[1] = ui->groupBox_2->isChecked();
        variants[2] = ui->groupBox_3->isChecked();
        variants[3] = ui->groupBox_4->isChecked();
        variants[4] = ui->groupBox_5->isChecked();
        variants[5] = ui->groupBox_6->isChecked();
        this->status.setVariants(variants);
        // Set tabs of variants in outputs
        for (int i=0; i<VARIANT_MAX; i++) {
            ui->tabWidgetOuputVariants->setTabEnabled(i, variants[i]);
        }
    }
    else {
        if (status == 0){ //this is for multiple run tab
            QStringList countries;
            QVector<bool> selectedVariants = this->status.getVariants();
            ui->runMultipleButton->setText(RUN_BUTTON);
            ui->runMultipleButton->setStyleSheet("background-color:yellow");
            ui->tabWidgetMultipleVariants->setTabEnabled(0, false);
            ui->tabWidgetMultipleVariants->setTabEnabled(1, false);
            ui->tabWidgetMultipleVariants->setTabEnabled(2, false);
            ui->tabWidgetMultipleVariants->setTabEnabled(3, false);
            ui->tabWidgetMultipleVariants->setTabEnabled(4, false);
            ui->tabWidgetMultipleVariants->setTabEnabled(5, false);

            QStringList allCountries = script->getAllCountries(); //get countries from previous step
            ui->treeWidgetPlot1->cleanupTree();
            if (selectedVariants[0]) {
                countries << allCountries.at(0) << allCountries.at(1);
                ui->treeWidgetPlot1->setVariant(countries, 1);
                ui->treeWidgetPlot1->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(0, true);
            }

            ui->treeWidgetPlot2->cleanupTree();
            countries.clear();
            if (selectedVariants[1]) {
                countries << allCountries.at(2) << allCountries.at(3);
                ui->treeWidgetPlot2->setVariant(countries, 2);
                ui->treeWidgetPlot2->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(1, true);
            }

            ui->treeWidgetPlot3->cleanupTree();
            countries.clear();
            if (selectedVariants[2]) {
                countries << allCountries.at(4) << allCountries.at(5);
                ui->treeWidgetPlot3->setVariant(countries, 3);
                ui->treeWidgetPlot3->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(2, true);
            }

            ui->treeWidgetPlot4->cleanupTree();
            countries.clear();
            if (selectedVariants[3]) {
                countries << allCountries.at(6) << allCountries.at(7);
                ui->treeWidgetPlot4->setVariant(countries, 4);
                ui->treeWidgetPlot4->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(3, true);
            }

            ui->treeWidgetPlot5->cleanupTree();
            countries.clear();
            if (selectedVariants[4]) {
                countries << allCountries.at(8) << allCountries.at(9);
                ui->treeWidgetPlot5->setVariant(countries, 5);
                ui->treeWidgetPlot5->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(4, true);
            }

            ui->treeWidgetPlot6->cleanupTree();
            countries.clear();
            if (selectedVariants[5]) {
                countries << allCountries.at(10) << allCountries.at(11);
                ui->treeWidgetPlot6->setVariant(countries, 6);
                ui->treeWidgetPlot6->populateTree();
                ui->tabWidgetMultipleVariants->setTabEnabled(5, true);
            }

            ui->runButton->setEnabled(true);
            this->status.slotRunMultipleFinished(true);
        }
        else
            this->status.slotRunMultipleFinished(false);
    }
}

void MainWindow::slotFinishedScript(int running)
{
    ui->progressScript->setValue(running);

    QStringList allCountries = script->getAllCountries();
    qDebug("current step: %d", script->getCurrentStep());
    switch (script->getCurrentStep()) {
    case 0:
        ui->treeWidget11->cleanupContryTree();
        if (allCountries.size()>=1) {
            ui->treeWidget11->setCountry(allCountries.at(0), 1);
            ui->treeWidget11->populateCountryTree();
        }
        ui->treeWidget12->cleanupContryTree();
        if (allCountries.size()>=2) {
            ui->treeWidget12->setCountry(allCountries.at(1), 1);
            ui->treeWidget12->populateCountryTree();
        }
        break;
    case 1:
        ui->treeWidget21->cleanupContryTree();
        if (allCountries.size()>=3) {
            ui->treeWidget21->setCountry(allCountries.at(2), 2);
            ui->treeWidget21->populateCountryTree();
        }
        ui->treeWidget22->cleanupContryTree();
        if (allCountries.size()>=4) {
            ui->treeWidget22->setCountry(allCountries.at(3), 2);
            ui->treeWidget22->populateCountryTree();
        }
        break;
    case 2:
        ui->treeWidget31->cleanupContryTree();
        if (allCountries.size()>=5) {
            ui->treeWidget31->setCountry(allCountries.at(4), 3);
            ui->treeWidget31->populateCountryTree();
        }
        ui->treeWidget32->cleanupContryTree();
        if (allCountries.size()>=6) {
            ui->treeWidget32->setCountry(allCountries.at(5), 3);
            ui->treeWidget32->populateCountryTree();
        }
        break;
    case 3:
        ui->treeWidget41->cleanupContryTree();
        if (allCountries.size()>=7) {
            ui->treeWidget41->setCountry(allCountries.at(6), 4);
            ui->treeWidget41->populateCountryTree();
        }
        ui->treeWidget42->cleanupContryTree();
        if (allCountries.size()>=8) {
            ui->treeWidget42->setCountry(allCountries.at(7), 4);
            ui->treeWidget42->populateCountryTree();
        }
        break;
    case 4:
        ui->treeWidget51->cleanupContryTree();
        if (allCountries.size()>=9) {
            ui->treeWidget51->setCountry(allCountries.at(8), 5);
            ui->treeWidget51->populateCountryTree();
        }
        ui->treeWidget52->cleanupContryTree();
        if (allCountries.size()>=10) {
            ui->treeWidget52->setCountry(allCountries.at(9), 5);
            ui->treeWidget52->populateCountryTree();
        }
        break;
    case 5:
        ui->treeWidget61->cleanupContryTree();
        if (allCountries.size()>=11) {
            ui->treeWidget61->setCountry(allCountries.at(10), 6);
            ui->treeWidget61->populateCountryTree();
        }
        ui->treeWidget62->cleanupContryTree();
        if (allCountries.size()>=12) {
            ui->treeWidget62->setCountry(allCountries.at(11), 6);
            ui->treeWidget62->populateCountryTree();
        }
        break;
    }
}

void MainWindow::slotFinishedMultipleScript(int running)
{
    ui->progressMultipleScript->setValue(running);
}

void MainWindow::on_runButton_clicked()
{
    QStringList countriesList;

    if (ui->runButton->text() == RUN_BUTTON) {
        if (script)
            delete script;
        script = new LaunchScripts;
        connect(script, &LaunchScripts::signalSendToTextEdit, this, &MainWindow::slotReadyReadStandardOutput);
        connect(script, &LaunchScripts::signalFinished, this, &MainWindow::slotAllScriptsFinished);
        connect(script, &LaunchScripts::signalFinishedScript, this, &MainWindow::slotFinishedScript);

        ui->outputScriptTextEdit->clear();
        slotReadyReadStandardOutput("Cleaning configuration files...");
        script->cleanConfigDir();

        //CONFIG files
        if (ui->groupBox_1->isChecked()) {
            if (ui->comboBox_1a->currentText()==ui->comboBox_1b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_1a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_1a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }
            script->copyFastaFile(ui->lineEdit_1a->text(), 11);
            script->setTxtFile(ui->comboBox_1a->currentText(), 11);
            slotReadyReadStandardOutput("Writing configuration file 1a...");
            countriesList << ui->comboBox_1a->currentText();

            if (ui->comboBox_1b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_1b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_1b->text(), 12);
                script->setTxtFile(ui->comboBox_1b->currentText(), 12);
                slotReadyReadStandardOutput("Writing configuration file 1b...");
                countriesList << ui->comboBox_1b->currentText();
            }

        }
        if (ui->groupBox_2->isChecked()) {
            if (ui->comboBox_2a->currentText()==ui->comboBox_2b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_2a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_2a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }            
            script->copyFastaFile(ui->lineEdit_2a->text(), 21);
            script->setTxtFile(ui->comboBox_2a->currentText(), 21);
            slotReadyReadStandardOutput("Writing configuration file 2a...");
            countriesList << ui->comboBox_2a->currentText();

            if (ui->comboBox_2b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_2b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_2b->text(), 22);
                script->setTxtFile(ui->comboBox_2b->currentText(), 22);
                slotReadyReadStandardOutput("Writing configuration file 2b...");
                countriesList << ui->comboBox_2b->currentText();
            }

        }
        if (ui->groupBox_3->isChecked()) {
            if (ui->comboBox_3a->currentText()==ui->comboBox_3b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_3a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_3a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }            
            script->copyFastaFile(ui->lineEdit_3a->text(), 31);
            script->setTxtFile(ui->comboBox_3a->currentText(), 31);
            slotReadyReadStandardOutput("Writing configuration file 3a...");
            countriesList << ui->comboBox_3a->currentText();

            if (ui->comboBox_3b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_3b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_3b->text(), 32);
                script->setTxtFile(ui->comboBox_3b->currentText(), 32);
                slotReadyReadStandardOutput("Writing configuration file 3b...");
                countriesList << ui->comboBox_3b->currentText();
            }

        }
        if (ui->groupBox_4->isChecked()) {
            if (ui->comboBox_4a->currentText()==ui->comboBox_4b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_4a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_4a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }            
            script->copyFastaFile(ui->lineEdit_4a->text(), 41);
            script->setTxtFile(ui->comboBox_4a->currentText(), 41);
            slotReadyReadStandardOutput("Writing configuration file 4a...");
            countriesList << ui->comboBox_4a->currentText();

            if (ui->comboBox_4b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_4b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_4b->text(), 42);
                script->setTxtFile(ui->comboBox_4b->currentText(), 42);
                slotReadyReadStandardOutput("Writing configuration file 4b...");
                countriesList << ui->comboBox_4b->currentText();
            }

        }
        if (ui->groupBox_5->isChecked()) {
            if (ui->comboBox_5a->currentText()==ui->comboBox_5b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_5a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_5a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }            
            script->copyFastaFile(ui->lineEdit_5a->text(), 51);
            script->setTxtFile(ui->comboBox_5a->currentText(), 51);
            slotReadyReadStandardOutput("Writing configuration file 5a...");
            countriesList << ui->comboBox_5a->currentText();

            if (ui->comboBox_5b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_5b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_5b->text(), 52);
                script->setTxtFile(ui->comboBox_5b->currentText(), 52);
                slotReadyReadStandardOutput("Writing configuration file 5b...");
                countriesList << ui->comboBox_5b->currentText();
            }

        }
        if (ui->groupBox_6->isChecked()) {
            if (ui->comboBox_6a->currentText()==ui->comboBox_6b->currentText()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The two countries for ONE variant MUST BE different."));
                return;
            }
            // Check country
            if (ui->comboBox_6a->currentText() == "None") {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("The country parameter cannot be set to None."));
                return;
            }
            // Check FASTA if country is not empty
            if (ui->lineEdit_6a->text().isEmpty()) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("FASTA file is empty, check the configuration."));
                return;
            }            
            script->copyFastaFile(ui->lineEdit_6a->text(), 61);
            script->setTxtFile(ui->comboBox_6a->currentText(), 61);
            slotReadyReadStandardOutput("Writing configuration file 6a...");
            countriesList << ui->comboBox_6a->currentText();

            if (ui->comboBox_6b->currentText() != "None") {
                // Check FASTA if country is not empty
                if (ui->lineEdit_6b->text().isEmpty()) {
                    QMessageBox::information(this,
                                             tr("Unable to start processing"),
                                             tr("FASTA file is empty, check the configuration."));
                    return;
                }
                script->copyFastaFile(ui->lineEdit_6b->text(), 62);
                script->setTxtFile(ui->comboBox_6b->currentText(), 62);
                slotReadyReadStandardOutput("Writing configuration file 6b...");
                countriesList << ui->comboBox_6b->currentText();
            }

        }

        //Check NONE in country ??TODO
        if (countriesList.isEmpty()) {
            QMessageBox::information(this,
                                     tr("Unable to start processing"),
                                     tr("At least one country must be selected."));
            return;
        }

        //Start processing
        checkedVariants[0] = ui->groupBox_1->isChecked();
        checkedVariants[1] = ui->groupBox_2->isChecked();
        checkedVariants[2] = ui->groupBox_3->isChecked();
        checkedVariants[3] = ui->groupBox_4->isChecked();
        checkedVariants[4] = ui->groupBox_5->isChecked();
        checkedVariants[5] = ui->groupBox_6->isChecked();
        //Check variants continuity
        int diff;
        for (int i=0; i<5; i++) {
            diff = ((int)checkedVariants[i+1])-((int)checkedVariants[i]);
            if (diff>0) {
                QMessageBox::information(this,
                                         tr("Unable to start processing"),
                                         tr("Variants cannot be skipped"));
                return;
            }
        }
        if (! script->prepareScript(checkedVariants)) {
            QMessageBox::information(this,
                                     tr("Unable to start processing"),
                                     tr("No variants have been checked"));
            return;
        }
        //Set the progressbar
        int cnt = 0;
        for (int i=0; i<6; i++)
            cnt += checkedVariants[i];
        ui->progressScript->setRange(0, cnt);
        //end progressbar
        script->startScript();
        ui->runButton->setText(STOP_BUTTON);
        ui->runButton->setStyleSheet("background-color:red");
        // button disable
        ui->runMultipleButton->setEnabled(false);
        status.slotRunSumsStarted();
    }
    else { //STOP
        script->cancel();
        ui->runButton->setText(RUN_BUTTON);
        ui->runButton->setStyleSheet("background-color:yellow");
        ui->runMultipleButton->setEnabled(false);
        status.slotRunSumsFinished(false);
    }
}


void MainWindow::on_selectAllButton_clicked()
{
    ui->groupBox_1->setChecked(true);
    ui->groupBox_2->setChecked(true);
    ui->groupBox_3->setChecked(true);
    ui->groupBox_4->setChecked(true);
    ui->groupBox_5->setChecked(true);
    ui->groupBox_6->setChecked(true);
}

void MainWindow::on_unselectAllButton_clicked()
{
    ui->groupBox_1->setChecked(true);
    ui->groupBox_2->setChecked(false);
    ui->groupBox_3->setChecked(false);
    ui->groupBox_4->setChecked(false);
    ui->groupBox_5->setChecked(false);
    ui->groupBox_6->setChecked(false);
}

void MainWindow::on_cleanButton_1a_clicked()
{
    ui->lineEdit_1a->setText(QString());
}

void MainWindow::on_cleanButton_1b_clicked()
{
    ui->lineEdit_1b->setText(QString());
}

void MainWindow::on_cleanButton_2a_clicked()
{
    ui->lineEdit_2a->setText(QString());
}

void MainWindow::on_cleanButton_2b_clicked()
{
    ui->lineEdit_2b->setText(QString());
}

void MainWindow::on_cleanButton_3a_clicked()
{
    ui->lineEdit_3a->setText(QString());
}

void MainWindow::on_cleanButton_3b_clicked()
{
    ui->lineEdit_3b->setText(QString());
}

void MainWindow::on_cleanButton_4a_clicked()
{
    ui->lineEdit_4a->setText(QString());
}

void MainWindow::on_cleanButton_4b_clicked()
{
    ui->lineEdit_4b->setText(QString());
}

void MainWindow::on_cleanButton_5a_clicked()
{
    ui->lineEdit_5a->setText(QString());
}

void MainWindow::on_cleanButton_5b_clicked()
{
    ui->lineEdit_5b->setText(QString());
}

void MainWindow::on_cleanButton_6a_clicked()
{
    ui->lineEdit_6a->setText(QString());
}

void MainWindow::on_cleanButton_6b_clicked()
{
    ui->lineEdit_6b->setText(QString());
}

void MainWindow::on_runMultipleButton_clicked()
{
    if (ui->runMultipleButton->text() == RUN_BUTTON) {
        if (scriptMultiple)
            delete scriptMultiple;
        scriptMultiple = new LaunchScripts;
        connect(scriptMultiple, &LaunchScripts::signalSendToTextEdit, this, &MainWindow::slotReadyReadMultipleStandardOutput);
        connect(scriptMultiple, &LaunchScripts::signalFinished, this, &MainWindow::slotAllScriptsFinished);
        connect(scriptMultiple, &LaunchScripts::signalFinishedScript, this, &MainWindow::slotFinishedMultipleScript);

        ui->outputScriptMultipleTextEdit->clear();
        scriptMultiple->cleanAllPlotsDir();
        scriptMultiple->prepareMultipleScript();
        scriptMultiple->startScript();
        ui->runMultipleButton->setText(STOP_BUTTON);
        ui->runMultipleButton->setStyleSheet("background-color:red");
        ui->runButton->setEnabled(false);
        status.slotRunMultipleStarted();
    }
    else { //STOP
        scriptMultiple->cancel();
        ui->runMultipleButton->setText(RUN_BUTTON);
        ui->runMultipleButton->setStyleSheet("background-color:yellow");
        ui->runButton->setEnabled(true);
        status.slotRunMultipleFinished(false);
    }
}
