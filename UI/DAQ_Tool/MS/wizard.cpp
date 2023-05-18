#include "wizard.h"
#include "ui_wizard.h"

using namespace std;
using namespace chrono;

Wizard::Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{

    QDir::setCurrent(workingDir);        /* set the current directory where the config file will be written, it will be changed according to defining data path */

//    setWindowFlags(Qt::CustomizeWindowHint);
//    setWindowFlag(Qt::CustomizeWindowHint);
//    setWindowFlag(Qt::WindowCloseButtonHint, false);
//    setWindowFlag(Qt::WindowTitleHint, true);

    ui->setupUi(this);

    Client::writePV("MS:ExperimentalFileName", "testtttttt");
//    ui->usersExperiment->setDisabled(true);
    ui->energyCalibraion->setDisabled(true);
    ui->twoThetaTempScan->setDisabled(true);
    ui->thetaTwoThetaScan->setDisabled(true);

    intervalsTable = new intervals(this);                 /* create a new instance from ::intervals class */
    samplesGUI     = new class samples(this);                   /* create a new instance from ::samples class */

    initializing();

    this->setFixedSize(this->size());   // fix the window size;

    /* create an infinite loop to check some updated fields */
    Timer = new QTimer(this);
    this->Timer->start(100);
    connect(Timer, SIGNAL(timeout()), this, SLOT(checkStatus()));

    connect(this, &QWizard::finished, this, &Wizard::onWizardFinished); /* go to onWizardFinished when an (exit, cancel, finish) emitted signal (but it customized just for "Finish Button") */

    /* get the current time "timeStamp" to be added to the file name */
    system_clock::time_point now = system_clock::now();
    time_t currentTime = system_clock::to_time_t(now);
    tm* currTime = localtime(&currentTime);
    strftime(timeStamp, sizeof(timeStamp), "%Y%m%dT%H%M%S", currTime);
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::initializing()
{
    /* This function to initialize the GUI at startup, it will be called in the constructor,
        mainly, it sets some PVs in the initial state*/

    Client::writePV(MS_ExperimentType, MS_ExperimentType_val);
    Client::writePV(MS_ScanningType, MS_ScanningType_val);
    Client::writePV(MS_ConfigurationsFile, MS_ConfigurationsFile_val);
    Client::writePV(MS_CheckTable, MS_CheckTable_val);
    Client::writePV(MS_CheckSamples, MS_CheckSamples_val);

    ui->proposalIDValue->clear();

    loadFile_ = No;
    startLoading = No;

//    if(configFile_ == 1)
        ui->samplesButton->setEnabled(false);
    ui->validIntervals->setHidden(true);
    ui->validSamples->setHidden(true);
}

void Wizard::intervalsButtonClicked()
{
    intervalsTable->show();     // open the table widget
    intervalsTable->validateTable();
}

void Wizard::on_intervalsButton_clicked()
{
    // this button for twoThetaStep Scan GUI
    intervalsButtonClicked();
//    intervalsTable->loadData("/home/dcasu/UI/DAQ_Tool/MS/tableData.json");
}

void Wizard::on_intervalsButton2_clicked()
{
    // this button for twoThetaTemp Scan GUI
}

void Wizard::on_intervalsButton3_clicked()
{
    // this button for twoThetaSlits Scan GUI
}

void Wizard::on_intervalsButton4_clicked()
{
    // this button for thetaTwoTheta Scan GUI
}

int Wizard::nextId() const
{
    /* this function determines what is the next page based on the current page conditions ,
        if the conditions are true, it will return the nextID, otherwise, the nextID = currentID (will not go to the next) */

    switch(this->currentId())
    {
    case 1:                                                             // the 1st page (experimentType)
        if(experimentType_ == 1)                                        // if it is (Users) go to "proposalID page"
            return 2;
        else if(experimentType_ == 2 or experimentType_ == 3)           // if it is (local or energyCalibration) go to "scanningType page"
            return 3;
        break;

    case 2:             /**********   the validation of proposalID will be added later  **********/
        return 3;
        break;

    case 3:
        if(scanningType_ != 0)                                          // the scanning type must be selected to be able to continue
            return 4;
        break;

    case 4:
        /* if config file = new ==> clear all fields and go to specific ID,
            else go to load config file page */

        if(configFile_ == 1 and scanningType_ == 1)
        {
            clearFields();
            return 6;
        }
        else if(configFile_ == 2 and scanningType_ == 1)
            return 5;
        else if(configFile_ == 1 and scanningType_ == 3)
            return 8;
        else if(configFile_ == 2 and scanningType_ == 3)
            return 5;
        break;

    case 5:
        if(configFile_ == 2 and startLoading == 1)
        {
            return 6;
        }
        break;

    case 6:
        if (intervals_ and samples_ and scans_ and expFileName_ and settlingTime_ and checkTable_ and checkSample_ and checkNSamples_)
        {
        return 10;
        }
        break;

    case 10:
        ui->filePath->setText(workingDir + ui->expFileName->text() + timeStamp + ".xdi");
        return -1;

    default:
        ;
    }
}

void Wizard::clearFields() const
{
    // clear all fields for new config file

    Client::writePV(MS_Intervals, MS_Intervals_val);
    Client::writePV(MS_Samples, MS_Samples_val);
    Client::writePV(MS_Scans, MS_Scans_val);
    Client::writePV(MS_SettlingTime, MS_SettlingTime_val);
    Client::writePV(MS_UseRobot, MS_UseRobot_val);

    usleep(100000);

    ui->intervals->clear();
    ui->samples->clear();
    ui->scans->clear();
    ui->expFileName->clear();
    ui->settlingTime->clear();
    ui->userComments->clear();
    ui->expComments->clear();
}

void Wizard::checkStatus()
{
    // timer loop every 100ms

   experimentType_ = experimentType->get().toInt();
   scanningType_   = scanningType->get().toInt();
   configFile_     = configFile->get().toInt();
   robotInUse_     = robotInUse->get().toInt();
   checkTable_     = checkTable->get().toBool();
   checkSample_    = checkSample->get().toBool();

   if(checkTable_ == 1)
       ui->validIntervals->setHidden(true);
   else
       ui->validIntervals->setHidden(false);

//   if(checkSample_ == 1)
//       ui->validSamples->setHidden(true);
//   else
//       ui->validSamples->setHidden(false);

   if(ui->samples->text().toInt() == samplesGUI->getCheckCount() and checkSample_ == 1)
   {
//       Client::writePV(MS_CheckSamples, Yes);
       ui->validSamples->setHidden(true);
       checkNSamples_ = Yes;
   }
   else
   {
//       Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
       ui->validSamples->setHidden(false);
       checkNSamples_ = No;
   }

   switch (experimentType_)
   {
   case 1:
       experimentTypeS = "Users";
       break;
   case 2:
       experimentTypeS = "Local";
       break;
   case 3:
       experimentTypeS = "Energy Calibration";
       break;
   default:
       experimentTypeS = "";
       break;
   }

   switch (scanningType_)
   {
   case 1:
       scanningTypeS = "Two Theta Step Scan";
       break;
   case 2:
       scanningTypeS = "Two Theta Temperature Scan";
       break;
   case 3:
       scanningTypeS = " Two Theta Scan with Slits Configurations";
       break;
   case 4:
       scanningTypeS = "Theta Two Theta Scan";
       break;
   default:
       scanningTypeS = "";
       break;
   }

   switch (configFile_)
   {
   case 1:
       configFileS = "Created a new one";
       break;
   case 2:
       configFileS = "Loaded";
       break;
   default:
       configFileS = "";
       break;
   }

   switch (robotInUse_)
   {
   case 1:
       robotInUseS = "Yes";
       break;
   case 2:
       robotInUseS = "No";
       break;
   default:
       configFileS = "";
       break;
   }
}

void Wizard::on_intervals_textEdited(const QString &NInt)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(NInt);
    intervalsTable->enterRows(NInt.toInt());
}

void Wizard::on_samples_textEdited(const QString &samples)
{
    // samples validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSamples(samples);
}

void Wizard::on_scans_textEdited(const QString &scans)
{
    // scans validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkScans(scans);
}

void Wizard::on_expFileName_textEdited(const QString &fileName)
{
    // file name validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(fileName);
}

void Wizard::on_settlingTime_textEdited(const QString &settlingTime)
{
    // settling time validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(settlingTime);
}

void Wizard::checkIntervals(const QString &NInt)
{
    // Nintervals validation

    if(regex_match(NInt.toStdString(), regex("^[1-9][0-9]*$")))
    {
        intervals_ = Yes;    // trigger to nextID function
        setBorderLineEdit(No, ui->intervals);       // clear the style sheet
        Client::writePV(MS_CheckTable, MS_CheckTable_val);
        ui->validIntervals->setHidden(false);
    }
    else
    {
        intervals_ = No;
        setBorderLineEdit(Yes, ui->intervals);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter valid Number of intervals");
    }
}

void Wizard::checkSamples(const QString &samples)
{
    // samples validation

//    if(regex_match(samples.toStdString(), regex("^[1-9][0-9]*$")))
    if(samples.toInt() > 0 and samples.toInt() < 41)
    {
        samples_ = Yes;
        ui->samplesButton->setEnabled(true);
        setBorderLineEdit(No, ui->samples);       // clear the style sheet
    }
    else
    {
        samples_ = No;
        ui->samplesButton->setEnabled(false);

        setBorderLineEdit(Yes, ui->samples);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid number of Samples, and, make sure to click on the Samples button to keep or change the default values");
    }

    if(samples.toInt() != samplesGUI->getCheckCount())
    {
        Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
        ui->validSamples->setHidden(false);
    }
}

void Wizard::checkScans(const QString &scans)
{
    // scans validation

    if(regex_match(scans.toStdString(), regex("^[1-9][0-9]*$")))
    {
        scans_ = Yes;
        setBorderLineEdit(No, ui->scans);       // clear the style sheet
    }
    else
    {
        scans_ = No;
        setBorderLineEdit(Yes, ui->scans);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid number of scans");
    }
}

void Wizard::checkExpFileName(const QString &fileName)
{
    // file name validation

    if((regex_match(fileName.toStdString(), regex("^[a-z|A-Z|0-9]*[a-z|A-Z|0-9|_]+"))))
    {
        expFileName_ = Yes;

        configFileName = ui->expFileName->text() + "_" + timeStamp + ".config";
        fullFileName = fileName;
        setBorderLineEdit(No, ui->expFileName);       // clear the style sheet
    }
    else
    {
        expFileName_ = No;
        setBorderLineEdit(Yes, ui->expFileName);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid data file name");
    }
}

void Wizard::checkSettlingTime(const QString &settlingTime)
{
    // settling time validation

    if(regex_match(settlingTime.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+")))
    {
        settlingTime_ = Yes;
        setBorderLineEdit(No, ui->settlingTime);       // clear the style sheet
    }
    else
    {
        settlingTime_ = No;
        setBorderLineEdit(Yes, ui->settlingTime);       // clear the style sheet
//        UImessage(UItittle, "Please enter a valid settling time");
    }
}

void Wizard::configFileCheck()
{
//    checkIntervals(ui->intervals->text());
    checkSamples(ui->samples->text());
    checkScans(ui->scans->text());
    checkExpFileName(ui->expFileName->text());
    checkSettlingTime(ui->settlingTime->text());
}

void Wizard::on_loadConfigFileButton_clicked()
{
    // get and validate the config file chosen

    loadedFileName = QFileDialog::getOpenFileName(this, "Open", workingDir);   // open file dialog

    if(loadedFileName.endsWith(".config"))
    {
        if (!loadedFileName.isEmpty()) {
            ui->expConfigFile->setText(loadedFileName);
            setBorderLabel(No, ui->expConfigFile);       // clear the style sheet
            startLoading = Yes;
            loadConfigFile(loadedFileName);
        }
        else
        {
            ui->expConfigFile->setText("File is empty!!");
            setBorderLabel(Yes, ui->expConfigFile);
            startLoading = No;
        }
    }
    else
    {
        ui->expConfigFile->setText("File Error!!");
        setBorderLabel(Yes, ui->expConfigFile);
        startLoading = No;
    }
}

void Wizard::loadConfigFile(const QString& configFile)
{
    QFile file(configFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();        // can use QStreamTex, but QByte array easier ti use
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        QJsonObject jsonObj = jsonDoc.object();

        ui->intervals->setText(jsonObj["NIntervals"].toString());
        Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
        checkIntervals(ui->intervals->text());

        intervalsTable->loadIntervalsFromJson(jsonObj["Intervals"].toArray());
        ui->samples->setText(jsonObj["NSamples"].toString());
        samplesGUI->loadSamplesData(jsonObj["Samples"].toArray());
        ui->scans->setText(jsonObj["Nscans"].toString());
        ui->expFileName->setText(jsonObj["expFileName"].toString());
        ui->settlingTime->setText(jsonObj["settlingTime"].toString());
        ui->userComments->setText(jsonObj["userComments"].toString());
        ui->expComments->setText(jsonObj["expComments"].toString());
        const char* pvName = "MS:ExperimentalFileName";
        const char* value = "Hellohgds, sdadsdfsfdfdsasadasd!";
        writeStringWaveform(pvName, value);

        Client::writePV(MS_Samples, jsonObj["NSamples"].toString());
        Client::writePV(MS_Scans, jsonObj["Nscans"].toString());
        Client::writePV(MS_SettlingTime, jsonObj["settlingTime"].toString());
        Client::writePV(MS_UseRobot,jsonObj["robotInUse"].toString());

        configFileCheck();

        loadFile_ = Yes;
    }
    else
    {
        loadFile_ = No;
//        QMessageBox::information(this,"MS/XRD scan tool","Unable to read configuration file, scanning can not continue!!");
        ui->filePath->setText("Unable to read configuration file, scanning can not continue!!");
    }
}

void Wizard::createConfigFile(QString &config)
{
    QFile file(config);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject jsonObj;

        jsonObj["expType"]          = experimentTypeS;
        jsonObj["scanningType"]     = scanningTypeS;
        jsonObj["loadedConfig"]     = configFileS;
        jsonObj["NIntervals"]       = ui->intervals->text();
        jsonObj["Intervals"]        = intervalsTable->createIntervalsJson();
        jsonObj["NSamples"]         = ui->samples->text();
        jsonObj["Samples"]          = samplesGUI->getSamplesData();
        jsonObj["Nscans"]           = ui->scans->text();
        jsonObj["expFileName"]      = fullFileName;
        jsonObj["settlingTime"]     = ui->settlingTime->text();
        jsonObj["robotInUse"]       = robotInUseS;
        jsonObj["userComments"]     = ui->userComments->text();
        jsonObj["expComments"]      = ui->expComments->text();

        QJsonDocument jsonDoc(jsonObj);
        file.write(jsonDoc.toJson());
    }
}
void Wizard::onWizardFinished(int order)
{
    if(order == QDialog::Accepted)     // it works just on "finish button"
    {
        if(configFile_ == 2)
            configFileName = ui->expFileName->text() + "_" + timeStamp + ".config";
        createConfigFile(configFileName);
    }
}

void Wizard::setBorderLineEdit(bool val, QLineEdit *lineEdit)
{
    if(val)
        lineEdit->setStyleSheet("border: 2.25px solid red;");
    else
        lineEdit->setStyleSheet("");
}

void Wizard::setBorderLabel(bool val, QLabel* label)
{
    if(val)
        label->setStyleSheet("border: 2.25px solid red;");
    else
        label->setStyleSheet("");
}

void Wizard::UImessage(const QString &tittle, const QString &message)
{
    QMessageBox::information(this, tittle, message);
}

void Wizard::on_samplesButton_clicked()
{
    samplesGUI->show();
}

void Wizard::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->ignore();    // ignore the Escape button press event
    }
}

void Wizard::closeEvent(QCloseEvent *event)
{
    event->ignore();       // Ignore the close event
}

void Wizard::writeStringWaveform(const char* pvName, const char* value) {
        // Initialize the Channel Access library
        SEVCHK(ca_context_create(ca_disable_preemptive_callback), "Failed to create Channel Access context");

        // Create the Channel Access channel
        chid channel;
        SEVCHK(ca_create_channel(pvName, NULL, NULL, CA_PRIORITY_DEFAULT, &channel), "Failed to create channel");

        // Wait for the connection to be established
        SEVCHK(ca_pend_io(10.0), "Connection timeout");

        // Write the string to the waveform PV
        if (ca_state(channel) == cs_conn) {
            unsigned long numElements = strlen(value);  // Number of elements in the waveform

            // Allocate a DBR_CHAR waveform buffer
            dbr_char_t* buffer = static_cast<dbr_char_t*>(calloc(numElements, sizeof(dbr_char_t)));

            // Copy the string to the waveform buffer
            strncpy(reinterpret_cast<char*>(buffer), value, numElements);

            // Write the string to the waveform PV
            SEVCHK(ca_array_put(DBR_CHAR, numElements, channel, buffer), "Failed to write to PV");
            SEVCHK(ca_flush_io(), "Failed to flush I/O");
            std::cout << "String written to PV successfully." << std::endl;

            // Clean up the waveform buffer
            free(buffer);
        } else {
            std::cerr << "Channel is not connected." << std::endl;
        }

        // Clean up and release resources
        ca_clear_channel(channel);
//        ca_context_destroy();
    }
