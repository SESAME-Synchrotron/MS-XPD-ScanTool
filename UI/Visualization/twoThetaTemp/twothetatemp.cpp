#include "twothetatemp.h"
#include "ui_twothetatemp.h"

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

TwoThetaTemp::TwoThetaTemp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TwoThetaTemp)
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

                if(mins == 1 and secs == 0)
                    ui->scanRemainingTimeVal->setText("00:01:00 (be finished soon)");
                else
                {
                    QTime time(hrs, mins, secs);
                    QString expectedRemainingTime;

                    if(remainingTime >= (24*3600))
                        expectedRemainingTime = QString("%1 days %2").arg(days).arg(time.toString("HH:mm:ss"));
                    else
                        expectedRemainingTime = QString(time.toString("HH:mm:ss"));

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
        else
            remainingTime = this->remainingTimePV->get().toDouble();
    });
}

TwoThetaTemp::~TwoThetaTemp()
{
    delete ui;
}

void TwoThetaTemp::logs()
{
    QString logText;
    logText = getLogText(mainPath.toStdString() + logFileName.toStdString());

    if(logText.isEmpty())
        logText = getLogText(dataPath.toStdString() + ui->SEDPath->text().toStdString() + "/" + ui->SEDPath->text().toStdString() + ".log");

    ui->logs->setText(logText);
}

QString TwoThetaTemp::getLogText(const string& filePath)
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

void TwoThetaTemp::on_browse_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Browse", dataPath + ui->SEDPath->text());
    QDesktopServices::openUrl(QUrl(file, QUrl::TolerantMode));
}

void TwoThetaTemp::on_scanStatusVal_dbValueChanged(int out)
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

void TwoThetaTemp::on_experimentTypeVal_dbValueChanged(int out)
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

void TwoThetaTemp::on_proposalIDVal_dbValueChanged(const QString &out)
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

void TwoThetaTemp::on_intervalVal_dbValueChanged(const QString &out)
{
    ui->twoThetaStartVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaEndVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->twoThetaStepSizeVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->exposureTimeVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->tStartVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->tEndVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->tStepSizeVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->scansVal->setVariableNameSubstitutionsProperty("N=" + out);
    ui->waitingTimeVal->setVariableNameSubstitutionsProperty("N=" + out);
}

void TwoThetaTemp::checkMissedPoints()
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

void TwoThetaTemp::on_spinnerStatusInd_dbValueChanged(bool out)
{
    if(out)
        ui->spinnerStatusVal->setText("not move");
    else
        ui->spinnerStatusVal->setText("moving");
}

void TwoThetaTemp::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        event->ignore();    // ignore the Escape button press event
}

void TwoThetaTemp::closeEvent(QCloseEvent *event)
{
    if(!closeFlag)
        event->ignore();       // Ignore the close event
}

void TwoThetaTemp::on_close_clicked()
{
    QMessageBox::StandardButton val;
    val = QMessageBox::question(this, "Alert", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No);

    if(val == QMessageBox::Yes)
    {
        closeFlag = 1;
        this->close();
    }
}
