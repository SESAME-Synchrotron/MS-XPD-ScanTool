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
#include <QtWidgets/QLineEdit>
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
    QGridLayout *gridLayout_20;
    QGroupBox *experimentSelection;
    QGridLayout *gridLayout_4;
    QERadioButton *usersExperiment;
    QERadioButton *localExperiment;
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
    QGridLayout *gridLayout_21;
    QGroupBox *scanningTypeGroupBox;
    QGridLayout *gridLayout_8;
    QERadioButton *twoThetaScan;
    QERadioButton *twoThetaTempScan;
    QERadioButton *twoThetaSlitsScan;
    QERadioButton *thetaTwoThetaScan;
    QWizardPage *configurationsFile;
    QGridLayout *gridLayout_22;
    QGroupBox *configurationsFileGroubBox;
    QGridLayout *gridLayout_5;
    QERadioButton *configurationsFileCreate;
    QERadioButton *configurationsFileLoad;
    QWizardPage *loadConfigFile;
    QWidget *gridLayoutWidget_6;
    QGridLayout *loadConfigFileLayout;
    QLabel *loadConfigFileLabel;
    QLabel *expConfigFile;
    QPushButton *loadConfigFileButton;
    QWizardPage *robot;
    QGridLayout *gridLayout_23;
    QGroupBox *robotGroupBox;
    QGridLayout *gridLayout_6;
    QERadioButton *robotYes;
    QERadioButton *robotNo;
    QLabel *robotLabel;
    QLabel *robotInUse;
    QELabel *useRobotFeedback;
    QWizardPage *experimentalGUI;
    QGridLayout *gridLayout_24;
    QGroupBox *experimentalParameters;
    QGridLayout *gridLayout_11;
    QLabel *intervalsLabel;
    QPushButton *intervalsButton;
    QLabel *validIntervals;
    QLabel *samplesLabel;
    QPushButton *samplesButton;
    QLabel *validSamples;
    QLabel *scansLabel;
    QLabel *expFileNameLabel;
    QLabel *settlingTimeLabel;
    QELineEdit *settlingTime;
    QLabel *settlingTimeUnit;
    QELineEdit *intervals;
    QELineEdit *samples;
    QELineEdit *scans;
    QELineEdit *expFileName;
    QGroupBox *testingModeGroupBox;
    QGridLayout *gridLayout_7;
    QLabel *testingModeLabel;
    QERadioButton *testingModeYes;
    QLabel *tesingMode;
    QELabel *testingModeFeedback;
    QERadioButton *testingModeNo;
    QGroupBox *Comments;
    QGridLayout *gridLayout_9;
    QLabel *sampleName;
    QELineEdit *sampleNameVal;
    QLabel *userCommentsLabel;
    QELineEdit *userComments;
    QLabel *expCommentsLabel;
    QELineEdit *expComments;
    QSpacerItem *verticalSpacer;
    QWizardPage *twoThetaTemp;
    QGridLayout *gridLayout_25;
    QGroupBox *experimentalParameters2;
    QGridLayout *gridLayout_10;
    QLabel *intervalsLabel2;
    QELineEdit *intervals2;
    QPushButton *intervalsButton2;
    QLabel *validIntervals2;
    QLabel *deadbandLabel;
    QELineEdit *deadband;
    QLabel *expFileNameLabel2;
    QELineEdit *expFileName2;
    QLabel *settlingTimeLabel2;
    QELineEdit *settlingTime2;
    QLabel *settlingTimeUnit2;
    QGroupBox *testingModeGroupBox2;
    QGridLayout *gridLayout_12;
    QERadioButton *testingModeYes2;
    QERadioButton *testingModeNo2;
    QLabel *testingModeLabel2;
    QLabel *tesingMode2;
    QELabel *testingModeFeedback2;
    QGroupBox *Comments2;
    QGridLayout *gridLayout_13;
    QLabel *sampleName2;
    QELineEdit *sampleNameVal2;
    QLabel *userCommentsLabel2;
    QELineEdit *userComments2;
    QLabel *expCommentsLabel2;
    QELineEdit *expComments2;
    QSpacerItem *verticalSpacer_2;
    QWizardPage *twoThetaSlits;
    QGridLayout *gridLayout_19;
    QGroupBox *slitConfigurationsGroupBox;
    QGridLayout *gridLayout_18;
    QLineEdit *initZeroPixelPos;
    QLabel *yStartLabel;
    QLineEdit *yEnd;
    QLabel *twoThetaOffsetLabel;
    QLabel *initZeroPixelPosLabel;
    QLineEdit *sampleToDetDis;
    QLineEdit *yStart;
    QLabel *yEndLabel;
    QLabel *sampleToDetDisLabel;
    QPushButton *modify;
    QLineEdit *twoThetaOffset;
    QLabel *xAxisRangeLabel;
    QLabel *xLabel;
    QLineEdit *x;
    QLineEdit *xAxisRange;
    QGroupBox *experimentalParameters3;
    QGridLayout *gridLayout_3;
    QLabel *intervalsLabel3;
    QPushButton *intervalsButton3;
    QLabel *validIntervals3;
    QLabel *samplesLabel3;
    QPushButton *samplesButton3;
    QLabel *validSamples3;
    QLabel *scansLabel3;
    QLabel *expFileNameLabel3;
    QLabel *settlingTimeLabel3;
    QELineEdit *settlingTime3;
    QLabel *settlingTimeUnit3;
    QELineEdit *intervals3;
    QELineEdit *samples3;
    QELineEdit *scans3;
    QELineEdit *expFileName3;
    QGroupBox *Comments3;
    QGridLayout *gridLayout_15;
    QLabel *expCommentsLabel3;
    QELineEdit *expComments3;
    QELineEdit *sampleNameVal3;
    QLabel *userCommentsLabel3;
    QLabel *sampleName3;
    QELineEdit *userComments3;
    QGroupBox *testingModeGroupBox3;
    QGridLayout *gridLayout_14;
    QERadioButton *testingModeYes3;
    QERadioButton *testingModeNo3;
    QLabel *testingModeLabel3;
    QLabel *tesingMode3;
    QELabel *testingModeFeedback3;
    QWizardPage *thetaTwoTheta;
    QGridLayout *gridLayout_26;
    QGroupBox *experimentalParameters4;
    QGridLayout *gridLayout_16;
    QLabel *intervalsLabel4;
    QENumericEdit *intervals4;
    QPushButton *intervalsButton4;
    QLabel *samplesLabel4;
    QENumericEdit *samples4;
    QPushButton *samplesButton4;
    QLabel *scansLabel4;
    QENumericEdit *scans4;
    QLabel *expFileNameLabel4;
    QELineEdit *expFileName4;
    QLabel *settlingTimeLabel4;
    QENumericEdit *settlingTime4;
    QGroupBox *Comments4;
    QGridLayout *gridLayout_17;
    QLabel *userCommentsLabel4;
    QELineEdit *userComments4;
    QLabel *expCommentsLabel4;
    QELineEdit *expComments4;
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
        Wizard->resize(480, 701);
        Wizard->setCursor(QCursor(Qt::ArrowCursor));
        Wizard->setOptions(QWizard::HaveHelpButton|QWizard::NoBackButtonOnStartPage|QWizard::NoDefaultButton);
        experimentType = new QWizardPage();
        experimentType->setObjectName(QString::fromUtf8("experimentType"));
        gridLayout_20 = new QGridLayout(experimentType);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        experimentSelection = new QGroupBox(experimentType);
        experimentSelection->setObjectName(QString::fromUtf8("experimentSelection"));
        experimentSelection->setCursor(QCursor(Qt::ArrowCursor));
        experimentSelection->setAutoFillBackground(false);
        experimentSelection->setFlat(false);
        experimentSelection->setCheckable(false);
        gridLayout_4 = new QGridLayout(experimentSelection);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        usersExperiment = new QERadioButton(experimentSelection);
        usersExperiment->setObjectName(QString::fromUtf8("usersExperiment"));
        usersExperiment->setCursor(QCursor(Qt::PointingHandCursor));
        usersExperiment->setVariableAsToolTip(false);
        usersExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        usersExperiment->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        gridLayout_4->addWidget(usersExperiment, 0, 0, 1, 1);

        localExperiment = new QERadioButton(experimentSelection);
        localExperiment->setObjectName(QString::fromUtf8("localExperiment"));
        localExperiment->setCursor(QCursor(Qt::PointingHandCursor));
        localExperiment->setVariableAsToolTip(false);
        localExperiment->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_4->addWidget(localExperiment, 1, 0, 1, 1);

        energyCalibraion = new QERadioButton(experimentSelection);
        energyCalibraion->setObjectName(QString::fromUtf8("energyCalibraion"));
        energyCalibraion->setCursor(QCursor(Qt::PointingHandCursor));
        energyCalibraion->setVariableAsToolTip(false);
        energyCalibraion->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_4->addWidget(energyCalibraion, 2, 0, 1, 1);


        gridLayout_20->addWidget(experimentSelection, 0, 0, 1, 1);

        Wizard->setPage(1, experimentType);
        proposalID = new QWizardPage();
        proposalID->setObjectName(QString::fromUtf8("proposalID"));
        proposalIDGroupBox = new QGroupBox(proposalID);
        proposalIDGroupBox->setObjectName(QString::fromUtf8("proposalIDGroupBox"));
        proposalIDGroupBox->setGeometry(QRect(9, 9, 441, 81));
        gridLayout = new QGridLayout(proposalIDGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        proposalIDValue = new QELineEdit(proposalIDGroupBox);
        proposalIDValue->setObjectName(QString::fromUtf8("proposalIDValue"));
        proposalIDValue->setDragEnabled(true);
        proposalIDValue->setWriteOnLoseFocus(true);
        proposalIDValue->setVariableAsToolTip(false);
        proposalIDValue->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        proposalIDValue->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout->addWidget(proposalIDValue, 0, 0, 1, 1);

        layoutWidget = new QWidget(proposalID);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 360, 441, 271));
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
        gridLayout_21 = new QGridLayout(scanningType);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        scanningTypeGroupBox = new QGroupBox(scanningType);
        scanningTypeGroupBox->setObjectName(QString::fromUtf8("scanningTypeGroupBox"));
        scanningTypeGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        scanningTypeGroupBox->setAutoFillBackground(false);
        scanningTypeGroupBox->setFlat(false);
        scanningTypeGroupBox->setCheckable(false);
        gridLayout_8 = new QGridLayout(scanningTypeGroupBox);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        twoThetaScan = new QERadioButton(scanningTypeGroupBox);
        twoThetaScan->setObjectName(QString::fromUtf8("twoThetaScan"));
        twoThetaScan->setCursor(QCursor(Qt::PointingHandCursor));
        twoThetaScan->setVariableAsToolTip(false);
        twoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        twoThetaScan->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        gridLayout_8->addWidget(twoThetaScan, 0, 0, 1, 1);

        twoThetaTempScan = new QERadioButton(scanningTypeGroupBox);
        twoThetaTempScan->setObjectName(QString::fromUtf8("twoThetaTempScan"));
        twoThetaTempScan->setCursor(QCursor(Qt::PointingHandCursor));
        twoThetaTempScan->setVariableAsToolTip(false);
        twoThetaTempScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_8->addWidget(twoThetaTempScan, 1, 0, 1, 1);

        twoThetaSlitsScan = new QERadioButton(scanningTypeGroupBox);
        twoThetaSlitsScan->setObjectName(QString::fromUtf8("twoThetaSlitsScan"));
        twoThetaSlitsScan->setCursor(QCursor(Qt::PointingHandCursor));
        twoThetaSlitsScan->setVariableAsToolTip(false);
        twoThetaSlitsScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_8->addWidget(twoThetaSlitsScan, 2, 0, 1, 1);

        thetaTwoThetaScan = new QERadioButton(scanningTypeGroupBox);
        thetaTwoThetaScan->setObjectName(QString::fromUtf8("thetaTwoThetaScan"));
        thetaTwoThetaScan->setCursor(QCursor(Qt::PointingHandCursor));
        thetaTwoThetaScan->setVariableAsToolTip(false);
        thetaTwoThetaScan->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_8->addWidget(thetaTwoThetaScan, 3, 0, 1, 1);


        gridLayout_21->addWidget(scanningTypeGroupBox, 0, 0, 1, 1);

        Wizard->setPage(3, scanningType);
        configurationsFile = new QWizardPage();
        configurationsFile->setObjectName(QString::fromUtf8("configurationsFile"));
        gridLayout_22 = new QGridLayout(configurationsFile);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        configurationsFileGroubBox = new QGroupBox(configurationsFile);
        configurationsFileGroubBox->setObjectName(QString::fromUtf8("configurationsFileGroubBox"));
        configurationsFileGroubBox->setCursor(QCursor(Qt::ArrowCursor));
        configurationsFileGroubBox->setAutoFillBackground(false);
        configurationsFileGroubBox->setFlat(false);
        configurationsFileGroubBox->setCheckable(false);
        gridLayout_5 = new QGridLayout(configurationsFileGroubBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        configurationsFileCreate = new QERadioButton(configurationsFileGroubBox);
        configurationsFileCreate->setObjectName(QString::fromUtf8("configurationsFileCreate"));
        configurationsFileCreate->setCursor(QCursor(Qt::PointingHandCursor));
        configurationsFileCreate->setVariableAsToolTip(false);
        configurationsFileCreate->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));
        configurationsFileCreate->setProperty("separator", QVariant::fromValue(QERadioButton::NoSeparator));

        gridLayout_5->addWidget(configurationsFileCreate, 0, 0, 1, 1);

        configurationsFileLoad = new QERadioButton(configurationsFileGroubBox);
        configurationsFileLoad->setObjectName(QString::fromUtf8("configurationsFileLoad"));
        configurationsFileLoad->setCursor(QCursor(Qt::PointingHandCursor));
        configurationsFileLoad->setVariableAsToolTip(false);
        configurationsFileLoad->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_5->addWidget(configurationsFileLoad, 1, 0, 1, 1);


        gridLayout_22->addWidget(configurationsFileGroubBox, 0, 0, 1, 1);

        Wizard->setPage(4, configurationsFile);
        loadConfigFile = new QWizardPage();
        loadConfigFile->setObjectName(QString::fromUtf8("loadConfigFile"));
        gridLayoutWidget_6 = new QWidget(loadConfigFile);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(10, 30, 441, 61));
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
        gridLayout_23 = new QGridLayout(robot);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        robotGroupBox = new QGroupBox(robot);
        robotGroupBox->setObjectName(QString::fromUtf8("robotGroupBox"));
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
        gridLayout_6 = new QGridLayout(robotGroupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        robotYes = new QERadioButton(robotGroupBox);
        robotYes->setObjectName(QString::fromUtf8("robotYes"));
        robotYes->setCursor(QCursor(Qt::PointingHandCursor));
        robotYes->setFocusPolicy(Qt::StrongFocus);
        robotYes->setVariableAsToolTip(false);
        robotYes->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_6->addWidget(robotYes, 0, 1, 1, 1);

        robotNo = new QERadioButton(robotGroupBox);
        robotNo->setObjectName(QString::fromUtf8("robotNo"));
        robotNo->setCursor(QCursor(Qt::PointingHandCursor));
        robotNo->setFocusPolicy(Qt::StrongFocus);
        robotNo->setVariableAsToolTip(false);
        robotNo->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_6->addWidget(robotNo, 1, 1, 1, 1);

        robotLabel = new QLabel(robotGroupBox);
        robotLabel->setObjectName(QString::fromUtf8("robotLabel"));
        robotLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_6->addWidget(robotLabel, 0, 0, 2, 1);

        robotInUse = new QLabel(robotGroupBox);
        robotInUse->setObjectName(QString::fromUtf8("robotInUse"));

        gridLayout_6->addWidget(robotInUse, 0, 2, 2, 1);

        useRobotFeedback = new QELabel(robotGroupBox);
        useRobotFeedback->setObjectName(QString::fromUtf8("useRobotFeedback"));
        useRobotFeedback->setCursor(QCursor(Qt::IBeamCursor));
        useRobotFeedback->setFrameShape(QFrame::StyledPanel);
        useRobotFeedback->setAlignment(Qt::AlignCenter);
        useRobotFeedback->setWordWrap(true);
        useRobotFeedback->setVariableAsToolTip(false);
        useRobotFeedback->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        useRobotFeedback->setAddUnits(false);

        gridLayout_6->addWidget(useRobotFeedback, 0, 3, 2, 1);


        gridLayout_23->addWidget(robotGroupBox, 0, 0, 1, 1);

        Wizard->setPage(6, robot);
        experimentalGUI = new QWizardPage();
        experimentalGUI->setObjectName(QString::fromUtf8("experimentalGUI"));
        gridLayout_24 = new QGridLayout(experimentalGUI);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        experimentalParameters = new QGroupBox(experimentalGUI);
        experimentalParameters->setObjectName(QString::fromUtf8("experimentalParameters"));
        experimentalParameters->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters->setAutoFillBackground(false);
        experimentalParameters->setFlat(false);
        experimentalParameters->setCheckable(false);
        gridLayout_11 = new QGridLayout(experimentalParameters);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        intervalsLabel = new QLabel(experimentalParameters);
        intervalsLabel->setObjectName(QString::fromUtf8("intervalsLabel"));
        intervalsLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_11->addWidget(intervalsLabel, 0, 0, 1, 1);

        intervalsButton = new QPushButton(experimentalParameters);
        intervalsButton->setObjectName(QString::fromUtf8("intervalsButton"));
        intervalsButton->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton->setFocusPolicy(Qt::StrongFocus);

        gridLayout_11->addWidget(intervalsButton, 0, 3, 1, 1);

        validIntervals = new QLabel(experimentalParameters);
        validIntervals->setObjectName(QString::fromUtf8("validIntervals"));
        QFont font2;
        font2.setPointSize(14);
        validIntervals->setFont(font2);

        gridLayout_11->addWidget(validIntervals, 0, 4, 1, 1);

        samplesLabel = new QLabel(experimentalParameters);
        samplesLabel->setObjectName(QString::fromUtf8("samplesLabel"));
        samplesLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_11->addWidget(samplesLabel, 1, 0, 1, 1);

        samplesButton = new QPushButton(experimentalParameters);
        samplesButton->setObjectName(QString::fromUtf8("samplesButton"));
        samplesButton->setCursor(QCursor(Qt::PointingHandCursor));
        samplesButton->setFocusPolicy(Qt::StrongFocus);

        gridLayout_11->addWidget(samplesButton, 1, 3, 1, 1);

        validSamples = new QLabel(experimentalParameters);
        validSamples->setObjectName(QString::fromUtf8("validSamples"));
        validSamples->setFont(font2);

        gridLayout_11->addWidget(validSamples, 1, 4, 1, 1);

        scansLabel = new QLabel(experimentalParameters);
        scansLabel->setObjectName(QString::fromUtf8("scansLabel"));
        scansLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_11->addWidget(scansLabel, 2, 0, 1, 1);

        expFileNameLabel = new QLabel(experimentalParameters);
        expFileNameLabel->setObjectName(QString::fromUtf8("expFileNameLabel"));
        expFileNameLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_11->addWidget(expFileNameLabel, 3, 0, 1, 1);

        settlingTimeLabel = new QLabel(experimentalParameters);
        settlingTimeLabel->setObjectName(QString::fromUtf8("settlingTimeLabel"));
        settlingTimeLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_11->addWidget(settlingTimeLabel, 4, 0, 1, 1);

        settlingTime = new QELineEdit(experimentalParameters);
        settlingTime->setObjectName(QString::fromUtf8("settlingTime"));
        settlingTime->setAlignment(Qt::AlignCenter);
        settlingTime->setDragEnabled(true);
        settlingTime->setWriteOnLoseFocus(true);
        settlingTime->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        gridLayout_11->addWidget(settlingTime, 4, 1, 1, 1);

        settlingTimeUnit = new QLabel(experimentalParameters);
        settlingTimeUnit->setObjectName(QString::fromUtf8("settlingTimeUnit"));
        settlingTimeUnit->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout_11->addWidget(settlingTimeUnit, 4, 2, 1, 1);

        intervals = new QELineEdit(experimentalParameters);
        intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->setAlignment(Qt::AlignCenter);
        intervals->setDragEnabled(true);
        intervals->setWriteOnLoseFocus(true);
        intervals->setVariableAsToolTip(false);
        intervals->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_11->addWidget(intervals, 0, 1, 1, 2);

        samples = new QELineEdit(experimentalParameters);
        samples->setObjectName(QString::fromUtf8("samples"));
        samples->setAlignment(Qt::AlignCenter);
        samples->setDragEnabled(true);
        samples->setWriteOnLoseFocus(true);
        samples->setVariableAsToolTip(false);
        samples->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        samples->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_11->addWidget(samples, 1, 1, 1, 2);

        scans = new QELineEdit(experimentalParameters);
        scans->setObjectName(QString::fromUtf8("scans"));
        scans->setAlignment(Qt::AlignCenter);
        scans->setDragEnabled(true);
        scans->setWriteOnLoseFocus(true);
        scans->setVariableAsToolTip(false);
        scans->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        scans->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_11->addWidget(scans, 2, 1, 1, 2);

        expFileName = new QELineEdit(experimentalParameters);
        expFileName->setObjectName(QString::fromUtf8("expFileName"));
        expFileName->setDragEnabled(true);
        expFileName->setWriteOnLoseFocus(true);
        expFileName->setVariableAsToolTip(false);
        expFileName->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_11->addWidget(expFileName, 3, 1, 1, 2);


        gridLayout_24->addWidget(experimentalParameters, 0, 0, 1, 1);

        testingModeGroupBox = new QGroupBox(experimentalGUI);
        testingModeGroupBox->setObjectName(QString::fromUtf8("testingModeGroupBox"));
        sizePolicy2.setHeightForWidth(testingModeGroupBox->sizePolicy().hasHeightForWidth());
        testingModeGroupBox->setSizePolicy(sizePolicy2);
        testingModeGroupBox->setMinimumSize(QSize(0, 0));
        testingModeGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox->setAutoFillBackground(false);
        testingModeGroupBox->setFlat(false);
        testingModeGroupBox->setCheckable(false);
        gridLayout_7 = new QGridLayout(testingModeGroupBox);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        testingModeLabel = new QLabel(testingModeGroupBox);
        testingModeLabel->setObjectName(QString::fromUtf8("testingModeLabel"));
        testingModeLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_7->addWidget(testingModeLabel, 0, 0, 2, 1);

        testingModeYes = new QERadioButton(testingModeGroupBox);
        testingModeYes->setObjectName(QString::fromUtf8("testingModeYes"));
        testingModeYes->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeYes->setFocusPolicy(Qt::StrongFocus);
        testingModeYes->setVariableAsToolTip(false);
        testingModeYes->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_7->addWidget(testingModeYes, 0, 1, 1, 1);

        tesingMode = new QLabel(testingModeGroupBox);
        tesingMode->setObjectName(QString::fromUtf8("tesingMode"));
        tesingMode->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_7->addWidget(tesingMode, 0, 2, 2, 1);

        testingModeFeedback = new QELabel(testingModeGroupBox);
        testingModeFeedback->setObjectName(QString::fromUtf8("testingModeFeedback"));
        testingModeFeedback->setCursor(QCursor(Qt::IBeamCursor));
        testingModeFeedback->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback->setAlignment(Qt::AlignCenter);
        testingModeFeedback->setWordWrap(true);
        testingModeFeedback->setVariableAsToolTip(false);
        testingModeFeedback->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback->setAddUnits(false);

        gridLayout_7->addWidget(testingModeFeedback, 0, 3, 2, 1);

        testingModeNo = new QERadioButton(testingModeGroupBox);
        testingModeNo->setObjectName(QString::fromUtf8("testingModeNo"));
        testingModeNo->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeNo->setFocusPolicy(Qt::StrongFocus);
        testingModeNo->setVariableAsToolTip(false);
        testingModeNo->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_7->addWidget(testingModeNo, 1, 1, 1, 1);


        gridLayout_24->addWidget(testingModeGroupBox, 1, 0, 1, 1);

        Comments = new QGroupBox(experimentalGUI);
        Comments->setObjectName(QString::fromUtf8("Comments"));
        sizePolicy2.setHeightForWidth(Comments->sizePolicy().hasHeightForWidth());
        Comments->setSizePolicy(sizePolicy2);
        Comments->setMinimumSize(QSize(0, 0));
        Comments->setCursor(QCursor(Qt::ArrowCursor));
        Comments->setAutoFillBackground(false);
        Comments->setFlat(false);
        Comments->setCheckable(false);
        gridLayout_9 = new QGridLayout(Comments);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        sampleName = new QLabel(Comments);
        sampleName->setObjectName(QString::fromUtf8("sampleName"));
        sampleName->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_9->addWidget(sampleName, 0, 0, 1, 1);

        sampleNameVal = new QELineEdit(Comments);
        sampleNameVal->setObjectName(QString::fromUtf8("sampleNameVal"));
        sampleNameVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sampleNameVal->setDragEnabled(true);
        sampleNameVal->setWriteOnLoseFocus(true);
        sampleNameVal->setVariableAsToolTip(false);
        sampleNameVal->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_9->addWidget(sampleNameVal, 0, 1, 1, 1);

        userCommentsLabel = new QLabel(Comments);
        userCommentsLabel->setObjectName(QString::fromUtf8("userCommentsLabel"));
        userCommentsLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_9->addWidget(userCommentsLabel, 1, 0, 1, 1);

        userComments = new QELineEdit(Comments);
        userComments->setObjectName(QString::fromUtf8("userComments"));
        userComments->setDragEnabled(true);
        userComments->setWriteOnLoseFocus(true);
        userComments->setVariableAsToolTip(false);
        userComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_9->addWidget(userComments, 1, 1, 1, 1);

        expCommentsLabel = new QLabel(Comments);
        expCommentsLabel->setObjectName(QString::fromUtf8("expCommentsLabel"));
        expCommentsLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_9->addWidget(expCommentsLabel, 2, 0, 1, 1);

        expComments = new QELineEdit(Comments);
        expComments->setObjectName(QString::fromUtf8("expComments"));
        expComments->setDragEnabled(true);
        expComments->setWriteOnLoseFocus(true);
        expComments->setVariableAsToolTip(false);
        expComments->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_9->addWidget(expComments, 2, 1, 1, 1);


        gridLayout_24->addWidget(Comments, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 210, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_24->addItem(verticalSpacer, 2, 0, 1, 1);

        Wizard->setPage(7, experimentalGUI);
        twoThetaTemp = new QWizardPage();
        twoThetaTemp->setObjectName(QString::fromUtf8("twoThetaTemp"));
        gridLayout_25 = new QGridLayout(twoThetaTemp);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        experimentalParameters2 = new QGroupBox(twoThetaTemp);
        experimentalParameters2->setObjectName(QString::fromUtf8("experimentalParameters2"));
        experimentalParameters2->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters2->setAutoFillBackground(false);
        experimentalParameters2->setFlat(false);
        experimentalParameters2->setCheckable(false);
        gridLayout_10 = new QGridLayout(experimentalParameters2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        intervalsLabel2 = new QLabel(experimentalParameters2);
        intervalsLabel2->setObjectName(QString::fromUtf8("intervalsLabel2"));
        intervalsLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_10->addWidget(intervalsLabel2, 0, 0, 1, 1);

        intervals2 = new QELineEdit(experimentalParameters2);
        intervals2->setObjectName(QString::fromUtf8("intervals2"));
        intervals2->setAlignment(Qt::AlignCenter);
        intervals2->setDragEnabled(true);
        intervals2->setWriteOnLoseFocus(true);
        intervals2->setVariableAsToolTip(false);
        intervals2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals2->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_10->addWidget(intervals2, 0, 1, 1, 2);

        intervalsButton2 = new QPushButton(experimentalParameters2);
        intervalsButton2->setObjectName(QString::fromUtf8("intervalsButton2"));
        intervalsButton2->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton2->setFocusPolicy(Qt::StrongFocus);

        gridLayout_10->addWidget(intervalsButton2, 0, 3, 1, 1);

        validIntervals2 = new QLabel(experimentalParameters2);
        validIntervals2->setObjectName(QString::fromUtf8("validIntervals2"));
        validIntervals2->setFont(font2);

        gridLayout_10->addWidget(validIntervals2, 0, 4, 1, 1);

        deadbandLabel = new QLabel(experimentalParameters2);
        deadbandLabel->setObjectName(QString::fromUtf8("deadbandLabel"));
        deadbandLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_10->addWidget(deadbandLabel, 1, 0, 1, 1);

        deadband = new QELineEdit(experimentalParameters2);
        deadband->setObjectName(QString::fromUtf8("deadband"));
        deadband->setAlignment(Qt::AlignCenter);
        deadband->setDragEnabled(true);
        deadband->setWriteOnLoseFocus(true);
        deadband->setVariableAsToolTip(false);
        deadband->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        deadband->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        gridLayout_10->addWidget(deadband, 1, 1, 1, 2);

        expFileNameLabel2 = new QLabel(experimentalParameters2);
        expFileNameLabel2->setObjectName(QString::fromUtf8("expFileNameLabel2"));
        expFileNameLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_10->addWidget(expFileNameLabel2, 2, 0, 1, 1);

        expFileName2 = new QELineEdit(experimentalParameters2);
        expFileName2->setObjectName(QString::fromUtf8("expFileName2"));
        expFileName2->setDragEnabled(true);
        expFileName2->setWriteOnLoseFocus(true);
        expFileName2->setVariableAsToolTip(false);
        expFileName2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_10->addWidget(expFileName2, 2, 1, 1, 2);

        settlingTimeLabel2 = new QLabel(experimentalParameters2);
        settlingTimeLabel2->setObjectName(QString::fromUtf8("settlingTimeLabel2"));
        settlingTimeLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_10->addWidget(settlingTimeLabel2, 3, 0, 1, 1);

        settlingTime2 = new QELineEdit(experimentalParameters2);
        settlingTime2->setObjectName(QString::fromUtf8("settlingTime2"));
        settlingTime2->setAlignment(Qt::AlignCenter);
        settlingTime2->setDragEnabled(true);
        settlingTime2->setWriteOnLoseFocus(true);
        settlingTime2->setVariableAsToolTip(false);
        settlingTime2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime2->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        gridLayout_10->addWidget(settlingTime2, 3, 1, 1, 1);

        settlingTimeUnit2 = new QLabel(experimentalParameters2);
        settlingTimeUnit2->setObjectName(QString::fromUtf8("settlingTimeUnit2"));
        settlingTimeUnit2->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout_10->addWidget(settlingTimeUnit2, 3, 2, 1, 1);


        gridLayout_25->addWidget(experimentalParameters2, 0, 0, 1, 1);

        testingModeGroupBox2 = new QGroupBox(twoThetaTemp);
        testingModeGroupBox2->setObjectName(QString::fromUtf8("testingModeGroupBox2"));
        sizePolicy2.setHeightForWidth(testingModeGroupBox2->sizePolicy().hasHeightForWidth());
        testingModeGroupBox2->setSizePolicy(sizePolicy2);
        testingModeGroupBox2->setMinimumSize(QSize(0, 0));
        testingModeGroupBox2->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox2->setAutoFillBackground(false);
        testingModeGroupBox2->setFlat(false);
        testingModeGroupBox2->setCheckable(false);
        gridLayout_12 = new QGridLayout(testingModeGroupBox2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        testingModeYes2 = new QERadioButton(testingModeGroupBox2);
        testingModeYes2->setObjectName(QString::fromUtf8("testingModeYes2"));
        testingModeYes2->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeYes2->setFocusPolicy(Qt::StrongFocus);
        testingModeYes2->setVariableAsToolTip(false);
        testingModeYes2->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_12->addWidget(testingModeYes2, 0, 1, 1, 1);

        testingModeNo2 = new QERadioButton(testingModeGroupBox2);
        testingModeNo2->setObjectName(QString::fromUtf8("testingModeNo2"));
        testingModeNo2->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeNo2->setFocusPolicy(Qt::StrongFocus);
        testingModeNo2->setVariableAsToolTip(false);
        testingModeNo2->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_12->addWidget(testingModeNo2, 1, 1, 1, 1);

        testingModeLabel2 = new QLabel(testingModeGroupBox2);
        testingModeLabel2->setObjectName(QString::fromUtf8("testingModeLabel2"));
        testingModeLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_12->addWidget(testingModeLabel2, 0, 0, 2, 1);

        tesingMode2 = new QLabel(testingModeGroupBox2);
        tesingMode2->setObjectName(QString::fromUtf8("tesingMode2"));
        tesingMode2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_12->addWidget(tesingMode2, 0, 2, 2, 1);

        testingModeFeedback2 = new QELabel(testingModeGroupBox2);
        testingModeFeedback2->setObjectName(QString::fromUtf8("testingModeFeedback2"));
        testingModeFeedback2->setCursor(QCursor(Qt::IBeamCursor));
        testingModeFeedback2->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback2->setAlignment(Qt::AlignCenter);
        testingModeFeedback2->setWordWrap(true);
        testingModeFeedback2->setVariableAsToolTip(false);
        testingModeFeedback2->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback2->setAddUnits(false);

        gridLayout_12->addWidget(testingModeFeedback2, 0, 3, 2, 1);


        gridLayout_25->addWidget(testingModeGroupBox2, 1, 0, 1, 1);

        Comments2 = new QGroupBox(twoThetaTemp);
        Comments2->setObjectName(QString::fromUtf8("Comments2"));
        sizePolicy2.setHeightForWidth(Comments2->sizePolicy().hasHeightForWidth());
        Comments2->setSizePolicy(sizePolicy2);
        Comments2->setMinimumSize(QSize(0, 0));
        Comments2->setCursor(QCursor(Qt::ArrowCursor));
        Comments2->setAutoFillBackground(false);
        Comments2->setFlat(false);
        Comments2->setCheckable(false);
        gridLayout_13 = new QGridLayout(Comments2);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        sampleName2 = new QLabel(Comments2);
        sampleName2->setObjectName(QString::fromUtf8("sampleName2"));
        sampleName2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_13->addWidget(sampleName2, 0, 0, 1, 1);

        sampleNameVal2 = new QELineEdit(Comments2);
        sampleNameVal2->setObjectName(QString::fromUtf8("sampleNameVal2"));
        sampleNameVal2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sampleNameVal2->setDragEnabled(true);
        sampleNameVal2->setWriteOnLoseFocus(true);
        sampleNameVal2->setVariableAsToolTip(false);
        sampleNameVal2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_13->addWidget(sampleNameVal2, 0, 1, 1, 1);

        userCommentsLabel2 = new QLabel(Comments2);
        userCommentsLabel2->setObjectName(QString::fromUtf8("userCommentsLabel2"));
        userCommentsLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_13->addWidget(userCommentsLabel2, 1, 0, 1, 1);

        userComments2 = new QELineEdit(Comments2);
        userComments2->setObjectName(QString::fromUtf8("userComments2"));
        userComments2->setDragEnabled(true);
        userComments2->setWriteOnLoseFocus(true);
        userComments2->setVariableAsToolTip(false);
        userComments2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_13->addWidget(userComments2, 1, 1, 1, 1);

        expCommentsLabel2 = new QLabel(Comments2);
        expCommentsLabel2->setObjectName(QString::fromUtf8("expCommentsLabel2"));
        expCommentsLabel2->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_13->addWidget(expCommentsLabel2, 2, 0, 1, 1);

        expComments2 = new QELineEdit(Comments2);
        expComments2->setObjectName(QString::fromUtf8("expComments2"));
        expComments2->setDragEnabled(true);
        expComments2->setWriteOnLoseFocus(true);
        expComments2->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_13->addWidget(expComments2, 2, 1, 1, 1);


        gridLayout_25->addWidget(Comments2, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 240, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_25->addItem(verticalSpacer_2, 2, 0, 1, 1);

        Wizard->setPage(8, twoThetaTemp);
        twoThetaSlits = new QWizardPage();
        twoThetaSlits->setObjectName(QString::fromUtf8("twoThetaSlits"));
        gridLayout_19 = new QGridLayout(twoThetaSlits);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        slitConfigurationsGroupBox = new QGroupBox(twoThetaSlits);
        slitConfigurationsGroupBox->setObjectName(QString::fromUtf8("slitConfigurationsGroupBox"));
        sizePolicy2.setHeightForWidth(slitConfigurationsGroupBox->sizePolicy().hasHeightForWidth());
        slitConfigurationsGroupBox->setSizePolicy(sizePolicy2);
        slitConfigurationsGroupBox->setMinimumSize(QSize(0, 0));
        slitConfigurationsGroupBox->setCursor(QCursor(Qt::ArrowCursor));
        slitConfigurationsGroupBox->setAutoFillBackground(false);
        slitConfigurationsGroupBox->setFlat(false);
        slitConfigurationsGroupBox->setCheckable(false);
        gridLayout_18 = new QGridLayout(slitConfigurationsGroupBox);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        initZeroPixelPos = new QLineEdit(slitConfigurationsGroupBox);
        initZeroPixelPos->setObjectName(QString::fromUtf8("initZeroPixelPos"));
        QPalette palette;
        QBrush brush(QColor(200, 200, 200, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(239, 239, 239, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        initZeroPixelPos->setPalette(palette);
        initZeroPixelPos->setAlignment(Qt::AlignCenter);
        initZeroPixelPos->setDragEnabled(true);
        initZeroPixelPos->setReadOnly(true);

        gridLayout_18->addWidget(initZeroPixelPos, 7, 1, 1, 4);

        yStartLabel = new QLabel(slitConfigurationsGroupBox);
        yStartLabel->setObjectName(QString::fromUtf8("yStartLabel"));
        yStartLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(yStartLabel, 4, 0, 1, 1);

        yEnd = new QLineEdit(slitConfigurationsGroupBox);
        yEnd->setObjectName(QString::fromUtf8("yEnd"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        yEnd->setPalette(palette1);
        yEnd->setAlignment(Qt::AlignCenter);
        yEnd->setDragEnabled(true);
        yEnd->setReadOnly(true);

        gridLayout_18->addWidget(yEnd, 4, 4, 1, 1);

        twoThetaOffsetLabel = new QLabel(slitConfigurationsGroupBox);
        twoThetaOffsetLabel->setObjectName(QString::fromUtf8("twoThetaOffsetLabel"));
        twoThetaOffsetLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(twoThetaOffsetLabel, 6, 0, 1, 1);

        initZeroPixelPosLabel = new QLabel(slitConfigurationsGroupBox);
        initZeroPixelPosLabel->setObjectName(QString::fromUtf8("initZeroPixelPosLabel"));
        initZeroPixelPosLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(initZeroPixelPosLabel, 7, 0, 1, 1);

        sampleToDetDis = new QLineEdit(slitConfigurationsGroupBox);
        sampleToDetDis->setObjectName(QString::fromUtf8("sampleToDetDis"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        sampleToDetDis->setPalette(palette2);
        sampleToDetDis->setAlignment(Qt::AlignCenter);
        sampleToDetDis->setDragEnabled(true);
        sampleToDetDis->setReadOnly(true);

        gridLayout_18->addWidget(sampleToDetDis, 5, 1, 1, 4);

        yStart = new QLineEdit(slitConfigurationsGroupBox);
        yStart->setObjectName(QString::fromUtf8("yStart"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        yStart->setPalette(palette3);
        yStart->setAlignment(Qt::AlignCenter);
        yStart->setDragEnabled(true);
        yStart->setReadOnly(true);

        gridLayout_18->addWidget(yStart, 4, 1, 1, 1);

        yEndLabel = new QLabel(slitConfigurationsGroupBox);
        yEndLabel->setObjectName(QString::fromUtf8("yEndLabel"));
        yEndLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(yEndLabel, 4, 3, 1, 1);

        sampleToDetDisLabel = new QLabel(slitConfigurationsGroupBox);
        sampleToDetDisLabel->setObjectName(QString::fromUtf8("sampleToDetDisLabel"));
        sampleToDetDisLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(sampleToDetDisLabel, 5, 0, 1, 1);

        modify = new QPushButton(slitConfigurationsGroupBox);
        modify->setObjectName(QString::fromUtf8("modify"));
        modify->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_18->addWidget(modify, 0, 0, 1, 5);

        twoThetaOffset = new QLineEdit(slitConfigurationsGroupBox);
        twoThetaOffset->setObjectName(QString::fromUtf8("twoThetaOffset"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        twoThetaOffset->setPalette(palette4);
        twoThetaOffset->setAlignment(Qt::AlignCenter);
        twoThetaOffset->setDragEnabled(true);
        twoThetaOffset->setReadOnly(true);

        gridLayout_18->addWidget(twoThetaOffset, 6, 1, 1, 4);

        xAxisRangeLabel = new QLabel(slitConfigurationsGroupBox);
        xAxisRangeLabel->setObjectName(QString::fromUtf8("xAxisRangeLabel"));
        xAxisRangeLabel->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_18->addWidget(xAxisRangeLabel, 1, 0, 1, 1);

        xLabel = new QLabel(slitConfigurationsGroupBox);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout_18->addWidget(xLabel, 1, 3, 1, 1);

        x = new QLineEdit(slitConfigurationsGroupBox);
        x->setObjectName(QString::fromUtf8("x"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        x->setPalette(palette5);
        x->setAlignment(Qt::AlignCenter);
        x->setDragEnabled(true);
        x->setReadOnly(true);

        gridLayout_18->addWidget(x, 1, 4, 1, 1);

        xAxisRange = new QLineEdit(slitConfigurationsGroupBox);
        xAxisRange->setObjectName(QString::fromUtf8("xAxisRange"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        xAxisRange->setPalette(palette6);
        xAxisRange->setAlignment(Qt::AlignCenter);
        xAxisRange->setDragEnabled(true);
        xAxisRange->setReadOnly(true);

        gridLayout_18->addWidget(xAxisRange, 1, 1, 1, 1);


        gridLayout_19->addWidget(slitConfigurationsGroupBox, 4, 0, 1, 1);

        experimentalParameters3 = new QGroupBox(twoThetaSlits);
        experimentalParameters3->setObjectName(QString::fromUtf8("experimentalParameters3"));
        experimentalParameters3->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters3->setAutoFillBackground(false);
        experimentalParameters3->setFlat(false);
        experimentalParameters3->setCheckable(false);
        gridLayout_3 = new QGridLayout(experimentalParameters3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        intervalsLabel3 = new QLabel(experimentalParameters3);
        intervalsLabel3->setObjectName(QString::fromUtf8("intervalsLabel3"));
        intervalsLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(intervalsLabel3, 0, 0, 1, 1);

        intervalsButton3 = new QPushButton(experimentalParameters3);
        intervalsButton3->setObjectName(QString::fromUtf8("intervalsButton3"));
        intervalsButton3->setCursor(QCursor(Qt::PointingHandCursor));
        intervalsButton3->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(intervalsButton3, 0, 3, 1, 1);

        validIntervals3 = new QLabel(experimentalParameters3);
        validIntervals3->setObjectName(QString::fromUtf8("validIntervals3"));
        validIntervals3->setFont(font2);

        gridLayout_3->addWidget(validIntervals3, 0, 4, 1, 1);

        samplesLabel3 = new QLabel(experimentalParameters3);
        samplesLabel3->setObjectName(QString::fromUtf8("samplesLabel3"));
        samplesLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(samplesLabel3, 1, 0, 1, 1);

        samplesButton3 = new QPushButton(experimentalParameters3);
        samplesButton3->setObjectName(QString::fromUtf8("samplesButton3"));
        samplesButton3->setCursor(QCursor(Qt::PointingHandCursor));
        samplesButton3->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(samplesButton3, 1, 3, 1, 1);

        validSamples3 = new QLabel(experimentalParameters3);
        validSamples3->setObjectName(QString::fromUtf8("validSamples3"));
        validSamples3->setFont(font2);

        gridLayout_3->addWidget(validSamples3, 1, 4, 1, 1);

        scansLabel3 = new QLabel(experimentalParameters3);
        scansLabel3->setObjectName(QString::fromUtf8("scansLabel3"));
        scansLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(scansLabel3, 2, 0, 1, 1);

        expFileNameLabel3 = new QLabel(experimentalParameters3);
        expFileNameLabel3->setObjectName(QString::fromUtf8("expFileNameLabel3"));
        expFileNameLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(expFileNameLabel3, 3, 0, 1, 1);

        settlingTimeLabel3 = new QLabel(experimentalParameters3);
        settlingTimeLabel3->setObjectName(QString::fromUtf8("settlingTimeLabel3"));
        settlingTimeLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(settlingTimeLabel3, 4, 0, 1, 1);

        settlingTime3 = new QELineEdit(experimentalParameters3);
        settlingTime3->setObjectName(QString::fromUtf8("settlingTime3"));
        settlingTime3->setAlignment(Qt::AlignCenter);
        settlingTime3->setDragEnabled(true);
        settlingTime3->setWriteOnLoseFocus(true);
        settlingTime3->setVariableAsToolTip(false);
        settlingTime3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        settlingTime3->setProperty("format", QVariant::fromValue(QELineEdit::Floating));

        gridLayout_3->addWidget(settlingTime3, 4, 1, 1, 1);

        settlingTimeUnit3 = new QLabel(experimentalParameters3);
        settlingTimeUnit3->setObjectName(QString::fromUtf8("settlingTimeUnit3"));
        settlingTimeUnit3->setCursor(QCursor(Qt::IBeamCursor));

        gridLayout_3->addWidget(settlingTimeUnit3, 4, 2, 1, 1);

        intervals3 = new QELineEdit(experimentalParameters3);
        intervals3->setObjectName(QString::fromUtf8("intervals3"));
        intervals3->setAlignment(Qt::AlignCenter);
        intervals3->setDragEnabled(true);
        intervals3->setWriteOnLoseFocus(true);
        intervals3->setVariableAsToolTip(false);
        intervals3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        intervals3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_3->addWidget(intervals3, 0, 1, 1, 2);

        samples3 = new QELineEdit(experimentalParameters3);
        samples3->setObjectName(QString::fromUtf8("samples3"));
        samples3->setAlignment(Qt::AlignCenter);
        samples3->setDragEnabled(true);
        samples3->setWriteOnLoseFocus(true);
        samples3->setVariableAsToolTip(false);
        samples3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        samples3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_3->addWidget(samples3, 1, 1, 1, 2);

        scans3 = new QELineEdit(experimentalParameters3);
        scans3->setObjectName(QString::fromUtf8("scans3"));
        scans3->setAlignment(Qt::AlignCenter);
        scans3->setDragEnabled(true);
        scans3->setWriteOnLoseFocus(true);
        scans3->setVariableAsToolTip(false);
        scans3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));
        scans3->setProperty("format", QVariant::fromValue(QELineEdit::Integer));

        gridLayout_3->addWidget(scans3, 2, 1, 1, 2);

        expFileName3 = new QELineEdit(experimentalParameters3);
        expFileName3->setObjectName(QString::fromUtf8("expFileName3"));
        expFileName3->setDragEnabled(true);
        expFileName3->setWriteOnLoseFocus(true);
        expFileName3->setVariableAsToolTip(false);
        expFileName3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_3->addWidget(expFileName3, 3, 1, 1, 2);


        gridLayout_19->addWidget(experimentalParameters3, 0, 0, 1, 1);

        Comments3 = new QGroupBox(twoThetaSlits);
        Comments3->setObjectName(QString::fromUtf8("Comments3"));
        sizePolicy2.setHeightForWidth(Comments3->sizePolicy().hasHeightForWidth());
        Comments3->setSizePolicy(sizePolicy2);
        Comments3->setMinimumSize(QSize(0, 0));
        Comments3->setCursor(QCursor(Qt::ArrowCursor));
        Comments3->setAutoFillBackground(false);
        Comments3->setFlat(false);
        Comments3->setCheckable(false);
        gridLayout_15 = new QGridLayout(Comments3);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        expCommentsLabel3 = new QLabel(Comments3);
        expCommentsLabel3->setObjectName(QString::fromUtf8("expCommentsLabel3"));
        expCommentsLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_15->addWidget(expCommentsLabel3, 2, 0, 1, 1);

        expComments3 = new QELineEdit(Comments3);
        expComments3->setObjectName(QString::fromUtf8("expComments3"));
        expComments3->setDragEnabled(true);
        expComments3->setWriteOnLoseFocus(true);
        expComments3->setVariableAsToolTip(false);
        expComments3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_15->addWidget(expComments3, 2, 1, 1, 1);

        sampleNameVal3 = new QELineEdit(Comments3);
        sampleNameVal3->setObjectName(QString::fromUtf8("sampleNameVal3"));
        sampleNameVal3->setDragEnabled(true);
        sampleNameVal3->setWriteOnLoseFocus(true);
        sampleNameVal3->setVariableAsToolTip(false);
        sampleNameVal3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_15->addWidget(sampleNameVal3, 0, 1, 1, 1);

        userCommentsLabel3 = new QLabel(Comments3);
        userCommentsLabel3->setObjectName(QString::fromUtf8("userCommentsLabel3"));
        userCommentsLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_15->addWidget(userCommentsLabel3, 1, 0, 1, 1);

        sampleName3 = new QLabel(Comments3);
        sampleName3->setObjectName(QString::fromUtf8("sampleName3"));
        sampleName3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_15->addWidget(sampleName3, 0, 0, 1, 1);

        userComments3 = new QELineEdit(Comments3);
        userComments3->setObjectName(QString::fromUtf8("userComments3"));
        userComments3->setDragEnabled(true);
        userComments3->setWriteOnLoseFocus(true);
        userComments3->setVariableAsToolTip(false);
        userComments3->setProperty("displayAlarmStateOption", QVariant::fromValue(QEGenericEdit::Never));

        gridLayout_15->addWidget(userComments3, 1, 1, 1, 1);


        gridLayout_19->addWidget(Comments3, 6, 0, 1, 1);

        testingModeGroupBox3 = new QGroupBox(twoThetaSlits);
        testingModeGroupBox3->setObjectName(QString::fromUtf8("testingModeGroupBox3"));
        sizePolicy2.setHeightForWidth(testingModeGroupBox3->sizePolicy().hasHeightForWidth());
        testingModeGroupBox3->setSizePolicy(sizePolicy2);
        testingModeGroupBox3->setMinimumSize(QSize(0, 0));
        testingModeGroupBox3->setCursor(QCursor(Qt::ArrowCursor));
        testingModeGroupBox3->setAutoFillBackground(false);
        testingModeGroupBox3->setFlat(false);
        testingModeGroupBox3->setCheckable(false);
        gridLayout_14 = new QGridLayout(testingModeGroupBox3);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        testingModeYes3 = new QERadioButton(testingModeGroupBox3);
        testingModeYes3->setObjectName(QString::fromUtf8("testingModeYes3"));
        testingModeYes3->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeYes3->setFocusPolicy(Qt::StrongFocus);
        testingModeYes3->setVariableAsToolTip(false);
        testingModeYes3->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_14->addWidget(testingModeYes3, 0, 1, 1, 1);

        testingModeNo3 = new QERadioButton(testingModeGroupBox3);
        testingModeNo3->setObjectName(QString::fromUtf8("testingModeNo3"));
        testingModeNo3->setCursor(QCursor(Qt::PointingHandCursor));
        testingModeNo3->setFocusPolicy(Qt::StrongFocus);
        testingModeNo3->setVariableAsToolTip(false);
        testingModeNo3->setProperty("displayAlarmStateOption", QVariant::fromValue(QERadioButton::Never));

        gridLayout_14->addWidget(testingModeNo3, 1, 1, 1, 1);

        testingModeLabel3 = new QLabel(testingModeGroupBox3);
        testingModeLabel3->setObjectName(QString::fromUtf8("testingModeLabel3"));
        testingModeLabel3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_14->addWidget(testingModeLabel3, 0, 0, 2, 1);

        tesingMode3 = new QLabel(testingModeGroupBox3);
        tesingMode3->setObjectName(QString::fromUtf8("tesingMode3"));
        tesingMode3->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_14->addWidget(tesingMode3, 0, 2, 2, 1);

        testingModeFeedback3 = new QELabel(testingModeGroupBox3);
        testingModeFeedback3->setObjectName(QString::fromUtf8("testingModeFeedback3"));
        testingModeFeedback3->setCursor(QCursor(Qt::IBeamCursor));
        testingModeFeedback3->setFrameShape(QFrame::StyledPanel);
        testingModeFeedback3->setAlignment(Qt::AlignCenter);
        testingModeFeedback3->setWordWrap(true);
        testingModeFeedback3->setVariableAsToolTip(false);
        testingModeFeedback3->setProperty("displayAlarmStateOption", QVariant::fromValue(QELabel::Never));
        testingModeFeedback3->setAddUnits(false);

        gridLayout_14->addWidget(testingModeFeedback3, 0, 3, 2, 1);


        gridLayout_19->addWidget(testingModeGroupBox3, 5, 0, 1, 1);

        Wizard->setPage(9, twoThetaSlits);
        thetaTwoTheta = new QWizardPage();
        thetaTwoTheta->setObjectName(QString::fromUtf8("thetaTwoTheta"));
        gridLayout_26 = new QGridLayout(thetaTwoTheta);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        experimentalParameters4 = new QGroupBox(thetaTwoTheta);
        experimentalParameters4->setObjectName(QString::fromUtf8("experimentalParameters4"));
        experimentalParameters4->setCursor(QCursor(Qt::ArrowCursor));
        experimentalParameters4->setAutoFillBackground(false);
        experimentalParameters4->setFlat(false);
        experimentalParameters4->setCheckable(false);
        gridLayout_16 = new QGridLayout(experimentalParameters4);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        intervalsLabel4 = new QLabel(experimentalParameters4);
        intervalsLabel4->setObjectName(QString::fromUtf8("intervalsLabel4"));

        gridLayout_16->addWidget(intervalsLabel4, 0, 0, 1, 1);

        intervals4 = new QENumericEdit(experimentalParameters4);
        intervals4->setObjectName(QString::fromUtf8("intervals4"));
        intervals4->setAlignment(Qt::AlignCenter);
        intervals4->setLeadingZeros(0);
        intervals4->setPrecision(0);
        intervals4->setMinimum(0.000000000000000);

        gridLayout_16->addWidget(intervals4, 0, 1, 1, 1);

        intervalsButton4 = new QPushButton(experimentalParameters4);
        intervalsButton4->setObjectName(QString::fromUtf8("intervalsButton4"));

        gridLayout_16->addWidget(intervalsButton4, 0, 2, 1, 1);

        samplesLabel4 = new QLabel(experimentalParameters4);
        samplesLabel4->setObjectName(QString::fromUtf8("samplesLabel4"));

        gridLayout_16->addWidget(samplesLabel4, 1, 0, 1, 1);

        samples4 = new QENumericEdit(experimentalParameters4);
        samples4->setObjectName(QString::fromUtf8("samples4"));
        samples4->setAlignment(Qt::AlignCenter);
        samples4->setLeadingZeros(0);
        samples4->setPrecision(0);
        samples4->setMinimum(0.000000000000000);

        gridLayout_16->addWidget(samples4, 1, 1, 1, 1);

        samplesButton4 = new QPushButton(experimentalParameters4);
        samplesButton4->setObjectName(QString::fromUtf8("samplesButton4"));

        gridLayout_16->addWidget(samplesButton4, 1, 2, 1, 1);

        scansLabel4 = new QLabel(experimentalParameters4);
        scansLabel4->setObjectName(QString::fromUtf8("scansLabel4"));

        gridLayout_16->addWidget(scansLabel4, 2, 0, 1, 1);

        scans4 = new QENumericEdit(experimentalParameters4);
        scans4->setObjectName(QString::fromUtf8("scans4"));
        scans4->setAlignment(Qt::AlignCenter);
        scans4->setLeadingZeros(0);
        scans4->setPrecision(0);
        scans4->setMinimum(0.000000000000000);

        gridLayout_16->addWidget(scans4, 2, 1, 1, 1);

        expFileNameLabel4 = new QLabel(experimentalParameters4);
        expFileNameLabel4->setObjectName(QString::fromUtf8("expFileNameLabel4"));

        gridLayout_16->addWidget(expFileNameLabel4, 3, 0, 1, 1);

        expFileName4 = new QELineEdit(experimentalParameters4);
        expFileName4->setObjectName(QString::fromUtf8("expFileName4"));
        expFileName4->setWriteOnLoseFocus(true);

        gridLayout_16->addWidget(expFileName4, 3, 1, 1, 1);

        settlingTimeLabel4 = new QLabel(experimentalParameters4);
        settlingTimeLabel4->setObjectName(QString::fromUtf8("settlingTimeLabel4"));

        gridLayout_16->addWidget(settlingTimeLabel4, 4, 0, 1, 1);

        settlingTime4 = new QENumericEdit(experimentalParameters4);
        settlingTime4->setObjectName(QString::fromUtf8("settlingTime4"));
        settlingTime4->setAlignment(Qt::AlignCenter);
        settlingTime4->setLeadingZeros(0);
        settlingTime4->setPrecision(0);
        settlingTime4->setMinimum(0.000000000000000);

        gridLayout_16->addWidget(settlingTime4, 4, 1, 1, 1);


        gridLayout_26->addWidget(experimentalParameters4, 0, 0, 1, 1);

        Comments4 = new QGroupBox(thetaTwoTheta);
        Comments4->setObjectName(QString::fromUtf8("Comments4"));
        sizePolicy2.setHeightForWidth(Comments4->sizePolicy().hasHeightForWidth());
        Comments4->setSizePolicy(sizePolicy2);
        Comments4->setMinimumSize(QSize(0, 0));
        Comments4->setCursor(QCursor(Qt::ArrowCursor));
        Comments4->setAutoFillBackground(false);
        Comments4->setFlat(false);
        Comments4->setCheckable(false);
        gridLayout_17 = new QGridLayout(Comments4);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        userCommentsLabel4 = new QLabel(Comments4);
        userCommentsLabel4->setObjectName(QString::fromUtf8("userCommentsLabel4"));

        gridLayout_17->addWidget(userCommentsLabel4, 0, 0, 1, 1);

        userComments4 = new QELineEdit(Comments4);
        userComments4->setObjectName(QString::fromUtf8("userComments4"));
        userComments4->setWriteOnLoseFocus(true);

        gridLayout_17->addWidget(userComments4, 0, 1, 1, 1);

        expCommentsLabel4 = new QLabel(Comments4);
        expCommentsLabel4->setObjectName(QString::fromUtf8("expCommentsLabel4"));

        gridLayout_17->addWidget(expCommentsLabel4, 1, 0, 1, 1);

        expComments4 = new QELineEdit(Comments4);
        expComments4->setObjectName(QString::fromUtf8("expComments4"));
        expComments4->setWriteOnLoseFocus(true);

        gridLayout_17->addWidget(expComments4, 1, 1, 1, 1);


        gridLayout_26->addWidget(Comments4, 1, 0, 1, 1);

        Wizard->setPage(10, thetaTwoTheta);
        finishPage = new QWizardPage();
        finishPage->setObjectName(QString::fromUtf8("finishPage"));
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName(QString::fromUtf8("finishLabel"));
        finishLabel->setGeometry(QRect(10, 10, 161, 16));
        gridLayoutWidget_5 = new QWidget(finishPage);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(10, 590, 441, 41));
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
        QWidget::setTabOrder(settlingTime3, modify);
        QWidget::setTabOrder(modify, xAxisRange);
        QWidget::setTabOrder(xAxisRange, x);
        QWidget::setTabOrder(x, yStart);
        QWidget::setTabOrder(yStart, yEnd);
        QWidget::setTabOrder(yEnd, sampleToDetDis);
        QWidget::setTabOrder(sampleToDetDis, twoThetaOffset);
        QWidget::setTabOrder(twoThetaOffset, initZeroPixelPos);
        QWidget::setTabOrder(initZeroPixelPos, testingModeYes3);
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
#if QT_CONFIG(tooltip)
        Wizard->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        experimentType->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentType->setTitle(QString());
        experimentType->setSubTitle(QString());
#if QT_CONFIG(tooltip)
        experimentSelection->setToolTip(QCoreApplication::translate("Wizard", "Experiment Type: (Users:Proposal, Local:IH)", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentSelection->setTitle(QCoreApplication::translate("Wizard", "Please choose your experiment type", nullptr));
#if QT_CONFIG(tooltip)
        usersExperiment->setToolTip(QCoreApplication::translate("Wizard", "Proposal Experiment", nullptr));
#endif // QT_CONFIG(tooltip)
        usersExperiment->setText(QCoreApplication::translate("Wizard", "Users Experiment", nullptr));
        usersExperiment->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        usersExperiment->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        usersExperiment->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        usersExperiment->setClickCheckedText(QCoreApplication::translate("Wizard", "Users", nullptr));
#if QT_CONFIG(tooltip)
        localExperiment->setToolTip(QCoreApplication::translate("Wizard", "In House Experiment", nullptr));
#endif // QT_CONFIG(tooltip)
        localExperiment->setText(QCoreApplication::translate("Wizard", "Local Experiment", nullptr));
        localExperiment->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        localExperiment->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        localExperiment->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        localExperiment->setClickCheckedText(QCoreApplication::translate("Wizard", "Local", nullptr));
#if QT_CONFIG(tooltip)
        energyCalibraion->setToolTip(QCoreApplication::translate("Wizard", "Energy Calibration", nullptr));
#endif // QT_CONFIG(tooltip)
        energyCalibraion->setText(QCoreApplication::translate("Wizard", "Energy Calibration", nullptr));
        energyCalibraion->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentType", nullptr)));
        energyCalibraion->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        energyCalibraion->setClickText(QCoreApplication::translate("Wizard", "3", nullptr));
        energyCalibraion->setClickCheckedText(QCoreApplication::translate("Wizard", "Energy Calibration", nullptr));
#if QT_CONFIG(tooltip)
        proposalID->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        proposalIDGroupBox->setToolTip(QCoreApplication::translate("Wizard", "Proposal ID", nullptr));
#endif // QT_CONFIG(tooltip)
        proposalIDGroupBox->setTitle(QCoreApplication::translate("Wizard", "Please enter your proposal ID", nullptr));
#if QT_CONFIG(tooltip)
        proposalIDValue->setToolTip(QCoreApplication::translate("Wizard", "Proposal ID, e.g. 20172001", nullptr));
#endif // QT_CONFIG(tooltip)
        proposalIDValue->setPlaceholderText(QCoreApplication::translate("Wizard", "minimum characters 8, e.g. 20172001", nullptr));
        proposalIDValue->setText(QCoreApplication::translate("Wizard", "0", nullptr));
        proposalIDValue->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ProposalID", nullptr)));
        proposalIDValue->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        proposalIDWarning->setToolTip(QCoreApplication::translate("Wizard", "This proposal is not scheduled today!", nullptr));
#endif // QT_CONFIG(tooltip)
        proposalIDWarning->setText(QString());
#if QT_CONFIG(tooltip)
        Yes->setToolTip(QCoreApplication::translate("Wizard", "Proceed", nullptr));
#endif // QT_CONFIG(tooltip)
        Yes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
#if QT_CONFIG(tooltip)
        No->setToolTip(QCoreApplication::translate("Wizard", "Cancel", nullptr));
#endif // QT_CONFIG(tooltip)
        No->setText(QCoreApplication::translate("Wizard", "No", nullptr));
#if QT_CONFIG(tooltip)
        scanningType->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        scanningTypeGroupBox->setToolTip(QCoreApplication::translate("Wizard", "Scanning Type : (TwoTheta Scan, TwoTheta Temperature Scan, TwoTheta Scan with Slits Configurations, ThetaTwoTheta Scan)", nullptr));
#endif // QT_CONFIG(tooltip)
        scanningTypeGroupBox->setTitle(QCoreApplication::translate("Wizard", "Please choose the scanning type", nullptr));
        twoThetaScan->setText(QCoreApplication::translate("Wizard", "2\316\270 Scan", nullptr));
        twoThetaScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaScan->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        twoThetaScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta Step Scan", nullptr));
#if QT_CONFIG(tooltip)
        twoThetaTempScan->setToolTip(QCoreApplication::translate("Wizard", "TwoTheta Temperature Scan", nullptr));
#endif // QT_CONFIG(tooltip)
        twoThetaTempScan->setText(QCoreApplication::translate("Wizard", "2\316\270-Temperature Scan", nullptr));
        twoThetaTempScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaTempScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaTempScan->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        twoThetaTempScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta Temp Scan", nullptr));
#if QT_CONFIG(tooltip)
        twoThetaSlitsScan->setToolTip(QCoreApplication::translate("Wizard", "TwoTheta Scan With Slits Configurations", nullptr));
#endif // QT_CONFIG(tooltip)
        twoThetaSlitsScan->setText(QCoreApplication::translate("Wizard", "2\316\270 Scan with Slits configurations", nullptr));
        twoThetaSlitsScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        twoThetaSlitsScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        twoThetaSlitsScan->setClickText(QCoreApplication::translate("Wizard", "3", nullptr));
        twoThetaSlitsScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Two Theta with Slits Scan", nullptr));
#if QT_CONFIG(tooltip)
        thetaTwoThetaScan->setToolTip(QCoreApplication::translate("Wizard", "ThetaTwoTheta Scan", nullptr));
#endif // QT_CONFIG(tooltip)
        thetaTwoThetaScan->setText(QCoreApplication::translate("Wizard", "\316\270-2\316\270 Scan", nullptr));
        thetaTwoThetaScan->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ScanningType", nullptr)));
        thetaTwoThetaScan->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        thetaTwoThetaScan->setClickText(QCoreApplication::translate("Wizard", "4", nullptr));
        thetaTwoThetaScan->setClickCheckedText(QCoreApplication::translate("Wizard", "Theta Two Theta Scan", nullptr));
#if QT_CONFIG(tooltip)
        configurationsFile->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        configurationsFileGroubBox->setToolTip(QCoreApplication::translate("Wizard", "Create or Load a configurations file", nullptr));
#endif // QT_CONFIG(tooltip)
        configurationsFileGroubBox->setTitle(QCoreApplication::translate("Wizard", "You can create a new configuration file or load existing one", nullptr));
#if QT_CONFIG(tooltip)
        configurationsFileCreate->setToolTip(QCoreApplication::translate("Wizard", "Create a new configurations file", nullptr));
#endif // QT_CONFIG(tooltip)
        configurationsFileCreate->setText(QCoreApplication::translate("Wizard", "Create configuration file", nullptr));
        configurationsFileCreate->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ConfigurationsFile", nullptr)));
        configurationsFileCreate->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        configurationsFileCreate->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        configurationsFileCreate->setClickCheckedText(QCoreApplication::translate("Wizard", "Create", nullptr));
#if QT_CONFIG(tooltip)
        configurationsFileLoad->setToolTip(QCoreApplication::translate("Wizard", "Load a configurations file", nullptr));
#endif // QT_CONFIG(tooltip)
        configurationsFileLoad->setText(QCoreApplication::translate("Wizard", "Load configuration file", nullptr));
        configurationsFileLoad->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ConfigurationsFile", nullptr)));
        configurationsFileLoad->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        configurationsFileLoad->setClickText(QCoreApplication::translate("Wizard", "2", nullptr));
        configurationsFileLoad->setClickCheckedText(QCoreApplication::translate("Wizard", "Load", nullptr));
#if QT_CONFIG(tooltip)
        loadConfigFile->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        loadConfigFileLabel->setText(QCoreApplication::translate("Wizard", "Exp. config file:", nullptr));
#if QT_CONFIG(tooltip)
        expConfigFile->setToolTip(QCoreApplication::translate("Wizard", "Loaded configurations file path", nullptr));
#endif // QT_CONFIG(tooltip)
        expConfigFile->setText(QString());
#if QT_CONFIG(tooltip)
        loadConfigFileButton->setToolTip(QCoreApplication::translate("Wizard", "Browse", nullptr));
#endif // QT_CONFIG(tooltip)
        loadConfigFileButton->setText(QCoreApplication::translate("Wizard", "...", nullptr));
#if QT_CONFIG(tooltip)
        robot->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        robotGroupBox->setTitle(QCoreApplication::translate("Wizard", "Arm Robot", nullptr));
#if QT_CONFIG(tooltip)
        robotYes->setToolTip(QCoreApplication::translate("Wizard", "YES", nullptr));
#endif // QT_CONFIG(tooltip)
        robotYes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        robotYes->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        robotYes->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        robotYes->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        robotYes->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
#if QT_CONFIG(tooltip)
        robotNo->setToolTip(QCoreApplication::translate("Wizard", "NO", nullptr));
#endif // QT_CONFIG(tooltip)
        robotNo->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        robotNo->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        robotNo->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        robotNo->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        robotLabel->setText(QCoreApplication::translate("Wizard", "Use robot", nullptr));
#if QT_CONFIG(tooltip)
        robotInUse->setToolTip(QCoreApplication::translate("Wizard", "Feedback", nullptr));
#endif // QT_CONFIG(tooltip)
        robotInUse->setText(QCoreApplication::translate("Wizard", "Robot in use:", nullptr));
#if QT_CONFIG(tooltip)
        useRobotFeedback->setToolTip(QCoreApplication::translate("Wizard", "Feedback", nullptr));
#endif // QT_CONFIG(tooltip)
        useRobotFeedback->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UseRobot", nullptr)));
        useRobotFeedback->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        experimentalGUI->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        experimentalParameters->setToolTip(QCoreApplication::translate("Wizard", "Scan Parameters", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentalParameters->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        intervalsLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        intervalsButton->setToolTip(QCoreApplication::translate("Wizard", "View Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervalsButton->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#if QT_CONFIG(tooltip)
        validIntervals->setToolTip(QCoreApplication::translate("Wizard", "Number of intervals or intervals table not valid!", nullptr));
#endif // QT_CONFIG(tooltip)
        validIntervals->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        samplesLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of samples <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        samplesButton->setToolTip(QCoreApplication::translate("Wizard", "Select Samples Positions", nullptr));
#endif // QT_CONFIG(tooltip)
        samplesButton->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
#if QT_CONFIG(tooltip)
        validSamples->setToolTip(QCoreApplication::translate("Wizard", "Number of samples or samples choices not valid!", nullptr));
#endif // QT_CONFIG(tooltip)
        validSamples->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        scansLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of scans <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        expFileNameLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. data folder name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        settlingTimeLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        settlingTime->setToolTip(QCoreApplication::translate("Wizard", "Spinner Settling Time", nullptr));
#endif // QT_CONFIG(tooltip)
        settlingTime->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
#if QT_CONFIG(tooltip)
        intervals->setToolTip(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervals->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        samples->setToolTip(QCoreApplication::translate("Wizard", "Samples", nullptr));
#endif // QT_CONFIG(tooltip)
        samples->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Samples", nullptr)));
        samples->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        scans->setToolTip(QCoreApplication::translate("Wizard", "Scans", nullptr));
#endif // QT_CONFIG(tooltip)
        scans->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Scans", nullptr)));
        scans->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        expFileName->setToolTip(QCoreApplication::translate("Wizard", "Experiment Folder Name (special characters not allowed)", nullptr));
#endif // QT_CONFIG(tooltip)
        expFileName->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        testingModeGroupBox->setToolTip(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeGroupBox->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        testingModeLabel->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
#if QT_CONFIG(tooltip)
        testingModeYes->setToolTip(QCoreApplication::translate("Wizard", "YES", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeYes->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        tesingMode->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
#if QT_CONFIG(tooltip)
        testingModeFeedback->setToolTip(QCoreApplication::translate("Wizard", "Feedback", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeFeedback->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        testingModeNo->setToolTip(QCoreApplication::translate("Wizard", "NO", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeNo->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
#if QT_CONFIG(tooltip)
        Comments->setToolTip(QCoreApplication::translate("Wizard", "General Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        Comments->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        sampleName->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        sampleNameVal->setToolTip(QCoreApplication::translate("Wizard", "Sample Name", nullptr));
#endif // QT_CONFIG(tooltip)
        sampleNameVal->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        userCommentsLabel->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
#if QT_CONFIG(tooltip)
        userComments->setToolTip(QCoreApplication::translate("Wizard", "User Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        userComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expCommentsLabel->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
#if QT_CONFIG(tooltip)
        expComments->setToolTip(QCoreApplication::translate("Wizard", "Experiment Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        expComments->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        twoThetaTemp->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentalParameters2->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        intervalsLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        intervals2->setToolTip(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervals2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        intervalsButton2->setToolTip(QCoreApplication::translate("Wizard", "View Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervalsButton2->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#if QT_CONFIG(tooltip)
        validIntervals2->setToolTip(QCoreApplication::translate("Wizard", "Number of intervals or intervals table not valid!", nullptr));
#endif // QT_CONFIG(tooltip)
        validIntervals2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        deadbandLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Temperature deadband <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        deadband->setToolTip(QCoreApplication::translate("Wizard", "Temperature Deadband", nullptr));
#endif // QT_CONFIG(tooltip)
        deadband->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TempDeadband", nullptr)));
        deadband->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expFileNameLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. data folder name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        expFileName2->setToolTip(QCoreApplication::translate("Wizard", "Experiment Folder Name (special characters not allowed)", nullptr));
#endif // QT_CONFIG(tooltip)
        expFileName2->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeLabel2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        settlingTime2->setToolTip(QCoreApplication::translate("Wizard", "Spinner Settling Time", nullptr));
#endif // QT_CONFIG(tooltip)
        settlingTime2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit2->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
        testingModeGroupBox2->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
#if QT_CONFIG(tooltip)
        testingModeYes2->setToolTip(QCoreApplication::translate("Wizard", "YES", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeYes2->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes2->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes2->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
#if QT_CONFIG(tooltip)
        testingModeNo2->setToolTip(QCoreApplication::translate("Wizard", "NO", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeNo2->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo2->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeLabel2->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        tesingMode2->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
#if QT_CONFIG(tooltip)
        testingModeFeedback2->setToolTip(QCoreApplication::translate("Wizard", "Feedback", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeFeedback2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        Comments2->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        sampleName2->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        sampleNameVal2->setToolTip(QCoreApplication::translate("Wizard", "Sample Name", nullptr));
#endif // QT_CONFIG(tooltip)
        sampleNameVal2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        userCommentsLabel2->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
#if QT_CONFIG(tooltip)
        userComments2->setToolTip(QCoreApplication::translate("Wizard", "User Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        userComments2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        expCommentsLabel2->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
#if QT_CONFIG(tooltip)
        expComments2->setToolTip(QCoreApplication::translate("Wizard", "Experiment Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        expComments2->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments2->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        twoThetaSlits->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        slitConfigurationsGroupBox->setTitle(QCoreApplication::translate("Wizard", "Slits Configurations", nullptr));
#if QT_CONFIG(tooltip)
        initZeroPixelPos->setToolTip(QCoreApplication::translate("Wizard", "Initial Zero Pixel Position", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        yStartLabel->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        yStartLabel->setText(QCoreApplication::translate("Wizard", "Y-start", nullptr));
#if QT_CONFIG(tooltip)
        yEnd->setToolTip(QCoreApplication::translate("Wizard", "Y-Axis End Value", nullptr));
#endif // QT_CONFIG(tooltip)
        twoThetaOffsetLabel->setText(QCoreApplication::translate("Wizard", "2\316\270-offset", nullptr));
        initZeroPixelPosLabel->setText(QCoreApplication::translate("Wizard", "Initial zero pixel position", nullptr));
#if QT_CONFIG(tooltip)
        sampleToDetDis->setToolTip(QCoreApplication::translate("Wizard", "Sample To Detector Distance", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        yStart->setToolTip(QCoreApplication::translate("Wizard", "Y-Axis Start Value", nullptr));
#endif // QT_CONFIG(tooltip)
        yEndLabel->setText(QCoreApplication::translate("Wizard", "Y-end", nullptr));
        sampleToDetDisLabel->setText(QCoreApplication::translate("Wizard", "Sample to detector distance", nullptr));
#if QT_CONFIG(tooltip)
        modify->setToolTip(QCoreApplication::translate("Wizard", "Change Slits Configurations", nullptr));
#endif // QT_CONFIG(tooltip)
        modify->setText(QCoreApplication::translate("Wizard", "Modify", nullptr));
#if QT_CONFIG(tooltip)
        twoThetaOffset->setToolTip(QCoreApplication::translate("Wizard", "TwoTheta Offset", nullptr));
#endif // QT_CONFIG(tooltip)
        xAxisRangeLabel->setText(QCoreApplication::translate("Wizard", "X-Axis range", nullptr));
#if QT_CONFIG(tooltip)
        xLabel->setToolTip(QCoreApplication::translate("Wizard", "X-Axis Value", nullptr));
#endif // QT_CONFIG(tooltip)
        xLabel->setText(QCoreApplication::translate("Wizard", "X", nullptr));
#if QT_CONFIG(tooltip)
        x->setToolTip(QCoreApplication::translate("Wizard", "X-Axis Value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        xAxisRange->setToolTip(QCoreApplication::translate("Wizard", "X-Axis Range", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentalParameters3->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        intervalsLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of intervals <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        intervalsButton3->setToolTip(QCoreApplication::translate("Wizard", "View Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervalsButton3->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#if QT_CONFIG(tooltip)
        validIntervals3->setToolTip(QCoreApplication::translate("Wizard", "Number of intervals or intervals table not valid!", nullptr));
#endif // QT_CONFIG(tooltip)
        validIntervals3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        samplesLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of samples <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        samplesButton3->setToolTip(QCoreApplication::translate("Wizard", "Select Samples Positions", nullptr));
#endif // QT_CONFIG(tooltip)
        samplesButton3->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
#if QT_CONFIG(tooltip)
        validSamples3->setToolTip(QCoreApplication::translate("Wizard", "Number of samples or samples choices not valid!", nullptr));
#endif // QT_CONFIG(tooltip)
        validSamples3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p><span style=\" color:#ff0000;\">!</span></p></body></html>", nullptr));
        scansLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Number of scans <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        expFileNameLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Exp. data folder name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
        settlingTimeLabel3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Settling time <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        settlingTime3->setToolTip(QCoreApplication::translate("Wizard", "Spinner Settling Time", nullptr));
#endif // QT_CONFIG(tooltip)
        settlingTime3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)SettlingTime", nullptr)));
        settlingTime3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        settlingTimeUnit3->setText(QCoreApplication::translate("Wizard", "sec", nullptr));
#if QT_CONFIG(tooltip)
        intervals3->setToolTip(QCoreApplication::translate("Wizard", "Intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        intervals3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Intervals", nullptr)));
        intervals3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        samples3->setToolTip(QCoreApplication::translate("Wizard", "Samples", nullptr));
#endif // QT_CONFIG(tooltip)
        samples3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Samples", nullptr)));
        samples3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        scans3->setToolTip(QCoreApplication::translate("Wizard", "Scans", nullptr));
#endif // QT_CONFIG(tooltip)
        scans3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Scans", nullptr)));
        scans3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        expFileName3->setToolTip(QCoreApplication::translate("Wizard", "Experiment Folder Name (special characters not allowed)", nullptr));
#endif // QT_CONFIG(tooltip)
        expFileName3->setPlaceholderText(QCoreApplication::translate("Wizard", "e.g. scanMS01", nullptr));
        expFileName3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentalFileName", nullptr)));
        expFileName3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        Comments3->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        expCommentsLabel3->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
#if QT_CONFIG(tooltip)
        expComments3->setToolTip(QCoreApplication::translate("Wizard", "Experiment Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        expComments3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)ExperimentComments", nullptr)));
        expComments3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        sampleNameVal3->setToolTip(QCoreApplication::translate("Wizard", "Sample Name", nullptr));
#endif // QT_CONFIG(tooltip)
        sampleNameVal3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)Sample", nullptr)));
        sampleNameVal3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        userCommentsLabel3->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        sampleName3->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Sample Name <span style=\" vertical-align:super;\">*</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        userComments3->setToolTip(QCoreApplication::translate("Wizard", "User Comments", nullptr));
#endif // QT_CONFIG(tooltip)
        userComments3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)UserComments", nullptr)));
        userComments3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeGroupBox3->setTitle(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
#if QT_CONFIG(tooltip)
        testingModeYes3->setToolTip(QCoreApplication::translate("Wizard", "YES", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeYes3->setText(QCoreApplication::translate("Wizard", "Yes", nullptr));
        testingModeYes3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeYes3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeYes3->setClickText(QCoreApplication::translate("Wizard", "1", nullptr));
        testingModeYes3->setClickCheckedText(QCoreApplication::translate("Wizard", "Yes", nullptr));
#if QT_CONFIG(tooltip)
        testingModeNo3->setToolTip(QCoreApplication::translate("Wizard", "NO", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeNo3->setText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeNo3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeNo3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
        testingModeNo3->setClickCheckedText(QCoreApplication::translate("Wizard", "No", nullptr));
        testingModeLabel3->setText(QCoreApplication::translate("Wizard", "Testing Mode", nullptr));
        tesingMode3->setText(QCoreApplication::translate("Wizard", "Testing Mode RBV", nullptr));
#if QT_CONFIG(tooltip)
        testingModeFeedback3->setToolTip(QCoreApplication::translate("Wizard", "Feedback", nullptr));
#endif // QT_CONFIG(tooltip)
        testingModeFeedback3->setProperty("variable", QVariant(QCoreApplication::translate("Wizard", "$(P)TestingMode", nullptr)));
        testingModeFeedback3->setProperty("variableSubstitutions", QVariant(QCoreApplication::translate("Wizard", "P=MS:", nullptr)));
#if QT_CONFIG(tooltip)
        thetaTwoTheta->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        experimentalParameters4->setTitle(QCoreApplication::translate("Wizard", "Experiment setup parameters", nullptr));
        intervalsLabel4->setText(QCoreApplication::translate("Wizard", "Number of intervals", nullptr));
        intervalsButton4->setText(QCoreApplication::translate("Wizard", "Intervals", nullptr));
        samplesLabel4->setText(QCoreApplication::translate("Wizard", "Number of samples", nullptr));
        samplesButton4->setText(QCoreApplication::translate("Wizard", "Samples", nullptr));
        scansLabel4->setText(QCoreApplication::translate("Wizard", "Number of scans", nullptr));
        expFileNameLabel4->setText(QCoreApplication::translate("Wizard", "Exp. data folder name *", nullptr));
        settlingTimeLabel4->setText(QCoreApplication::translate("Wizard", "Settling time", nullptr));
        Comments4->setTitle(QCoreApplication::translate("Wizard", "Comments:", nullptr));
        userCommentsLabel4->setText(QCoreApplication::translate("Wizard", "User Comments", nullptr));
        expCommentsLabel4->setText(QCoreApplication::translate("Wizard", "Exp. Comments", nullptr));
#if QT_CONFIG(tooltip)
        finishPage->setToolTip(QCoreApplication::translate("Wizard", "<html><head/><body><p>DAQ Tool | ID09 - MS/XPD (Materials Science/X-ray Powder Diffraction) beamline</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        finishLabel->setText(QCoreApplication::translate("Wizard", "<html><head/><body><p>Press <span style=\" text-decoration: underline;\">F</span>inish to start scan</p></body></html>", nullptr));
        fullFilePath->setText(QCoreApplication::translate("Wizard", "Data path:", nullptr));
#if QT_CONFIG(tooltip)
        filePath->setToolTip(QCoreApplication::translate("Wizard", "Data Destination", nullptr));
#endif // QT_CONFIG(tooltip)
        filePath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Wizard: public Ui_Wizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARD_H
