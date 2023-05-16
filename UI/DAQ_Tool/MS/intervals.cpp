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
    this->setFixedSize(this->size());

}

intervals::~intervals()
{
    delete ui;
}

void intervals::initializing()
{

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

void intervals::on_tableWidget_cellChanged()
{
    // validate the cells
    validateTable();
}

void intervals::on_tableWidget_itemSelectionChanged()
{
    validateTable();
}

void intervals::validateTable()
{
    bool checkAllCells = true;

    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->tableWidget->columnCount(); column++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(row, column);

            /* we are checking if the item is nullptr to avoid segmentation fault
                because when we try to access or dereference a null pointer, it leads to undefined behavior*/
            if(item == nullptr or item->text().isEmpty())
            {
                checkAllCells = false;
//                setCellBackground(checkAllCells, row, column);   /*********** segmentation fault   ******************/

                break;              //  exit from the slave for loop
            }

            switch (column)
            {
                case 0:
                    if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                    {
                        checkAllCells = false;
                    }
                    setCellBackground(checkAllCells, row, column);
                    break;

                case 1:
                    if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                    {
                        checkAllCells = false;
                    }
                    setCellBackground(checkAllCells, row, column);
                    break;

                case 2:
                    if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                    {
                        checkAllCells = false;
                    }
                    setCellBackground(checkAllCells, row, column);
                    break;

                case 3:
                    if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                    {
                        checkAllCells = false;
                    }
                    setCellBackground(checkAllCells, row, column);
                    break;
            }

            if(!checkAllCells)
                break;     //  exit from the slave for loop
        }

        if(!checkAllCells)
            break;   //  exit from the master for loop
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(checkAllCells);

    if(checkAllCells)
    {
        Client::writePV(MS_checkTable, Yes);
    }
    else
    {
        Client::writePV(MS_checkTable, MS_checkTable_val);
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
        validateTable();
    }
}
