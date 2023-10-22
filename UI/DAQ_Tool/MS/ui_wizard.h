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
    QGridLayout *gridLayout;
    QELineEdit *proposalIDValue;
    QWidget *layoutWidget;
    QGridLayout *validProposalIDLayout;
    QLabel *proposalIDWarning;
    QSpacerItem *horizontalSpacer;
    QPushButton *Yes;
    QPushButton *No;
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
    QWizardPage *robot;
    QGroupBox *robotGroupBox;
    QWidget *gridLayoutWidget_23;
    QGridLayout *robotLayout;
    QERadioButton *robotNo;
    QLabel *robotLabel;
    QERadioButton *robotYes;
    QLabel *robotInUse;
    QELabel *useRobotFeedback;
    QWizardPage *experimentalGUI;
    QGroupBox *experimentalParameters;
    QWidget *gridLayoutWidget_20;
    QGridLayout *experimentalParametersLayout;
    QELineEdit *scans;
    QELineEdit *settlingTime;
    QELineEdit *intervals;
    QELineEdit *expFileName;
    QLabel *expFileNameLabel;
    QPushButton *intervalsButton;
    QLabel *settlingTimeUnit;
    QLabel *scansLabel;
    QLabel *settlingTimeLabel;
    QLabel *intervalsLabel;
    QLabel *validIntervals;
    QLabel *validSamples;
    QPushButton *samplesButton;
    QELineEdit *samples;
    QLabel *samplesLabel;
    QGroupBox *Comments;
    QWidget *gridLayoutWidget_21;
    QGridLayout *CommentsLayout;
    QLabel *userCommentsLabel;
    QLabel *expCommentsLabel;
    QELineEdit *userComments;
    QELineEdit *expComments;
    QLabel *sampleName;
    QELineEdit *sampleNameVal;
    QGroupBox *testingModeGroupBox;
    QWidget *gridLayoutWidget_22;
    QGridLayout *testingModeLayout;
    QERadioButton *testingModeNo;
    QLabel *testingModeLabel;
    QERadioButton *testingModeYes;
    QLabel *tesingMode;
    QELabel *testingModeFeedback;
    QWizardPage *twoThetaTemp;
    QGroupBox *experimentalParameters2;
    QWidget *gridLayoutWidget_24;
    QGridLayout *experimentalParametersLayout2;
    QLabel *intervalsLabel2;
    QELineEdit *deadband;
    QLabel *settlingTimeUnit2;
    QLabel *settlingTimeLabel2;
    QELineEdit *expFileName2;
    QLabel *expFileNameLabel2;
    QLabel *validIntervals2;
    QELineEdit *settlingTime2;
    QLabel *deadbandLabel;
    QELineEdit *intervals2;
    QPushButton *intervalsButton2;
    QGroupBox *Comments2;
    QWidget *gridLayoutWidget_25;
    QGridLayout *CommentsLayout2;
    QLabel *userCommentsLabel2;
    QLabel *expCommentsLabel2;
    QELineEdit *userComments2;
    QELineEdit *expComments2;
    QLabel *sampleName2;
    QELineEdit *sampleNameVal2;
    QGroupBox *testingModeGroupBox2;
    QWidget *gridLayoutWidget_27;
    QGridLayout *testingModeLayout2;
    QERadioButton *testingModeNo2;
    QLabel *testingModeLabel2;
    QERadioButton *testingModeYes2;
    QLabel *tesingMode2;
    QELabel *testingModeFeedback2;
    QWizardPage *twoThetaSlits;
    QGroupBox *slitConfigurationsGroupBox;
    QGroupBox *testingModeGroupBox3;
    QWidget *gridLayoutWidget_34;
    QGridLayout *testingModeLayout3;
    QERadioButton *testingModeNo3;
    QLabel *testingModeLabel3;
    QERadioButton *testingModeYes3;
    QLabel *tesingMode3;
    QELabel *testingModeFeedback3;
    QGroupBox *experimentalParameters3;
    QWidget *gridLayoutWidget_35;
    QGridLayout *experimentalParametersLayout3;
    QELineEdit *samples3;
    QLabel *samplesLabel3;
    QPushButton *intervalsButton3;
    QELineEdit *settlingTime3;
    QLabel *settlingTimeLabel3;
    QELineEdit *intervals3;
    QLabel *settlingTimeUnit3;
    QPushButton *samplesButton3;
    QLabel *scansLabel3;
    QELineEdit *scans3;
    QLabel *intervalsLabel3;
    QLabel *expFileNameLabel3;
    QELineEdit *expFileName3;
    QLabel *validIntervals3;
    QLabel *validSamples3;
    QGroupBox *Comments3;
    QWidget *gridLayoutWidget_36;
    QGridLayout *CommentsLayout3;
    QELineEdit *expComments3;
    QELineEdit *userComments3;
    QLabel *expCommentsLabel3;
    QLabel *userCommentsLabel3;
    QLabel *sampleName3;
    QELineEdit *sampleNameVal3;
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
        localExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        experimentSelectionLayout->addWidget(localExperiment, 1, 0, 1, 1);

        usersExperiment = new QERadioButton(gridLayoutWidget);
        usersExperiment->setObjectName(QString::fromUtf8("usersExperiment"));
        usersExperiment->setCursor(QCursor(Qt::ArrowCursor));
        usersExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        usersExperiment->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        experimentSelectionLayout->addWidget(usersExperiment, 0, 0, 1, 1);

        energyCalibraion = new QERadioButton(gridLayoutWidget);
        energyCalibraion->setObjectName(QString::fromUtf8("energyCalibraion"));
        energyCalibraion->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        experimentSelectionLayout->addWidget(energyCalibraion, 2, 0, 1, 1);

        Wizard->setPage(1, experimentType);
        proposalID = new QWizardPage();
        proposalID->setObjectName(QString::fromUtf8("proposalID"));
        proposalIDGroupBox = new QGroupBox(proposalID);
        proposalIDGroupBox->setObjectName(QString::fromUtf8("proposalIDGroupBox"));
        proposalIDGroupBox->setGeometry(QRect(0, 0, 411, 91));
        gridLayout = new QGridLayout(proposalIDGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        proposalIDValue = new QELineEdit(proposalIDGroupBox);
        proposalIDValue->setObjectName(QString::fromUtf8("proposalIDValue"));
        proposalIDValue->setDragEnabled(true);
        proposalIDValue->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        proposalIDValue->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout->addWidget(proposalIDValue, 0, 0, 1, 1);

        layoutWidget = new QWidget(proposalID);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 240, 411, 301));
        validProposalIDLayout = new QGridLayout(layoutWidget);
        validProposalIDLayout->setObjectName(QString::fromUtf8("validProposalIDLayout"));
        validProposalIDLayout->setContentsMargins(0, 0, 0, 0);
        proposalIDWarning = new QLabel(layoutWidget);
        proposalIDWarning->setObjectName(QString::fromUtf8("proposalIDWarning"));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif CJK TC SemiBold"));
        font.setPointSize(11);
        font.setItalic(false);
        proposalIDWarning->setFont(font);
        proposalIDWarning->setCursor(QCursor(Qt::IBeamCursor));
        proposalIDWarning->setFrameShape(QFrame::NoFrame);
        proposalIDWarning->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        proposalIDWarning->setWordWrap(true);
        proposalIDWarning->setMargin(7);

        validProposalIDLayout->addWidget(proposalIDWarning, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        validProposalIDLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        Yes = new QPushButton(layoutWidget);
        Yes->setObjectName(QString::fromUtf8("Yes"));
        Yes->setCursor(QCursor(Qt::PointingHandCursor));

        validProposalIDLayout->addWidget(Yes, 1, 1, 1, 1);

        No = new QPushButton(layoutWidget);
        No->setObjectName(QString::fromUtf8("No"));
        No->setCursor(QCursor(Qt::PointingHandCursor));

        validProposalIDLayout->addWidget(No, 1, 2, 1, 1);

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
        twoThetaSlitsScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        scanningTypeLayout->addWidget(twoThetaSlitsScan, 2, 0, 1, 1);

        twoThetaScan = new QERadioButton(gridLayoutWidget_3);
        twoThetaScan->setObjectName(QString::fromUtf8("twoThetaScan"));
        twoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        twoThetaScan->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        scanningTypeLayout->addWidget(twoThetaScan, 0, 0, 1, 1);

        twoThetaTempScan = new QERadioButton(gridLayoutWidget_3);
        twoThetaTempScan->setObjectName(QString::fromUtf8("twoThetaTempScan"));
        twoThetaTempScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        scanningTypeLayout->addWidget(twoThetaTempScan, 1, 0, 1, 1);

        thetaTwoThetaScan = new QERadioButton(gridLayoutWidget_3);
        thetaTwoThetaScan->setObjectName(QString::fromUtf8("thetaTwoThetaScan"));
        thetaTwoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

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
        configurationsFileLoad->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        configurationsFileLayout->addWidget(configurationsFileLoad, 1, 0, 1, 1);

        configurationsFileCreate = new QERadioButton(gridLayoutWidget_4);
        configurationsFileCreate->setObjectName(QString::fromUtf8("configurationsFileCreate"));
        configurationsFileCreate->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        configurationsFileCreate->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        configurationsFileLayout->addWidget(configurationsFileCreate, 0, 0, 1, 1);

        Wizard->setPage(4, configurationsFile);
        loadConfigFile = new QWizardPage();
        loadConfigFile->setObjectName(QString::fromUtf8("loadConfigFile"));
        gridLayoutWidget_6 = new QWidget(loadConfigFile);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 40, 411, 51));
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
        QFont font1;
        font1.setPointSize(8);
        expConfigFile->setFont(font1);
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
        robot = new QWizardPage();
        robot->setObjectName(QString::fromUtf8("robot"));
        robotGroupBox = new QGroupBox(robot);
        robotGroupBox->setObjectName(QString::fromUtf8("robotGroupBox"));
        robotGroupBox->setGeometry(QRect(0, 0, 411, 91));
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
        gridLayoutWidget_23 = new QWidget(robotGroupBox);
        gridLayoutWidget_23->setObjectName(QString::fromUtf8("gridLayoutWidget_23"));
        gridLayoutWidget_23->setGeometry(QRect(10, 30, 391, 50));
        robotLayout = new QGridLayout(gridLayoutWidget_23);
        robotLayout->setObjectName(QString::fromUtf8("robotLayout"));
        robotLayout->setContentsMargins(0, 0, 0, 0);
        robotNo = new QERadioButton(gridLayoutWidget_23);
        robotNo->setObjectName(QString::fromUtf8("robotNo"));
        robotNo->setFocusPolicy(Qt::StrongFocus);
        robotNo->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        robotLayout->addWidget(robotNo, 1, 1, 1, 1);

        robotLabel = new QLabel(gridLayoutWidget_23);
        robotLabel->setObjectName(QString::fromUtf8("robotLabel"));
        robotLabel->setCursor(QCursor(Qt::IBeamCursor));

        robotLayout->addWidget(robotLabel, 0, 0, 2, 1);

        robotYes = new QERadioButton(gridLayoutWidget_23);
        robotYes->setObjectName(QString::fromUtf8("robotYes"));
        robotYes->setFocusPolicy(Qt::StrongFocus);
        robotYes->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        robotLayout->addWidget(robotYes, 0, 1, 1, 1);

        robotInUse = new QLabel(gridLayoutWidget_23);
        robotInUse->setObjectName(QString::fromUtf8("robotInUse"));

        robotLayout->addWidget(robotInUse, 0, 2, 2, 1);

        useRobotFeedback = new QELabel(gridLayoutWidget_23);
        useRobotFeedback->setObjectName(QString::fromUtf8("useRobotFeedback"));
        useRobotFeedback->setFrameShape(QFrame::StyledPanel);
        useRobotFeedback->setAlignment(Qt::AlignCenter);
        useRobotFeedback->setWordWrap(true);
        useRobotFeedback->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        useRobotFeedback->setAddUnits(false);

        robotLayout->addWidget(useRobotFeedback, 0, 3, 2, 1);

        Wizard->setPage(6, robot);
        experimentalGUI = new QWizardPage();
        experimentalGUI->setObjectName(QString::fromUtf8("experimentalGUI"));
        experimentalParameters = new QGroupBox(experimentalGUI);
        experimentalParameters->setObjectName(QString::fromUtf8("experimentalParameters"));
        experimentalParameters->setGeometry(QRect(0, 0, 411, 191));
        experimentalParameters->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters->setAutoFillBackground(false);
        experimentalParameters->setFlat(false);
        experimentalParameters->setCheckable(false);
        gridLayoutWidget_20 = new QWidget(experimentalParameters);
        gridLayoutWidget_20->setObjectName(QString::fromUtf8("gridLayoutWidget_20"));
        gridLayoutWidget_20->setGeometry(QRect(10, 30, 391, 151));
        experimentalParametersLayout = new QGridLayout(gridLayoutWidget_20);
        experimentalParametersLayout->setObjectName(QString::fromUtf8("experimentalParametersLayout"));
        experimentalParametersLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout->setContentsMargins(0, 0, 0, 0);
        scans = new QELineEdit(gridLayoutWidget_20);
        scans->setObjectName(QString::fromUtf8("scans"));
        scans->setAlignment(Qt::AlignCenter);
        scans->setDragEnabled(true);
        scans->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        scans->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout->addWidget(scans, 2, 1, 1, 2);

        settlingTime = new QELineEdit(gridLayoutWidget_20);
        settlingTime->setObjectName(QString::fromUtf8("settlingTime"));
        settlingTime->setAlignment(Qt::AlignCenter);
        settlingTime->setDragEnabled(true);
        settlingTime->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        experimentalParametersLayout->addWidget(settlingTime, 4, 1, 1, 1);

        intervals = new QELineEdit(gridLayoutWidget_20);
        intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->setAlignment(Qt::AlignCenter);
        intervals->setDragEnabled(true);
        intervals->setWriteOnEnter(true);
        intervals->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout->addWidget(intervals, 0, 1, 1, 2);

        expFileName = new QELineEdit(gridLayoutWidget_20);
        expFileName->setObjectName(QString::fromUtf8("expFileName"));
        expFileName->setDragEnabled(true);
        expFileName->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        experimentalParametersLayout->addWidget(expFileName, 3, 1, 1, 2);

        expFileNameLabel = new QLabel(gridLayoutWidget_20);
        expFileNameLabel->setObjectName(QString::fromUtf8("expFileNameLabel"));
        expFileNameLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout->addWidget(expFileNameLabel, 3, 0, 1, 1);

        intervalsButton = new QPushButton(gridLayoutWidget_20);
        intervalsButton->setObjectName(QString::fromUtf8("intervalsButton"));
        intervalsButton->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout->addWidget(intervalsButton, 0, 3, 1, 1);

        settlingTimeUnit = new QLabel(gridLayoutWidget_20);
        settlingTimeUnit->setObjectName(QString::fromUtf8("settlingTimeUnit"));

        experimentalParametersLayout->addWidget(settlingTimeUnit, 4, 2, 1, 1);

        scansLabel = new QLabel(gridLayoutWidget_20);
        scansLabel->setObjectName(QString::fromUtf8("scansLabel"));
        scansLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout->addWidget(scansLabel, 2, 0, 1, 1);

        settlingTimeLabel = new QLabel(gridLayoutWidget_20);
        settlingTimeLabel->setObjectName(QString::fromUtf8("settlingTimeLabel"));
        settlingTimeLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout->addWidget(settlingTimeLabel, 4, 0, 1, 1);

        intervalsLabel = new QLabel(gridLayoutWidget_20);
        intervalsLabel->setObjectName(QString::fromUtf8("intervalsLabel"));
        intervalsLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout->addWidget(intervalsLabel, 0, 0, 1, 1);

        validIntervals = new QLabel(gridLayoutWidget_20);
        validIntervals->setObjectName(QString::fromUtf8("validIntervals"));
        QFont font2;
        font2.setPointSize(14);
        validIntervals->setFont(font2);

        experimentalParametersLayout->addWidget(validIntervals, 0, 4, 1, 1);

        validSamples = new QLabel(gridLayoutWidget_20);
        validSamples->setObjectName(QString::fromUtf8("validSamples"));
        validSamples->setFont(font2);

        experimentalParametersLayout->addWidget(validSamples, 1, 4, 1, 1);

        samplesButton = new QPushButton(gridLayoutWidget_20);
        samplesButton->setObjectName(QString::fromUtf8("samplesButton"));
        samplesButton->setCursor(QCursor(Qt::PointingHandCursor));
        samplesButton->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout->addWidget(samplesButton, 1, 3, 1, 1);

        samples = new QELineEdit(gridLayoutWidget_20);
        samples->setObjectName(QString::fromUtf8("samples"));
        samples->setAlignment(Qt::AlignCenter);
        samples->setDragEnabled(true);
        samples->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        samples->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout->addWidget(samples, 1, 1, 1, 2);

        samplesLabel = new QLabel(gridLayoutWidget_20);
        samplesLabel->setObjectName(QString::fromUtf8("samplesLabel"));
        samplesLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout->addWidget(samplesLabel, 1, 0, 1, 1);

        Comments = new QGroupBox(experimentalGUI);
        Comments->setObjectName(QString::fromUtf8("Comments"));
        Comments->setGeometry(QRect(0, 410, 411, 131));
        sizePolicy2.setHeightForWidth(Comments->sizePolicy().hasHeightForWidth());
        Comments->setSizePolicy(sizePolicy2);
        Comments->setMinimumSize(QSize(0, 0));
        Comments->setCursor(QCursor(Qt::ArrowCursor));
        Comments->setAutoFillBackground(false);
        Comments->setFlat(false);
        Comments->setCheckable(false);
        gridLayoutWidget_21 = new QWidget(Comments);
        gridLayoutWidget_21->setObjectName(QString::fromUtf8("gridLayoutWidget_21"));
        gridLayoutWidget_21->setGeometry(QRect(10, 30, 391, 91));
        CommentsLayout = new QGridLayout(gridLayoutWidget_21);
        CommentsLayout->setObjectName(QString::fromUtf8("CommentsLayout"));
        CommentsLayout->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel = new QLabel(gridLayoutWidget_21);
        userCommentsLabel->setObjectName(QString::fromUtf8("userCommentsLabel"));
        userCommentsLabel->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout->addWidget(userCommentsLabel, 1, 0, 1, 1);

        expCommentsLabel = new QLabel(gridLayoutWidget_21);
        expCommentsLabel->setObjectName(QString::fromUtf8("expCommentsLabel"));
        expCommentsLabel->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout->addWidget(expCommentsLabel, 2, 0, 1, 1);

        userComments = new QELineEdit(gridLayoutWidget_21);
        userComments->setObjectName(QString::fromUtf8("userComments"));
        userComments->setDragEnabled(true);
        userComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout->addWidget(userComments, 1, 1, 1, 1);

        expComments = new QELineEdit(gridLayoutWidget_21);
        expComments->setObjectName(QString::fromUtf8("expComments"));
        expComments->setDragEnabled(true);
        expComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout->addWidget(expComments, 2, 1, 1, 1);

        sampleName = new QLabel(gridLayoutWidget_21);
        sampleName->setObjectName(QString::fromUtf8("sampleName"));

        CommentsLayout->addWidget(sampleName, 0, 0, 1, 1);

        sampleNameVal = new QELineEdit(gridLayoutWidget_21);
        sampleNameVal->setObjectName(QString::fromUtf8("sampleNameVal"));
        sampleNameVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sampleNameVal->setDragEnabled(true);
        sampleNameVal->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout->addWidget(sampleNameVal, 0, 1, 1, 1);

        testingModeGroupBox = new QGroupBox(experimentalGUI);
        testingModeGroupBox->setObjectName(QString::fromUtf8("testingModeGroupBox"));
        testingModeGroupBox->setGeometry(QRect(0, 200, 411, 91));
        sizePolicy2.setHeightForWidth(testingModeGroupBox->sizePolicy().hasHeightForWidth());
        testingModeGroupBox->setSizePolicy(sizePolicy2);
        testingModeGroupBox->setMinimumSize(QSize(0, 0));
        testingModeGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox->setAutoFillBackground(false);
        testingModeGroupBox->setFlat(false);
        testingModeGroupBox->setCheckable(false);
        gridLayoutWidget_22 = new QWidget(testingModeGroupBox);
        gridLayoutWidget_22->setObjectName(QString::fromUtf8("gridLayoutWidget_22"));
        gridLayoutWidget_22->setGeometry(QRect(10, 30, 391, 50));
        testingModeLayout = new QGridLayout(gridLayoutWidget_22);
        testingModeLayout->setObjectName(QString::fromUtf8("testingModeLayout"));
        testingModeLayout->setContentsMargins(0, 0, 0, 0);
        testingModeNo = new QERadioButton(gridLayoutWidget_22);
        testingModeNo->setObjectName(QString::fromUtf8("testingModeNo"));
        testingModeNo->setFocusPolicy(Qt::StrongFocus);
        testingModeNo->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout->addWidget(testingModeNo, 1, 1, 1, 1);

        testingModeLabel = new QLabel(gridLayoutWidget_22);
        testingModeLabel->setObjectName(QString::fromUtf8("testingModeLabel"));
        testingModeLabel->setCursor(QCursor(Qt::IBeamCursor));

        testingModeLayout->addWidget(testingModeLabel, 0, 0, 2, 1);

        testingModeYes = new QERadioButton(gridLayoutWidget_22);
        testingModeYes->setObjectName(QString::fromUtf8("testingModeYes"));
        testingModeYes->setFocusPolicy(Qt::StrongFocus);
        testingModeYes->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout->addWidget(testingModeYes, 0, 1, 1, 1);

        tesingMode = new QLabel(gridLayoutWidget_22);
        tesingMode->setObjectName(QString::fromUtf8("tesingMode"));

        testingModeLayout->addWidget(tesingMode, 0, 2, 2, 1);

        testingModeFeedback = new QELabel(gridLayoutWidget_22);
        testingModeFeedback->setObjectName(QString::fromUtf8("testingModeFeedback"));
        testingModeFeedback->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback->setAlignment(Qt::AlignCenter);
        testingModeFeedback->setWordWrap(true);
        testingModeFeedback->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback->setAddUnits(false);

        testingModeLayout->addWidget(testingModeFeedback, 0, 3, 2, 1);

        Wizard->setPage(7, experimentalGUI);
        twoThetaTemp = new QWizardPage();
        twoThetaTemp->setObjectName(QString::fromUtf8("twoThetaTemp"));
        experimentalParameters2 = new QGroupBox(twoThetaTemp);
        experimentalParameters2->setObjectName(QString::fromUtf8("experimentalParameters2"));
        experimentalParameters2->setGeometry(QRect(0, 0, 411, 191));
        experimentalParameters2->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters2->setAutoFillBackground(false);
        experimentalParameters2->setFlat(false);
        experimentalParameters2->setCheckable(false);
        gridLayoutWidget_24 = new QWidget(experimentalParameters2);
        gridLayoutWidget_24->setObjectName(QString::fromUtf8("gridLayoutWidget_24"));
        gridLayoutWidget_24->setGeometry(QRect(10, 30, 391, 151));
        experimentalParametersLayout2 = new QGridLayout(gridLayoutWidget_24);
        experimentalParametersLayout2->setObjectName(QString::fromUtf8("experimentalParametersLayout2"));
        experimentalParametersLayout2->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout2->setContentsMargins(0, 0, 0, 0);
        intervalsLabel2 = new QLabel(gridLayoutWidget_24);
        intervalsLabel2->setObjectName(QString::fromUtf8("intervalsLabel2"));
        intervalsLabel2->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout2->addWidget(intervalsLabel2, 0, 0, 1, 1);

        deadband = new QELineEdit(gridLayoutWidget_24);
        deadband->setObjectName(QString::fromUtf8("deadband"));
        deadband->setAlignment(Qt::AlignCenter);
        deadband->setDragEnabled(true);
        deadband->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        deadband->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        experimentalParametersLayout2->addWidget(deadband, 1, 1, 1, 2);

        settlingTimeUnit2 = new QLabel(gridLayoutWidget_24);
        settlingTimeUnit2->setObjectName(QString::fromUtf8("settlingTimeUnit2"));

        experimentalParametersLayout2->addWidget(settlingTimeUnit2, 3, 2, 1, 1);

        settlingTimeLabel2 = new QLabel(gridLayoutWidget_24);
        settlingTimeLabel2->setObjectName(QString::fromUtf8("settlingTimeLabel2"));
        settlingTimeLabel2->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout2->addWidget(settlingTimeLabel2, 3, 0, 1, 1);

        expFileName2 = new QELineEdit(gridLayoutWidget_24);
        expFileName2->setObjectName(QString::fromUtf8("expFileName2"));
        expFileName2->setDragEnabled(true);
        expFileName2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        experimentalParametersLayout2->addWidget(expFileName2, 2, 1, 1, 2);

        expFileNameLabel2 = new QLabel(gridLayoutWidget_24);
        expFileNameLabel2->setObjectName(QString::fromUtf8("expFileNameLabel2"));
        expFileNameLabel2->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout2->addWidget(expFileNameLabel2, 2, 0, 1, 1);

        validIntervals2 = new QLabel(gridLayoutWidget_24);
        validIntervals2->setObjectName(QString::fromUtf8("validIntervals2"));
        validIntervals2->setFont(font2);

        experimentalParametersLayout2->addWidget(validIntervals2, 0, 4, 1, 1);

        settlingTime2 = new QELineEdit(gridLayoutWidget_24);
        settlingTime2->setObjectName(QString::fromUtf8("settlingTime2"));
        settlingTime2->setAlignment(Qt::AlignCenter);
        settlingTime2->setDragEnabled(true);
        settlingTime2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime2->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        experimentalParametersLayout2->addWidget(settlingTime2, 3, 1, 1, 1);

        deadbandLabel = new QLabel(gridLayoutWidget_24);
        deadbandLabel->setObjectName(QString::fromUtf8("deadbandLabel"));
        deadbandLabel->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout2->addWidget(deadbandLabel, 1, 0, 1, 1);

        intervals2 = new QELineEdit(gridLayoutWidget_24);
        intervals2->setObjectName(QString::fromUtf8("intervals2"));
        intervals2->setAlignment(Qt::AlignCenter);
        intervals2->setDragEnabled(true);
        intervals2->setWriteOnEnter(true);
        intervals2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals2->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout2->addWidget(intervals2, 0, 1, 1, 2);

        intervalsButton2 = new QPushButton(gridLayoutWidget_24);
        intervalsButton2->setObjectName(QString::fromUtf8("intervalsButton2"));
        intervalsButton2->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton2->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout2->addWidget(intervalsButton2, 0, 3, 1, 1);

        Comments2 = new QGroupBox(twoThetaTemp);
        Comments2->setObjectName(QString::fromUtf8("Comments2"));
        Comments2->setGeometry(QRect(0, 410, 411, 131));
        sizePolicy2.setHeightForWidth(Comments2->sizePolicy().hasHeightForWidth());
        Comments2->setSizePolicy(sizePolicy2);
        Comments2->setMinimumSize(QSize(0, 0));
        Comments2->setCursor(QCursor(Qt::ArrowCursor));
        Comments2->setAutoFillBackground(false);
        Comments2->setFlat(false);
        Comments2->setCheckable(false);
        gridLayoutWidget_25 = new QWidget(Comments2);
        gridLayoutWidget_25->setObjectName(QString::fromUtf8("gridLayoutWidget_25"));
        gridLayoutWidget_25->setGeometry(QRect(10, 30, 391, 91));
        CommentsLayout2 = new QGridLayout(gridLayoutWidget_25);
        CommentsLayout2->setObjectName(QString::fromUtf8("CommentsLayout2"));
        CommentsLayout2->setContentsMargins(0, 0, 0, 0);
        userCommentsLabel2 = new QLabel(gridLayoutWidget_25);
        userCommentsLabel2->setObjectName(QString::fromUtf8("userCommentsLabel2"));
        userCommentsLabel2->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout2->addWidget(userCommentsLabel2, 1, 0, 1, 1);

        expCommentsLabel2 = new QLabel(gridLayoutWidget_25);
        expCommentsLabel2->setObjectName(QString::fromUtf8("expCommentsLabel2"));
        expCommentsLabel2->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout2->addWidget(expCommentsLabel2, 2, 0, 1, 1);

        userComments2 = new QELineEdit(gridLayoutWidget_25);
        userComments2->setObjectName(QString::fromUtf8("userComments2"));
        userComments2->setDragEnabled(true);
        userComments2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout2->addWidget(userComments2, 1, 1, 1, 1);

        expComments2 = new QELineEdit(gridLayoutWidget_25);
        expComments2->setObjectName(QString::fromUtf8("expComments2"));
        expComments2->setDragEnabled(true);
        expComments2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout2->addWidget(expComments2, 2, 1, 1, 1);

        sampleName2 = new QLabel(gridLayoutWidget_25);
        sampleName2->setObjectName(QString::fromUtf8("sampleName2"));

        CommentsLayout2->addWidget(sampleName2, 0, 0, 1, 1);

        sampleNameVal2 = new QELineEdit(gridLayoutWidget_25);
        sampleNameVal2->setObjectName(QString::fromUtf8("sampleNameVal2"));
        sampleNameVal2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sampleNameVal2->setDragEnabled(true);
        sampleNameVal2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout2->addWidget(sampleNameVal2, 0, 1, 1, 1);

        testingModeGroupBox2 = new QGroupBox(twoThetaTemp);
        testingModeGroupBox2->setObjectName(QString::fromUtf8("testingModeGroupBox2"));
        testingModeGroupBox2->setGeometry(QRect(0, 200, 411, 91));
        sizePolicy2.setHeightForWidth(testingModeGroupBox2->sizePolicy().hasHeightForWidth());
        testingModeGroupBox2->setSizePolicy(sizePolicy2);
        testingModeGroupBox2->setMinimumSize(QSize(0, 0));
        testingModeGroupBox2->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox2->setAutoFillBackground(false);
        testingModeGroupBox2->setFlat(false);
        testingModeGroupBox2->setCheckable(false);
        gridLayoutWidget_27 = new QWidget(testingModeGroupBox2);
        gridLayoutWidget_27->setObjectName(QString::fromUtf8("gridLayoutWidget_27"));
        gridLayoutWidget_27->setGeometry(QRect(10, 30, 391, 50));
        testingModeLayout2 = new QGridLayout(gridLayoutWidget_27);
        testingModeLayout2->setObjectName(QString::fromUtf8("testingModeLayout2"));
        testingModeLayout2->setContentsMargins(0, 0, 0, 0);
        testingModeNo2 = new QERadioButton(gridLayoutWidget_27);
        testingModeNo2->setObjectName(QString::fromUtf8("testingModeNo2"));
        testingModeNo2->setFocusPolicy(Qt::StrongFocus);
        testingModeNo2->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout2->addWidget(testingModeNo2, 1, 1, 1, 1);

        testingModeLabel2 = new QLabel(gridLayoutWidget_27);
        testingModeLabel2->setObjectName(QString::fromUtf8("testingModeLabel2"));
        testingModeLabel2->setCursor(QCursor(Qt::IBeamCursor));

        testingModeLayout2->addWidget(testingModeLabel2, 0, 0, 2, 1);

        testingModeYes2 = new QERadioButton(gridLayoutWidget_27);
        testingModeYes2->setObjectName(QString::fromUtf8("testingModeYes2"));
        testingModeYes2->setFocusPolicy(Qt::StrongFocus);
        testingModeYes2->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout2->addWidget(testingModeYes2, 0, 1, 1, 1);

        tesingMode2 = new QLabel(gridLayoutWidget_27);
        tesingMode2->setObjectName(QString::fromUtf8("tesingMode2"));

        testingModeLayout2->addWidget(tesingMode2, 0, 2, 2, 1);

        testingModeFeedback2 = new QELabel(gridLayoutWidget_27);
        testingModeFeedback2->setObjectName(QString::fromUtf8("testingModeFeedback2"));
        testingModeFeedback2->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback2->setAlignment(Qt::AlignCenter);
        testingModeFeedback2->setWordWrap(true);
        testingModeFeedback2->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback2->setAddUnits(false);

        testingModeLayout2->addWidget(testingModeFeedback2, 0, 3, 2, 1);

        Wizard->setPage(8, twoThetaTemp);
        twoThetaSlits = new QWizardPage();
        twoThetaSlits->setObjectName(QString::fromUtf8("twoThetaSlits"));
        slitConfigurationsGroupBox = new QGroupBox(twoThetaSlits);
        slitConfigurationsGroupBox->setObjectName(QString::fromUtf8("slitConfigurationsGroupBox"));
        slitConfigurationsGroupBox->setGeometry(QRect(0, 300, 411, 81));
        sizePolicy2.setHeightForWidth(slitConfigurationsGroupBox->sizePolicy().hasHeightForWidth());
        slitConfigurationsGroupBox->setSizePolicy(sizePolicy2);
        slitConfigurationsGroupBox->setMinimumSize(QSize(0, 0));
        slitConfigurationsGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        slitConfigurationsGroupBox->setAutoFillBackground(false);
        slitConfigurationsGroupBox->setFlat(false);
        slitConfigurationsGroupBox->setCheckable(false);
        testingModeGroupBox3 = new QGroupBox(twoThetaSlits);
        testingModeGroupBox3->setObjectName(QString::fromUtf8("testingModeGroupBox3"));
        testingModeGroupBox3->setGeometry(QRect(0, 200, 411, 91));
        sizePolicy2.setHeightForWidth(testingModeGroupBox3->sizePolicy().hasHeightForWidth());
        testingModeGroupBox3->setSizePolicy(sizePolicy2);
        testingModeGroupBox3->setMinimumSize(QSize(0, 0));
        testingModeGroupBox3->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox3->setAutoFillBackground(false);
        testingModeGroupBox3->setFlat(false);
        testingModeGroupBox3->setCheckable(false);
        gridLayoutWidget_34 = new QWidget(testingModeGroupBox3);
        gridLayoutWidget_34->setObjectName(QString::fromUtf8("gridLayoutWidget_34"));
        gridLayoutWidget_34->setGeometry(QRect(10, 30, 391, 50));
        testingModeLayout3 = new QGridLayout(gridLayoutWidget_34);
        testingModeLayout3->setObjectName(QString::fromUtf8("testingModeLayout3"));
        testingModeLayout3->setContentsMargins(0, 0, 0, 0);
        testingModeNo3 = new QERadioButton(gridLayoutWidget_34);
        testingModeNo3->setObjectName(QString::fromUtf8("testingModeNo3"));
        testingModeNo3->setFocusPolicy(Qt::StrongFocus);
        testingModeNo3->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout3->addWidget(testingModeNo3, 1, 1, 1, 1);

        testingModeLabel3 = new QLabel(gridLayoutWidget_34);
        testingModeLabel3->setObjectName(QString::fromUtf8("testingModeLabel3"));
        testingModeLabel3->setCursor(QCursor(Qt::IBeamCursor));

        testingModeLayout3->addWidget(testingModeLabel3, 0, 0, 2, 1);

        testingModeYes3 = new QERadioButton(gridLayoutWidget_34);
        testingModeYes3->setObjectName(QString::fromUtf8("testingModeYes3"));
        testingModeYes3->setFocusPolicy(Qt::StrongFocus);
        testingModeYes3->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        testingModeLayout3->addWidget(testingModeYes3, 0, 1, 1, 1);

        tesingMode3 = new QLabel(gridLayoutWidget_34);
        tesingMode3->setObjectName(QString::fromUtf8("tesingMode3"));

        testingModeLayout3->addWidget(tesingMode3, 0, 2, 2, 1);

        testingModeFeedback3 = new QELabel(gridLayoutWidget_34);
        testingModeFeedback3->setObjectName(QString::fromUtf8("testingModeFeedback3"));
        testingModeFeedback3->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback3->setAlignment(Qt::AlignCenter);
        testingModeFeedback3->setWordWrap(true);
        testingModeFeedback3->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback3->setAddUnits(false);

        testingModeLayout3->addWidget(testingModeFeedback3, 0, 3, 2, 1);

        experimentalParameters3 = new QGroupBox(twoThetaSlits);
        experimentalParameters3->setObjectName(QString::fromUtf8("experimentalParameters3"));
        experimentalParameters3->setGeometry(QRect(0, 0, 411, 191));
        experimentalParameters3->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters3->setAutoFillBackground(false);
        experimentalParameters3->setFlat(false);
        experimentalParameters3->setCheckable(false);
        gridLayoutWidget_35 = new QWidget(experimentalParameters3);
        gridLayoutWidget_35->setObjectName(QString::fromUtf8("gridLayoutWidget_35"));
        gridLayoutWidget_35->setGeometry(QRect(10, 30, 391, 151));
        experimentalParametersLayout3 = new QGridLayout(gridLayoutWidget_35);
        experimentalParametersLayout3->setObjectName(QString::fromUtf8("experimentalParametersLayout3"));
        experimentalParametersLayout3->setSizeConstraint(QLayout::SetDefaultConstraint);
        experimentalParametersLayout3->setContentsMargins(0, 0, 0, 0);
        samples3 = new QELineEdit(gridLayoutWidget_35);
        samples3->setObjectName(QString::fromUtf8("samples3"));
        samples3->setAlignment(Qt::AlignCenter);
        samples3->setDragEnabled(true);
        samples3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        samples3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout3->addWidget(samples3, 1, 1, 1, 2);

        samplesLabel3 = new QLabel(gridLayoutWidget_35);
        samplesLabel3->setObjectName(QString::fromUtf8("samplesLabel3"));
        samplesLabel3->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout3->addWidget(samplesLabel3, 1, 0, 1, 1);

        intervalsButton3 = new QPushButton(gridLayoutWidget_35);
        intervalsButton3->setObjectName(QString::fromUtf8("intervalsButton3"));
        intervalsButton3->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton3->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout3->addWidget(intervalsButton3, 0, 3, 1, 1);

        settlingTime3 = new QELineEdit(gridLayoutWidget_35);
        settlingTime3->setObjectName(QString::fromUtf8("settlingTime3"));
        settlingTime3->setAlignment(Qt::AlignCenter);
        settlingTime3->setDragEnabled(true);
        settlingTime3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime3->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        experimentalParametersLayout3->addWidget(settlingTime3, 4, 1, 1, 1);

        settlingTimeLabel3 = new QLabel(gridLayoutWidget_35);
        settlingTimeLabel3->setObjectName(QString::fromUtf8("settlingTimeLabel3"));
        settlingTimeLabel3->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout3->addWidget(settlingTimeLabel3, 4, 0, 1, 1);

        intervals3 = new QELineEdit(gridLayoutWidget_35);
        intervals3->setObjectName(QString::fromUtf8("intervals3"));
        intervals3->setAlignment(Qt::AlignCenter);
        intervals3->setDragEnabled(true);
        intervals3->setWriteOnEnter(true);
        intervals3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout3->addWidget(intervals3, 0, 1, 1, 2);

        settlingTimeUnit3 = new QLabel(gridLayoutWidget_35);
        settlingTimeUnit3->setObjectName(QString::fromUtf8("settlingTimeUnit3"));

        experimentalParametersLayout3->addWidget(settlingTimeUnit3, 4, 2, 1, 1);

        samplesButton3 = new QPushButton(gridLayoutWidget_35);
        samplesButton3->setObjectName(QString::fromUtf8("samplesButton3"));
        samplesButton3->setCursor(QCursor(Qt::PointingHandCursor));
        samplesButton3->setFocusPolicy(Qt::StrongFocus);

        experimentalParametersLayout3->addWidget(samplesButton3, 1, 3, 1, 1);

        scansLabel3 = new QLabel(gridLayoutWidget_35);
        scansLabel3->setObjectName(QString::fromUtf8("scansLabel3"));
        scansLabel3->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout3->addWidget(scansLabel3, 2, 0, 1, 1);

        scans3 = new QELineEdit(gridLayoutWidget_35);
        scans3->setObjectName(QString::fromUtf8("scans3"));
        scans3->setAlignment(Qt::AlignCenter);
        scans3->setDragEnabled(true);
        scans3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        scans3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        experimentalParametersLayout3->addWidget(scans3, 2, 1, 1, 2);

        intervalsLabel3 = new QLabel(gridLayoutWidget_35);
        intervalsLabel3->setObjectName(QString::fromUtf8("intervalsLabel3"));
        intervalsLabel3->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout3->addWidget(intervalsLabel3, 0, 0, 1, 1);

        expFileNameLabel3 = new QLabel(gridLayoutWidget_35);
        expFileNameLabel3->setObjectName(QString::fromUtf8("expFileNameLabel3"));
        expFileNameLabel3->setCursor(QCursor(Qt::IBeamCursor));

        experimentalParametersLayout3->addWidget(expFileNameLabel3, 3, 0, 1, 1);

        expFileName3 = new QELineEdit(gridLayoutWidget_35);
        expFileName3->setObjectName(QString::fromUtf8("expFileName3"));
        expFileName3->setDragEnabled(true);
        expFileName3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        experimentalParametersLayout3->addWidget(expFileName3, 3, 1, 1, 2);

        validIntervals3 = new QLabel(gridLayoutWidget_35);
        validIntervals3->setObjectName(QString::fromUtf8("validIntervals3"));
        validIntervals3->setFont(font2);

        experimentalParametersLayout3->addWidget(validIntervals3, 0, 4, 1, 1);

        validSamples3 = new QLabel(gridLayoutWidget_35);
        validSamples3->setObjectName(QString::fromUtf8("validSamples3"));
        validSamples3->setFont(font2);

        experimentalParametersLayout3->addWidget(validSamples3, 1, 4, 1, 1);

        Comments3 = new QGroupBox(twoThetaSlits);
        Comments3->setObjectName(QString::fromUtf8("Comments3"));
        Comments3->setGeometry(QRect(0, 410, 411, 131));
        sizePolicy2.setHeightForWidth(Comments3->sizePolicy().hasHeightForWidth());
        Comments3->setSizePolicy(sizePolicy2);
        Comments3->setMinimumSize(QSize(0, 0));
        Comments3->setCursor(QCursor(Qt::ArrowCursor));
        Comments3->setAutoFillBackground(false);
        Comments3->setFlat(false);
        Comments3->setCheckable(false);
        gridLayoutWidget_36 = new QWidget(Comments3);
        gridLayoutWidget_36->setObjectName(QString::fromUtf8("gridLayoutWidget_36"));
        gridLayoutWidget_36->setGeometry(QRect(10, 30, 391, 91));
        CommentsLayout3 = new QGridLayout(gridLayoutWidget_36);
        CommentsLayout3->setObjectName(QString::fromUtf8("CommentsLayout3"));
        CommentsLayout3->setContentsMargins(0, 0, 0, 0);
        expComments3 = new QELineEdit(gridLayoutWidget_36);
        expComments3->setObjectName(QString::fromUtf8("expComments3"));
        expComments3->setDragEnabled(true);
        expComments3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout3->addWidget(expComments3, 2, 1, 1, 1);

        userComments3 = new QELineEdit(gridLayoutWidget_36);
        userComments3->setObjectName(QString::fromUtf8("userComments3"));
        userComments3->setDragEnabled(true);
        userComments3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout3->addWidget(userComments3, 1, 1, 1, 1);

        expCommentsLabel3 = new QLabel(gridLayoutWidget_36);
        expCommentsLabel3->setObjectName(QString::fromUtf8("expCommentsLabel3"));
        expCommentsLabel3->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout3->addWidget(expCommentsLabel3, 2, 0, 1, 1);

        userCommentsLabel3 = new QLabel(gridLayoutWidget_36);
        userCommentsLabel3->setObjectName(QString::fromUtf8("userCommentsLabel3"));
        userCommentsLabel3->setCursor(QCursor(Qt::IBeamCursor));

        CommentsLayout3->addWidget(userCommentsLabel3, 1, 0, 1, 1);

        sampleName3 = new QLabel(gridLayoutWidget_36);
        sampleName3->setObjectName(QString::fromUtf8("sampleName3"));

        CommentsLayout3->addWidget(sampleName3, 0, 0, 1, 1);

        sampleNameVal3 = new QELineEdit(gridLayoutWidget_36);
        sampleNameVal3->setObjectName(QString::fromUtf8("sampleNameVal3"));
        sampleNameVal3->setDragEnabled(true);
        sampleNameVal3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        CommentsLayout3->addWidget(sampleNameVal3, 0, 1, 1, 1);

        Wizard->setPage(9, twoThetaSlits);
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

        Wizard->setPage(10, thetaTwoTheta);
        finishPage = new QWizardPage();
        finishPage->setObjectName(QString::fromUtf8("finishPage"));
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName(QString::fromUtf8("finishLabel"));
        finishLabel->setGeometry(QRect(0, 0, 161, 16));
        gridLayoutWidget_5 = new QWidget(finishPage);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 510, 411, 41));
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
        filePath->setFont(font1);
        filePath->setCursor(QCursor(Qt::IBeamCursor));
        filePath->setFrameShape(QFrame::StyledPanel);
        filePath->setWordWrap(true);

        filePathLayout->addWidget(filePath, 0, 1, 1, 1);

        Wizard->setPage(11, finishPage);
        QWidget::setTabOrder(usersExperiment, localExperiment);
        QWidget::setTabOrder(localExperiment, energyCalibraion);
        QWidget::setTabOrder(energyCalibraion, proposalIDValue);
        QWidget::setTabOrder(proposalIDValue, twoThetaScan);
        QWidget::setTabOrder(twoThetaScan, twoThetaTempScan);
        QWidget::setTabOrder(twoThetaTempScan, twoThetaSlitsScan);
        QWidget::setTabOrder(twoThetaSlitsScan, thetaTwoThetaScan);
        QWidget::setTabOrder(thetaTwoThetaScan, configurationsFileCreate);
        QWidget::setTabOrder(configurationsFileCreate, configurationsFileLoad);
        QWidget::setTabOrder(configurationsFileLoad, loadConfigFileButton);
        QWidget::setTabOrder(loadConfigFileButton, robotYes);
        QWidget::setTabOrder(robotYes, robotNo);
        QWidget::setTabOrder(robotNo, intervals);
        QWidget::setTabOrder(intervals, intervalsButton);
        QWidget::setTabOrder(intervalsButton, samples);
        QWidget::setTabOrder(samples, samplesButton);
        QWidget::setTabOrder(samplesButton, scans);
        QWidget::setTabOrder(scans, expFileName);
        QWidget::setTabOrder(expFileName, settlingTime);
        QWidget::setTabOrder(settlingTime, testingModeYes);
        QWidget::setTabOrder(testingModeYes, testingModeNo);
        QWidget::setTabOrder(testingModeNo, sampleNameVal);
        QWidget::setTabOrder(sampleNameVal, userComments);
        QWidget::setTabOrder(userComments, expComments);
        QWidget::setTabOrder(expComments, intervals3);
        QWidget::setTabOrder(intervals3, intervalsButton3);
        QWidget::setTabOrder(intervalsButton3, samples3);
        QWidget::setTabOrder(samples3, samplesButton3);
        QWidget::setTabOrder(samplesButton3, scans3);
        QWidget::setTabOrder(scans3, expFileName3);
        QWidget::setTabOrder(expFileName3, settlingTime3);
        QWidget::setTabOrder(settlingTime3, testingModeYes3);
        QWidget::setTabOrder(testingModeYes3, testingModeNo3);
        QWidget::setTabOrder(testingModeNo3, sampleNameVal3);
        QWidget::setTabOrder(sampleNameVal3, userComments3);
        QWidget::setTabOrder(userComments3, expComments3);
        QWidget::setTabOrder(expComments3, intervals2);
        QWidget::setTabOrder(intervals2, intervalsButton2);
        QWidget::setTabOrder(intervalsButton2, deadband);
        QWidget::setTabOrder(deadband, expFileName2);
        QWidget::setTabOrder(expFileName2, settlingTime2);
        QWidget::setTabOrder(settlingTime2, testingModeYes2);
        QWidget::setTabOrder(testingModeYes2, testingModeNo2);
        QWidget::setTabOrder(testingModeNo2, sampleNameVal2);
        QWidget::setTabOrder(sampleNameVal2, userComments2);
        QWidget::setTabOrder(userComments2, expComments2);
        QWidget::setTabOrder(expComments2, intervalsButton4);
        QWidget::setTabOrder(intervalsButton4, samplesButton4);
        QWidget::setTabOrder(samplesButton4, expFileName4);
        QWidget::setTabOrder(expFileName4, userComments4);
        QWidget::setTabOrder(userComments4, expComments4);
        QWidget::setTabOrder(expComments4, Yes);
        QWidget::setTabOrder(Yes, No);

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
        proposalIDValue->setPlaceholderText(QCoreApplication::translate("Wizard", "minimum characters 8, e.g. 20172001", nullptr));
        proposalIDValue->setText(QCoreApplication::translate("Wizard", "0", nullptr));
        proposalIDValue->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ProposalID", nullptr)));
        proposalIDValue->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        proposalIDWarning->setText(QString());
        Yes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        No->setText(QCoreApplication::translate("Wizard", "No", nullptr));
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
        experimentalParameters->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        scans->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Scans", nullptr)));
        scans->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTime->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        intervals->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expFileName->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expFileNameLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. file name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        intervalsButton->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        settlingTimeUnit->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
        scansLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of scans <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        settlingTimeLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        intervalsLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        validIntervals->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        validSamples->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        samplesButton->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        samples->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Samples", nullptr)));
        samples->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        samplesLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of samples <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        Comments->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        userComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        sampleName->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        sampleNameVal->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeGroupBox->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeNo->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeLabel->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeYes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        tesingMode->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
        testingModeFeedback->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        experimentalParameters2->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        intervalsLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        deadband->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TempDeadband", nullptr)));
        deadband->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit2->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
        settlingTimeLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        expFileName2->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expFileNameLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. file name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        validIntervals2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        settlingTime2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        deadbandLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Temperature deadband <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        intervals2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        intervalsButton2->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        Comments2->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel2->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel2->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        userComments2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expComments2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        sampleName2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        sampleNameVal2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeGroupBox2->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeNo2->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo2->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeLabel2->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeYes2->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes2->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes2->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        tesingMode2->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
        testingModeFeedback2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        slitConfigurationsGroupBox->setTitle(QCoreApplication::translate("Wizard", "Slits Configurations", nullptr));
        testingModeGroupBox3->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeNo3->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo3->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeLabel3->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeYes3->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes3->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes3->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        tesingMode3->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
        testingModeFeedback3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        experimentalParameters3->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        samples3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Samples", nullptr)));
        samples3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        samplesLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of samples <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        intervalsButton3->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        settlingTime3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        intervals3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit3->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
        samplesButton3->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of scans <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        scans3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Scans", nullptr)));
        scans3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        intervalsLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        expFileNameLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. file name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        expFileName3->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        validIntervals3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        validSamples3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        Comments3->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        expComments3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        userComments3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expCommentsLabel3->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
        userCommentsLabel3->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        sampleName3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        sampleNameVal3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
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
