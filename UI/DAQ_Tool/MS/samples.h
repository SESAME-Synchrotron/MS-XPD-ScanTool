#ifndef SAMPLES_H
#define SAMPLES_H

#include <QDialog>

#include <iostream>
#include <stdlib.h>
#include <sstream>

#include <qepicspv.h>
#include <client.h>

#include <QELineEdit.h>
#include <QCheckBox>
#include <QPushButton>
#include <QSimpleShape.h>
#include <QVector>
#include <QCloseEvent>

#include <regex>
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

    QJsonValue getPickingOrder();

    void loadSamplesData(const QJsonArray& samplesArray, const QJsonValue& OrderArray);

    int getSamplesCount();

    void initializing();

    void clearContents();

    int Nsamples;
    bool checkSample;

private slots:

    void on_Sample1_checkBox_stateChanged(int state);

    void on_Sample2_checkBox_stateChanged(int state);

    void on_Sample3_checkBox_stateChanged(int state);

    void on_Sample4_checkBox_stateChanged(int state);

    void on_Sample5_checkBox_stateChanged(int state);

    void on_Sample6_checkBox_stateChanged(int state);

    void on_Sample7_checkBox_stateChanged(int state);

    void on_Sample8_checkBox_stateChanged(int state);

    void on_Sample9_checkBox_stateChanged(int state);

    void on_Sample10_checkBox_stateChanged(int state);

    void on_Sample11_checkBox_stateChanged(int state);

    void on_Sample12_checkBox_stateChanged(int state);

    void on_Sample13_checkBox_stateChanged(int state);

    void on_Sample14_checkBox_stateChanged(int state);

    void on_Sample15_checkBox_stateChanged(int state);

    void on_Sample16_checkBox_stateChanged(int state);

    void on_Sample17_checkBox_stateChanged(int state);

    void on_Sample18_checkBox_stateChanged(int state);

    void on_Sample19_checkBox_stateChanged(int state);

    void on_Sample20_checkBox_stateChanged(int state);

    void on_Sample21_checkBox_stateChanged(int state);

    void on_Sample22_checkBox_stateChanged(int state);

    void on_Sample23_checkBox_stateChanged(int state);

    void on_Sample24_checkBox_stateChanged(int state);

    void on_Sample25_checkBox_stateChanged(int state);

    void on_Sample26_checkBox_stateChanged(int state);

    void on_Sample27_checkBox_stateChanged(int state);

    void on_Sample28_checkBox_stateChanged(int state);

    void on_Sample29_checkBox_stateChanged(int state);

    void on_Sample30_checkBox_stateChanged(int state);

    void on_Sample31_checkBox_stateChanged(int state);

    void on_Sample32_checkBox_stateChanged(int state);

    void on_Sample33_checkBox_stateChanged(int state);

    void on_Sample34_checkBox_stateChanged(int state);

    void on_Sample35_checkBox_stateChanged(int state);

    void on_Sample36_checkBox_stateChanged(int state);

    void on_Sample37_checkBox_stateChanged(int state);

    void on_Sample38_checkBox_stateChanged(int state);

    void on_Sample39_checkBox_stateChanged(int state);

    void on_Sample40_checkBox_stateChanged(int state);

    void checkSamples(int state, int location);

    void on_pickingOrder_textEdited(const QString &order);

    void on_pickingOrderRBV_dbValueChanged(bool out);

    void on_pickingOrderRBV_dbValueChanged(const QString &out);

    void setBorderLineEdit(bool val, QLineEdit *lineEdit);

    void on_buttonBox_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::samples *ui;

    const int container = 40;

    bool Yes = 1;
    bool No  = 0;
    bool pickingOrder = 0;
    bool validOrder = 0;

    QString pickingOrderS;

    QString PV_Prefix = "MS:";
    QString MS_SamplesPositions = PV_Prefix + "SamplesPositions";
    QString MS_PickingOrder     = PV_Prefix + "PickingOrder";

    QVector<QCheckBox*> checkButtons;
    QVector<QELineEdit*> lineEdits;
    QVector<QSimpleShape*> simpleShapes;
    QVector<QCheckBox*> checkedButtons;
    QVector<int> ordering;
};

#endif // SAMPLES_H
