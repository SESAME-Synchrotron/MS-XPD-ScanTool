#include "twothetaslits.h"
#include "ui_twothetaslits.h"

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

TwoThetaSlits::TwoThetaSlits(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TwoThetaSlits)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());   // fix the window size;

    ui->missedPointsLabel->setHidden(true);
    ui->missedPointsVal->setHidden(true);

    // read log file every 100 ms
    checkLogs = new QTimer(this);
    this->checkLogs->start(100);
    connect(checkLogs, SIGNAL(timeout()), this, SLOT(logs()));

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

    // calculate remaining time
    remainingTime = this->remainingTimePV->get().toDouble();
    remaining = new QTimer(this);
    this->remaining->start(990);
    connect(remaining, &QTimer::timeout, [this]() mutable {
        if(scanStatus == 1)
        {
            if(remainingTime > 0)
            {
                int days = static_cast<int>(remainingTime / 86400);
                double remainingSeconds = fmod(remainingTime, 86400);
                int hrs = static_cast<int>(remainingSeconds / 3600);
                remainingSeconds = fmod(remainingSeconds, 3600);
                int mins = static_cast<int>(remainingSeconds / 60);
                int secs = static_cast<int>(fmod(remainingSeconds, 60));

                 QTime time(hrs, mins, secs);

                 QString expectedRemainingTime;
                if(remainingTime >= (24*3600))
                    expectedRemainingTime = QString("%1 days %2").arg(days).arg(time.toString("HH:mm:ss"));
                else
                    expectedRemainingTime = QString(time.toString("HH:mm:ss"));

                ui->scanRemainingTimeVal->setText(expectedRemainingTime);

                remainingTime -= 1;
            }
            else
            {
                remainingTime = this->remainingTimePV->get().toDouble();
                ui->scanRemainingTimeVal->setText("--:--:--");
            }
        }
        else
            remainingTime = this->remainingTimePV->get().toDouble();
    });
}

TwoThetaSlits::~TwoThetaSlits()
{
    delete ui;
}

void TwoThetaSlits::logs()
{
    QString logText;
    logText = getLogText(mainPath.toStdString() + logFileName.toStdString());

    if(logText.isEmpty())
        logText = getLogText(dataPath.toStdString() + ui->SEDPath->text().toStdString() + "/" + ui->SEDPath->text().toStdString() + ".log");

    ui->logs->setText(logText);
}

QString TwoThetaSlits::getLogText(const string& filePath)
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

void TwoThetaSlits::on_browse_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Browse", dataPath + ui->SEDPath->text());
    QDesktopServices::openUrl(QUrl(file, QUrl::TolerantMode));
}

void TwoThetaSlits::on_scanStatusVal_dbValueChanged(int out)
{
    scanStatus = out;

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

void TwoThetaSlits::on_experimentTypeVal_dbValueChanged(int out)
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

void TwoThetaSlits::on_proposalIDVal_dbValueChanged(const QString &out)
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

void TwoThetaSlits::on_intervalVal_dbValueChanged(const QString &out)
{
    ui->twoThetaStartVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaEndVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaStepSizeVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->exposureTimeVal->setVariableNameSubstitutionsProperty("N=" + out);
}

void TwoThetaSlits::checkMissedPoints()
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

void TwoThetaSlits::on_robotInUseVal_dbValueChanged(bool out)
{
    if(out)
    {
        ui->robotStatusGroupBox->setHidden(false);
        ui->allSamplesTotalCollectedScanPointsLabel->setHidden(false);
        ui->allSamplesTotalCollectedScanPointsVal->setHidden(false);
        ui->intervalRemainingTimeLabel->setText("<html><head/><body><p>Expected Remaining Time <span style=\" font-weight:600; vertical-align:sub;\">(for the current sample)</span></p></body></html>");
    }
    else
    {
        ui->robotStatusGroupBox->setHidden(true);
        ui->allSamplesTotalCollectedScanPointsLabel->setHidden(true);
        ui->allSamplesTotalCollectedScanPointsVal->setHidden(true);
        ui->intervalRemainingTimeLabel->setText("<html><head/><body><p>Expected Remaining Time</p></body></html>");
    }
}

void TwoThetaSlits::on_skippedVal_dbValueChanged(const QString &out)
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

void TwoThetaSlits::on_notReturnVal_dbValueChanged(const QString &out)
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

void TwoThetaSlits::on_spinnerStatusInd_dbValueChanged(bool out)
{
    if(out)
        ui->spinnerStatusVal->setText("not move");
    else
        ui->spinnerStatusVal->setText("moving");
}

void TwoThetaSlits::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        event->ignore();    // ignore the Escape button press event
}

void TwoThetaSlits::closeEvent(QCloseEvent *event)
{
    if(!closeFlag)
        event->ignore();       // Ignore the close event
}

void TwoThetaSlits::on_close_clicked()
{
    QMessageBox::StandardButton val;
    val = QMessageBox::question(this, "Alert", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No);

    if(val == QMessageBox::Yes)
    {
        closeFlag = 1;
        this->close();
    }
}
