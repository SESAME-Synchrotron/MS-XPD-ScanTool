#include "intervals.h"
#include "ui_intervals.h"
#include <client.h>
#include <iostream>
#include "stdlib.h"
#include <regex>
#include <QMessageBox>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>

using namespace std;

intervals::intervals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::intervals)
{
    ui->setupUi(this);

    QDir::setCurrent(workingDir);        /* set the current directory where the "table.json" file will be written, it will be changed according to defining data path */
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

intervals::~intervals()
{
    delete ui;
}

void intervals::initializing()
{
//    Client::writePV(MS_checkTable, MS_checkTable_val);
}

void intervals::enterRows(int row)
{
    ui->tableWidget->setRowCount(row);
}

int intervals::getRows()
{
    return ui->tableWidget->rowCount();
}

void intervals::setCellBackground(bool val, int row, int col)
{
    if(val)
        ui->tableWidget->item(row,col)->setBackground(Qt::white);
    else
        ui->tableWidget->item(row,col)->setBackground(Qt::red);
}

void intervals::UImessage(const QString &tittle, const QString &message)
{
    QMessageBox::information(this, tittle, message);
}

void intervals::on_tableWidget_cellChanged(int row, int column)
{
    // validate the cells

    switch (column)
    {
        case 0:
            if(regex_match(ui->tableWidget->item(row, 0)->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
            {
                column_0 = Yes;
                setCellBackground(column_0, row, column);
            }
            else
            {
                column_0 = No;
                setCellBackground(column_0, row, column);
//                UImessage(UItittle, "Please enter valid start point");
            }
            break;

        case 1:
            if(regex_match(ui->tableWidget->item(row, 1)->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
            {
                column_1 = Yes;
                setCellBackground(column_1, row, column);

            }
            else
            {
                column_1 = No;
                setCellBackground(column_1, row, column);
//                UImessage(UItittle, "Please enter valid end point");
            }
            break;

        case 2:
            if(regex_match(ui->tableWidget->item(row, 2)->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
            {
               column_2 = Yes;
               setCellBackground(column_2, row, column);
            }
            else
            {
               column_2 = No;
               setCellBackground(column_2, row, column);
//               UImessage(UItittle, "Please enter valid step size");
            }
            break;

        case 3:
            if(regex_match(ui->tableWidget->item(row, 3)->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
            {
                column_3 = Yes;
                setCellBackground(column_3, row, column);
            }
            else
            {
                column_3 = No;
                setCellBackground(column_3, row, column);
//                UImessage(UItittle, "Please enter valid exposure time");
            }
            break;
    }
}

void intervals::on_tableWidget_itemSelectionChanged()
{
    // enable or disable "Ok button" based on "on_tableWidget_cellChanged" function

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);

            /* we are checking if the item is nullptr to avoid segmentation fault
                because when we try to access or dereference a null pointer, it leads to undefined behavior*/
            if(item != nullptr && !(item->text().isEmpty()) && column_0 && column_1 && column_2 && column_3)
            {
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
                Client::writePV(MS_checkTable, Yes);
                cout<<"donnnne"<<endl;
            }
            else
            {
                Client::writePV(MS_checkTable, MS_checkTable_val);
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
                break;
            }
        }
    }
}

void intervals::on_buttonBox_clicked(QAbstractButton *button)
{
    // create a tmp file to save the table data "table.json", to keep the data in the table after closing it

    QPushButton *okButton = qobject_cast<QPushButton*>(button);

    if (okButton == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
//        Client::writePV(MS_checkTable, Yes);

//        QFile file("tableData.json");
//        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//        {
//            QJsonArray rowsArray;
//            for (int i = 0; i < ui->tableWidget->rowCount(); i++)
//            {
//                QJsonArray colsArray;
//                for (int j = 0; j < ui->tableWidget->columnCount(); j++)
//                {
//                    QTableWidgetItem* item = ui->tableWidget->item(i, j);
//                    if (item && !item->text().isEmpty())
//                    {
//                        colsArray.append(item->text());
//                    }
//                    else
//                    {
//                        colsArray.append("");
//                    }
//                }
//                rowsArray.append(colsArray);
//            }

//            QJsonObject jsonObj;
//            jsonObj["intervals"] = ui->tableWidget->rowCount();
//            jsonObj["cols"] = ui->tableWidget->columnCount();
//            jsonObj["data"] = rowsArray;

//            QJsonDocument jsonDoc(jsonObj);
//            file.write(jsonDoc.toJson());
//        }
    }
}

void intervals::loadData(QString fileName)
{
    // load the table data from the tmp file "table.json"

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        QJsonObject jsonObj = jsonDoc.object();
        int rowCount = jsonObj["intervals"].toInt();
        int colCount = jsonObj["cols"].toInt();

        if(Nintervals->get().toInt() == rowCount)
        {
            ui->tableWidget->setRowCount(rowCount);
            ui->tableWidget->setColumnCount(colCount);

            QJsonArray rowsArray = jsonObj["data"].toArray();
            for (int i = 0; i < rowCount; i++)
            {
                QJsonArray colsArray = rowsArray[i].toArray();
                for (int j = 0; j < colCount; j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem(colsArray[j].toString());
                    ui->tableWidget->setItem(i, j, item);
//                    Client::writePV(MS_checkTable, Yes);
                }
            }
        }
        else
            ui->tableWidget->clearContents();
    }
}

QJsonArray intervals::createIntervalsJson()
{
    // returns the JSONArray of the table to be written in the config file, this function will be called in wizard.cpp

    QJsonArray intervalsArray;
    QJsonObject intervalObj;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QJsonObject jsonObj;

        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if (item && !item->text().isEmpty())
            {
                QString value = item->text();
                QString key;

                switch (j)
                {
                    case 0:
                        key = "Startpoint";
                        break;
                    case 1:
                        key = "Endpoint";
                        break;
                    case 2:
                        key = "Stepsize";
                        break;
                    case 3:
                        key = "Exposuretime";
                        break;
                    default:
                        break;
                }

                jsonObj[key] = value;
            }
        }

        intervalsArray.append(jsonObj);
    }
    intervalObj["Intervals"] = intervalsArray;

    return intervalsArray;

    //    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    //    {
    //        QJsonObject intervalObj;

    //        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
    //        {
    //            QTableWidgetItem* item = ui->tableWidget->item(i, j);
    //            if (item && !item->text().isEmpty())
    //            {
    //                QString colName = ui->tableWidget->horizontalHeaderItem(j)->text();
    //                intervalObj[colName] = item->text();
    //            }
    //        }

    //        intervalsArray.append(intervalObj);
    //    }

    //    QJsonObject jsonObj;
    //    jsonObj["Intervals"] = intervalsArray;
}

void intervals::loadIntervalsFromJson(const QJsonArray& intervalsArray)
{
    // load the table data from config file

    cout<<"rrrrrrrrrr"<<endl;

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (const QJsonValue& intervalsIndex : intervalsArray)
    {
        QJsonObject intervalObj = intervalsIndex.toObject();

        QString startPoint = intervalObj["Startpoint"].toString();
        QString endPoint = intervalObj["Endpoint"].toString();
        QString stepSize = intervalObj["Stepsize"].toString();
        QString exposureTime = intervalObj["Exposuretime"].toString();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(startPoint));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(endPoint));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(stepSize));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(exposureTime));
        on_tableWidget_itemSelectionChanged();
        cout<<"rrrrrrfffffffffffffffrrrr"<<endl;

    }
}
