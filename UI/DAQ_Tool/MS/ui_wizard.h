/********************************************************************************
** Form generated from reading UI file 'wizard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARD_H
#define UI_WIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>
#include "QECheckBox.h"
#include "QELabel.h"
#include "QELineEdit.h"
#include "QENumericEdit.h"
#include "QERadioButton.h"

QT_BEGIN_NAMESPACE

class Ui_Wizard
{
public:
    QWizardPage *experimentType;
    QGroupBox *experimentSelection;
    QWidget *gridLayoutWidget;
    QGridLayout *experimentSelectionLayout;
    QERadioButton *localExperiment;
    QERadioButton *usersExperiment;
    QERadioButton *energyCalibraion;
    QWizardPage *proposalID;
    QGroupBox *proposalIDGroupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *proposalIDLayout;
    QELineEdit *proposalIDValue;
    QWizardPage *scanningType;
    QGroupBox *scanningTypeGroupBox;
    QWidget *gridLayoutWidget_3;
    QGridLayout *scanningTypeLayout;
    QERadioButton *twoThetaSlitsScan;
    QERadioButton *twoThetaScan;
    QERadioButton *twoThetaTempScan;
    QERadioButton *thetaTwoThetaScan;
    QWizardPage *configurationsFile;
    QGroupBox *configurationsFileGroubBox;
    QWidget *gridLayoutWidget_4;
    QGridLayout *configurationsFileLayout;
    QERadioButton *configurationsFileLoad;
    QERadioButton *configurationsFileCreate;
    QWizardPage *loadConfigFile;
    QWidget *gridLayoutWidget_6;
    QGridLayout *loadConfigFileLayout;
    QLabel *loadConfigFileLabel;
    QLabel *expConfigFile;
    QPushButton *loadConfigFileButton;
    QWizardPage *experimentalGUI;
    QGroupBox *robotGroupBox;
    QWidget *gridLayoutWidget_19;
    QGridLayout *robotLayout;
    QERadioButton *robotNo;
    QLabel *robotLabel;
    QERadioButton *robotYes;
    QLabel *robotInUse;
    QELabel *useRobotFeedback;
    QGroupBox *experimentalParameters_5;
    QWidget *gridLayoutWidget_20;
    QGridLayout *experimentalParametersLayout_5;
    QELineEdit *samples;
    QLabel *samplesLabel;
    QPushButton *intervalsButton;
    QELineEdit *settlingTime;
    QLabel *settlingTimeLabel;
    QELineEdit *intervals;
    QLabel *settlingTimeUnit;
    QPushButton *samplesButton;
    QLabel *scansLabel;
    QELineEdit *scans;
    QLabel *intervalsLabel;
    QLabel *expFileNameLabel;
    QELineEdit *expFileName;
    QLabel *validIntervals;
    QLabel *validSamples;
    QGroupBox *Comments;
    QWidget *gridLayoutWidget_21;
    QGridLayout *CommentsLayout;
    QLabel *userCommentsLabel;
    QLabel *expCommentsLabel;
    QELineEdit *expComments;
    QELineEdit *userComments;
    QWizardPage *twoThetaTemp;
    QGroupBox *gasBlowerGroupBox;
    QGroupBox *Comments2;
    QWidget *gridLayoutWidget_13;
    QGridLayout *CommentsLayout2;
    QLabel *userCommentsLabel2;
    QLabel *expCommentsLabel2;
    QELineEdit *expComments2;
    QELineEdit *userComments2;
    QGroupBox *experimentalParameters2;
    QWidget *gridLayoutWidget_25;
    QGridLayout *experimentalParametersLayout2;
    QLabel *samplesLabel2;
    QPushButton *intervalsButton2;
    QPushButton *samplesButton2;
    QLabel *scansLabel2;
    QLabel *expFileNameLabel2;
    QLabel *settlingTimeLabel2;
    QLabel *intervalsLabel2;
    QENumericEdit *intervals2;
    QENumericEdit *samples2;
    QENumericEdit *scans2;
    QELineEdit *expFileName2;
    QENumericEdit *settlingTime2;
    QWizardPage *twoThetaSlits;
    QGroupBox *slitConfigurationsGroupBox;
    QGroupBox *experimentalParameters3;
    QWidget *gridLayoutWidget_23;
    QGridLayout *experimentalParametersLayout3;
    QLabel *samplesLabel3;
    QPushButton *intervalsButton3;
    QPushButton *samplesButton3;
    QLabel *scansLabel3;
    QLabel *expFileNameLabel3;
    QLabel *settlingTimeLabel3;
    QLabel *intervalsLabel3;
    QENumericEdit *intervals3;
    QENumericEdit *samples3;
    QENumericEdit *scans3;
    QELineEdit *expFileName3;
    QENumericEdit *settlingTime3;
    QGroupBox *Comments3;
    QWidget *gridLayoutWidget_24;
    QGridLayout *CommentsLayout3;
    QLabel *userCommentsLabel3;
    QLabel *expCommentsLabel3;
    QELineEdit *expComments3;
    QELineEdit *userComments3;
    QGroupBox *robotGroupBox3_2;
    QWidget *gridLayoutWidget_27;
    QGridLayout *robotLayout3_2;
    QLabel *robotLabel3_2;
    QECheckBox *robotCheckBox3_2;
    QSpacerItem *horizontalSpacer3_2;
    QWizardPage *thetaTwoTheta;
    QGroupBox *Comments4;
    QWidget *gridLayoutWidget_18;
    QGridLayout *CommentsLayout4;
    QLabel *userCommentsLabel4;
    QLabel *expCommentsLabel4;
    QELineEdit *expComments4;
    QELineEdit *userComments4;
    QGroupBox *experimentalParameters4;
    QWidget *gridLayoutWidget_26;
    QGridLayout *experimentalParametersLayout4;
    QLabel *samplesLabel4;
    QPushButton *intervalsButton4;
    QPushButton *samplesButton4;
    QLabel *scansLabel4;
    QLabel *expFileNameLabel4;
    QLabel *settlingTimeLabel4;
    QLabel *intervalsLabel4;
    QENumericEdit *intervals4;
    QENumericEdit *samples4;
    QENumericEdit *scans4;
    QELineEdit *expFileName4;
    QENumericEdit *settlingTime4;
    QWizardPage *finishPage;
    QLabel *finishLabel;
    QWidget *gridLayoutWidget_5;
    QGridLayout *filePathLayout;
    QLabel *fullFilePath;
    QLabel *filePath;

    void setupUi(QWizard *Wizard)
    {
        if (Wizard->objectName().isEmpty())
            Wizard->setObjectName(QString::fromUtf8("Wizard"));
        Wizard->setWindowModality(Qt::ApplicationModal);
        Wizard->setEnabled(true);
        Wizard->resize(433, 613);
        Wizard->setCursor(QCursor(Qt::ArrowCursor));
        Wizard->setOptions(QWizard::HaveHelpButton|QWizard::NoBackButtonOnStartPage|QWizard::NoDefaultButton);
        experimentType = new QWizardPage();
        experimentType->setObjectName(QString::fromUtf8("experimentType"));
        experimentSelection = new QGroupBox(experimentType);
        experimentSelection->setObjectName(QString::fromUtf8("experimentSelection"));
        experimentSelection->setGeometry(QRect(0, 0, 411, 121));
        experimentSelection->setCursor(QCursor(Qt::ArrowCursor));
        experimentSelection->setAutoFillBackground(false);
        experimentSelection->setFlat(false);
        experimentSelection->setCheckable(false);
        gridLayoutWidget = new QWidget(experimentSelection);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 81));
        experimentSelectionLayout = new QGridLayout(gridLayoutWidget);
        experimentSelectionLayout->setObjectName(QString::fromUtf8("experimentSelectionLayout"));
        experimentSelectionLayout->setContentsMargins(0, 0, 0, 0);
        localExperiment = new QERadioButton(gridLayoutWidget);
        localExperiment->setObjectName(QString::fromUtf8("localExperiment"));
        localExperiment->setCursor(QCursor(Qt::ArrowCursor));
        localExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        experimentSelectionLayout->addWidget(localExperiment, 1, 0, 1, 1);

        usersExperiment = new QERadioButton(gridLayoutWidget);
        usersExperiment->setObjectName(QString::fromUtf8("usersExperiment"));
        usersExperiment->setCursor(QCursor(Qt::ArrowCursor));
        usersExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));
        usersExperiment->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        experimentSelectionLayout->addWidget(usersExperiment, 0, 0, 1, 1);

        energyCalibraion = new QERadioButton(gridLayoutWidget);
        energyCalibraion->setObjectName(QString::fromUtf8("energyCalibraion"));
        energyCalibraion->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        experimentSelectionLayout->addWidget(energyCalibraion, 2, 0, 1, 1);

        Wizard->setPage(1, experimentType);
        proposalID = new QWizardPage();
        proposalID->setObjectName(QString::fromUtf8("proposalID"));
        proposalIDGroupBox = new QGroupBox(proposalID);
        proposalIDGroupBox->setObjectName(QString::fromUtf8("proposalIDGroupBox"));
        proposalIDGroupBox->setGeometry(QRect(0, 0, 411, 91));
        gridLayoutWidget_2 = new QWidget(proposalIDGroupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 30, 331, 54));
        proposalIDLayout = new QGridLayout(gridLayoutWidget_2);
        proposalIDLayout->setObjectName(QString::fromUtf8("proposalIDLayout"));
        proposalIDLayout->setContentsMargins(0, 0, 0, 0);
        proposalIDValue = new QELineEdit(gridLayoutWidget_2);
        proposalIDValue->setObjectName(QString::fromUtf8("proposalIDValue"));
        proposalIDValue->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhNoTextHandles);
        proposalIDValue->setDragEnabled(false);
        proposalIDValue->setClearButtonEnabled(false);

        proposalIDLayout->addWidget(proposalIDValue, 0, 0, 1, 1);

        Wizard->setPage(2, proposalID);
        scanningType = new QWizardPage();
        scanningType->setObjectName(QString::fromUtf8("scanningType"));
        scanningTypeGroupBox = new QGroupBox(scanningType);
        scanningTypeGroupBox->setObjectName(QString::fromUtf8("scanningTypeGroupBox"));
        scanningTypeGroupBox->setGeometry(QRect(0, 0, 411, 141));
        scanningTypeGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        scanningTypeGroupBox->setAutoFillBackground(false);
        scanningTypeGroupBox->setFlat(false);
        scanningTypeGroupBox->setCheckable(false);
        gridLayoutWidget_3 = new QWidget(scanningTypeGroupBox);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 30, 321, 104));
        scanningTypeLayout = new QGridLayout(gridLayoutWidget_3);
        scanningTypeLayout->setObjectName(QString::fromUtf8("scanningTypeLayout"));
        scanningTypeLayout->setContentsMargins(0, 0, 0, 0);
        twoThetaSlitsScan = new QERadioButton(gridLayoutWidget_3);
        twoThetaSlitsScan->setObjectName(QString::fromUtf8("twoThetaSlitsScan"));
        twoThetaSlitsScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        scanningTypeLayout->addWidget(twoThetaSlitsScan, 2, 0, 1, 1);

        twoThetaScan = new QERadioButton(gridLayoutWidget_3);
        twoThetaScan->setObjectName(QString::fromUtf8("twoThetaScan"));
        twoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));
        twoThetaScan->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        scanningTypeLayout->addWidget(twoThetaScan, 0, 0, 1, 1);

        twoThetaTempScan = new QERadioButton(gridLayoutWidget_3);
        twoThetaTempScan->setObjectName(QString::fromUtf8("twoThetaTempScan"));
        twoThetaTempScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        scanningTypeLayout->addWidget(twoThetaTempScan, 1, 0, 1, 1);

        thetaTwoThetaScan = new QERadioButton(gridLayoutWidget_3);
        thetaTwoThetaScan->setObjectName(QString::fromUtf8("thetaTwoThetaScan"));
        thetaTwoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        scanningTypeLayout->addWidget(thetaTwoThetaScan, 3, 0, 1, 1);

        Wizard->setPage(3, scanningType);
        configurationsFile = new QWizardPage();
        configurationsFile->setObjectName(QString::fromUtf8("configurationsFile"));
        configurationsFileGroubBox = new QGroupBox(configurationsFile);
        configurationsFileGroubBox->setObjectName(QString::fromUtf8("configurationsFileGroubBox"));
        configurationsFileGroubBox->setGeometry(QRect(0, 0, 411, 91));
        configurationsFileGroubBox->setCursor(QCursor(Qt::ArrowCursor));
        configurationsFileGroubBox->setAutoFillBackground(false);
        configurationsFileGroubBox->setFlat(false);
        configurationsFileGroubBox->setCheckable(false);
        gridLayoutWidget_4 = new QWidget(configurationsFileGroubBox);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 30, 321, 51));
        configurationsFileLayout = new QGridLayout(gridLayoutWidget_4);
        configurationsFileLayout->setObjectName(QString::fromUtf8("configurationsFileLayout"));
        configurationsFileLayout->setContentsMargins(0, 0, 0, 0);
        configurationsFileLoad = new QERadioButton(gridLayoutWidget_4);
        configurationsFileLoad->setObjectName(QString::fromUtf8("configurationsFileLoad"));
        configurationsFileLoad->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        configurationsFileLayout->addWidget(configurationsFileLoad, 1, 0, 1, 1);

        configurationsFileCreate = new QERadioButton(gridLayoutWidget_4);
        configurationsFileCreate->setObjectName(QString::fromUtf8("configurationsFileCreate"));
        configurationsFileCreate->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));
        configurationsFileCreate->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        configurationsFileLayout->addWidget(configurationsFileCreate, 0, 0, 1, 1);

        Wizard->setPage(4, configurationsFile);
        loadConfigFile = new QWizardPage();
        loadConfigFile->setObjectName(QString::fromUtf8("loadConfigFile"));
        gridLayoutWidget_6 = new QWidget(loadConfigFile);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 40, 411, 31));
        loadConfigFileLayout = new QGridLayout(gridLayoutWidget_6);
        loadConfigFileLayout->setObjectName(QString::fromUtf8("loadConfigFileLayout"));
        loadConfigFileLayout->setContentsMargins(0, 0, 0, 0);
        loadConfigFileLabel = new QLabel(gridLayoutWidget_6);
        loadConfigFileLabel->setObjectName(QString::fromUtf8("loadConfigFileLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loadConfigFileLabel->sizePolicy().hasHeightForWidth());
        loadConfigFileLabel->setSizePolicy(sizePolicy);

        loadConfigFileLayout->addWidget(loadConfigFileLabel, 0, 0, 1, 1);

        expConfigFile = new QLabel(gridLayoutWidget_6);
        expConfigFile->setObjectName(QString::fromUtf8("expConfigFile"));
        QFont font;
        font.setPointSize(8);
        expConfigFile->setFont(font);
        expConfigFile->setCursor(QCursor(Qt::IBeamCursor));
        expConfigFile->setFrameShape(QFrame::StyledPanel);
        expConfigFile->setWordWrap(true);

        loadConfigFileLayout->addWidget(expConfigFile, 0, 1, 1, 1);

        loadConfigFileButton = new QPushButton(gridLayoutWidget_6);
        loadConfigFileButton->setObjectName(QString::fromUtf8("loadConfigFileButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loadConfigFileButton->sizePolicy().hasHeightForWidth());
        loadConfigFileButton->setSizePolicy(sizePolicy1);
        loadConfigFileButton->setMinimumSize(QSize(2, 0));
        loadConfigFileButton->setMaximumSize(QSize(30, 16777215));
        loadConfigFileButton->setCursor(QCursor(Qt::PointingHandCursor));

        loadConfigFileLayout->addWidget(loadConfigFileButton, 0, 2, 1, 1);

        Wizard->setPage(5, loadConfigFile);
        experimentalGUI = new QWizardPage();
        experimentalGUI->setObjectName(QString::fromUtf8("experimentalGUI"));
        robotGroupBox = new QGroupBox(experimentalGUI);
        robotGroupBox->setObjectName(QString::fromUtf8("robotGroupBox"));
        robotGroupBox->setGeometry(QRect(0, 200, 411, 91));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(robotGroupBox->sizePolicy().hasHeightForWidth());
        robotGroupBox->setSizePolicy(sizePolicy2);
        robotGroupBox->setMinimumSize(QSize(0, 0));
        robotGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        robotGroupBox->setAutoFillBackground(false);
        robotGroupBox->setFlat(false);
        robotGroupBox->setCheckable(false);
        gridLayoutWidget_19 = new QWidget(robotGroupBox);
        gridLayoutWidget_19->setObjectName(QString::fromUtf8("gridLayoutWidget_19"));
        gridLayoutWidget_19->setGeometry(QRect(10, 30, 391, 50));
        robotLayout = new QGridLayout(gridLayoutWidget_19);
        robotLayout->setObjectName(QString::fromUtf8("robotLayout"));
        robotLayout->setContentsMargins(0, 0, 0, 0);
        robotNo = new QERadioButton(gridLayoutWidget_19);
        robotNo->setObjectName(QString::fromUtf8("robotNo"));
        robotNo->setFocusPolicy(Qt::StrongFocus);
        robotNo->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        robotLayout->addWidget(robotNo, 1, 1, 1, 1);

        robotLabel = new QLabel(gridLayoutWidget_19);
        robotLabel->setObjectName(QString::fromUtf8("robotLabel"));
        robotLabel->setCursor(QCursor(Qt::IBeamCursor));

        robotLayout->addWidget(robotLabel, 0, 0, 2, 1);

        robotYes = new QERadioButton(gridLayoutWidget_19);
        robotYes->setObjectName(QString::fromUtf8("robotYes"));
        robotYes->setFocusPolicy(Qt::StrongFocus);
        robotYes->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::WhenInAlarm));

        robotLayout->addWidget(robotYes, 0, 1, 1, 1);

        robotInUse = new QLabel(gridLayoutWidget_19);
        robotInUse->setObjectName(QString::fromUtf8("robotInUse"));

        robotLayout->addWidget(robotInUse, 0, 2, 2, 1);

        useRobotFeedback = new QELabel(gridLayoutWidget_19);
        useRobotFeedback->setObjectName(QString::fromUtf8("useRobotFeedback"));
        useRobotFeedback->setFrameShape(QFrame::StyledPanel);
        useRobotFeedback->setAlignment(Qt::AlignCenter);
        useRobotFeedback->setWordWrap(true);
        useRobotFeedback->setAddUnits(false);

        robotLayout->addWidget(useRobotFeedback, 0, 3, 2, 1);

        experimentalParameters_5 = new QGroupBox(experimentalGUI);
        experimentalParameters_5->setObjectName(QString::fromUtf8("experimentalParameters_5"));
        experimentalParameters_5->setGeometry(QRect(0, 0, 411, 191));
        experimentalParameters_5->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters_5->setAutoFillBackground(false);
        experimentalParameters_5->setFlat(false);
        experimentalParameters_5->setCheckable(false);
        gridLayoutWidget_20 = new QWidget(experimentalParameters_5);
        gridLayoutWidget_20->setObjectName(QString::fromUtf8("gridLayoutWidget_20"));
        gridLayoutWidget_20->setGeometry(QRect(10, 30, 391, 151));
        experimentalParametersLayout_5 = new QGridLayout(gridLayoutWidget_20);
        experimentalParametersLayout_5->setObjectName(QString::fromUtf8("experimentalParametersLayout_5"));
        experimentalParametersLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout_5->setContentsMargins(0, 0, 0, 0);
        samples = new QELineEdit(gridLayoutWidget_20);
        samples->setObjectName(QString::fromUtf8("samples"));
        samples->setAlignment(Qt::AlignCenter);
        samples->setDragEnabled(true);
        samples->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));
        samples->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout_5->addWidget(samples, 1, 1, 1, 2);

        samplesLabel = new QLabel(gridLayoutWidget_20);
        samplesLabel->setObjectName(QString::fromUtf8("samplesLabel"));
        samplesLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout_5->addWidget(samplesLabel, 1, 0, 1, 1);

        intervalsButton = new QPushButton(gridLayoutWidget_20);
        intervalsButton->setObjectName(QString::fromUtf8("intervalsButton"));
        intervalsButton->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout_5->addWidget(intervalsButton, 0, 3, 1, 1);

        settlingTime = new QELineEdit(gridLayoutWidget_20);
        settlingTime->setObjectName(QString::fromUtf8("settlingTime"));
        settlingTime->setAlignment(Qt::AlignCenter);
        settlingTime->setDragEnabled(true);
        settlingTime->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));
        settlingTime->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        experimentalParametersLayout_5->addWidget(settlingTime, 4, 1, 1, 1);

        settlingTimeLabel = new QLabel(gridLayoutWidget_20);
        settlingTimeLabel->setObjectName(QString::fromUtf8("settlingTimeLabel"));
        settlingTimeLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout_5->addWidget(settlingTimeLabel, 4, 0, 1, 1);

        intervals = new QELineEdit(gridLayoutWidget_20);
        intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->setAlignment(Qt::AlignCenter);
        intervals->setDragEnabled(true);
        intervals->setWriteOnEnter(true);
        intervals->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));
        intervals->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout_5->addWidget(intervals, 0, 1, 1, 2);

        settlingTimeUnit = new QLabel(gridLayoutWidget_20);
        settlingTimeUnit->setObjectName(QString::fromUtf8("settlingTimeUnit"));

        experimentalParametersLayout_5->addWidget(settlingTimeUnit, 4, 2, 1, 1);

        samplesButton = new QPushButton(gridLayoutWidget_20);
        samplesButton->setObjectName(QString::fromUtf8("samplesButton"));
        samplesButton->setCursor(QCursor(Qt::PointingHandCursor));
        samplesButton->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout_5->addWidget(samplesButton, 1, 3, 1, 1);

        scansLabel = new QLabel(gridLayoutWidget_20);
        scansLabel->setObjectName(QString::fromUtf8("scansLabel"));
        scansLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout_5->addWidget(scansLabel, 2, 0, 1, 1);

        scans = new QELineEdit(gridLayoutWidget_20);
        scans->setObjectName(QString::fromUtf8("scans"));
        scans->setAlignment(Qt::AlignCenter);
        scans->setDragEnabled(true);
        scans->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));
        scans->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout_5->addWidget(scans, 2, 1, 1, 2);

        intervalsLabel = new QLabel(gridLayoutWidget_20);
        intervalsLabel->setObjectName(QString::fromUtf8("intervalsLabel"));
        intervalsLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout_5->addWidget(intervalsLabel, 0, 0, 1, 1);

        expFileNameLabel = new QLabel(gridLayoutWidget_20);
        expFileNameLabel->setObjectName(QString::fromUtf8("expFileNameLabel"));
        expFileNameLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout_5->addWidget(expFileNameLabel, 3, 0, 1, 1);

        expFileName = new QELineEdit(gridLayoutWidget_20);
        expFileName->setObjectName(QString::fromUtf8("expFileName"));
        expFileName->setDragEnabled(true);
        expFileName->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));

        experimentalParametersLayout_5->addWidget(expFileName, 3, 1, 1, 2);

        validIntervals = new QLabel(gridLayoutWidget_20);
        validIntervals->setObjectName(QString::fromUtf8("validIntervals"));
        QFont font1;
        font1.setPointSize(14);
        validIntervals->setFont(font1);

        experimentalParametersLayout_5->addWidget(validIntervals, 0, 4, 1, 1);

        validSamples = new QLabel(gridLayoutWidget_20);
        validSamples->setObjectName(QString::fromUtf8("validSamples"));
        validSamples->setFont(font1);

        experimentalParametersLayout_5->addWidget(validSamples, 1, 4, 1, 1);

        Comments = new QGroupBox(experimentalGUI);
        Comments->setObjectName(QString::fromUtf8("Comments"));
        Comments->setGeometry(QRect(0, 450, 411, 101));
        sizePolicy2.setHeightForWidth(Comments->sizePolicy().hasHeightForWidth());
        Comments->setSizePolicy(sizePolicy2);
        Comments->setMinimumSize(QSize(0, 0));
        Comments->setCursor(QCursor(Qt::ArrowCursor));
        Comments->setAutoFillBackground(false);
        Comments->setFlat(false);
        Comments->setCheckable(false);
        gridLayoutWidget_21 = new QWidget(Comments);
        gridLayoutWidget_21->setObjectName(QString::fromUtf8("gridLayoutWidget_21"));
        gridLayoutWidget_21->setGeometry(QRect(10, 30, 391, 70));
        CommentsLayout = new QGridLayout(gridLayoutWidget_21);
        CommentsLayout->setObjectName(QString::fromUtf8("CommentsLayout"));
        CommentsLayout->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel = new QLabel(gridLayoutWidget_21);
        userCommentsLabel->setObjectName(QString::fromUtf8("userCommentsLabel"));
        userCommentsLabel->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout->addWidget(userCommentsLabel, 0, 0, 1, 1);

        expCommentsLabel = new QLabel(gridLayoutWidget_21);
        expCommentsLabel->setObjectName(QString::fromUtf8("expCommentsLabel"));
        expCommentsLabel->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout->addWidget(expCommentsLabel, 1, 0, 1, 1);

        expComments = new QELineEdit(gridLayoutWidget_21);
        expComments->setObjectName(QString::fromUtf8("expComments"));
        expComments->setDragEnabled(true);
        expComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));

        CommentsLayout->addWidget(expComments, 1, 1, 1, 1);

        userComments = new QELineEdit(gridLayoutWidget_21);
        userComments->setObjectName(QString::fromUtf8("userComments"));
        userComments->setDragEnabled(true);
        userComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::WhenInAlarm));

        CommentsLayout->addWidget(userComments, 0, 1, 1, 1);

        Wizard->setPage(6, experimentalGUI);
        twoThetaTemp = new QWizardPage();
        twoThetaTemp->setObjectName(QString::fromUtf8("twoThetaTemp"));
        gasBlowerGroupBox = new QGroupBox(twoThetaTemp);
        gasBlowerGroupBox->setObjectName(QString::fromUtf8("gasBlowerGroupBox"));
        gasBlowerGroupBox->setGeometry(QRect(0, 200, 411, 91));
        gasBlowerGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        gasBlowerGroupBox->setAutoFillBackground(false);
        gasBlowerGroupBox->setFlat(false);
        gasBlowerGroupBox->setCheckable(false);
        Comments2 = new QGroupBox(twoThetaTemp);
        Comments2->setObjectName(QString::fromUtf8("Comments2"));
        Comments2->setGeometry(QRect(0, 450, 411, 101));
        sizePolicy2.setHeightForWidth(Comments2->sizePolicy().hasHeightForWidth());
        Comments2->setSizePolicy(sizePolicy2);
        Comments2->setMinimumSize(QSize(0, 0));
        Comments2->setCursor(QCursor(Qt::ArrowCursor));
        Comments2->setAutoFillBackground(false);
        Comments2->setFlat(false);
        Comments2->setCheckable(false);
        gridLayoutWidget_13 = new QWidget(Comments2);
        gridLayoutWidget_13->setObjectName(QString::fromUtf8("gridLayoutWidget_13"));
        gridLayoutWidget_13->setGeometry(QRect(10, 30, 391, 66));
        CommentsLayout2 = new QGridLayout(gridLayoutWidget_13);
        CommentsLayout2->setObjectName(QString::fromUtf8("CommentsLayout2"));
        CommentsLayout2->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel2 = new QLabel(gridLayoutWidget_13);
        userCommentsLabel2->setObjectName(QString::fromUtf8("userCommentsLabel2"));

        CommentsLayout2->addWidget(userCommentsLabel2, 0, 0, 1, 1);

        expCommentsLabel2 = new QLabel(gridLayoutWidget_13);
        expCommentsLabel2->setObjectName(QString::fromUtf8("expCommentsLabel2"));

        CommentsLayout2->addWidget(expCommentsLabel2, 1, 0, 1, 1);

        expComments2 = new QELineEdit(gridLayoutWidget_13);
        expComments2->setObjectName(QString::fromUtf8("expComments2"));

        CommentsLayout2->addWidget(expComments2, 1, 1, 1, 1);

        userComments2 = new QELineEdit(gridLayoutWidget_13);
        userComments2->setObjectName(QString::fromUtf8("userComments2"));

        CommentsLayout2->addWidget(userComments2, 0, 1, 1, 1);

        experimentalParameters2 = new QGroupBox(twoThetaTemp);
        experimentalParameters2->setObjectName(QString::fromUtf8("experimentalParameters2"));
        experimentalParameters2->setGeometry(QRect(0, 0, 411, 181));
        experimentalParameters2->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters2->setAutoFillBackground(false);
        experimentalParameters2->setFlat(false);
        experimentalParameters2->setCheckable(false);
        gridLayoutWidget_25 = new QWidget(experimentalParameters2);
        gridLayoutWidget_25->setObjectName(QString::fromUtf8("gridLayoutWidget_25"));
        gridLayoutWidget_25->setGeometry(QRect(10, 30, 391, 141));
        experimentalParametersLayout2 = new QGridLayout(gridLayoutWidget_25);
        experimentalParametersLayout2->setObjectName(QString::fromUtf8("experimentalParametersLayout2"));
        experimentalParametersLayout2->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout2->setContentsMargins(0, 0, 0, 0);
        samplesLabel2 = new QLabel(gridLayoutWidget_25);
        samplesLabel2->setObjectName(QString::fromUtf8("samplesLabel2"));

        experimentalParametersLayout2->addWidget(samplesLabel2, 1, 0, 1, 1);

        intervalsButton2 = new QPushButton(gridLayoutWidget_25);
        intervalsButton2->setObjectName(QString::fromUtf8("intervalsButton2"));

        experimentalParametersLayout2->addWidget(intervalsButton2, 0, 2, 1, 1);

        samplesButton2 = new QPushButton(gridLayoutWidget_25);
        samplesButton2->setObjectName(QString::fromUtf8("samplesButton2"));

        experimentalParametersLayout2->addWidget(samplesButton2, 1, 2, 1, 1);

        scansLabel2 = new QLabel(gridLayoutWidget_25);
        scansLabel2->setObjectName(QString::fromUtf8("scansLabel2"));

        experimentalParametersLayout2->addWidget(scansLabel2, 2, 0, 1, 1);

        expFileNameLabel2 = new QLabel(gridLayoutWidget_25);
        expFileNameLabel2->setObjectName(QString::fromUtf8("expFileNameLabel2"));

        experimentalParametersLayout2->addWidget(expFileNameLabel2, 3, 0, 1, 1);

        settlingTimeLabel2 = new QLabel(gridLayoutWidget_25);
        settlingTimeLabel2->setObjectName(QString::fromUtf8("settlingTimeLabel2"));

        experimentalParametersLayout2->addWidget(settlingTimeLabel2, 4, 0, 1, 1);

        intervalsLabel2 = new QLabel(gridLayoutWidget_25);
        intervalsLabel2->setObjectName(QString::fromUtf8("intervalsLabel2"));

        experimentalParametersLayout2->addWidget(intervalsLabel2, 0, 0, 1, 1);

        intervals2 = new QENumericEdit(gridLayoutWidget_25);
        intervals2->setObjectName(QString::fromUtf8("intervals2"));
        intervals2->setAlignment(Qt::AlignCenter);
        intervals2->setLeadingZeros(0);
        intervals2->setPrecision(0);
        intervals2->setMinimum(0.000000000000000);

        experimentalParametersLayout2->addWidget(intervals2, 0, 1, 1, 1);

        samples2 = new QENumericEdit(gridLayoutWidget_25);
        samples2->setObjectName(QString::fromUtf8("samples2"));
        samples2->setAlignment(Qt::AlignCenter);
        samples2->setLeadingZeros(0);
        samples2->setPrecision(0);
        samples2->setMinimum(0.000000000000000);

        experimentalParametersLayout2->addWidget(samples2, 1, 1, 1, 1);

        scans2 = new QENumericEdit(gridLayoutWidget_25);
        scans2->setObjectName(QString::fromUtf8("scans2"));
        scans2->setAlignment(Qt::AlignCenter);
        scans2->setLeadingZeros(0);
        scans2->setPrecision(0);
        scans2->setMinimum(0.000000000000000);

        experimentalParametersLayout2->addWidget(scans2, 2, 1, 1, 1);

        expFileName2 = new QELineEdit(gridLayoutWidget_25);
        expFileName2->setObjectName(QString::fromUtf8("expFileName2"));

        experimentalParametersLayout2->addWidget(expFileName2, 3, 1, 1, 1);

        settlingTime2 = new QENumericEdit(gridLayoutWidget_25);
        settlingTime2->setObjectName(QString::fromUtf8("settlingTime2"));
        settlingTime2->setAlignment(Qt::AlignCenter);
        settlingTime2->setLeadingZeros(0);
        settlingTime2->setPrecision(0);
        settlingTime2->setMinimum(0.000000000000000);

        experimentalParametersLayout2->addWidget(settlingTime2, 4, 1, 1, 1);

        Wizard->setPage(7, twoThetaTemp);
        twoThetaSlits = new QWizardPage();
        twoThetaSlits->setObjectName(QString::fromUtf8("twoThetaSlits"));
        slitConfigurationsGroupBox = new QGroupBox(twoThetaSlits);
        slitConfigurationsGroupBox->setObjectName(QString::fromUtf8("slitConfigurationsGroupBox"));
        slitConfigurationsGroupBox->setGeometry(QRect(0, 190, 411, 81));
        sizePolicy2.setHeightForWidth(slitConfigurationsGroupBox->sizePolicy().hasHeightForWidth());
        slitConfigurationsGroupBox->setSizePolicy(sizePolicy2);
        slitConfigurationsGroupBox->setMinimumSize(QSize(0, 0));
        slitConfigurationsGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        slitConfigurationsGroupBox->setAutoFillBackground(false);
        slitConfigurationsGroupBox->setFlat(false);
        slitConfigurationsGroupBox->setCheckable(false);
        experimentalParameters3 = new QGroupBox(twoThetaSlits);
        experimentalParameters3->setObjectName(QString::fromUtf8("experimentalParameters3"));
        experimentalParameters3->setGeometry(QRect(0, 0, 411, 181));
        experimentalParameters3->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters3->setAutoFillBackground(false);
        experimentalParameters3->setFlat(false);
        experimentalParameters3->setCheckable(false);
        gridLayoutWidget_23 = new QWidget(experimentalParameters3);
        gridLayoutWidget_23->setObjectName(QString::fromUtf8("gridLayoutWidget_23"));
        gridLayoutWidget_23->setGeometry(QRect(10, 30, 391, 141));
        experimentalParametersLayout3 = new QGridLayout(gridLayoutWidget_23);
        experimentalParametersLayout3->setObjectName(QString::fromUtf8("experimentalParametersLayout3"));
        experimentalParametersLayout3->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout3->setContentsMargins(0, 0, 0, 0);
        samplesLabel3 = new QLabel(gridLayoutWidget_23);
        samplesLabel3->setObjectName(QString::fromUtf8("samplesLabel3"));

        experimentalParametersLayout3->addWidget(samplesLabel3, 1, 0, 1, 1);

        intervalsButton3 = new QPushButton(gridLayoutWidget_23);
        intervalsButton3->setObjectName(QString::fromUtf8("intervalsButton3"));

        experimentalParametersLayout3->addWidget(intervalsButton3, 0, 2, 1, 1);

        samplesButton3 = new QPushButton(gridLayoutWidget_23);
        samplesButton3->setObjectName(QString::fromUtf8("samplesButton3"));

        experimentalParametersLayout3->addWidget(samplesButton3, 1, 2, 1, 1);

        scansLabel3 = new QLabel(gridLayoutWidget_23);
        scansLabel3->setObjectName(QString::fromUtf8("scansLabel3"));

        experimentalParametersLayout3->addWidget(scansLabel3, 2, 0, 1, 1);

        expFileNameLabel3 = new QLabel(gridLayoutWidget_23);
        expFileNameLabel3->setObjectName(QString::fromUtf8("expFileNameLabel3"));

        experimentalParametersLayout3->addWidget(expFileNameLabel3, 3, 0, 1, 1);

        settlingTimeLabel3 = new QLabel(gridLayoutWidget_23);
        settlingTimeLabel3->setObjectName(QString::fromUtf8("settlingTimeLabel3"));

        experimentalParametersLayout3->addWidget(settlingTimeLabel3, 4, 0, 1, 1);

        intervalsLabel3 = new QLabel(gridLayoutWidget_23);
        intervalsLabel3->setObjectName(QString::fromUtf8("intervalsLabel3"));

        experimentalParametersLayout3->addWidget(intervalsLabel3, 0, 0, 1, 1);

        intervals3 = new QENumericEdit(gridLayoutWidget_23);
        intervals3->setObjectName(QString::fromUtf8("intervals3"));
        intervals3->setAlignment(Qt::AlignCenter);
        intervals3->setLeadingZeros(0);
        intervals3->setPrecision(0);
        intervals3->setMinimum(0.000000000000000);

        experimentalParametersLayout3->addWidget(intervals3, 0, 1, 1, 1);

        samples3 = new QENumericEdit(gridLayoutWidget_23);
        samples3->setObjectName(QString::fromUtf8("samples3"));
        samples3->setAlignment(Qt::AlignCenter);
        samples3->setLeadingZeros(0);
        samples3->setPrecision(0);
        samples3->setMinimum(0.000000000000000);

        experimentalParametersLayout3->addWidget(samples3, 1, 1, 1, 1);

        scans3 = new QENumericEdit(gridLayoutWidget_23);
        scans3->setObjectName(QString::fromUtf8("scans3"));
        scans3->setAlignment(Qt::AlignCenter);
        scans3->setLeadingZeros(0);
        scans3->setPrecision(0);
        scans3->setMinimum(0.000000000000000);

        experimentalParametersLayout3->addWidget(scans3, 2, 1, 1, 1);

        expFileName3 = new QELineEdit(gridLayoutWidget_23);
        expFileName3->setObjectName(QString::fromUtf8("expFileName3"));
        expFileName3->setWriteOnFinish(false);

        experimentalParametersLayout3->addWidget(expFileName3, 3, 1, 1, 1);

        settlingTime3 = new QENumericEdit(gridLayoutWidget_23);
        settlingTime3->setObjectName(QString::fromUtf8("settlingTime3"));
        settlingTime3->setAlignment(Qt::AlignCenter);
        settlingTime3->setLeadingZeros(0);
        settlingTime3->setPrecision(0);
        settlingTime3->setMinimum(0.000000000000000);

        experimentalParametersLayout3->addWidget(settlingTime3, 4, 1, 1, 1);

        Comments3 = new QGroupBox(twoThetaSlits);
        Comments3->setObjectName(QString::fromUtf8("Comments3"));
        Comments3->setGeometry(QRect(0, 450, 411, 101));
        sizePolicy2.setHeightForWidth(Comments3->sizePolicy().hasHeightForWidth());
        Comments3->setSizePolicy(sizePolicy2);
        Comments3->setMinimumSize(QSize(0, 0));
        Comments3->setCursor(QCursor(Qt::ArrowCursor));
        Comments3->setAutoFillBackground(false);
        Comments3->setFlat(false);
        Comments3->setCheckable(false);
        gridLayoutWidget_24 = new QWidget(Comments3);
        gridLayoutWidget_24->setObjectName(QString::fromUtf8("gridLayoutWidget_24"));
        gridLayoutWidget_24->setGeometry(QRect(10, 30, 391, 66));
        CommentsLayout3 = new QGridLayout(gridLayoutWidget_24);
        CommentsLayout3->setObjectName(QString::fromUtf8("CommentsLayout3"));
        CommentsLayout3->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel3 = new QLabel(gridLayoutWidget_24);
        userCommentsLabel3->setObjectName(QString::fromUtf8("userCommentsLabel3"));

        CommentsLayout3->addWidget(userCommentsLabel3, 0, 0, 1, 1);

        expCommentsLabel3 = new QLabel(gridLayoutWidget_24);
        expCommentsLabel3->setObjectName(QString::fromUtf8("expCommentsLabel3"));

        CommentsLayout3->addWidget(expCommentsLabel3, 1, 0, 1, 1);

        expComments3 = new QELineEdit(gridLayoutWidget_24);
        expComments3->setObjectName(QString::fromUtf8("expComments3"));
        expComments3->setWriteOnFinish(false);

        CommentsLayout3->addWidget(expComments3, 1, 1, 1, 1);

        userComments3 = new QELineEdit(gridLayoutWidget_24);
        userComments3->setObjectName(QString::fromUtf8("userComments3"));
        userComments3->setWriteOnFinish(false);

        CommentsLayout3->addWidget(userComments3, 0, 1, 1, 1);

        robotGroupBox3_2 = new QGroupBox(twoThetaSlits);
        robotGroupBox3_2->setObjectName(QString::fromUtf8("robotGroupBox3_2"));
        robotGroupBox3_2->setGeometry(QRect(0, 280, 411, 81));
        sizePolicy2.setHeightForWidth(robotGroupBox3_2->sizePolicy().hasHeightForWidth());
        robotGroupBox3_2->setSizePolicy(sizePolicy2);
        robotGroupBox3_2->setMinimumSize(QSize(0, 0));
        robotGroupBox3_2->setCursor(QCursor(Qt::ArrowCursor));
        robotGroupBox3_2->setAutoFillBackground(false);
        robotGroupBox3_2->setFlat(false);
        robotGroupBox3_2->setCheckable(false);
        gridLayoutWidget_27 = new QWidget(robotGroupBox3_2);
        gridLayoutWidget_27->setObjectName(QString::fromUtf8("gridLayoutWidget_27"));
        gridLayoutWidget_27->setGeometry(QRect(10, 30, 331, 31));
        robotLayout3_2 = new QGridLayout(gridLayoutWidget_27);
        robotLayout3_2->setObjectName(QString::fromUtf8("robotLayout3_2"));
        robotLayout3_2->setContentsMargins(0, 0, 0, 0);
        robotLabel3_2 = new QLabel(gridLayoutWidget_27);
        robotLabel3_2->setObjectName(QString::fromUtf8("robotLabel3_2"));

        robotLayout3_2->addWidget(robotLabel3_2, 0, 0, 1, 1);

        robotCheckBox3_2 = new QECheckBox(gridLayoutWidget_27);
        robotCheckBox3_2->setObjectName(QString::fromUtf8("robotCheckBox3_2"));

        robotLayout3_2->addWidget(robotCheckBox3_2, 0, 1, 1, 1);

        horizontalSpacer3_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        robotLayout3_2->addItem(horizontalSpacer3_2, 0, 2, 1, 1);

        Wizard->setPage(8, twoThetaSlits);
        thetaTwoTheta = new QWizardPage();
        thetaTwoTheta->setObjectName(QString::fromUtf8("thetaTwoTheta"));
        Comments4 = new QGroupBox(thetaTwoTheta);
        Comments4->setObjectName(QString::fromUtf8("Comments4"));
        Comments4->setGeometry(QRect(0, 448, 411, 101));
        sizePolicy2.setHeightForWidth(Comments4->sizePolicy().hasHeightForWidth());
        Comments4->setSizePolicy(sizePolicy2);
        Comments4->setMinimumSize(QSize(0, 0));
        Comments4->setCursor(QCursor(Qt::ArrowCursor));
        Comments4->setAutoFillBackground(false);
        Comments4->setFlat(false);
        Comments4->setCheckable(false);
        gridLayoutWidget_18 = new QWidget(Comments4);
        gridLayoutWidget_18->setObjectName(QString::fromUtf8("gridLayoutWidget_18"));
        gridLayoutWidget_18->setGeometry(QRect(10, 30, 391, 66));
        CommentsLayout4 = new QGridLayout(gridLayoutWidget_18);
        CommentsLayout4->setObjectName(QString::fromUtf8("CommentsLayout4"));
        CommentsLayout4->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel4 = new QLabel(gridLayoutWidget_18);
        userCommentsLabel4->setObjectName(QString::fromUtf8("userCommentsLabel4"));

        CommentsLayout4->addWidget(userCommentsLabel4, 0, 0, 1, 1);

        expCommentsLabel4 = new QLabel(gridLayoutWidget_18);
        expCommentsLabel4->setObjectName(QString::fromUtf8("expCommentsLabel4"));

        CommentsLayout4->addWidget(expCommentsLabel4, 1, 0, 1, 1);

        expComments4 = new QELineEdit(gridLayoutWidget_18);
        expComments4->setObjectName(QString::fromUtf8("expComments4"));

        CommentsLayout4->addWidget(expComments4, 1, 1, 1, 1);

        userComments4 = new QELineEdit(gridLayoutWidget_18);
        userComments4->setObjectName(QString::fromUtf8("userComments4"));

        CommentsLayout4->addWidget(userComments4, 0, 1, 1, 1);

        experimentalParameters4 = new QGroupBox(thetaTwoTheta);
        experimentalParameters4->setObjectName(QString::fromUtf8("experimentalParameters4"));
        experimentalParameters4->setGeometry(QRect(0, 0, 411, 181));
        experimentalParameters4->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters4->setAutoFillBackground(false);
        experimentalParameters4->setFlat(false);
        experimentalParameters4->setCheckable(false);
        gridLayoutWidget_26 = new QWidget(experimentalParameters4);
        gridLayoutWidget_26->setObjectName(QString::fromUtf8("gridLayoutWidget_26"));
        gridLayoutWidget_26->setGeometry(QRect(10, 30, 391, 141));
        experimentalParametersLayout4 = new QGridLayout(gridLayoutWidget_26);
        experimentalParametersLayout4->setObjectName(QString::fromUtf8("experimentalParametersLayout4"));
        experimentalParametersLayout4->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout4->setContentsMargins(0, 0, 0, 0);
        samplesLabel4 = new QLabel(gridLayoutWidget_26);
        samplesLabel4->setObjectName(QString::fromUtf8("samplesLabel4"));

        experimentalParametersLayout4->addWidget(samplesLabel4, 1, 0, 1, 1);

        intervalsButton4 = new QPushButton(gridLayoutWidget_26);
        intervalsButton4->setObjectName(QString::fromUtf8("intervalsButton4"));

        experimentalParametersLayout4->addWidget(intervalsButton4, 0, 2, 1, 1);

        samplesButton4 = new QPushButton(gridLayoutWidget_26);
        samplesButton4->setObjectName(QString::fromUtf8("samplesButton4"));

        experimentalParametersLayout4->addWidget(samplesButton4, 1, 2, 1, 1);

        scansLabel4 = new QLabel(gridLayoutWidget_26);
        scansLabel4->setObjectName(QString::fromUtf8("scansLabel4"));

        experimentalParametersLayout4->addWidget(scansLabel4, 2, 0, 1, 1);

        expFileNameLabel4 = new QLabel(gridLayoutWidget_26);
        expFileNameLabel4->setObjectName(QString::fromUtf8("expFileNameLabel4"));

        experimentalParametersLayout4->addWidget(expFileNameLabel4, 3, 0, 1, 1);

        settlingTimeLabel4 = new QLabel(gridLayoutWidget_26);
        settlingTimeLabel4->setObjectName(QString::fromUtf8("settlingTimeLabel4"));

        experimentalParametersLayout4->addWidget(settlingTimeLabel4, 4, 0, 1, 1);

        intervalsLabel4 = new QLabel(gridLayoutWidget_26);
        intervalsLabel4->setObjectName(QString::fromUtf8("intervalsLabel4"));

        experimentalParametersLayout4->addWidget(intervalsLabel4, 0, 0, 1, 1);

        intervals4 = new QENumericEdit(gridLayoutWidget_26);
        intervals4->setObjectName(QString::fromUtf8("intervals4"));
        intervals4->setAlignment(Qt::AlignCenter);
        intervals4->setLeadingZeros(0);
        intervals4->setPrecision(0);
        intervals4->setMinimum(0.000000000000000);

        experimentalParametersLayout4->addWidget(intervals4, 0, 1, 1, 1);

        samples4 = new QENumericEdit(gridLayoutWidget_26);
        samples4->setObjectName(QString::fromUtf8("samples4"));
        samples4->setAlignment(Qt::AlignCenter);
        samples4->setLeadingZeros(0);
        samples4->setPrecision(0);
        samples4->setMinimum(0.000000000000000);

        experimentalParametersLayout4->addWidget(samples4, 1, 1, 1, 1);

        scans4 = new QENumericEdit(gridLayoutWidget_26);
        scans4->setObjectName(QString::fromUtf8("scans4"));
        scans4->setAlignment(Qt::AlignCenter);
        scans4->setLeadingZeros(0);
        scans4->setPrecision(0);
        scans4->setMinimum(0.000000000000000);

        experimentalParametersLayout4->addWidget(scans4, 2, 1, 1, 1);

        expFileName4 = new QELineEdit(gridLayoutWidget_26);
        expFileName4->setObjectName(QString::fromUtf8("expFileName4"));

        experimentalParametersLayout4->addWidget(expFileName4, 3, 1, 1, 1);

        settlingTime4 = new QENumericEdit(gridLayoutWidget_26);
        settlingTime4->setObjectName(QString::fromUtf8("settlingTime4"));
        settlingTime4->setAlignment(Qt::AlignCenter);
        settlingTime4->setLeadingZeros(0);
        settlingTime4->setPrecision(0);
        settlingTime4->setMinimum(0.000000000000000);

        experimentalParametersLayout4->addWidget(settlingTime4, 4, 1, 1, 1);

        Wizard->setPage(9, thetaTwoTheta);
        finishPage = new QWizardPage();
        finishPage->setObjectName(QString::fromUtf8("finishPage"));
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName(QString::fromUtf8("finishLabel"));
        finishLabel->setGeometry(QRect(0, 0, 161, 16));
        gridLayoutWidget_5 = new QWidget(finishPage);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 520, 411, 31));
        filePathLayout = new QGridLayout(gridLayoutWidget_5);
        filePathLayout->setObjectName(QString::fromUtf8("filePathLayout"));
        filePathLayout->setContentsMargins(0, 0, 0, 0);
        fullFilePath = new QLabel(gridLayoutWidget_5);
        fullFilePath->setObjectName(QString::fromUtf8("fullFilePath"));
        sizePolicy.setHeightForWidth(fullFilePath->sizePolicy().hasHeightForWidth());
        fullFilePath->setSizePolicy(sizePolicy);

        filePathLayout->addWidget(fullFilePath, 0, 0, 1, 1);

        filePath = new QLabel(gridLayoutWidget_5);
        filePath->setObjectName(QString::fromUtf8("filePath"));
        filePath->setFont(font);
        filePath->setCursor(QCursor(Qt::IBeamCursor));
        filePath->setFrameShape(QFrame::StyledPanel);

        filePathLayout->addWidget(filePath, 0, 1, 1, 1);

        Wizard->setPage(10, finishPage);

        retranslateUi(Wizard);

        QMetaObject::connectSlotsByName(Wizard);
    } // setupUi

    void retranslateUi(QWizard *Wizard)
    {
        Wizard->setWindowTitle(QCoreApplication::translate("Wizard", "MS Scanning Tool", nullptr));
        experimentType->setTitle(QString());
        experimentType->setSubTitle(QString());
        experimentSelection->setTitle(QCoreApplication::translate("Wizard", "Please choose your experiment type", nullptr));
        localExperiment->setText(QCoreApplication::translate("Wizard", "Local Experiment", nullptr));
        localExperiment->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        localExperiment->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        localExperiment->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        localExperiment->setClickCheckedText(QCoreApplication::translate("Wizard", "Local", nullptr));
        usersExperiment->setText(QCoreApplication::translate("Wizard", "Users Experiment", nullptr));
        usersExperiment->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        usersExperiment->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        usersExperiment->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        usersExperiment->setClickCheckedText(QCoreApplication::translate("Wizard", "Users", nullptr));
        energyCalibraion->setText(QCoreApplication::translate("Wizard", "Energy Calibration", nullptr));
        energyCalibraion->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        energyCalibraion->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        energyCalibraion->setClickText(QCoreApplication::translate("Wizard", "3", nullptr));
        energyCalibraion->setClickCheckedText(QCoreApplication::translate("Wizard", "Energy Calibration", nullptr));
        proposalIDGroupBox->setTitle(QCoreApplication::translate("Wizard", "Please enter your proposal ID", nullptr));
#if QT_CONFIG(whatsthis)
        proposalIDValue->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        proposalIDValue->setInputMask(QString());
        proposalIDValue->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. 20172001", nullptr));
        proposalIDValue->setText(QString());
        scanningTypeGroupBox->setTitle(QCoreApplication::translate("Wizard", "Please choose the scanning type", nullptr));
        twoThetaSlitsScan->setText(QCoreApplication::translate("Wizard", "2\316\270 Scan with Slits configurations", nullptr));
        twoThetaSlitsScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaSlitsScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaSlitsScan->setClickText(QCoreApplication::translate("Wizard", "3", nullptr));
        twoThetaSlitsScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta with Slits Scan", nullptr));
        twoThetaScan->setText(QCoreApplication::translate("Wizard", "2\316\270 Scan", nullptr));
        twoThetaScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaScan->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        twoThetaScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta Step Scan", nullptr));
        twoThetaTempScan->setText(QCoreApplication::translate("Wizard", "2\316\270-Temperature Scan", nullptr));
        twoThetaTempScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaTempScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaTempScan->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        twoThetaTempScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta Temp Scan", nullptr));
        thetaTwoThetaScan->setText(QCoreApplication::translate("Wizard", "\316\270-2\316\270 Scan", nullptr));
        thetaTwoThetaScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        thetaTwoThetaScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        thetaTwoThetaScan->setClickText(QCoreApplication::translate("Wizard", "4", nullptr));
        thetaTwoThetaScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Theta Two Theta Scan", nullptr));
        configurationsFileGroubBox->setTitle(QCoreApplication::translate("Wizard", "You can create a new configuration file or load existing one", nullptr));
        configurationsFileLoad->setText(QCoreApplication::translate("Wizard", "Load configuration file", nullptr));
        configurationsFileLoad->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ConfigurationsFile", nullptr)));
        configurationsFileLoad->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        configurationsFileLoad->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        configurationsFileLoad->setClickCheckedText(QCoreApplication::translate("Wizard", "Load", nullptr));
        configurationsFileCreate->setText(QCoreApplication::translate("Wizard", "Create configuration file", nullptr));
        configurationsFileCreate->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ConfigurationsFile", nullptr)));
        configurationsFileCreate->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        configurationsFileCreate->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        configurationsFileCreate->setClickCheckedText(QCoreApplication::translate("Wizard", "Create", nullptr));
        loadConfigFileLabel->setText(QCoreApplication::translate("Wizard", "Exp. config file:", nullptr));
        expConfigFile->setText(QString());
        loadConfigFileButton->setText(QCoreApplication::translate("Wizard", "...", nullptr));
        robotGroupBox->setTitle(QCoreApplication::translate("Wizard", "Arm Robot", nullptr));
        robotNo->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        robotNo->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        robotNo->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        robotNo->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        robotLabel->setText(QCoreApplication::translate("Wizard", "Use robot", nullptr));
        robotYes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        robotYes->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        robotYes->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        robotYes->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        robotYes->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        robotInUse->setText(QCoreApplication::translate("Wizard", "Robot in use:", nullptr));
        useRobotFeedback->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        useRobotFeedback->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        experimentalParameters_5->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        samples->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Samples", nullptr)));
        samples->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        samplesLabel->setText(QCoreApplication::translate("Wizard", "Number of samples", nullptr));
        intervalsButton->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        settlingTime->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeLabel->setText(QCoreApplication::translate("Wizard", "Settling time", nullptr));
        intervals->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
        samplesButton->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel->setText(QCoreApplication::translate("Wizard", "Number of scans", nullptr));
        scans->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Scans", nullptr)));
        scans->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        intervalsLabel->setText(QCoreApplication::translate("Wizard", "Number of intervals", nullptr));
        expFileNameLabel->setText(QCoreApplication::translate("Wizard", "Exp. file name", nullptr));
        expFileName->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        validIntervals->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        validSamples->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        Comments->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        expComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        userComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        gasBlowerGroupBox->setTitle(QCoreApplication::translate("Wizard", "Gas Blower", nullptr));
        Comments2->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel2->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel2->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        experimentalParameters2->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        samplesLabel2->setText(QCoreApplication::translate("Wizard", "Number of samples", nullptr));
        intervalsButton2->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        samplesButton2->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel2->setText(QCoreApplication::translate("Wizard", "Number of scans", nullptr));
        expFileNameLabel2->setText(QCoreApplication::translate("Wizard", "Exp. file name", nullptr));
        settlingTimeLabel2->setText(QCoreApplication::translate("Wizard", "Settling time", nullptr));
        intervalsLabel2->setText(QCoreApplication::translate("Wizard", "Number of intervals", nullptr));
        slitConfigurationsGroupBox->setTitle(QCoreApplication::translate("Wizard", "Slits Configurations", nullptr));
        experimentalParameters3->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        samplesLabel3->setText(QCoreApplication::translate("Wizard", "Number of samples", nullptr));
        intervalsButton3->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        samplesButton3->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel3->setText(QCoreApplication::translate("Wizard", "Number of scans", nullptr));
        expFileNameLabel3->setText(QCoreApplication::translate("Wizard", "Exp. file name", nullptr));
        settlingTimeLabel3->setText(QCoreApplication::translate("Wizard", "Settling time", nullptr));
        intervalsLabel3->setText(QCoreApplication::translate("Wizard", "Number of intervals", nullptr));
        Comments3->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel3->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel3->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        robotGroupBox3_2->setTitle(QCoreApplication::translate("Wizard", "Arm Robot", nullptr));
        robotLabel3_2->setText(QCoreApplication::translate("Wizard", "Use robot", nullptr));
        robotCheckBox3_2->setText(QString());
        Comments4->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel4->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel4->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        experimentalParameters4->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        samplesLabel4->setText(QCoreApplication::translate("Wizard", "Number of samples", nullptr));
        intervalsButton4->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        samplesButton4->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel4->setText(QCoreApplication::translate("Wizard", "Number of scans", nullptr));
        expFileNameLabel4->setText(QCoreApplication::translate("Wizard", "Exp. file name", nullptr));
        settlingTimeLabel4->setText(QCoreApplication::translate("Wizard", "Settling time", nullptr));
        intervalsLabel4->setText(QCoreApplication::translate("Wizard", "Number of intervals", nullptr));
        finishLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Press <span style=\" text-decoration: underline;\">F</span>inish to start scan</p></body></html>", nullptr));
        fullFilePath->setText(QCoreApplication::translate("Wizard", "Full file path:", nullptr));
        filePath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Wizard: public Ui_Wizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARD_H
