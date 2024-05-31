#include "twothetastep.h"
#include "ui_twothetastep.h"

std::vector<std::string> getLastLines(std::ifstream& in, int n=10)
{
    std::vector<std::string> lines;
    std::string line;

    while(getline(in, line))
    {
        lines.push_back(line);
        if(lines.size() > static_cast<size_t>(n)) lines.erase(lines.begin());
    }
    return lines;
}

TwoThetaStep::TwoThetaStep(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TwoThetaStep)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    ui->missedPointsLabel->setHidden(true);
    ui->missedPointsVal->setHidden(true);

    // read log file every 100 ms
    checkLogs = new QTimer(this);
    this->checkLogs->start(100);
    connect(checkLogs, SIGNAL(timeout()), this, SLOT(logs()));

    // calculate release time from starting time
    elapsed = new QTimer(this);
    this->elapsed->start(950);
    connect(elapsed, &QTimer::timeout, [this]() {
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
    connect(remaining, &QTimer::timeout, [this]() {
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

                if(mins == 1 and secs == 0) ui->scanRemainingTimeVal->setText("00:01:00 (be finished soon)");
                else
                {
                    QTime time(hrs, mins, secs);
                    QString expectedRemainingTime;
                    expectedRemainingTime = (remainingTime >= (24*3600)) ? QString("%1 days %2").arg(days).arg(time.toString("HH:mm:ss")) : QString(time.toString("HH:mm:ss"));
                    ui->scanRemainingTimeVal->setText(expectedRemainingTime);
                    remainingTime--;
                }
            }
            else
            {
                remainingTime = this->remainingTimePV->get().toDouble();
                ui->scanRemainingTimeVal->setText("--:--:--");
            }
        }
        else remainingTime = this->remainingTimePV->get().toDouble();
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
    if(logText.isEmpty()) logText = getLogText(dataPath.toStdString() + ui->SEDPath->text().toStdString() + "/" + ui->SEDPath->text().toStdString() + ".log");
    ui->logs->setText(logText);
}

QString TwoThetaStep::getLogText(const std::string& filePath)
{
    std::ifstream file(filePath);

    if(file)
    {
        std::vector<std::string> lastLines = getLastLines(file);
        QString logs;
        for(const std::string& line : lastLines) logs += QString::fromUtf8(line.c_str()) + "\n";
        return logs;
    }
    return QString();
}

void TwoThetaStep::on_browse_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Browse", dataPath + ui->SEDPath->text());
    QDesktopServices::openUrl(QUrl(file, QUrl::TolerantMode));
}

void TwoThetaStep::on_scanStatusVal_dbValueChanged(int out)
{
    scanStatus = out;

    switch(out)
    {
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
        ui->scanRemainingTimeVal->setText("--:--:--");
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
    bool val = out != 1;
    ui->proposalIDLabel->setHidden(val);
    ui->proposalIDVal->setHidden(val);
    ui->proposalTitleLabel->setHidden(val);
    ui->proposalTitleVal->setHidden(val);
}

void TwoThetaStep::on_proposalIDVal_dbValueChanged(const QString &out)
{
    QFile file(scheduledProposalsCSV);
    QString proposalTitle;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->proposalTitleVal->setText("---");
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

void TwoThetaStep::on_scansVal_dbValueChanged(int out)
{
    bool val = out == 1;
    ui->waitingTimeLabel->setEnabled(!val);
    ui->waitingTimeVal->setEnabled(!val);
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
    ui->robotStatusGroupBox->setHidden(!out);
    ui->allSamplesTotalCollectedScanPointsLabel->setHidden(!out);
    ui->allSamplesTotalCollectedScanPointsVal->setHidden(!out);
    ui->GIXRDLabel->setHidden(out);
    ui->GIXRDVal->setHidden(out);
    ui->intervalRemainingTimeLabel->setText(out ? "<html><head/><body><p>Expected Remaining Time <span style=\" font-weight:600; vertical-align:sub;\">(for the current sample)</span></p></body></html>" :
                                                  "<html><head/><body><p>Expected Remaining Time</p></body></html>");
}

void TwoThetaStep::on_skippedVal_dbValueChanged(const QString &out)
{
    bool val = out == "0" or out == "---";

    ui->skippedLabel->setHidden(val);
    ui->skippedVal->setHidden(val);
    ui->skippedInd->setHidden(val);

    if(!val)
    {
        ui->skippedInd->setColour0Property(QColor(255,255,0));
        ui->skippedInd->setFlashProperty(0, true);
        ui->skippedInd->setFlashRate(QEScanTimers::Medium);
    }
}

void TwoThetaStep::on_notReturnVal_dbValueChanged(const QString &out)
{
    bool val = out == "0" or out == "---";

    ui->notReturnLabel->setHidden(val);
    ui->notReturnVal->setHidden(val);
    ui->notReturnInd->setHidden(val);

    if(!val)
    {
        ui->notReturnInd->setColour0Property(QColor(255,255,0));
        ui->notReturnInd->setFlashProperty(0, true);
        ui->notReturnInd->setFlashRate(QEScanTimers::Medium);
    }
}

void TwoThetaStep::on_SCVal_dbValueChanged(int out)
{
    ui->SCPos->setText(out%9 == 0? QString(out/9+9) : "---");
}

void TwoThetaStep::on_spinnerStatusInd_dbValueChanged(bool out)
{
    ui->spinnerStatusVal->setText(out ? "not move" : "moving");
}

void TwoThetaStep::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) event->ignore();
}

void TwoThetaStep::closeEvent(QCloseEvent *event)
{
    if(!closeFlag) event->ignore();
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
