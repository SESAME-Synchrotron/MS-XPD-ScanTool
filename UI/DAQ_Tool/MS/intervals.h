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
#include <QRegExp>

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

    void loadIntervalsFromJson(const QJsonArray &intervalsArray, int type);

    QJsonArray createIntervalsJson(int type);

    void modifyTable(int type);

    bool checkTable;

private slots:

    void setCellBackground(bool val, int row, int col);

    void setBlinking(bool val, QSimpleShape *shape);

    void showIntervalWarning(bool val, int interval);

    void showTempWarning(bool val, int interval);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    QString getColumnKey(int column);

    QString getPVName(int name);

    bool validateTwoThetaTable();

    bool validateTemperatureTable();

    void validateTable();

    void on_buttonBox_clicked();

    void closeEvent(QCloseEvent *event);

private:

    Ui::intervals *ui;

    constexpr static int twoThetaStart           = 0;
    constexpr static int twoThetaEnd             = 1;
    constexpr static int twoThetaStepSize        = 2;
    constexpr static int expousreTime            = 3;
    constexpr static int temperatureStart        = 4;
    constexpr static int temperatureEnd          = 5;
    constexpr static int temperatureStepSize     = 6;
    constexpr static int nScans                  = 7;
    constexpr static int waitingTime = 8;

    bool Yes = 1;
    bool No  = 0;

    QString PV_Prefix = "MS:";
    QString MS_ScanningType   = PV_Prefix + "ScanningType";

    QEpicsPV* scanningType   = new QEpicsPV(MS_ScanningType);
};

#endif // INTERVALS_H
