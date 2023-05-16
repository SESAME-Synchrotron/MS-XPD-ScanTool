#ifndef INTERVALS_H
#define INTERVALS_H

#include <QDialog>
#include <qepicspv.h>
#include <QJsonArray>

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

private slots:

    void initializing();                // initialize the table at startup

    void on_tableWidget_cellChanged();

    void on_tableWidget_itemSelectionChanged();

    void validateTable();

private:

    Ui::intervals *ui;

    QString MS_Nintervals = "MS:Intervals"  ; int MS_Nintervals_val = 0;
    QString MS_checkTable = "MS:CheckTable" ; int MS_checkTable_val = 0;

    QString UItittle = "Intervals";
    QString workingDir = "/home/dcasu/XRD-Scan/UI/DAQ_Tool/MS/";

    QEpicsPV* Nintervals     = new QEpicsPV(MS_Nintervals);
    QEpicsPV* checkTable     = new QEpicsPV(MS_checkTable);

    bool Yes = 1;
    bool No  = 0;
};

#endif // INTERVALS_H
