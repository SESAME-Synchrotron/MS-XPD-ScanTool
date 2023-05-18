#ifndef INTERVALS_H
#define INTERVALS_H

#include <QDialog>

#include <iostream>
#include "stdlib.h"

#include <qepicspv.h>
#include <client.h>

#include <QCloseEvent>
#include <QAbstractButton>
#include <QMessageBox>
#include <QPushButton>

#include <regex>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>

namespace Ui {
class intervals;
}

class intervals : public QDialog
{
    Q_OBJECT

public:

    explicit intervals(QWidget *parent = nullptr);

    ~intervals();

    void setCellBackground(bool val, int row, int col);

    void UImessage(const QString &tittle , const QString &message);

    void enterRows(int row);

    int getRows();

    void loadData(QString fileName);

    void loadIntervalsFromJson(const QJsonArray& intervalsArray);

    QJsonArray createIntervalsJson();

    void validateTable();

private slots:

    void initializing();

    void on_tableWidget_cellChanged();

    void on_tableWidget_itemSelectionChanged();

    void on_buttonBox_clicked();

    void closeEvent(QCloseEvent *event);

private:

    Ui::intervals *ui;

    QString PV_Prefix = "MS:";

    QString MS_Nintervals =  PV_Prefix + "Intervals"  ; int MS_Nintervals_val = 0;
    QString MS_checkTable =  PV_Prefix + "CheckTable" ; int MS_checkTable_val = 0;

    QString UItittle = "Intervals";
    QString workingDir = "/home/dcasu/XRD-Scan/UI/DAQ_Tool/MS/";

    QEpicsPV* Nintervals     = new QEpicsPV(MS_Nintervals);
    QEpicsPV* checkTable     = new QEpicsPV(MS_checkTable);

    bool Yes = 1;
    bool No  = 0;
};

#endif // INTERVALS_H
