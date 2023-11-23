#include "twothetastep.h"
#include "ui_twothetastep.h"

using namespace std;

vector<string> getLastLines(ifstream& in, int n=10)
{
    // read last 10 lines from log file

    vector<string> lines;
    string line;

    while(getline(in, line))
    {
        lines.push_back(line);
        if(lines.size() > static_cast<size_t>(n))
            lines.erase(lines.begin());     // remove the oldest line if more than n lines are stored
    }

    return lines;
}

TwoThetaStep::TwoThetaStep(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TwoThetaStep)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());   // fix the window size;

    ui->missedPointsLabel->setHidden(true);
    ui->missedPointsVal->setHidden(true);

    // read log file every 100 ms
    checkLogs = new QTimer(this);
    this->checkLogs->start(100);
    connect(checkLogs,SIGNAL(timeout()),this,SLOT(logs()));

    // calculate release time from starting time
    elapsed = new QTimer(this);
    this->elapsed->start(950);
    connect(elapsed, &QTimer::timeout, [this]() mutable {
        if(ui->startTimeVal->text() != "---" and ui->endTimeVal->text() == "---")
        {
            int sec = QTime::fromString(ui->startTimeVal->text(), "hh:mm:ss").secsTo(QTime::currentTime());
            QTime elapsedTime(0, 0, 0);
            elapsedTime = elapsedTime.addSecs(sec);
            ui->elapsedTimeVal->setText(elapsedTime.toString("hh:mm:ss"));
        }
    });
}

TwoThetaStep::~TwoThetaStep()
{
    delete ui;
}

void TwoThetaStep::logs()
{
    QString logText;
    logText = getLogText(mainPath.toStdString() + logFileName.toStdString());

    if(logText.isEmpty())
        logText = getLogText(dataPath.toStdString() + ui->SEDPath->text().toStdString() + "/" + ui->SEDPath->text().toStdString() + ".log");

    ui->logs->setText(logText);
}

QString TwoThetaStep::getLogText(const string& filePath)
{
    ifstream file(filePath);

    if(file)
    {
        vector<string> lastLines = getLastLines(file);
        QString logs;

        for(const string& line : lastLines)
            logs += QString::fromUtf8(line.c_str()) + "\n";

        return logs;
    }

    return QString();   // return an empty string if the file cannot be opened
}

void TwoThetaStep::on_browse_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Browse", dataPath + ui->SEDPath->text());
    QDesktopServices::openUrl(QUrl(file, QUrl::TolerantMode));
}

void TwoThetaStep::on_scanStatusVal_dbValueChanged(int out)
{
    switch (out) {

    case 0:
        ui->pause->setEnabled(false);
        ui->resume->setEnabled(false);
        ui->stop->setEnabled(false);
        ui->scanStatusInd->setColour0Property(QColor(200,200,200));
        ui->scanStatusInd->setFlashProperty(0, false);
        break;
    case 1:
        ui->pause->setEnabled(true);
        ui->resume->setEnabled(false);
        ui->stop->setEnabled(true);
        ui->scanStatusInd->setColour0Property(QColor(0,255,0));
        ui->scanStatusInd->setFlashProperty(0, false);
        break;
    case 2:
        checkMissedPoints();
        ui->pause->setEnabled(false);
        ui->resume->setEnabled(false);
        ui->stop->setEnabled(false);
        ui->scanStatusInd->setColour0Property(QColor(0,0,255));
        ui->scanStatusInd->setFlashProperty(0, false);
        break;
    case 3:
        ui->pause->setEnabled(true);
        ui->resume->setEnabled(true);
        ui->stop->setEnabled(true);
        ui->scanStatusInd->setColour0Property(QColor(255,255,0));
        ui->scanStatusInd->setFlashProperty(0, true);
        ui->scanStatusInd->setFlashRate(QEScanTimers::Medium);
        break;
    case 4:
        ui->pause->setEnabled(false);
        ui->resume->setEnabled(false);
        ui->stop->setEnabled(true);
        ui->scanStatusInd->setColour0Property(QColor(255,0,0));
        ui->scanStatusInd->setFlashProperty(0, true);
        ui->scanStatusInd->setFlashRate(QEScanTimers::Fast);
        break;
    case 5:
        ui->stop->setEnabled(false);
        ui->pause->setEnabled(false);
        ui->resume->setEnabled(false);
        ui->scanStatusInd->setColour0Property(QColor(255,0,0));
        ui->scanStatusInd->setFlashProperty(0, true);
        ui->scanStatusInd->setFlashRate(QEScanTimers::VeryFast);
        break;
    }
}

void TwoThetaStep::on_experimentTypeVal_dbValueChanged(int out)
{
    if(out != 1)
    {
        ui->proposalIDLabel->setHidden(true);
        ui->proposalIDVal->setHidden(true);
        ui->proposalTitleLabel->setHidden(true);
        ui->proposalTitleVal->setHidden(true);
    }
    else
    {
        ui->proposalIDLabel->setHidden(false);
        ui->proposalIDVal->setHidden(false);
        ui->proposalTitleLabel->setHidden(false);
        ui->proposalTitleVal->setHidden(false);
}
}

void TwoThetaStep::on_proposalIDVal_dbValueChanged(const QString &out)
{
    QFile file(scheduledProposalsCSV);
    QString proposalTitle;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        ui->proposalTitleVal->setText("---");
    else {
           QTextStream in(&file);

           while(!in.atEnd())
           {
               QString line = in.readLine();
               QStringList fields = line.split(",");
               QString ID = fields.at(0).trimmed();
               QString title = fields.at(1).trimmed();;
               if(ID == out)
               {
                   proposalTitle = title;
                   break;
               }
           }
    file.close();
    ui->proposalTitleVal->setText(proposalTitle);
    }
}

void TwoThetaStep::on_intervalVal_dbValueChanged(const QString &out)
{
    ui->twoThetaStartVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaEndVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaStepSizeVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->exposureTimeVal->setVariableNameSubstitutionsProperty("N=" + out);
}

void TwoThetaStep::checkMissedPoints()
{
    QStringList points = ui->totalCollectedScanPointsVal->text().split('/');
    int collected = points[0].toInt();
    int total = points[1].toInt();

    if(collected != total)
    {
        ui->missedPointsLabel->setHidden(false);
        ui->missedPointsVal->setHidden(false);
    }
}

void TwoThetaStep::on_robotInUseVal_dbValueChanged(bool out)
{
    if(out)
    {
        ui->robotStatusGroupBox->setHidden(false);
        ui->allSamplesTotalCollectedScanPointsLabel->setHidden(false);
        ui->allSamplesTotalCollectedScanPointsVal->setHidden(false);
    }
    else
    {
        ui->robotStatusGroupBox->setHidden(true);
        ui->allSamplesTotalCollectedScanPointsLabel->setHidden(true);
        ui->allSamplesTotalCollectedScanPointsVal->setHidden(true);
    }
}

void TwoThetaStep::on_skippedVal_dbValueChanged(const QString &out)
{
    if(out == "0" or out == "---")
    {
        ui->skippedLabel->setHidden(true);
        ui->skippedVal->setHidden(true);;
        ui->skippedInd->setHidden(true);
    }
    else
    {
        ui->skippedLabel->setHidden(false);
        ui->skippedVal->setHidden(false);
        ui->skippedInd->setColour0Property(QColor(255,255,0));
        ui->skippedInd->setFlashProperty(0, true);
        ui->skippedInd->setFlashRate(QEScanTimers::Medium);
        ui->skippedInd->setHidden(false);
    }
}

void TwoThetaStep::on_notReturnVal_dbValueChanged(const QString &out)
{
    if(out == "0" or out == "---")
    {
        ui->notReturnLabel->setHidden(true);
        ui->notReturnVal->setHidden(true);
        ui->notReturnInd->setHidden(true);
    }
    else
    {
        ui->notReturnLabel->setHidden(false);
        ui->notReturnVal->setHidden(false);
        ui->notReturnInd->setColour0Property(QColor(255,255,0));
        ui->notReturnInd->setFlashProperty(0, true);
        ui->notReturnInd->setFlashRate(QEScanTimers::Medium);
        ui->notReturnInd->setHidden(false);
    }
}

void TwoThetaStep::on_spinnerStatusInd_dbValueChanged(bool out)
{
    if(out)
        ui->spinnerStatusVal->setText("not move");
    else
        ui->spinnerStatusVal->setText("moving");
}

void TwoThetaStep::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        event->ignore();    // ignore the Escape button press event
}

void TwoThetaStep::closeEvent(QCloseEvent *event)
{
    if(!closeFlag)
        event->ignore();       // Ignore the close event
}

void TwoThetaStep::on_close_clicked()
{
    QMessageBox::StandardButton val;
    val = QMessageBox::question(this, "Alert", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No);

    if(val == QMessageBox::Yes)
    {
        closeFlag = 1;
        this->close();
    }
}
