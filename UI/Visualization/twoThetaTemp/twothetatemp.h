#ifndef TWOTHETATEMP_H
#define TWOTHETATEMP_H

#include <QMainWindow>

#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>

#include <QTimer>
#include <QTime>

#include <qepicspv.h>

#include <fstream>
#include <sstream>
#include <QTextStream>
#include <QStringList>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class TwoThetaTemp; }
QT_END_NAMESPACE

class TwoThetaTemp : public QMainWindow
{
    Q_OBJECT

public:
    TwoThetaTemp(QWidget *parent = nullptr);
    ~TwoThetaTemp();

private:
    Ui::TwoThetaTemp *ui;

    QString getLogText(const std::string& filePath);

    QTimer* checkLogs;
    QTimer* elapsed;
    QTimer* remaining;

    QString mainPath = "/home/control/MS-XPD-ScanTool/";
    QString logFileName = "SED_MS_Scantool.log";
    QString dataPath = mainPath + "DATA/";
    QString scheduledProposalsCSV = mainPath + "metadata/MSScheduledProposals.csv";
    QString remainingTimeStr = "MS:ScanRemTime";

    QEpicsPV* remainingTimePV = new QEpicsPV(remainingTimeStr);

    double remainingTime;
    int scanStatus;

    bool closeFlag = 0;

private slots:

    void logs();

    void on_browse_clicked();

    void on_scanStatusVal_dbValueChanged(int out);

    void on_experimentTypeVal_dbValueChanged(int out);

    void on_proposalIDVal_dbValueChanged(const QString &out);

    void on_intervalVal_dbValueChanged(const QString &out);

    void checkMissedPoints();

    void on_spinnerStatusInd_dbValueChanged(bool out);

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_close_clicked();
};
#endif // TWOTHETATEMP_H
