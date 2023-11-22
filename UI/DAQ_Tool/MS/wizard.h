#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

#include "intervals.h"
#include "samples.h"

#include <iostream>
#include <stdlib.h>

#include <qepicspv.h>
#include <client.h>

#include <chrono>
#include <ctime>
#include <unistd.h>

#include <regex>
#include <string>

#include <QMessageBox>

#include <QFileDialog>
#include <QInputDialog>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:

    explicit Wizard(QWidget *parent = nullptr);
    ~Wizard();

private slots:

    void initializing();                 // initialize the GUI at startup

    void setBorderLineEdit(bool val, QLineEdit* lineEdit);

    void setBorderLabel(bool val, QLabel* label);

    void on_proposalIDValue_textEdited(const QString &arg1);

    void on_proposalIDValue_editingFinished();

    bool proposalID_lookup(QString &file, QString &val);

    void intervalsButtonClicked();       // this function will be called to open the table, for the four GUIs (scanning types)

    void on_intervalsButton_clicked();   // this button for twoThetaStep Scan GUI

    void on_intervalsButton2_clicked();  // this button for twoThetaTemp Scan GUI

    void on_intervalsButton3_clicked();  // this button for twoThetaSlits Scan GUI

    void on_intervalsButton4_clicked();  // this button for thetaTwoTheta Scan GUI

    int nextId() const;

    void checkStatus();

    void clearFields() const;

    void on_intervals_textEdited(const QString &arg1);

    void on_samples_textEdited(const QString &arg1);

    void on_scans_textEdited(const QString &arg1);

    void on_deadband_textEdited(const QString &arg1);

    void on_expFileName_textEdited(const QString &arg1);

    void on_settlingTime_textEdited(const QString &arg1);

    void on_sampleNameVal_textEdited(const QString &arg1);

    void checkIntervals(const QString &arg1, QLineEdit* lineEdit);

    void checkSamples(const QString &arg1, QLineEdit* lineEdit);

    void checkScans(const QString &arg1, QLineEdit* lineEdit);

    void checkExpFileName(const QString &arg1, QLineEdit* lineEdit);

    void checkSettlingTime(const QString &arg1, QLineEdit* lineEdit);

    void checkSampleName(const QString &arg1, QLineEdit* lineEdit);

    void configFileCheck();

    void on_loadConfigFileButton_clicked();

    void loadConfigFile(const QString& configFile);

    void createConfigFile(QString &config);

    void onWizardFinished(int order);

    void on_samplesButton_clicked();

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_intervals3_textEdited(const QString &arg1);

    void on_samples3_textEdited(const QString &arg1);

    void on_scans3_textEdited(const QString &arg1);

    void on_expFileName3_textEdited(const QString &arg1);

    void on_settlingTime3_textEdited(const QString &arg1);

    void on_samplesButton3_clicked();

    void on_sampleNameVal3_textEdited(const QString &arg1);

    void on_Yes_clicked();

    void on_No_clicked();

    void on_intervals2_textEdited(const QString &arg1);

    void on_expFileName2_textEdited(const QString &arg1);

    void on_settlingTime2_textEdited(const QString &arg1);

    void on_sampleNameVal2_textEdited(const QString &arg1);

    void on_twoThetaScan_dbValueChanged();

    void on_usersExperiment_dbValueChanged(const QString &out);

    void on_twoThetaScan_dbValueChanged(const QString &out);

    void on_configurationsFileCreate_dbValueChanged(const QString &out);

    void on_robotYes_dbValueChanged(const QString &out);

    void on_modify_clicked();

    void loadSlitsConfig() const;

    bool checkSlitsConfigInt(const QString &arg1, QLineEdit* lineEdit);

    bool checkSlitsConfigFloat(const QString &arg1, QLineEdit* lineEdit);

    void on_xAxisRange_textChanged(const QString &arg1);

    void on_x_textChanged(const QString &arg1);

    void on_yStart_textChanged(const QString &arg1);

    void on_yEnd_textChanged(const QString &arg1);

    void on_sampleToDetDis_textChanged(const QString &arg1);

    void on_twoThetaOffset_textChanged(const QString &arg1);

    void on_initZeroPixelPos_textChanged(const QString &arg1);

private:

    Ui::Wizard *ui;

    intervals* intervalsTable;
    samples* samplesGUI;

    /*****************************************************************/
    /* define the string PVs in order to be set in the Client EPICS */

    QString PV_Prefix = "MS:";

    QString MS_ExperimentType     = PV_Prefix + "ExperimentType"       ; int MS_ExperimentType_val     = 0;
    QString MS_ProposalID         = PV_Prefix + "ProposalID"           ; int MS_ProposalID_val         = 0;
    QString MS_ScanningType       = PV_Prefix + "ScanningType"         ; int MS_ScanningType_val       = 0;
    QString MS_ConfigurationsFile = PV_Prefix + "ConfigurationsFile"   ; int MS_ConfigurationsFile_val = 0;
    QString MS_Intervals          = PV_Prefix + "Intervals"            ; int MS_Intervals_val          = 0;
    QString MS_Samples            = PV_Prefix + "Samples"              ; int MS_Samples_val            = 0;
    QString MS_Scans              = PV_Prefix + "Scans"                ; int MS_Scans_val              = 0;
    QString MS_SettlingTime       = PV_Prefix + "SettlingTime"         ; int MS_SettlingTime_val       = 0;
    QString MS_UseRobot           = PV_Prefix + "UseRobot"             ; bool MS_UseRobot_val          = 0;
    QString MS_CheckTable         = PV_Prefix + "CheckTable"           ; bool MS_CheckTable_val        = 0;
    QString MS_CheckSamples       = PV_Prefix + "CheckSamples"         ; bool MS_CheckSamples_val      = 0;
    QString MS_ExperimentFileName = PV_Prefix + "ExperimentalFileName" ;
    QString MS_Sample             = PV_Prefix + "Sample"               ;
    QString MS_UserComments       = PV_Prefix + "UserComments"         ;
    QString MS_ExperimentComments = PV_Prefix + "ExperimentComments"   ;
    QString MS_CancelScan         = PV_Prefix + "CancelScan"           ; bool MS_CancelScan_val         = 0;
    QString MS_TestingMode        = PV_Prefix + "TestingMode"          ; bool MS_TestingMode_val        = 0;
    QString MS_TempDeadband       = PV_Prefix + "TempDeadband"         ; float MS_TempDeadband_val     = 0.1;
    QString MS_PickingOrder       = PV_Prefix + "PickingOrder"         ; bool MS_PickingOrder_val       = 0;
    QString MS_Supp_CreationTime  = PV_Prefix + "Supp:CreationTime"    ;
    QString MS_ScanStatus         = PV_Prefix + "ScanStatus"           ; bool MS_ScanStatus_val         = 0;
    QString MS_StartTime          = PV_Prefix + "StartTime"            ; QString MS_StartTime_val       = "---";
    QString MS_EndTime            = PV_Prefix + "EndTime"              ; QString MS_EndTime_val         = "---";
    QString MS_CurrentSample      = PV_Prefix + "CurrentSample"        ; bool MS_CurrentSample_val      = 0;
    QString MS_CurrentInterval    = PV_Prefix + "CurrentInterval"      ; bool MS_CurrentInterval_val    = 0;
    QString MS_CurrentScan        = PV_Prefix + "CurrentScan"          ; bool MS_CurrentScan_val        = 0;
    QString MS_CurrentPoint       = PV_Prefix + "CurrentPoint"         ; bool MS_CurrentPoint_val       = 0;
    QString MS_TotalPoints        = PV_Prefix + "TotalPoints"          ; bool MS_TotalPoints_val        = 0;
    QString MS_CollectedPoint     = PV_Prefix + "CollectedPoints"      ; QString MS_CollectedPoint_val  = "/";
    QString MS_SampleName         = PV_Prefix + "SampleName"           ; QString MS_SampleName_val      = "---";
    QString MS_SkippedSamples     = PV_Prefix + "SkippedSamples"       ; QString MS_SkippedSamples_val  = "---";
    QString MS_NotReturnSamples   = PV_Prefix + "NotReturnSamples"     ; QString MS_NotReturnSamples_val= "---";
    QString MS_TotalCollectedPoints     = PV_Prefix + "TotalCollectedPoints"    ; QString MS_TotalCollectedPoints_val    = "/";
    QString MS_AllTotalCollectedPoints  = PV_Prefix + "AllTotalCollectedPoints" ; QString MS_AllTotalCollectedPoints_val = "/";
    QString MS_IntervalRemaningTime     = PV_Prefix + "IntervalRemTime"         ; QString MS_IntervalRemainingTime_val   = "---";
    QString MS_ScanRemaningTime          = PV_Prefix + "ScanRemTime"            ; QString MS_ScanRemainingTime_val       = "---";

    QString UItittle = "MS/XPD scan tool";
    QString workingDir = "/home/control/MS-XPD-ScanTool";
    QString scanningToolCSV = "metadata/Scanning_Tool.csv";
    QString scheduledProposalsCSV = "metadata/MSScheduledProposals.csv";
    QString slitsConfigurationsFile = "configurations/slitsConfigurations.json";

    QEpicsPV* experimentType = new QEpicsPV(MS_ExperimentType);
    QEpicsPV* scanningType   = new QEpicsPV(MS_ScanningType);
    QEpicsPV* configFile     = new QEpicsPV(MS_ConfigurationsFile);
    QEpicsPV* checkTable     = new QEpicsPV(MS_CheckTable);
    QEpicsPV* checkSample    = new QEpicsPV(MS_CheckSamples);
    QEpicsPV* robotInUse     = new QEpicsPV(MS_UseRobot);

    bool Yes = 1;
    bool No  = 0;

    int experimentType_;
    int scanningType_;
    int configFile_;
    bool robotInUse_;
    bool startLoading;
    bool loadFile_;
    bool isLoaded_ = 0;
    mutable int checkScanningType_ = 0;
    bool validateProposalID;       // flag indicates if the proposal ID (length & datatype) valid
    bool validProposalID_ = No;    // flag indicates the proposal ID is scheduled
    bool validCSVFile;             // flag indicates the content of the CSV file is valid
    bool intervals_;
    bool samples_;
    bool scans_;
    bool expFileName_;
    bool settlingTime_;
    bool sampleName_;
    bool checkTable_;
    bool checkSample_;
    bool checkNSamples_;
    bool deadband_;
    bool xRange_;
    bool xVal_;
    bool yStartVal_;
    bool yEndVal_;
    bool sampleToDetDis_;
    bool offset_;
    bool initZeroPixelPos_;

    QTimer* Timer;

    char timeStamp[20];

    QString proposalID;
    QString proposalIDdb;
    QString experimentTypeS;
    QString scanningTypeS;
    QString configFileS;
    QString robotInUseS;
    QString fullFileName;
    QString configFileName;
    QString loadedFileName;
};

#endif // WIZARD_H
