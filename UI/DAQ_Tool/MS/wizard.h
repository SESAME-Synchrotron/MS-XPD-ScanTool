#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>
#include "intervals.h"
#include "samples.h"
#include <qepicspv.h>
#include <client.h>

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

signals:
    void goToCheck() const;


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

    void checkIntervals (const QString &arg1);

    void checkSamples (const QString &arg1);

    void checkScans (const QString &arg1);

    void checkExpFileName(const QString &arg1);

    void checkSettlingTime (const QString &arg1);

    void configFileCheck();

    void on_loadConfigFileButton_clicked();

    void loadConfigFile(const QString& configFile);

    void createConfigFile(QString &config);

    void onWizardFinished(int order);

    void on_samplesButton_clicked();

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

    QString MS_ExperimentType     = "MS:ExperimentType"    ; int MS_ExperimentType_val     = 0;
    QString MS_ScanningType       = "MS:ScanningType"      ; int MS_ScanningType_val       = 0;
    QString MS_ConfigurationsFile = "MS:ConfigurationsFile"; int MS_ConfigurationsFile_val = 0;
    QString MS_Intervals          = "MS:Intervals"         ; int MS_Intervals_val          = 0;
    QString MS_Samples            = "MS:Samples"           ; int MS_Samples_val            = 0;
    QString MS_Scans              = "MS:Scans"             ; int MS_Scans_val              = 0;
    QString MS_SettlingTime       = "MS:SettlingTime"      ; int MS_SettlingTime_val       = 0;
    QString MS_UseRobot           = "MS:UseRobot"          ; int MS_UseRobot_val           = 0;
    QString MS_CheckTable         = "MS:CheckTable"        ; int MS_CheckTable_val         = 0;
    QString MS_CheckSamples       = "MS:CheckSamples"      ; int MS_CheckSamples_val       = 0;

    QString UItittle = "MS/XRD scan tool";
    QString workingDir = "/home/dcasu/XRD-Scan/UI/DAQ_Tool/MS/";

    QEpicsPV* experimentType = new QEpicsPV(MS_ExperimentType);
    QEpicsPV* scanningType   = new QEpicsPV(MS_ScanningType);
    QEpicsPV* Nintervals     = new QEpicsPV(MS_Intervals);
    QEpicsPV* sample         = new QEpicsPV(MS_Samples);
    QEpicsPV* Nscans         = new QEpicsPV(MS_Scans);
//    QEpicsPV* expFileName    = new QEpicsPV("MS:ExperimentalFileName");
    QEpicsPV* settlingTime   = new QEpicsPV(MS_SettlingTime);
    QEpicsPV* configFile     = new QEpicsPV(MS_ConfigurationsFile);
    QEpicsPV* checkTable     = new QEpicsPV(MS_CheckTable);
    QEpicsPV* checkSample    = new QEpicsPV(MS_CheckSamples);
    QEpicsPV* robotInUse     = new QEpicsPV(MS_UseRobot);
//    QEpicsPV* userComments   = new QEpicsPV("MS:UserComments");
//    QEpicsPV* expComments    = new QEpicsPV("MS:ExperimentComments");

    int experimentType_;
    int scanningType_;
    int configFile_;
    int robotInUse_;
    int startLoading;
    mutable int loadFile_;    // (mutable) because it is used in "const" functions

    bool Yes = 1;
    bool No  = 0;

    bool intervals_;
    bool samples_;
    bool scans_;
    bool expFileName_;
    bool settlingTime_;
    bool checkTable_;
    bool checkSample_;

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
};

#endif // WIZARD_H
