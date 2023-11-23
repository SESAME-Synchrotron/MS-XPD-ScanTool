#ifndef TWOTHETATEMP_H
#define TWOTHETATEMP_H

#include <QMainWindow>

#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>

#include <QTimer>
#include <QTime>

#include <fstream>
#include <sstream>
#include <QTextStream>
#include <QStringList>

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

    QString mainPath = "/home/control/MS-XPD-ScanTool/";
    QString logFileName = "SED_MS_Scantool.log";
    QString dataPath = mainPath + "DATA/";
    QString scheduledProposalsCSV = mainPath + "metadata/MSScheduledProposals.csv";

    bool closeFlag = 0;

private slots:

    void logs();

    void on_browse_clicked();

    void on_scanStatusVal_dbValueChanged(int out);

    void on_experimentTypeVal_dbValueChanged(int out);

    void on_proposalIDVal_dbValueChanged(const QString &out);

    void on_intervalVal_dbValueChanged(const QString &out);

    void on_totalCollectedScanPointsVal_dbValueChanged(const QString &out);

    void on_spinnerStatusInd_dbValueChanged(bool out);

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_close_clicked();
};
#endif // TWOTHETATEMP_H
