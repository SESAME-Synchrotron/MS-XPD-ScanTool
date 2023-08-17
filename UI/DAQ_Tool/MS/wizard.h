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
#include <QTableWidget>

#include <QFileDialog>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

//#include "twothetastep.h"

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:

    explicit Wizard(QWidget *parent = nullptr);
    ~Wizard();

    void setBorderLineEdit(bool val, QLineEdit* lineEdit);

    void setBorderLabel(bool val, QLabel* label);

    void UImessage(const QString &tittle , const QString &message);

//signals:

//    void mandatorySignal() const;

private slots:

    void initializing();                 // initialize the GUI at startup

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

    void on_expFileName_textEdited(const QString &arg1);

    void on_settlingTime_textEdited(const QString &arg1);

    void checkIntervals (const QString &arg1, QLineEdit* lineEdit);

    void checkSamples (const QString &arg1, QLineEdit* lineEdit);

    void checkScans (const QString &arg1, QLineEdit* lineEdit);

    void checkExpFileName(const QString &arg1, QLineEdit* lineEdit);

    void checkSettlingTime (const QString &arg1, QLineEdit* lineEdit);

    void checkSampleName (QLineEdit* lineEdit);

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

    void on_sampleNameVal_textEdited();

    void on_sampleNameVal3_textEdited();

private:

    Ui::Wizard *ui;

    intervals* intervalsTable;
    samples* samplesGUI;
//    intervals* twoThetaTemp;
//    intervals* twoThetaSlits;
//    intervals* thetaTwoTheta;

    QPushButton *nextButton;

    /*****************************************************************/
    /* define the string PVs in order to be set in the Client EPICS */

    QString PV_Prefix = "MS:";

    QString MS_ExperimentType     = PV_Prefix + "ExperimentType"       ; int MS_ExperimentType_val     = 0;
    QString MS_ScanningType       = PV_Prefix + "ScanningType"         ; int MS_ScanningType_val       = 0;
    QString MS_ConfigurationsFile = PV_Prefix + "ConfigurationsFile"   ; int MS_ConfigurationsFile_val = 0;
    QString MS_Intervals          = PV_Prefix + "Intervals"            ; int MS_Intervals_val          = 0;
    QString MS_Samples            = PV_Prefix + "Samples"              ; int MS_Samples_val            = 0;
    QString MS_Scans              = PV_Prefix + "Scans"                ; int MS_Scans_val              = 0;
    QString MS_SettlingTime       = PV_Prefix + "SettlingTime"         ; int MS_SettlingTime_val       = 0;
    QString MS_UseRobot           = PV_Prefix + "UseRobot"             ; int MS_UseRobot_val           = 0;
    QString MS_CheckTable         = PV_Prefix + "CheckTable"           ; int MS_CheckTable_val         = 0;
    QString MS_CheckSamples       = PV_Prefix + "CheckSamples"         ; int MS_CheckSamples_val       = 0;
    QString MS_ExperimentFileName = PV_Prefix + "ExperimentalFileName" ;
    QString MS_Sample             = PV_Prefix + "Sample"               ;
    QString MS_UserComments       = PV_Prefix + "UserComments"         ;
    QString MS_ExperimentComments = PV_Prefix + "ExperimentComments"   ;
    QString MS_StartScan          = PV_Prefix + "StartScan"            ; int MS_StartScan_val          = 0;
    QString MS_StopScan           = PV_Prefix + "StopScan"             ; int MS_StopScan_val           = 0;
    QString MS_FinishScan         = PV_Prefix + "FinishScan"           ; int MS_FinishScan_val         = 0;
    QString MS_CancelScan         = PV_Prefix + "CancelScan"           ; int MS_CancelScan_val         = 0;
    QString MS_TestingMode        = PV_Prefix + "TestingMode"          ; int MS_TestingMode_val        = 0;

    QString UItittle = "MS/XRD scan tool";
    QString workingDir = "/home/dcasu/XRD-Scan/UI/DAQ_Tool/MS/";

    QEpicsPV* experimentType = new QEpicsPV(MS_ExperimentType);
    QEpicsPV* scanningType   = new QEpicsPV(MS_ScanningType);
    QEpicsPV* Nintervals     = new QEpicsPV(MS_Intervals);
    QEpicsPV* sample         = new QEpicsPV(MS_Samples);
    QEpicsPV* Nscans         = new QEpicsPV(MS_Scans);
    QEpicsPV* expFileName    = new QEpicsPV(MS_ExperimentFileName);
    QEpicsPV* settlingTime   = new QEpicsPV(MS_SettlingTime);
    QEpicsPV* configFile     = new QEpicsPV(MS_ConfigurationsFile);
    QEpicsPV* checkTable     = new QEpicsPV(MS_CheckTable);
    QEpicsPV* checkSample    = new QEpicsPV(MS_CheckSamples);
    QEpicsPV* robotInUse     = new QEpicsPV(MS_UseRobot);
    QEpicsPV* Sample         = new QEpicsPV(MS_Sample);
//    QEpicsPV* userComments   = new QEpicsPV(MS_UserComments);
//    QEpicsPV* expComments    = new QEpicsPV(MS_ExperimentComments);
//    QEpicsPV* startScan      = new QEpicsPV(MS_StartScan);
//    QEpicsPV* stopScan       = new QEpicsPV(MS_StartScan);
//    QEpicsPV* finishScan     = new QEpicsPV(MS_StartScan);
//    QEpicsPV* cancelScan     = new QEpicsPV(MS_StartScan);

    int experimentType_;
    int scanningType_;
    int configFile_;
    int robotInUse_;
    int startLoading;
    int loadFile_;
//    mutable int mandotarySignalN = 0;

    bool Yes = 1;
    bool No  = 0;

    bool intervals_;
    bool samples_;
    bool scans_;
    bool expFileName_;
    bool settlingTime_;
    bool sampleName_;
    bool checkTable_;
    bool checkSample_;
    bool checkNSamples_;

    QTimer* Timer;

    char timeStamp[20];

    QString experimentTypeS;
    QString scanningTypeS;
    QString configFileS;
    QString robotInUseS;
//    QString userCommentsS;
//    QString expCommentsS;
    QString fullFileName;
    QString configFileName;
    QString loadedFileName;

//    twoThetaStep_* twoThetaStep;
};

#endif // WIZARD_H
