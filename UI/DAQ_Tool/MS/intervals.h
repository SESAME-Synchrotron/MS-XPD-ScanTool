#ifndef INTERVALS_H
#define INTERVALS_H

#include <QDialog>

#include <iostream>
#include <stdlib.h>
#include <cmath>

#include <qepicspv.h>
#include <client.h>

#include <QCloseEvent>
#include <QTableWidget>

#include <QJsonArray>
#include <QJsonObject>

#include <QSimpleShape.h>

namespace Ui {
class intervals;
}

class intervals : public QDialog
{
    Q_OBJECT

public:

    explicit intervals(QWidget *parent = nullptr);

    ~intervals();

    void enterRows(int row);

    int getRows();

    void clearTable();

    void loadIntervalsFromJson(const QJsonArray& intervalsArray);

    QJsonArray createIntervalsJson();

    void modifyTable();

private slots:

    void setCellBackground(bool val, int row, int col);

    void setBlinking(bool val, QSimpleShape* shape);

    void showIntervalWarning(bool val, int interval);

    void showTempWarning(bool val, int interval);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    QString getColumnKey(int column);

    QString getPVName(int arg);

    bool validateTwoThetaTable();

    bool validateTemperatureTable();

    void validateTable();

    void on_buttonBox_clicked();

    void closeEvent(QCloseEvent *event);

private:

    Ui::intervals *ui;

    QString PV_Prefix = "MS:";

    QString MS_ScanningType   = PV_Prefix + "ScanningType";
    QString MS_Nintervals     = PV_Prefix + "Intervals"   ; int MS_Nintervals_val = 0;
    QString MS_checkTable     = PV_Prefix + "CheckTable"  ; int MS_checkTable_val = 0;

    constexpr static int twoThetaStart           = 0;
    constexpr static int twoThetaEnd             = 1;
    constexpr static int twoThetaStepSize        = 2;
    constexpr static int expousreTime            = 3;
    constexpr static int temperatureStart        = 4;
    constexpr static int temperatureEnd          = 5;
    constexpr static int temperatureStepSize     = 6;
    constexpr static int nScans                  = 7;
    constexpr static int temperatureSettlingTime = 8;

    QEpicsPV* Nintervals     = new QEpicsPV(MS_Nintervals);
    QEpicsPV* checkTable     = new QEpicsPV(MS_checkTable);
    QEpicsPV* scanningType   = new QEpicsPV(MS_ScanningType);

    bool Yes = 1;
    bool No  = 0;
};

#endif // INTERVALS_H
