#include "intervals.h"
#include "ui_intervals.h"

using namespace std;

intervals::intervals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::intervals)
{
    ui->setupUi(this);

    QDir::setCurrent(workingDir);        /* set the current directory where the "table.json" file will be written, it will be changed according to defining data path */

    this->setFixedSize(this->size());   // fix the window size
}

intervals::~intervals()
{
    delete ui;
}

void intervals::enterRows(int row)
{
    ui->tableWidget->setRowCount(row);      // this function is called from wizard class (to update the rows based on Intervals)
}

int intervals::getRows()
{
    return ui->tableWidget->rowCount();     // this function is called from wizard class (to send the rows count)
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

void intervals::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    /* check instantly for each entered item */

    bool checkItem = true;

    if(item != nullptr)
    {
        switch (item->column())
        {
            case 0:
                if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or !(item->text().toDouble() >= 5))
                {
                    checkItem = false;
                }
                setCellBackground(checkItem, item->row(), item->column());
                break;

            case 1:
                if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or (item->text().toDouble() > 90))
                {
                    checkItem = false;
                }
                setCellBackground(checkItem, item->row(), item->column());
                break;

            case 2:
                if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or !(item->text().toDouble() > 0))
                {
                    checkItem = false;
                }
                setCellBackground(checkItem, item->row(), item->column());
                break;

            case 3:
                if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                {
                    checkItem = false;
                }
                setCellBackground(checkItem, item->row(), item->column());
                break;
        }
    }
}

void intervals::validateTable()
{
    /* check the whole table data after loading the config file or exiting form the table */

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
                    if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or !(item->text().toDouble() >= 5 and ui->tableWidget->item(row, 1)->text().toDouble() <= 90))
                    {
                        checkAllCells = false;
                    }
                    else if(regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                        Client::writePV(PV_Prefix + QString("StartPoint%1").arg(row + 1), item->text().toDouble());

                    setCellBackground(checkAllCells, row, column);
                    break;

                case 1:
                    if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or (item->text().toDouble() < ui->tableWidget->item(row, 0)->text().toDouble()))
                    {
                        checkAllCells = false;
                    }
                    else if(regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                        Client::writePV(PV_Prefix + QString("EndPoint%1").arg(row + 1), item->text().toDouble());

                    setCellBackground(checkAllCells, row, column);
                    break;

                case 2:
                    if((!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*"))) or !(item->text().toDouble() > 0 and item->text().toDouble() <= ((ui->tableWidget->item(row, 1)->text().toDouble()) - (ui->tableWidget->item(row, 0)->text().toDouble()))))
                    {
                        checkAllCells = false;
                    }
                    else if(regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                        Client::writePV(PV_Prefix + QString("StepSize%1").arg(row + 1), item->text().toDouble());

                    setCellBackground(checkAllCells, row, column);
                    break;

                case 3:
                    if(!regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                    {
                        checkAllCells = false;
                    }
                    setCellBackground(checkAllCells, row, column);

                    if(regex_match(item->text().toStdString(), regex("^[0-9][0-9]*.?[0-9]*")))
                        Client::writePV(PV_Prefix + QString("ExposureTime%1").arg(row + 1), item->text().toDouble());

                    break;
            }

            if(!checkAllCells)
                break;     //  exit from the slave for loop
        }

        if(!checkAllCells)
            break;   //  exit from the master for loop
    }

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
    /* this function is not used (because the data will remain even after closing the table), the instance in wizard.cpp is exist (doesnot call the destructor) */
    /* load the table data from the tmp file "table.json" */

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
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
            for(int i = 0; i < rowCount; i++)
            {
                QJsonArray colsArray = rowsArray[i].toArray();
                for(int j = 0; j < colCount; j++)
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
    /* returns the JSONArray of the table to be written in the config file, this function will be called in wizard.cpp */

    QJsonArray intervalsArray;
    QJsonObject intervalObj;

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QJsonObject jsonObj;

        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if(item && !item->text().isEmpty())
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
    /* load the table data from config file, this function is called in wizard */

    ui->tableWidget->clearContents();   // clear contents before loading the data
    ui->tableWidget->setRowCount(0);    // remove all rows

    for(const QJsonValue& intervalsIndex : intervalsArray)
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

        Client::writePV(PV_Prefix + QString("StartPoint%1").arg(row + 1), startPoint.toDouble());
        Client::writePV(PV_Prefix + QString("EndPoint%1").arg(row + 1), startPoint.toDouble());
        Client::writePV(PV_Prefix + QString("StepSize%1").arg(row + 1), startPoint.toDouble());
        Client::writePV(PV_Prefix + QString("ExposureTime%1").arg(row + 1), startPoint.toDouble());
    }
    validateTable();     // validate the table after loading the data
}

void intervals::on_buttonBox_clicked()
{
    validateTable();
}

void intervals::closeEvent(QCloseEvent *event)
{
    event->ignore();       // Ignore the close event
}
