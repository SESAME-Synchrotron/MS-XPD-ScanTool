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

    /* lambda function to set the fields as mandatory fields, it is called in const function */
//    connect(this, &Wizard::mandatorySignal, [=]()
//    {
//        switch (mandotarySignalN) {
//        case 1:
//            setBorderLineEdit(Yes, ui->intervals);
//            setBorderLineEdit(Yes, ui->samples);
//            setBorderLineEdit(Yes, ui->scans);
//            setBorderLineEdit(Yes, ui->expFileName);
//            setBorderLineEdit(Yes, ui->settlingTime);
//            setBorderLineEdit(Yes, ui->sampleNameVal);
//            break;
//        case 3:
//            setBorderLineEdit(Yes, ui->intervals3);
//            setBorderLineEdit(Yes, ui->samples3);
//            setBorderLineEdit(Yes, ui->scans3);
//            setBorderLineEdit(Yes, ui->expFileName3);
//            setBorderLineEdit(Yes, ui->settlingTime3);
//            setBorderLineEdit(Yes, ui->sampleNameVal3);
//            break;
//        }
//    });

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
    Client::writePV(MS_StartScan, MS_StartScan_val);
    Client::writePV(MS_StopScan, MS_StopScan_val);
    Client::writePV(MS_FinishScan, MS_FinishScan_val);
    Client::writePV(MS_CancelScan, MS_CancelScan_val);
    Client::writePV(MS_TestingMode, MS_TestingMode_val);

    ui->proposalIDValue->clear();

    loadFile_ = No;
    startLoading = No;

//    if(configFile_ == 1)
//    switch (scanningType->get().toInt()) {

//    case 1:
        ui->samplesButton->setEnabled(false);
        ui->validIntervals->setHidden(true);
        ui->validSamples->setHidden(true);
//        break;

//    case 3:
        ui->samplesButton3->setEnabled(false);
        ui->validIntervals3->setHidden(true);
        ui->validSamples3->setHidden(true);
//        break;
//    }
}

void Wizard::intervalsButtonClicked()
{
    intervalsTable->show();     // open the table widget
}

void Wizard::on_intervalsButton_clicked()
{
    // this button for twoThetaStep Scan GUI
    intervalsButtonClicked();
}

void Wizard::on_intervalsButton2_clicked()
{
    // this button for twoThetaTemp Scan GUI
}

void Wizard::on_intervalsButton3_clicked()
{
    // this button for twoThetaSlits Scan GUI
    intervalsButtonClicked();
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
        else
            return 0;
        break;

    case 2:             /**********   the validation of proposalID will be added later  **********/
        return 3;
        break;

    case 3:
        if(scanningType_ != 0)                                          // the scanning type must be selected to be able to continue
            return 4;
        else
            return 0;
        break;

    case 4:
        /* if config file = new ==> clear all fields and go to specific ID,
            else go to load config file page */

        if(configFile_ == 1 and scanningType_ == 1)
        {
            clearFields();
            return 6;
        }
        else if(configFile_ == 2 and (scanningType_ == 1 or scanningType_ == 3))
            return 5;
        else if(configFile_ == 1 and scanningType_ == 3)
        {
            clearFields();
            return 6;
        }
        else
            return 0;
        break;

    case 5:
        if(configFile_ == 2 and startLoading == 1)
            return 6;
        else
            return 0;
        break;

    case 6:
        /* if the robot is not used, disable the samples GUI, beacuse by default the N samples = 1 */

        if(!robotInUse_)
        {
            switch (scanningType_)
            {
            case 1:
                ui->samplesLabel->setHidden(true);
                ui->samples->setHidden(true);
                ui->samplesButton->setHidden(true);
                ui->validSamples->setHidden(true);

                ui->sampleName->setHidden(false);
                ui->sampleNameVal->setHidden(false);

                return 7;
                break;

            case 3:
                ui->samplesLabel3->setHidden(true);
                ui->samples3->setHidden(true);
                ui->samplesButton3->setHidden(true);
                ui->validSamples3->setHidden(true);

                ui->sampleName3->setHidden(false);
                ui->sampleNameVal3->setHidden(false);

                return 9;
                break;
            }
            break;
        }

        else
        {
            switch (scanningType_)
            {
            case 1:
                ui->samplesLabel->setHidden(false);
                ui->samples->setHidden(false);
                ui->samplesButton->setHidden(false);
                ui->validSamples->setHidden(false);

                ui->sampleName->setHidden(true);
                ui->sampleNameVal->setHidden(true);

                return 7;
                break;

            case 3:
                ui->samplesLabel3->setHidden(false);
                ui->samples3->setHidden(false);
                ui->samplesButton3->setHidden(false);
                ui->validSamples3->setHidden(false);

                ui->sampleName3->setHidden(true);
                ui->sampleNameVal3->setHidden(true);

                return 9;
                break;
            }
            break;
        }


    case 7:
        if(robotInUse_)
        {
            if(intervals_ and samples_ and scans_ and expFileName_ and settlingTime_ and checkTable_ and checkSample_ and checkNSamples_)
                return 11;
            else
                return 0;
        }
        else
        {
            if(intervals_ and scans_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_)
                return 11;
            else
                return 0;
        }
        break;

    case 9:
        if(robotInUse_)
        {
            if(intervals_ and samples_ and scans_ and expFileName_ and settlingTime_ and checkTable_ and checkSample_ and checkNSamples_)
                return 11;
            else
                return 0;
        }
        else
        {
            if(intervals_ and scans_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_)
                return 11;
            else
                return 0;
        }
        break;

    case 11:
        ui->filePath->setText(workingDir + ui->expFileName->text() + timeStamp + ".xdi");
        return -1;

    default:
        return 0;
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

    switch (scanningType_)
    {
    case 1:
        ui->intervals->clear();
        ui->samples->clear();
        ui->scans->clear();
        ui->expFileName->clear();
        ui->settlingTime->clear();
        ui->userComments->clear();
        ui->expComments->clear();
        ui->sampleNameVal->clear();
//        mandotarySignalN = 1;
//        emit this->mandatorySignal();   // set mandotry field
        break;

    case 3:
        ui->intervals3->clear();
        ui->samples3->clear();
        ui->scans3->clear();
        ui->expFileName3->clear();
        ui->settlingTime3->clear();
        ui->userComments3->clear();
        ui->expComments3->clear();
        ui->sampleNameVal3->clear();
//        mandotarySignalN = 3;
//        emit this->mandatorySignal();    // set mandotry field
        break;
    }
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

   switch (scanningType_) {
   case 1:
       if(checkTable_ == 1)
           ui->validIntervals->setHidden(true);
       else
           ui->validIntervals->setHidden(false);
       break;

   case 3:
       if(checkTable_ == 1)
           ui->validIntervals3->setHidden(true);
       else
           ui->validIntervals3->setHidden(false);
       break;
   }

   if(robotInUse_)
   {

       switch (scanningType_)
       {
       case 1:
           if(ui->samples->text().toInt() == samplesGUI->getCheckCount() and checkSample_ == 1)
           {
               ui->validSamples->setHidden(true);
               checkNSamples_ = Yes;
           }
           else
           {
               ui->validSamples->setHidden(false);
               checkNSamples_ = No;
           }
           break;

       case 3:
           if(ui->samples3->text().toInt() == samplesGUI->getCheckCount() and checkSample_ == 1)
           {
               ui->validSamples3->setHidden(true);
               checkNSamples_ = Yes;
           }
           else
           {
               ui->validSamples3->setHidden(false);
               checkNSamples_ = No;
           }
           break;
       }
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
   case 0:
       robotInUseS = "No";
       break;
   case 1:
       robotInUseS = "Yes";
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
        checkIntervals(NInt, ui->intervals);
    intervalsTable->enterRows(NInt.toInt());
}

void Wizard::on_samples_textEdited(const QString &samples)
{
    // samples validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSamples(samples, ui->samples);
}

void Wizard::on_scans_textEdited(const QString &scans)
{
    // scans validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkScans(scans, ui->scans);
}

void Wizard::on_expFileName_textEdited(const QString &fileName)
{
    // file name validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(fileName, ui->expFileName);
}

void Wizard::on_settlingTime_textEdited(const QString &settlingTime)
{
    // settling time validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(settlingTime, ui->settlingTime);
}

void Wizard::on_sampleNameVal_textEdited(const QString &sampleName)
{
    // sample name validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSampleName(ui->sampleNameVal);
}

void Wizard::checkIntervals(const QString &NInt, QLineEdit* lineEdit)
{
    // Nintervals validation

    if(regex_match(NInt.toStdString(), regex("^[1-9][0-9]*$")))
    {
        intervals_ = Yes;    // trigger to nextID function
        setBorderLineEdit(No, lineEdit);       // clear the style sheet
        Client::writePV(MS_CheckTable, MS_CheckTable_val);

        switch (scanningType_) {

        case 1:
            ui->validIntervals->setHidden(false);
            break;

        case 3:
            ui->validIntervals3->setHidden(false);
            break;
        }
    }
    else
    {
        intervals_ = No;
        setBorderLineEdit(Yes, lineEdit);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter valid Number of intervals");
    }
}

void Wizard::checkSamples(const QString &samples, QLineEdit* lineEdit)
{
    // samples validation

//    if(regex_match(samples.toStdString(), regex("^[1-9][0-9]*$")))
    if(samples.toInt() > 0 and samples.toInt() < 41)
    {
        samples_ = Yes;
        switch (scanningType_) {

        case 1:
            ui->samplesButton->setEnabled(true);
            break;

        case 3:
            ui->samplesButton3->setEnabled(true);
            break;
        }
        setBorderLineEdit(No, lineEdit);       // clear the style sheet
    }
    else
    {
        samples_ = No;
        switch (scanningType_) {

        case 1:
            ui->samplesButton->setEnabled(false);
            break;

        case 3:
            ui->samplesButton3->setEnabled(false);
            break;
        }

        setBorderLineEdit(Yes, lineEdit);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid number of Samples, and, make sure to click on the Samples button to keep or change the default values");
    }

    if(samples.toInt() != samplesGUI->getCheckCount())
    {
        Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
        switch (scanningType_) {

        case 1:
            ui->validSamples->setHidden(false);
            break;

        case 3:
            ui->validSamples3->setHidden(false);
            break;
        }
    }
}

void Wizard::checkScans(const QString &scans, QLineEdit* lineEdit)
{
    // scans validation

    if(regex_match(scans.toStdString(), regex("^[1-9][0-9]*$")))
    {
        scans_ = Yes;
        setBorderLineEdit(No, lineEdit);       // clear the style sheet
    }
    else
    {
        scans_ = No;
        setBorderLineEdit(Yes, lineEdit);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid number of scans");
    }
}

void Wizard::checkExpFileName(const QString &fileName, QLineEdit* lineEdit)
{
    // file name validation

    if((regex_match(fileName.toStdString(), regex("^[a-z|A-Z|0-9]*[a-z|A-Z|0-9|_]+"))))
    {
        expFileName_ = Yes;

        configFileName = ui->expFileName->text() + "_" + timeStamp + ".config";
        fullFileName = fileName;
        setBorderLineEdit(No, lineEdit);       // clear the style sheet
    }
    else
    {
        expFileName_ = No;
        setBorderLineEdit(Yes, lineEdit);     // set the style sheet (red border)
//        UImessage(UItittle, "Please enter a valid data file name");
    }
}

void Wizard::checkSettlingTime(const QString &settlingTime, QLineEdit* lineEdit)
{
    // settling time validation

    if(regex_match(settlingTime.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+")))
    {
        settlingTime_ = Yes;
        setBorderLineEdit(No, lineEdit);       // clear the style sheet
    }
    else
    {
        settlingTime_ = No;
        setBorderLineEdit(Yes, lineEdit);       // clear the style sheet
//        UImessage(UItittle, "Please enter a valid settling time");
    }
}

void Wizard::checkSampleName(QLineEdit* lineEdit)
{
   if(lineEdit->text().trimmed().isEmpty())
   {
       sampleName_ = No;
       setBorderLineEdit(Yes, lineEdit);
   }
   else
   {
       sampleName_ = Yes;
       setBorderLineEdit(No, lineEdit);
   }
}

void Wizard::configFileCheck()
{
    switch (scanningType_) {

    case 1:
    //    checkIntervals(ui->intervals->text());
        checkSamples(ui->samples->text(), ui->samples);
        checkScans(ui->scans->text(), ui->scans);
        checkExpFileName(ui->expFileName->text(), ui->expFileName);
        checkSettlingTime(ui->settlingTime->text(), ui->settlingTime);
        break;

    case 3:
        checkSamples(ui->samples3->text(), ui->samples3);
        checkScans(ui->scans3->text(), ui->scans3);
        checkExpFileName(ui->expFileName3->text(), ui->expFileName3);
        checkSettlingTime(ui->settlingTime3->text(), ui->settlingTime3);
        break;
    }

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
        QByteArray jsonData = file.readAll();        // can use QStreamTex, but QByte array easier to use
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        QJsonObject jsonObj = jsonDoc.object();

        switch (scanningType_) {

        case 1:
            ui->intervals->setText(jsonObj["NIntervals"].toString());
            Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
            checkIntervals(ui->intervals->text(), ui->intervals);

            ui->samples->setText(jsonObj["NSamples"].toString());
            ui->scans->setText(jsonObj["Nscans"].toString());
            ui->expFileName->setText(jsonObj["expFileName"].toString());
            ui->settlingTime->setText(jsonObj["settlingTime"].toString());
            ui->userComments->setText(jsonObj["userComments"].toString());
            ui->expComments->setText(jsonObj["expComments"].toString());

            break;

        case 3:
            ui->intervals3->setText(jsonObj["NIntervals"].toString());
            Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
            checkIntervals(ui->intervals3->text(), ui->intervals3);

            ui->samples3->setText(jsonObj["NSamples"].toString());
            ui->scans3->setText(jsonObj["Nscans"].toString());
            ui->expFileName3->setText(jsonObj["expFileName"].toString());
            ui->settlingTime3->setText(jsonObj["settlingTime"].toString());
            ui->userComments3->setText(jsonObj["userComments"].toString());
            ui->expComments3->setText(jsonObj["expComments"].toString());
            break;
        }

        intervalsTable->loadIntervalsFromJson(jsonObj["Intervals"].toArray());

        if(robotInUse_)
            samplesGUI->loadSamplesData(jsonObj["Samples"].toArray());
        else
        {
            switch (scanningType_)
            {
            case 1:
                ui->sampleNameVal->setText(jsonObj["Sample"].toString());
                Client::writeStringToWaveform(MS_Sample, jsonObj["Sample"].toString());
                break;

            case 3:
                ui->sampleNameVal3->setText(jsonObj["Sample"].toString());
                Client::writeStringToWaveform(MS_Sample, jsonObj["Sample"].toString());
                break;
            }
        }

        Client::writePV(MS_Samples, jsonObj["NSamples"].toString());
        Client::writePV(MS_Scans, jsonObj["Nscans"].toString());
        Client::writePV(MS_SettlingTime, jsonObj["settlingTime"].toString());
        Client::writePV(MS_UseRobot,jsonObj["robotInUse"].toString());
        Client::writeStringToWaveform(MS_ExperimentFileName, jsonObj["expFileName"].toString());
        Client::writeStringToWaveform(MS_UserComments, jsonObj["userComments"].toString());
        Client::writeStringToWaveform(MS_ExperimentComments, jsonObj["expComments"].toString());

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

        switch (scanningType_) {

        case 1:
            jsonObj["NIntervals"]       = ui->intervals->text();
            jsonObj["NSamples"]         = ui->samples->text();
            jsonObj["Nscans"]           = ui->scans->text();
            jsonObj["settlingTime"]     = ui->settlingTime->text();
            jsonObj["userComments"]     = ui->userComments->text();
            jsonObj["expComments"]      = ui->expComments->text();

            break;

        case 3:
            jsonObj["NIntervals"]       = ui->intervals3->text();
            jsonObj["NSamples"]         = ui->samples3->text();
            jsonObj["Nscans"]           = ui->scans3->text();
            jsonObj["settlingTime"]     = ui->settlingTime3->text();
            jsonObj["userComments"]     = ui->userComments3->text();
            jsonObj["expComments"]      = ui->expComments3->text();

            break;
        }

        jsonObj["expType"]          = experimentTypeS;
        jsonObj["scanningType"]     = scanningTypeS;
        jsonObj["loadedConfig"]     = configFileS;
        jsonObj["Intervals"]        = intervalsTable->createIntervalsJson();

        if(robotInUse_)
            jsonObj["Samples"]      = samplesGUI->getSamplesData();
        else
        {
            switch (scanningType_)
            {
            case 1:
                jsonObj["Sample"] = ui->sampleNameVal->text();
                break;

            case 3:
                jsonObj["Sample"] = ui->sampleNameVal3->text();
                break;
            }
        }

        jsonObj["expFileName"]      = fullFileName;
        jsonObj["robotInUse"]       = robotInUseS;

        QJsonDocument jsonDoc(jsonObj);
        file.write(jsonDoc.toJson());
    }
}
void Wizard::onWizardFinished(int order)
{
    if(order == QDialog::Accepted)     // it works just on "finish button"
    {
        Client::writePV(MS_StartScan, Yes);

        if(configFile_ == 2)
            configFileName = ui->expFileName->text() + "_" + timeStamp + ".config";
        createConfigFile(configFileName);
    }

    if(order == QDialog::Rejected)
        Client::writePV(MS_CancelScan, Yes);
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
    samplesGUI->initializing();
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

void Wizard::on_intervals3_textEdited(const QString &arg1)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(arg1, ui->intervals3);
    intervalsTable->enterRows(arg1.toInt());
}

void Wizard::on_samples3_textEdited(const QString &arg1)
{
    // samples validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSamples(arg1, ui->samples3);
}

void Wizard::on_scans3_textEdited(const QString &arg1)
{
    // scans validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkScans(arg1, ui->scans3);
}

void Wizard::on_expFileName3_textEdited(const QString &arg1)
{
    // file name validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(arg1, ui->expFileName3);
}

void Wizard::on_settlingTime3_textEdited(const QString &arg1)
{
    // settling time validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(arg1, ui->settlingTime3);
}

void Wizard::on_sampleNameVal3_textEdited(const QString &arg1)
{
    // Ssample name validation

    if(configFile_ == 1 or loadFile_ ==1)
        checkSampleName(ui->sampleNameVal3);
}

void Wizard::on_samplesButton3_clicked()
{
    samplesGUI->initializing();
    samplesGUI->show();
}
