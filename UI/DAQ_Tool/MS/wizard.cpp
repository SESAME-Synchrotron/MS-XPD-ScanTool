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

    ui->energyCalibraion->setHidden(true);
//    ui->thetaTwoThetaScan->setDisabled(true);
//    ui->twoThetaTempScan->setDisabled(true);
//    ui->twoThetaSlitsScan->setDisabled(true);

    ui->Yes->setHidden(true);
    ui->No->setHidden(true);
    ui->proposalIDWarning->setHidden(true);

    intervalsTable = new intervals(this);                 /* create a new instance from ::intervals class */
    samplesGUI     = new class samples(this);             /* create a new instance from ::samples class */

    initializing();

    this->setFixedSize(this->size());   // fix the window size;

    /* create an infinite loop to check some updated fields */
    Timer = new QTimer(this);
    this->Timer->start(100);
    connect(Timer, SIGNAL(timeout()), this, SLOT(checkStatus()));

    connect(this, &QWizard::finished, this, &Wizard::onWizardFinished); /* go to onWizardFinished when an (exit, cancel, finish) emitted signal (but it customized just for "Finish Button") */
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
    Client::writePV(MS_ProposalID, MS_ProposalID_val);
    Client::writePV(MS_ScanningType, MS_ScanningType_val);
    Client::writePV(MS_ConfigurationsFile, MS_ConfigurationsFile_val);
    Client::writePV(MS_PickingOrder, MS_PickingOrder_val);
    Client::writePV(MS_CheckTable, MS_CheckTable_val);
    Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
    Client::writePV(MS_CancelScan, MS_CancelScan_val);
    Client::writePV(MS_GIXRD, MS_GIXRD_val);
    /* The rest of PVs are used in UI Visualization */
    Client::writePV(MS_TestingMode, MS_TestingMode_val);
    Client::writePV(MS_Notifications, MS_Notifications_val);
    Client::writePV(MS_ScanStatus, MS_ScanStatus_val);
    Client::writePV(MS_StartTime, MS_StartTime_val);
    Client::writePV(MS_EndTime, MS_EndTime_val);
    Client::writePV(MS_CurrentSample, MS_CurrentSample_val);
    Client::writePV(MS_CurrentInterval, MS_CurrentInterval_val);
    Client::writePV(MS_CurrentScan, MS_CurrentScan_val);
    Client::writePV(MS_CurrentPoint, MS_CurrentPoint_val);
    Client::writePV(MS_TotalPoints, MS_TotalPoints_val);
    Client::writePV(MS_CollectedPoint, MS_CollectedPoint_val);
    Client::writePV(MS_TotalCollectedPoints, MS_TotalCollectedPoints_val);
    Client::writePV(MS_AllTotalCollectedPoints, MS_AllTotalCollectedPoints_val);
    Client::writePV(MS_IntervalRemaningTime, MS_IntervalRemainingTime_val);
    Client::writePV(MS_ScanRemaningTime, MS_ScanRemainingTime_val);
    Client::writePV(MS_SampleName, MS_SampleName_val);
    Client::writePV(MS_SkippedSamples, MS_SkippedSamples_val);
    Client::writePV(MS_NotReturnSamples, MS_NotReturnSamples_val);

    ui->proposalIDValue->clear();

    loadFile_ = No;
    startLoading = No;

    ui->samplesButton->setEnabled(false);
    ui->validIntervals->setHidden(true);
    ui->validSamples->setHidden(true);
    ui->waitingTime->setEnabled(false);

    ui->validIntervals2->setHidden(true);

    ui->samplesButton3->setEnabled(false);
    ui->validIntervals3->setHidden(true);
    ui->validSamples3->setHidden(true);
    ui->waitingTime3->setEnabled(false);

    ui->waitingTime4->setEnabled(false);
}

void Wizard::intervalsButtonClicked()
{
    intervalsTable->show();     // open the table widget
}

void Wizard::on_intervalsButton_clicked()
{
    // this button for twoThetaStep Scan GUI
    intervalsTable->modifyTable();
    intervalsButtonClicked();
}

void Wizard::on_intervalsButton2_clicked()
{
    // this button for twoThetaTemp Scan GUI
    intervalsTable->modifyTable();
    intervalsButtonClicked();
}

void Wizard::on_intervalsButton3_clicked()
{
    // this button for twoThetaSlits Scan GUI
    intervalsTable->modifyTable();
    intervalsButtonClicked();
}

void Wizard::on_intervalsButton4_clicked()
{
    // this button for thetaTwoTheta Scan GUI
    intervalsTable->modifyTable();
    intervalsButtonClicked();
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
            return 1;
        break;

    case 2:
        /**********   check if the proposal ID is valid, and scheduled (in general)  **********/
        if(validProposalID_ and validateProposalID)
            return 3;
        else
            return 2;
        break;

    case 3:
        if(scanningType_ != 0)                                          // the scanning type must be selected to be able to continue
        {
            if(checkScanningType_ != this->scanningType->get().toInt())     // clear the loaded config file if scanning type has been changed (see case 5)
                ui->expConfigFile->clear();
            return 4;
        }
        else
            return 3;
        break;

    case 4:
        /* if config file = new ==> clear all fields and go to specific ID,
            else go to load config file page */

        if(configFile_ == 1 and scanningType_ == 1)
        {
            clearFields();
            return 6;
        }
        else if(configFile_ == 1 and scanningType_ == 2)
        {
            clearFields();
            return 8;
        }
        else if(configFile_ == 1 and scanningType_ == 3)
        {
            clearFields();
            return 6;
        }
        else if(configFile_ == 1 and scanningType_ == 4)
        {
            clearFields();
            return 10;
        }
        else if(configFile_ == 2 and (scanningType_ == 1 or scanningType_ == 2 or scanningType_ == 3 or scanningType_ == 4))
            return 5;
        else
            return 4;
        break;

    case 5:
        checkScanningType_ = this->scanningType->get().toInt();
        if(configFile_ == 2 and startLoading and !ui->expConfigFile->text().isEmpty())
        {
            if(scanningType_ == 2)
                return 8;
            else if(scanningType_ == 4)
                return 10;
            else
                return 6;
        }
        else
            return 5;
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
            if(intervals_ and samples_ and scans_ and waitingTime_ and expFileName_ and settlingTime_ and checkTable_ and checkSample_ and checkNSamples_)
                return 11;
            else
                return 7;
        }
        else
        {
            if(intervals_ and scans_ and waitingTime_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_)
                return 11;
            else
                return 7;
        }
        break;

    case 8:
        if(intervals_ and deadband_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_)
            return 11;
        else
            return 8;
        break;

    case 9:
        loadSlitsConfig();

        if(robotInUse_)
        {
            if(intervals_ and samples_ and scans_ and waitingTime_ and expFileName_ and settlingTime_ and checkTable_ and checkSample_ and checkNSamples_
                    and xRange_ and xVal_ and yStartVal_ and yEndVal_ and sampleToDetDis_ and offset_ and initZeroPixelPos_)
                return 11;
            else
                return 9;
        }
        else
        {
            if(intervals_ and scans_ and waitingTime_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_
                    and xRange_ and xVal_ and yStartVal_ and yEndVal_ and sampleToDetDis_ and offset_ and initZeroPixelPos_)
                return 11;
            else
                return 9;
        }
        break;

    case 10:
        loadSlitsConfig();

        if(intervals_ and scans_ and waitingTime_ and expFileName_ and settlingTime_ and sampleName_ and checkTable_
                and xRange_ and xVal_ and yStartVal_ and yEndVal_ and sampleToDetDis_ and offset_ and initZeroPixelPos_)
            return 11;
        else
            return 10;
        break;

    case 11:
        ui->filePath->setText(workingDir + "/DATA/" + ui->expFileName->text());
        return -1;

    default:
        return 0;
    }
}

void Wizard::clearFields() const
{
    // clear all fields for new config file

   intervalsTable->clearTable();

    Client::writePV(MS_Intervals, MS_Intervals_val);
    Client::writePV(MS_Samples, MS_Samples_val);
    Client::writePV(MS_Scans, MS_Scans_val);
    Client::writePV(MS_SettlingTime, MS_SettlingTime_val);
    Client::writePV(MS_WaitingTime, MS_WaitingTime_val);
    Client::writePV(MS_GIXRD, MS_GIXRD_val);
    Client::writePV(MS_UseRobot, MS_UseRobot_val);

    usleep(100000);
    resetFlags();

    switch (scanningType_)
    {
    case 1:
        ui->intervals->clear();
        ui->samples->clear();
        ui->scans->clear();
        ui->waitingTime->clear();
        ui->expFileName->clear();
        ui->settlingTime->clear();
        ui->userComments->clear();
        ui->expComments->clear();
        ui->sampleNameVal->clear();
        break;

    case 2:
        ui->intervals2->clear();
        ui->expFileName2->clear();
        ui->settlingTime2->clear();
        ui->userComments2->clear();
        ui->expComments2->clear();
        ui->sampleNameVal2->clear();
        Client::writePV(MS_TempDeadband, MS_TempDeadband_val);
        break;

    case 3:
        ui->intervals3->clear();
        ui->samples3->clear();
        ui->scans3->clear();
        ui->waitingTime3->clear();
        ui->expFileName3->clear();
        ui->settlingTime3->clear();
        ui->userComments3->clear();
        ui->expComments3->clear();
        ui->sampleNameVal3->clear();
        break;

    case 4:
        ui->intervals4->clear();
        ui->scans4->clear();
        ui->waitingTime4->clear();
        ui->expFileName4->clear();
        ui->settlingTime4->clear();
        ui->userComments4->clear();
        ui->expComments4->clear();
        ui->sampleNameVal4->clear();
        break;
    }
}

void Wizard::checkStatus()
{
    // timer loop every 100ms

   experimentType_ = experimentType->get().toInt();
   scanningType_   = scanningType->get().toInt();
   configFile_     = configFile->get().toInt();
   robotInUse_     = robotInUse->get().toBool();
   checkTable_     = checkTable->get().toBool();
   checkSample_    = checkSample->get().toBool();

   switch (scanningType_)
   {
   case 1:
       if(checkTable_ )
           ui->validIntervals->setHidden(true);
       else
           ui->validIntervals->setHidden(false);
       break;

   case 2:
       if(checkTable_)
           ui->validIntervals2->setHidden(true);
       else
           ui->validIntervals2->setHidden(false);
       break;

   case 3:
       if(checkTable_)
           ui->validIntervals3->setHidden(true);
       else
           ui->validIntervals3->setHidden(false);
       break;

   case 4:
       if(checkTable_)
           ui->validIntervals4->setHidden(true);
       else
           ui->validIntervals4->setHidden(false);
       break;
   }

   if(robotInUse_)
   {
       switch (scanningType_)
       {
       case 1:
           if(ui->samples->text().toInt() == samplesGUI->getSamplesCount() and checkSample_)
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
           if(ui->samples3->text().toInt() == samplesGUI->getSamplesCount() and checkSample_)
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
}

void Wizard::on_usersExperiment_dbValueChanged(const QString &out)
{
    experimentTypeS = out;
}

void Wizard::on_twoThetaScan_dbValueChanged(const QString &out)
{
    scanningTypeS = out;
}

void Wizard::on_configurationsFileCreate_dbValueChanged(const QString &out)
{
    configFileS = out;
}

void Wizard::on_GIXRDFeedback_dbValueChanged(const QString &out)
{
    GIXRDInUseS = out;
    if(out == "Yes")
        ui->GIXRD->setChecked(true);
    else
        ui->GIXRD->setChecked(false);
}

void Wizard::on_robotYes_dbValueChanged(const QString &out)
{
    robotInUseS = out;
    if(out == "Yes")
        ui->scanOptions->setHidden(true);
    else
        ui->scanOptions->setHidden(false);
}

void Wizard::on_testingModeFeedback_dbValueChanged(const QString &out)
{
    testingModeS = out;
}

void Wizard::resetFlags() const
{
    intervals_ = 0;
    scans_ = 0;
    waitingTime_ = 0;
    samples_ = 0;
    checkTable_ = 0;
    checkSample_ = 0;
    checkNSamples_ = 0;
    sampleName_ = 0;
    expFileName_ = 0;
    settlingTime_ = 0;
    deadband_ = 0;
}

void Wizard::on_twoThetaScan_dbValueChanged()
{
    // reset flags if the scanning type has been changed

    configFile_ = 0;
    resetFlags();
}

void Wizard::on_configurationsFileCreate_dbValueChanged(int out)
{
    if(out == 1)
        resetFlags();
    else if(out == 2)
        ui->expConfigFile->clear();
}

void Wizard::on_proposalIDValue_textEdited(const QString &arg1)
{
    /* check if the length and datatype of proposal ID valid */

    ui->proposalIDWarning->setHidden(true);
    ui->Yes->setHidden(true);
    ui->No->setHidden(true);

    if(regex_match(arg1.toStdString(), regex("\\d{8}")))
    {
        setBorderLineEdit(No, ui->proposalIDValue);
        validateProposalID = Yes;
        proposalID = arg1;
    }
    else
    {
        setBorderLineEdit(Yes, ui->proposalIDValue);
        validateProposalID = No;
    }
}

void Wizard::on_proposalIDValue_editingFinished()
{
    /* check if the proposal is scheduled according to this sequence:
                if the proposal ID is valid (length & datatype)
                                    V
                               NO   V  Yes
                (Do nothing) <<<<<<   >>>>>> (check Scanning_Tool.cdv file)
                                                            V
                                     Not exists             V  file exists
    (check MSScheduledProposals.csv file) <<<<<<                >>>>>> (check the content of csv)
                      V                                                         V
  value not exist     V  valid & value exists                        not valid  V   valid & value exists
(check if <<<<<<         >>>>>> (emit alaram to proceed)  (emit alarm) <<<<<<           >>>>>>  continue
the csv is valid)
        V
   NO   V  Yes
(emit<<<   >>>>>> (emit alarm wrong ID)
alaram)
    */

    if(validateProposalID and !ui->proposalIDValue->text().trimmed().isEmpty())
    {
        if(!proposalID_lookup(scanningToolCSV, proposalID))
        {
            validProposalID_ = No;
            if(proposalID_lookup(scheduledProposalsCSV, proposalID))
            {
                if(validCSVFile)
                {
                    ui->proposalIDWarning->setHidden(false);
                    ui->Yes->setHidden(false);
                    ui->No->setHidden(false);
                    ui->proposalIDWarning->setText("MS/XPD scan tool \n The proposal '"
                                                   + proposalID +
                                                   "' is not scheduled for today!. Proposal ID is a unique SED dataset identifier, "
                                                   "it is important to make sure that it is your's as PI or you are a member in this proposal, "
                                                   "otherwise, you would not have access to the data associated with this scan. Only authorised people "
                                                   "(i.e. beamline scientists or DCA team members), proposal PI or proposal participant can procceed with this proposal '"
                                                   + proposalID +
                                                   "'. \n Do you want to continue?");
                }
            }
            else
            {
                ui->proposalIDWarning->setHidden(false);
                ui->Yes->setHidden(true);
                ui->No->setHidden(true);
                if(!validCSVFile)
                    ui->proposalIDWarning->setText("Error reading metadata file!, MSScheduledProposals.csv files is not valid!, "
                                                   "Try to start the experiment again, "
                                                   "if the problem continues please contact the DCA Group");
                else
                    ui->proposalIDWarning->setText("Wrong proposal ID or not scheduled, Proposal ID verification");
            }
        }
        else
            if(!validCSVFile)
            {
                validProposalID_ = No;
                ui->proposalIDWarning->setHidden(false);
                ui->Yes->setHidden(true);
                ui->No->setHidden(true);
                ui->proposalIDWarning->setText("Error reading today's metadata file!, Scanning_Tool.csv files is not valid!, "
                                               "Try to start the experiment again, "
                                               "if the problem continues please contact the DCA Group");
            }
            else
            {
                validProposalID_ = Yes;
                ui->proposalIDWarning->setHidden(true);
                ui->Yes->setHidden(true);
                ui->No->setHidden(true);
            }
    }
}

bool Wizard::proposalID_lookup(QString &sch, QString &val)
{
    validCSVFile = No;
    QFile file(sch);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))       // return 0 if the file not exists
        return 0;
    else
    {
        QTextStream data(&file);
        bool valueFound = false;

        while(!data.atEnd())
        {
            QString line = data.readLine();
            QStringList fields = line.split(',');
            if(!fields.isEmpty())   // check if there is at least one field
            {
                validCSVFile = Yes;
                QString proposalHeader = fields.first(); // get the value only from the first column (proposal col)
                if(proposalHeader == val)  // check if the value exists
                {
                    QString endDate = fields.at(6); // check the end date
                    QDateTime date = QDateTime::fromString(endDate, "dd/MM/yyyy");
                    if(sch == scanningToolCSV)
                    {
                        if(date.date() == QDate::currentDate())
                        {
                            valueFound = true;
                            break;      // exit the loop once the value is found
                        }
                    }
                    else
                        {
                            valueFound = true;
                            break;      // exit the loop once the value is found
                        }
                }
            }
            else
                validCSVFile = No;
        }
        file.close();
        return valueFound;
    }
}

void Wizard::on_Yes_clicked()
{
    validProposalID_ = Yes;
    ui->proposalIDWarning->setHidden(true);
    ui->Yes->setHidden(true);
    ui->No->setHidden(true);
}

void Wizard::on_No_clicked()
{
    validProposalID_ = No;
    ui->proposalIDWarning->setHidden(true);
    ui->Yes->setHidden(true);
    ui->No->setHidden(true);
}

void Wizard::on_intervals_textEdited(const QString &NInt)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(NInt, ui->intervals);
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

void Wizard::on_waitingTime_textEdited(const QString &waitingTime)
{
    // waiting time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkWaitingTime(waitingTime, ui->waitingTime);
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
        checkSampleName(sampleName, ui->sampleNameVal);
}

void Wizard::checkIntervals(const QString &NInt, QLineEdit* lineEdit)
{
    // Nintervals validation

    intervalsTable->enterRows(NInt.toInt());

    if(NInt.toInt() > 0 and NInt.toInt() < 100)
    {
        intervals_ = Yes;
        setBorderLineEdit(No, lineEdit);
        Client::writePV(MS_CheckTable, MS_CheckTable_val);
    }
    else
    {
        intervals_ = No;
        setBorderLineEdit(Yes, lineEdit);
    }
}

void Wizard::checkSamples(const QString &samples, QLineEdit* lineEdit)
{
    // samples validation

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
        setBorderLineEdit(No, lineEdit);
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
        setBorderLineEdit(Yes, lineEdit);
    }

    if(samples.toInt() != samplesGUI->getSamplesCount())
        Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
}

void Wizard::checkScans(const QString &scans, QLineEdit* lineEdit)
{
    // scans validation

    if(scans.toInt() > 0 and scans.toInt() < 100)
    {
        scans_ = Yes;
        setBorderLineEdit(No, lineEdit);

        if(scans.toInt() > 1)
        {
            ui->waitingTime->setEnabled(true);
            ui->waitingTime3->setEnabled(true);
            ui->waitingTime4->setEnabled(true);

            switch (scanningType_)
            {
                case 1:
                    checkWaitingTime(ui->waitingTime->text(), ui->waitingTime);
                    break;
                case 3:
                    checkWaitingTime(ui->waitingTime->text(), ui->waitingTime3);
                    break;
                case 4:
                    checkWaitingTime(ui->waitingTime->text(), ui->waitingTime4);
                    break;
            }
        }
        else
        {
            ui->waitingTime->setEnabled(false);
            ui->waitingTime3->setEnabled(false);
            ui->waitingTime4->setEnabled(false);
            waitingTime_ = Yes;
        }
    }
    else
    {
        scans_ = No;
        setBorderLineEdit(Yes, lineEdit);

        ui->waitingTime->setEnabled(false);
        ui->waitingTime3->setEnabled(false);
        ui->waitingTime4->setEnabled(false);
    }
}

void Wizard::checkWaitingTime(const QString &waitingTime, QLineEdit* lineEdit)
{
    // waiting time validation

    if(lineEdit->isEnabled())
    {
        if(regex_match(waitingTime.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+")))
        {
            waitingTime_ = Yes;
            setBorderLineEdit(No, lineEdit);
        }
        else
        {
            waitingTime_ = No;
            setBorderLineEdit(Yes, lineEdit);
        }
    }
    else
        waitingTime_ = Yes;
}

void Wizard::on_deadband_textEdited(const QString &deadband)
{
    // temperature deadband validation

    if((regex_match(deadband.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+"))))
    {
        deadband_ = Yes;
        setBorderLineEdit(No, ui->deadband);
    }
    else
    {
        deadband_ = No;
        setBorderLineEdit(Yes, ui->deadband);
    }
}

void Wizard::checkExpFileName(const QString &fileName, QLineEdit* lineEdit)
{
    // file name validation

    if((regex_match(fileName.toStdString(), regex("^[a-z|A-Z|0-9]*[a-z|A-Z|0-9|_]+"))))
    {
        expFileName_ = Yes;
        fullFileName = fileName;
        setBorderLineEdit(No, lineEdit);
    }
    else
    {
        expFileName_ = No;
        setBorderLineEdit(Yes, lineEdit);
    }
}

void Wizard::checkSettlingTime(const QString &settlingTime, QLineEdit* lineEdit)
{
    // settling time validation

    if(regex_match(settlingTime.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+")))
    {
        settlingTime_ = Yes;
        setBorderLineEdit(No, lineEdit);
    }
    else
    {
        settlingTime_ = No;
        setBorderLineEdit(Yes, lineEdit);
    }
}

void Wizard::checkSampleName(const QString &sampleName, QLineEdit* lineEdit)
{
    // sample name validation

    if(lineEdit->text().trimmed().isEmpty() or !(regex_match(sampleName.toStdString(), regex("^[a-z|A-Z|0-9]*[a-z|A-Z|0-9|_]+"))))
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
        checkScans(ui->scans->text(), ui->scans);
        checkWaitingTime(ui->waitingTime->text(), ui->waitingTime);
        checkExpFileName(ui->expFileName->text(), ui->expFileName);
        checkSettlingTime(ui->settlingTime->text(), ui->settlingTime);
        break;

    case 2:
        on_deadband_textEdited(ui->deadband->text());
        checkExpFileName(ui->expFileName2->text(), ui->expFileName2);
        checkSettlingTime(ui->settlingTime2->text(), ui->settlingTime2);
        checkSampleName(ui->sampleName2->text(), ui->sampleNameVal2);
        break;

    case 3:
        checkScans(ui->scans3->text(), ui->scans3);
        checkWaitingTime(ui->waitingTime3->text(), ui->waitingTime);
        checkExpFileName(ui->expFileName3->text(), ui->expFileName3);
        checkSettlingTime(ui->settlingTime3->text(), ui->settlingTime3);
        break;

    case 4:
        checkScans(ui->scans4->text(), ui->scans4);
        checkWaitingTime(ui->waitingTime4->text(), ui->waitingTime);
        checkExpFileName(ui->expFileName4->text(), ui->expFileName4);
        checkSettlingTime(ui->settlingTime4->text(), ui->settlingTime4);
        checkSampleName(ui->sampleName4->text(), ui->sampleNameVal4);
        break;
    }
}

void Wizard::on_loadConfigFileButton_clicked()
{
    // get and validate the config file chosen

    loadedFileName = QFileDialog::getOpenFileName(this, "load config file (.config)", workingDir, "*.config");   // open file dialog

    if(loadedFileName.endsWith(".config"))
    {
        if(!loadedFileName.isEmpty())
        {
            ui->expConfigFile->setText(loadedFileName);
            setBorderLabel(No, ui->expConfigFile);
//            startLoading = Yes;
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
    /* start loading config file, "if the loaded config file matches the selected scan", else it won't complete */

    QFile file(configFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();        // can use QStreamText, but QByte array easier to use
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        QJsonObject jsonObj = jsonDoc.object();

        if(jsonObj["scanningOrder"].toInt() == scanningType_)
        {
            startLoading = Yes;
            setBorderLabel(No, ui->expConfigFile);

            Client::writePV(MS_UseRobot, jsonObj["robotInUse"].toString());

            switch (scanningType_) {

            case 1:
                ui->intervals->setText(jsonObj["NIntervals"].toString());
                Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
                checkIntervals(ui->intervals->text(), ui->intervals);

                ui->scans->setText(jsonObj["Nscans"].toString());

                if(jsonObj.contains("waitingTime"))
                {
                    Client::writePV(MS_WaitingTime, jsonObj["waitingTime"].toString());
                    ui->waitingTime->setText(jsonObj["waitingTime"].toString());
                }

                ui->expFileName->setText(jsonObj["expFileName"].toString());
                ui->settlingTime->setText(jsonObj["settlingTime"].toString());
                ui->userComments->setText(jsonObj["userComments"].toString());
                ui->expComments->setText(jsonObj["expComments"].toString());

                break;

            case 2:
                ui->intervals2->setText(jsonObj["NIntervals"].toString());
                Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
                checkIntervals(ui->intervals2->text(), ui->intervals2);

                ui->deadband->setText(jsonObj["tempDeadband"].toString());
                ui->expFileName2->setText(jsonObj["expFileName"].toString());
                ui->settlingTime2->setText(jsonObj["settlingTime"].toString());
                ui->sampleNameVal2->setText(jsonObj["Sample"].toString());
                ui->userComments2->setText(jsonObj["userComments"].toString());
                ui->expComments2->setText(jsonObj["expComments"].toString());
                Client::writePV(MS_TempDeadband, jsonObj["tempDeadband"].toString());

                break;

            case 3:
                ui->intervals3->setText(jsonObj["NIntervals"].toString());
                Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
                checkIntervals(ui->intervals3->text(), ui->intervals3);

                ui->scans3->setText(jsonObj["Nscans"].toString());

                if(jsonObj.contains("waitingTime"))
                {
                    Client::writePV(MS_WaitingTime, jsonObj["waitingTime"].toString());
                    ui->waitingTime3->setText(jsonObj["waitingTime"].toString());
                }

                ui->expFileName3->setText(jsonObj["expFileName"].toString());
                ui->settlingTime3->setText(jsonObj["settlingTime"].toString());
                ui->userComments3->setText(jsonObj["userComments"].toString());
                ui->expComments3->setText(jsonObj["expComments"].toString());
                break;

            case 4:
                ui->intervals4->setText(jsonObj["NIntervals"].toString());
                Client::writePV(MS_Intervals, jsonObj["NIntervals"].toString());
                checkIntervals(ui->intervals4->text(), ui->intervals4);

                ui->scans4->setText(jsonObj["Nscans"].toString());

                if(jsonObj.contains("waitingTime"))
                {
                    Client::writePV(MS_WaitingTime, jsonObj["waitingTime"].toString());
                    ui->waitingTime4->setText(jsonObj["waitingTime"].toString());
                }

                ui->expFileName4->setText(jsonObj["expFileName"].toString());
                ui->settlingTime4->setText(jsonObj["settlingTime"].toString());
                ui->sampleNameVal4->setText(jsonObj["Sample"].toString());
                ui->userComments4->setText(jsonObj["userComments"].toString());
                ui->expComments4->setText(jsonObj["expComments"].toString());
                break;
            }

            intervalsTable->loadIntervalsFromJson(jsonObj["Intervals"].toArray());

            if(jsonObj["robotInUse"].toString() == "Yes")
            {
                Client::writePV(MS_Samples, jsonObj["NSamples"].toString());
                switch (scanningType_)
                {
                case 1:
                    ui->samples->setText(jsonObj["NSamples"].toString());
                    checkSamples(ui->samples->text(), ui->samples);
                    break;

                case 3:
                    ui->samples3->setText(jsonObj["NSamples"].toString());
                    checkSamples(ui->samples3->text(), ui->samples3);
                    break;
                }
                samplesGUI->loadSamplesData(jsonObj["Samples"].toArray(), jsonObj["pickingOrder"]);
            }
            else
            {
                Client::writePV(MS_Sample, jsonObj["Sample"].toString());
                switch (scanningType_)
                {
                case 1:
                    Client::writePV(MS_GIXRD, jsonObj["GIXRD"].toString());
                    ui->sampleNameVal->setText(jsonObj["Sample"].toString());
                    checkSampleName(ui->sampleNameVal->text(), ui->sampleNameVal);
                    break;

                case 3:
                    ui->sampleNameVal3->setText(jsonObj["Sample"].toString());
                    checkSampleName(ui->sampleNameVal3->text(), ui->sampleNameVal3);
                    break;
                }
            }

            Client::writePV(MS_Scans, jsonObj["Nscans"].toString());
            Client::writePV(MS_SettlingTime, jsonObj["settlingTime"].toString());
            Client::writeStringToWaveform(MS_ExperimentFileName, jsonObj["expFileName"].toString());
            Client::writeStringToWaveform(MS_UserComments, jsonObj["userComments"].toString());
            Client::writeStringToWaveform(MS_ExperimentComments, jsonObj["expComments"].toString());

            configFileCheck();

            loadFile_ = Yes;
    }
        else
        {
            startLoading = No;
            setBorderLabel(Yes, ui->expConfigFile);
            QMessageBox::warning(this, "MS/XPD scan tool", "The chosen config file doesn't match with the scanning type!!");
        }
    }
    else
    {
        loadFile_ = No;
        ui->filePath->setText("Unable to read configuration file, scanning can not continue!!");
    }
}

void Wizard::createConfigFile(QString &config)
{
    QFile file(config);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject jsonObj;

        if(experimentType_ == 1)
            jsonObj["ProposalID"]       = ui->proposalIDValue->text();

        switch (scanningType_) {

        case 1:
            jsonObj["NIntervals"]       = ui->intervals->text();
            jsonObj["Nscans"]           = ui->scans->text();
            jsonObj["settlingTime"]     = ui->settlingTime->text();
            jsonObj["userComments"]     = ui->userComments->text();
            jsonObj["expComments"]      = ui->expComments->text();

            if(ui->scans->text().toInt() > 1)
                jsonObj["waitingTime"] = ui->waitingTime->text();

            break;

        case 2:
            jsonObj["NIntervals"]       = ui->intervals2->text();
            jsonObj["tempDeadband"]     = ui->deadband->text();
            jsonObj["settlingTime"]     = ui->settlingTime2->text();
            jsonObj["Sample"]           = ui->sampleNameVal2->text();
            jsonObj["userComments"]     = ui->userComments2->text();
            jsonObj["expComments"]      = ui->expComments2->text();

            break;

        case 3:
            jsonObj["NIntervals"]       = ui->intervals3->text();
            jsonObj["Nscans"]           = ui->scans3->text();
            jsonObj["settlingTime"]     = ui->settlingTime3->text();
            jsonObj["userComments"]     = ui->userComments3->text();
            jsonObj["expComments"]      = ui->expComments3->text();

            if(ui->scans3->text().toInt() > 1)
                jsonObj["waitingTime"] = ui->waitingTime3->text();

            break;

        case 4:
            jsonObj["NIntervals"]       = ui->intervals4->text();
            jsonObj["Nscans"]           = ui->scans4->text();
            jsonObj["settlingTime"]     = ui->settlingTime4->text();
            jsonObj["Sample"]           = ui->sampleNameVal4->text();
            jsonObj["userComments"]     = ui->userComments4->text();
            jsonObj["expComments"]      = ui->expComments4->text();

            if(ui->scans4->text().toInt() > 1)
                jsonObj["waitingTime"] = ui->waitingTime3->text();

            break;
        }

        jsonObj["expType"]          = experimentTypeS;
        jsonObj["scanningType"]     = scanningTypeS;
        jsonObj["loadedConfig"]     = configFileS;
        jsonObj["Intervals"]        = intervalsTable->createIntervalsJson();
        jsonObj["scanningOrder"]    = scanningType_;

        if(robotInUse_)
        {
            jsonObj["Samples"]      = samplesGUI->getSamplesData();
            jsonObj["pickingOrder"] = samplesGUI->getPickingOrder();

            switch (scanningType_)
            {
            case 1:
                jsonObj["NSamples"]         = ui->samples->text();
                break;

            case 3:
                jsonObj["NSamples"]         = ui->samples3->text();
                break;
            }
        }
        else
        {
            Client::writePV(MS_Samples, 1);
            jsonObj["NSamples"] = 1;
            switch (scanningType_)
            {
            case 1:
                jsonObj["GIXRD"]    = GIXRDInUseS;
                jsonObj["Sample"]   = ui->sampleNameVal->text();
                break;

            case 3:
                jsonObj["Sample"] = ui->sampleNameVal3->text();
                break;
            }
        }

        jsonObj["robotInUse"]       = robotInUseS;
        jsonObj["testingMode"]      = testingModeS;
        jsonObj["expFileName"]      = fullFileName;

        QJsonDocument jsonDoc(jsonObj);
        file.write(jsonDoc.toJson());
    }
}

void Wizard::onWizardFinished(int order)
{
    if(order == QDialog::Accepted)     // it works just on "finish button"
    {
        /* get the current time "timeStamp" to be added to the file name */
        system_clock::time_point now = system_clock::now();
        time_t currentTime = system_clock::to_time_t(now);
        tm* currTime = localtime(&currentTime);
        strftime(timeStamp, sizeof(timeStamp), "%Y%m%dT%H%M%S", currTime);

        Client::writePV(MS_Supp_CreationTime, timeStamp);

        configFileName = "config.config";
        createConfigFile(configFileName);
    }

    if(order == QDialog::Rejected)
        Client::writePV(MS_CancelScan, Yes);
}

void Wizard::on_testingModeFeedback_dbValueChanged(bool out)
{
    ui->notifications->setHidden(out);
}

void Wizard::setBorderLineEdit(bool val, QLineEdit* lineEdit)
{
    // 0: clear the style sheet , 1: set the style sheet (red border)
    (val)? lineEdit->setStyleSheet("border: 2.25px solid red;") : lineEdit->setStyleSheet("");
}

void Wizard::setBorderLabel(bool val, QLabel* label)
{
    // 0: clear the style sheet , 1: set the style sheet (red border)
    (val)? label->setStyleSheet("border: 2.25px solid red;") : label->setStyleSheet("");
}

void Wizard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        event->ignore();    // ignore the Escape button press event
}

void Wizard::closeEvent(QCloseEvent *event)
{
    event->ignore();       // Ignore the close event
}

void Wizard::on_samplesButton_clicked()
{
    samplesGUI->initializing();
    samplesGUI->show();
}

void Wizard::on_intervals2_textEdited(const QString &NInt)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(NInt, ui->intervals2);
}

void Wizard::on_expFileName2_textEdited(const QString &fileName)
{
    // file name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(fileName, ui->expFileName2);
}

void Wizard::on_settlingTime2_textEdited(const QString &settlingTime)
{
    // settling time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(settlingTime, ui->settlingTime2);
}

void Wizard::on_sampleNameVal2_textEdited(const QString &sampleName)
{
    // sample name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSampleName(sampleName, ui->sampleNameVal2);
}

void Wizard::on_intervals3_textEdited(const QString &NInt)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(NInt, ui->intervals3);
}

void Wizard::on_samples3_textEdited(const QString &samples)
{
    // samples validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSamples(samples, ui->samples3);
}

void Wizard::on_scans3_textEdited(const QString &scans)
{
    // scans validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkScans(scans, ui->scans3);
}

void Wizard::on_waitingTime3_textEdited(const QString &waitingTime)
{
    // waiting time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkWaitingTime(waitingTime, ui->waitingTime3);
}

void Wizard::on_expFileName3_textEdited(const QString &fileName)
{
    // file name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(fileName, ui->expFileName3);
}

void Wizard::on_settlingTime3_textEdited(const QString &settlingTime)
{
    // settling time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(settlingTime, ui->settlingTime3);
}

void Wizard::on_sampleNameVal3_textEdited(const QString &sampleName)
{
    // sample name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSampleName(sampleName, ui->sampleNameVal3);
}

void Wizard::on_samplesButton3_clicked()
{
    samplesGUI->initializing();
    samplesGUI->show();
}

void Wizard::on_intervals4_textEdited(const QString &NInt)
{
    // Nintervals validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkIntervals(NInt, ui->intervals4);
}

void Wizard::on_scans4_textEdited(const QString &scans)
{
    // scans validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkScans(scans, ui->scans4);
}

void Wizard::on_waitingTime4_textEdited(const QString &waitingTime)
{
    // waiting time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkWaitingTime(waitingTime, ui->waitingTime4);
}

void Wizard::on_expFileName4_textEdited(const QString &fileName)
{
    // file name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkExpFileName(fileName, ui->expFileName4);
}

void Wizard::on_settlingTime4_textEdited(const QString &settlingTime)
{
    // settling time validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSettlingTime(settlingTime, ui->settlingTime4);
}

void Wizard::on_sampleNameVal4_textEdited(const QString &sampleName)
{
    // sample name validation
    if(configFile_ == 1 or loadFile_ ==1)
        checkSampleName(sampleName, ui->sampleNameVal4);
}

void Wizard::on_modify_clicked()
{
    /* open a dialog to modify slits configurations and validate the changes */

    QFile file(slitsConfigurationsFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObject = doc.object();
        file.close();

        QString originalFile = QJsonDocument(jsonObject).toJson();

        bool ok;
        QString modified = QInputDialog::getMultiLineText(this, "Edit slits configurations parameters", "Modify the values:", originalFile, &ok);
        if(ok)
        {
            QJsonDocument doc = QJsonDocument::fromJson(modified.toUtf8());
            QJsonObject jsonObject = doc.object();
            if(!doc.isNull() and doc.isObject())
            {
                QFile file(slitsConfigurationsFile);
                if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << modified;
                    file.close();
                }
                loadSlitsConfig();
            }
            else
                QMessageBox::warning(this, "Invalid JSON!", "The JSON is not valid. Changes were not saved!");
        }
    }
    else
        QMessageBox::warning(this, "Not found!", "Couldn't open slits configurations file!");
}

void Wizard::loadSlitsConfig() const
{
    QFile file(slitsConfigurationsFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObject = doc.object();
        file.close();

        ui->xAxisRange->setText(jsonObject.contains("X-AxisRange") ? QString::number(jsonObject["X-AxisRange"].toDouble()) : "Not found!");
        ui->x->setText(jsonObject.contains("X") ? QString::number(jsonObject["X"].toDouble()) : "Not found!");
        ui->yStart->setText(jsonObject.contains("Y-Start") ? QString::number(jsonObject["Y-Start"].toDouble()) : "Not found!");
        ui->yEnd->setText(jsonObject.contains("Y-End") ? QString::number(jsonObject["Y-End"].toDouble()) : "Not found!");
        ui->sampleToDetDis->setText(jsonObject.contains("sampleToDetDistance") ? QString::number(jsonObject["sampleToDetDistance"].toDouble()) : "Not found!");
        ui->twoThetaOffset->setText(jsonObject.contains("2thetaOffset") ? QString::number(jsonObject["2thetaOffset"].toDouble()) : "Not found!");
        ui->initZeroPixelPos->setText(jsonObject.contains("initZeroPixelPos") ? QString::number(jsonObject["initZeroPixelPos"].toDouble()) : "Not found!");

        ui->xAxisRange2->setText(jsonObject.contains("X-AxisRange") ? QString::number(jsonObject["X-AxisRange"].toDouble()) : "Not found!");
        ui->x2->setText(jsonObject.contains("X") ? QString::number(jsonObject["X"].toDouble()) : "Not found!");
        ui->yStart2->setText(jsonObject.contains("Y-Start") ? QString::number(jsonObject["Y-Start"].toDouble()) : "Not found!");
        ui->yEnd2->setText(jsonObject.contains("Y-End") ? QString::number(jsonObject["Y-End"].toDouble()) : "Not found!");
        ui->sampleToDetDis2->setText(jsonObject.contains("sampleToDetDistance") ? QString::number(jsonObject["sampleToDetDistance"].toDouble()) : "Not found!");
        ui->twoThetaOffset2->setText(jsonObject.contains("2thetaOffset") ? QString::number(jsonObject["2thetaOffset"].toDouble()) : "Not found!");
        ui->initZeroPixelPos2->setText(jsonObject.contains("initZeroPixelPos") ? QString::number(jsonObject["initZeroPixelPos"].toDouble()) : "Not found!");
    }
}

bool Wizard::checkSlitsConfigInt(const QString &val, QLineEdit* lineEdit)
{
    bool isValid = false;
    if(regex_match(val.toStdString(), regex("[+]?[0-9]+")))
    {
        isValid = true;
        setBorderLineEdit(No, lineEdit);
    }
    else
    {
        isValid = false;
        setBorderLineEdit(Yes, lineEdit);
    }
    return isValid;
}

bool Wizard::checkSlitsConfigFloat(const QString &val, QLineEdit* lineEdit)
{
    bool isValid = false;
    if(regex_match(val.toStdString(), regex("[+]?([0-9]*[.])?[0-9]+")))
    {
        isValid = true;
        setBorderLineEdit(No, lineEdit);
    }
    else
    {
        isValid = false;
        setBorderLineEdit(Yes, lineEdit);
    }
    return isValid;
}

void Wizard::on_xAxisRange_textChanged(const QString &xAxisRange)
{
    // x axis range validation
    xRange_ = checkSlitsConfigInt(xAxisRange, ui->xAxisRange);
}

void Wizard::on_x_textChanged(const QString &x)
{
    // x axis value validation
    xVal_ = checkSlitsConfigInt(x, ui->x);
}

void Wizard::on_yStart_textChanged(const QString &yStart)
{
    // y axis start value validation
    yStartVal_ = checkSlitsConfigInt(yStart, ui->yStart);
}

void Wizard::on_yEnd_textChanged(const QString &yEnd)
{
    // y axis end value validation
    yEndVal_ = checkSlitsConfigInt(yEnd, ui->yEnd);
}

void Wizard::on_sampleToDetDis_textChanged(const QString &val)
{
    // sample to detector distance value validation
    sampleToDetDis_ = checkSlitsConfigFloat(val, ui->sampleToDetDis);
}

void Wizard::on_twoThetaOffset_textChanged(const QString &val)
{
    // two theta offset validation
    offset_ = checkSlitsConfigFloat(val, ui->twoThetaOffset);
}

void Wizard::on_initZeroPixelPos_textChanged(const QString &val)
{
    // initial zero pixel position validation
    initZeroPixelPos_ = checkSlitsConfigFloat(val, ui->initZeroPixelPos);
}

void Wizard::on_modify2_clicked()
{
    /* open a dialog to modify slits configurations and validate the changes */
    on_modify_clicked();
}

void Wizard::on_xAxisRange2_textChanged(const QString &xAxisRange)
{
    // x axis range validation
    xRange_ = checkSlitsConfigInt(xAxisRange, ui->xAxisRange2);
}

void Wizard::on_x2_textChanged(const QString &x)
{
    // x axis value validation
    xVal_ = checkSlitsConfigInt(x, ui->x2);
}

void Wizard::on_yStart2_textChanged(const QString &yStart)
{
    // y axis start value validation
    yStartVal_ = checkSlitsConfigInt(yStart, ui->yStart2);
}

void Wizard::on_yEnd2_textChanged(const QString &yEnd)
{
    // y axis end value validation
    yEndVal_ = checkSlitsConfigInt(yEnd, ui->yEnd2);
}

void Wizard::on_sampleToDetDis2_textChanged(const QString &val)
{
    // sample to detector distance value validation
    sampleToDetDis_ = checkSlitsConfigFloat(val, ui->sampleToDetDis2);
}

void Wizard::on_twoThetaOffset2_textChanged(const QString &val)
{
    // two theta offset validation
    offset_ = checkSlitsConfigFloat(val, ui->twoThetaOffset2);
}

void Wizard::on_initZeroPixelPos2_textChanged(const QString &val)
{
    // initial zero pixel position validation
    initZeroPixelPos_ = checkSlitsConfigFloat(val, ui->initZeroPixelPos2);
}

void Wizard::on_Wizard_helpRequested()
{
    QDesktopServices::openUrl(QUrl("https://ms-xpd.readthedocs.io"));
}
