#ifndef SAMPLES_H
#define SAMPLES_H

#include <QDialog>

#include <iostream>
#include "stdlib.h"

#include <qepicspv.h>
#include <client.h>

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "QSimpleShape.h"
#include <QVector>
#include <QCloseEvent>

#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class samples;
}

class samples : public QDialog
{
    Q_OBJECT

public:

    explicit samples(QWidget *parent = nullptr);
    ~samples();

    QJsonArray getSamplesData();

    void loadSamplesData(const QJsonArray& samplesArray);

    int getCheckCount();

    void clearContents();

private slots:

    void initializing();

    void on_Sample1_checkBox_stateChanged(int arg1);

    void on_Sample2_checkBox_stateChanged(int arg1);

    void on_Sample3_checkBox_stateChanged(int arg1);

    void on_Sample4_checkBox_stateChanged(int arg1);

    void on_Sample5_checkBox_stateChanged(int arg1);

    void on_Sample6_checkBox_stateChanged(int arg1);

    void on_Sample7_checkBox_stateChanged(int arg1);

    void on_Sample8_checkBox_stateChanged(int arg1);

    void on_Sample9_checkBox_stateChanged(int arg1);

    void on_Sample10_checkBox_stateChanged(int arg1);

    void on_Sample11_checkBox_stateChanged(int arg1);

    void on_Sample12_checkBox_stateChanged(int arg1);

    void on_Sample13_checkBox_stateChanged(int arg1);

    void on_Sample14_checkBox_stateChanged(int arg1);

    void on_Sample15_checkBox_stateChanged(int arg1);

    void on_Sample16_checkBox_stateChanged(int arg1);

    void on_Sample17_checkBox_stateChanged(int arg1);

    void on_Sample18_checkBox_stateChanged(int arg1);

    void on_Sample19_checkBox_stateChanged(int arg1);

    void on_Sample20_checkBox_stateChanged(int arg1);

    void on_Sample21_checkBox_stateChanged(int arg1);

    void on_Sample22_checkBox_stateChanged(int arg1);

    void on_Sample23_checkBox_stateChanged(int arg1);

    void on_Sample24_checkBox_stateChanged(int arg1);

    void on_Sample25_checkBox_stateChanged(int arg1);

    void on_Sample26_checkBox_stateChanged(int arg1);

    void on_Sample27_checkBox_stateChanged(int arg1);

    void on_Sample28_checkBox_stateChanged(int arg1);

    void on_Sample29_checkBox_stateChanged(int arg1);

    void on_Sample30_checkBox_stateChanged(int arg1);

    void on_Sample31_checkBox_stateChanged(int arg1);

    void on_Sample32_checkBox_stateChanged(int arg1);

    void on_Sample33_checkBox_stateChanged(int arg1);

    void on_Sample34_checkBox_stateChanged(int arg1);

    void on_Sample35_checkBox_stateChanged(int arg1);

    void on_Sample36_checkBox_stateChanged(int arg1);

    void on_Sample37_checkBox_stateChanged(int arg1);

    void on_Sample38_checkBox_stateChanged(int arg1);

    void on_Sample39_checkBox_stateChanged(int arg1);

    void on_Sample40_checkBox_stateChanged(int arg1);

    void checkSamples(int arg, QLineEdit* lineEdit, QSimpleShape* simpleShape);

    void on_buttonBox_clicked();

    void closeEvent(QCloseEvent *event);

//    void keyPressEvent(QKeyEvent *event);

    void on_OK_clicked();

private:
    Ui::samples *ui;

    QString PV_Prefix = "MS:";

    QString MS_Samples            = PV_Prefix + "Samples"           ; int MS_Samples_val            = 0;
    QString MS_CheckSamples       = PV_Prefix + "CheckSamples"      ; int MS_CheckSamples_val       = 0;

    QEpicsPV* sample         = new QEpicsPV(MS_Samples);
    QEpicsPV* checkSample    = new QEpicsPV(MS_CheckSamples);

    QVector<QCheckBox*> checkButtons;
    QVector<QLineEdit*> lineEdits;
    QVector<QSimpleShape*> simpleShapes;

    bool Yes = 1;
    bool No  = 0;
};

#endif // SAMPLES_H
