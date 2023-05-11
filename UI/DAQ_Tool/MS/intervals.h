#ifndef INTERVALS_H
#define INTERVALS_H

#include <QDialog>
#include <qepicspv.h>
#include <QTableWidget>
#include <QAbstractButton>
#include <QJsonArray>
//#include "wizard.h"

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

public slots:

    void on_buttonBox_clicked(QAbstractButton *button);

private slots:

    void initializing();                // initialize the table at startup

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_itemSelectionChanged();

private:

    Ui::intervals *ui;

    QString MS_checkTable = "MS:CheckTable" ; int MS_checkTable_val = 0;

    QString UItittle = "Intervals";
    QString workingDir = "/home/dcasu/UI/DAQ_Tool/MS/";

    QEpicsPV* Nintervals     = new QEpicsPV("MS:Intervals");
    QEpicsPV* checkTable     = new QEpicsPV(MS_checkTable);

    bool Yes = 1;
    bool No  = 0;

    bool column_0;
    bool column_1;
    bool column_2;
    bool column_3;
};

#endif // INTERVALS_H
