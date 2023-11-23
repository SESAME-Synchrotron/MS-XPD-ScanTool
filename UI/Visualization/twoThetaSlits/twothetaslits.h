#ifndef TWOTHETASLITS_H
#define TWOTHETASLITS_H

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
namespace Ui { class TwoThetaSlits; }
QT_END_NAMESPACE

class TwoThetaSlits : public QMainWindow
{
    Q_OBJECT

public:
    TwoThetaSlits(QWidget *parent = nullptr);
    ~TwoThetaSlits();

private:
    Ui::TwoThetaSlits *ui;

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

    void checkMissedPoints();

    void on_robotInUseVal_dbValueChanged(bool out);

    void on_skippedVal_dbValueChanged(const QString &out);

    void on_notReturnVal_dbValueChanged(const QString &out);

    void on_spinnerStatusInd_dbValueChanged(bool out);

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_close_clicked();
};
#endif // TWOTHETASLITS_H
