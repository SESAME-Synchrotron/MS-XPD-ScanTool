#include "intervals.h"
#include "ui_intervals.h"

intervals::intervals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::intervals)
{
    ui->setupUi(this);

    this->setModal(true);
    this->checkTable = 0;

    ui->intervalsWarning->setHidden(true);
    ui->intervalsWarningS1->setHidden(true);
    ui->intervalsWarningS2->setHidden(true);
    ui->note1S->setHidden(true);
    ui->note2S->setHidden(true);
    ui->note3S->setHidden(true);
    ui->note4S->setHidden(true);

    ui->intervalsWarning2->setHidden(true);
    ui->intervalsWarningS1_2->setHidden(true);
    ui->intervalsWarningS2_2->setHidden(true);
    ui->note1S_2->setHidden(true);
    ui->note2S_2->setHidden(true);
    ui->note3S_2->setHidden(true);
    ui->note4S_2->setHidden(true);
}

intervals::~intervals()
{
    delete ui;
}

void intervals::enterRows(int row)
{
    ui->tableWidget->setRowCount(row);
}

int intervals::getRows()
{
    return ui->tableWidget->rowCount();
}

void intervals::clearTable()
{
    if(getRows())
    {
        ui->tableWidget->clearContents();
        enterRows(0);
    }
}

void intervals::setCellBackground(bool val, int row, int col)
{
    val ? ui->tableWidget->item(row,col)->setBackground(Qt::white) : ui->tableWidget->item(row,col)->setBackground(Qt::red);
}

void intervals::setBlinking(bool val, QSimpleShape *shape)
{
    shape->setHidden(!val);
    shape->setFlash0Property(val);
}

void intervals::showIntervalWarning(bool val, int interval)
{
    ui->intervalsWarning->setText(QString("Interval %1!").arg(interval));
    ui->intervalsWarning->setHidden(!val);
    ui->intervalsWarningS1->setHidden(!val);
    ui->intervalsWarningS1->setFlash0Property(val);
    ui->intervalsWarningS2->setHidden(!val);
    ui->intervalsWarningS2->setFlash0Property(val);
}

void intervals::showTempWarning(bool val, int interval)
{
    ui->intervalsWarning2->setText(QString("Interval %1!").arg(interval));
    ui->intervalsWarning2->setHidden(!val);
    ui->intervalsWarningS1_2->setHidden(!val);
    ui->intervalsWarningS1_2->setFlash0Property(val);
    ui->intervalsWarningS2_2->setHidden(!val);
    ui->intervalsWarningS2_2->setFlash0Property(val);
}

void intervals::modifyTable(int type)
{
    /* modify table (add or delete columns) based on scanning Type */

    bool val = type == 2;

    ui->tableWidget->setColumnHidden(4, !val);
    ui->tableWidget->setColumnHidden(5, !val);
    ui->tableWidget->setColumnHidden(6, !val);
    ui->tableWidget->setColumnHidden(7, !val);
    ui->tableWidget->setColumnHidden(8, !val);
    ui->tempCautionsGB->setHidden(!val);

    if(val)
    {
        ui->tableWidget->setGeometry(10,10,1101,301);
        ui->buttonBox->setGeometry(1120,10,120,31);
        this->setFixedSize(1250,505);
    }
    else
    {
        ui->tableWidget->setGeometry(10,10,501,301);
        ui->buttonBox->setGeometry(520,10,100,31);
        this->setFixedSize(630,505);
    }
}

void intervals::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    /* check instantly for each entered item */

    bool checkItem = true;

    if(item != nullptr)
    {
        double cellVal = item->text().toDouble();
        bool cellEmpty = item->text().isEmpty();
        bool strCell = item->text().contains(QRegExp("[^0-9.]"));

        switch (item->column())
        {
            /* validate the two theta parameters
               ---------------------------------*/
            case twoThetaStart:
                if(!(cellVal >= 0.0 and cellVal <= 150.0) or cellEmpty or strCell)  // start point: 150 >= x >= 0
                    checkItem = false;

                setBlinking(!checkItem, ui->note1S);
                break;

            case twoThetaEnd:
                if(!(cellVal >= 0.0 and cellVal <= 150.0) or cellEmpty or strCell)  // end point: 150 >= x >= 0
                    checkItem = false;

                setBlinking(!checkItem, ui->note2S);
                setBlinking(!checkItem, ui->note3S);
                break;

            case twoThetaStepSize:
                if(!(cellVal >= 0.0 and cellVal <= 150.0) or cellEmpty or strCell)  // step size: 150 >= x >= 0
                    checkItem = false;

                setBlinking(!checkItem, ui->note4S);
                break;

            case expousreTime:
                if(!(cellVal > 0.0) or cellEmpty or strCell)  // exposure time: x > 0
                    checkItem = false;
                break;

            /* validate the temperature parameters
               ---------------------------------*/
            case temperatureStart:
                if(!(cellVal >= 25.0 and cellVal <= 1000.0) or cellEmpty or strCell)  // start point: 1000 >= x >= 25
                    checkItem = false;

                setBlinking(!checkItem, ui->note1S_2);
                break;

            case temperatureEnd:
                if(!(cellVal >= 25.0 and cellVal <= 1000.0) or cellEmpty or strCell)  // end point: 1000 >= x >= 25
                    checkItem = false;

                setBlinking(!checkItem, ui->note1S_2);
                break;

            case temperatureStepSize:
                if(!(abs(cellVal) <= 975.0) or cellEmpty)  // step size: 975 >= x >= -975
                    checkItem = false;

                setBlinking(!checkItem, ui->note2S_2);
                break;

            case nScans:
                if(!(item->text().toInt() > 0) or cellEmpty or strCell)  // Nscans: x > 0
                    checkItem = false;
                break;

            case waitingTime:

                if(!(cellVal > 0.0) or cellEmpty or strCell)  // waiting time: x > 0
                    checkItem = false;
                break;
        }
        setCellBackground(checkItem, item->row(), item->column());
    }
}

bool intervals::validateTwoThetaTable()
{
    /* check the two theta table data after loading the config file or exiting from the table */

    // disconnect on_tableWidget_itemChanged func to avoid many accessing to the cells and connect at the end
    disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));

    bool checkTwoThetaCells = true;

    for(int row = 0; row < getRows(); ++row)
    {
        for(int column = twoThetaStart; column <= expousreTime; ++column)           // check only two theta columns cols: 1, 2, 3, 4
        {
            QTableWidgetItem* item = ui->tableWidget->item(row, column);

            /*  check if the item is nullptr to avoid segmentation fault, trying to access or dereference a null pointer, it leads to undefined behavior */
            if(item == nullptr or item->text().isEmpty() or item->text().contains(QRegExp("[^0-9.]")))
            {
                checkTwoThetaCells = false;
                break;   //  exit from the slave for loop
            }

            double startCellVal = ui->tableWidget->item(row, 0)->text().toDouble();
            double endCellVal = ui->tableWidget->item(row, 1)->text().toDouble();
            double cellVal = item->text().toDouble();

            switch (column)
            {
                case twoThetaStart:
                    if(!(cellVal >= 0.0 and cellVal <= 150.0))
                        checkTwoThetaCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("StartPoint%1").arg(row + 1), cellVal);
                    break;

                case twoThetaEnd:
                    if(!(cellVal >= 0.0 and cellVal <= 150.0) or (cellVal < startCellVal))
                        checkTwoThetaCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("EndPoint%1").arg(row + 1), cellVal);

                    setBlinking(!checkTwoThetaCells, ui->note2S);
                    setBlinking(!checkTwoThetaCells, ui->note3S);
                    break;

                case twoThetaStepSize:
                    if(!(cellVal >= 0.0 and cellVal <= 150.0) or
                        !(cellVal <= (endCellVal - startCellVal)) or
                        (cellVal == 0.0 and (endCellVal - startCellVal) != 0.0))
                        checkTwoThetaCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("StepSize%1").arg(row + 1), cellVal);

                    setBlinking(!checkTwoThetaCells, ui->note4S);
                    break;

                case expousreTime:
                    if(!(cellVal > 0.0))
                        checkTwoThetaCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("ExposureTime%1").arg(row + 1), cellVal);
                    break;
            }
            setCellBackground(checkTwoThetaCells, row, column);
            showIntervalWarning(!checkTwoThetaCells, row+1);
            if(!checkTwoThetaCells)
            {
                break;     //  exit from the slave for loop
            }
        }
        if(!checkTwoThetaCells)
            break;   //  exit from the master for loop
    }
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));
    return checkTwoThetaCells;
}

bool intervals::validateTemperatureTable()
{
    /* check the two theta temperature table data after loading the config file or exiting from the table */

    // disconnect on_tableWidget_itemChanged func to avoid many accessing to the cells and connect at the end
    disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));

    bool checkTemperatureCells = true;

    for(int row = 0; row < getRows(); ++row)
    {
        for(int column = temperatureStart; column <= waitingTime; ++column)           // check only two theta columns cols: 5, 6, 7, 8
        {
            QTableWidgetItem* item = ui->tableWidget->item(row, column);

            /*  check if the item is nullptr to avoid segmentation fault, trying to access or dereference a null pointer, it leads to undefined behavior */
            if(item == nullptr or item->text().isEmpty() or item->text().contains(QRegExp("[^0-9.-]")))
            {
                checkTemperatureCells = false;
                break;   //  exit from the slave for loop
            }

            double startCellVal = ui->tableWidget->item(row, 4)->text().toDouble();
            double endCellVal = ui->tableWidget->item(row, 5)->text().toDouble();
            double diff = endCellVal - startCellVal;
            double cellVal = item->text().toDouble();

            switch (column)
            {
                case temperatureStart:
                    if(!(cellVal >= 25.0 and cellVal <= 1000.0))
                        checkTemperatureCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("TStart%1").arg(row + 1), cellVal);

                    setBlinking(!checkTemperatureCells, ui->note1S_2);
                    break;

                case temperatureEnd:
                    if(!(cellVal >= 25.0 and cellVal <= 1000.0))
                            checkTemperatureCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("TEnd%1").arg(row + 1), cellVal);

                    setBlinking(!checkTemperatureCells, ui->note1S_2);
                    break;

                case temperatureStepSize:
                    if((!(abs(cellVal) <= 975.0)))
                        checkTemperatureCells = false;
                    else if(cellVal == 0.0)
                    {
                         if(diff != 0.0)
                             checkTemperatureCells = false;
                    }
                    else if(cellVal > 0.0)
                    {
                        if(!(cellVal <= diff))
                            checkTemperatureCells = false;
                    }
                    else if(cellVal < 0.0)
                    {
                         if(!(cellVal >= diff))
                            checkTemperatureCells = false;
                    }

                    if(checkTemperatureCells)
                        Client::writePV(PV_Prefix + QString("TStepSize%1").arg(row + 1), cellVal);

                    setBlinking(!checkTemperatureCells, ui->note2S_2);
                    setBlinking(!checkTemperatureCells, ui->note3S_2);
                    setBlinking(!checkTemperatureCells, ui->note4S_2);
                    break;

                case nScans:
                    if(!(cellVal > 0.0))
                        checkTemperatureCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("NScans%1").arg(row + 1), cellVal);
                    break;

                case waitingTime:
                    if(!(cellVal > 0.0))
                        checkTemperatureCells = false;
                    else
                        Client::writePV(PV_Prefix + QString("TWaitingTime%1").arg(row + 1), cellVal);
                    break;
            }
            setCellBackground(checkTemperatureCells, item->row(), item->column());
            showTempWarning(!checkTemperatureCells, row+1);
            if(!checkTemperatureCells)
                break;     //  exit from the slave for loop
        }
        if(!checkTemperatureCells)
            break;   //  exit from the master for loop
    }
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));
    return checkTemperatureCells;
}

QString intervals::getColumnKey(int column)
{
    switch (column)
    {
        case twoThetaStart:
            return "TwoThetaStartpoint";
        case twoThetaEnd:
            return "TwoThetaEndpoint";
        case twoThetaStepSize:
            return "TwoThetaStepSize";
        case expousreTime:
            return "Exposuretime";
        case temperatureStart:
            return "TemperatureStartPoint";
        case temperatureEnd:
            return "TemperatureEndPoint";
        case temperatureStepSize:
            return "TemperatureStepSize";
        case nScans:
            return "NScans";
        case waitingTime:
            return "WaitingTime";
        default:
            return "";
    }
}

QString intervals::getPVName(int name)
{
    switch (name)
    {
        case twoThetaStart:
            return "StartPoint";
        case twoThetaEnd:
            return "EndPoint";
        case twoThetaStepSize:
            return "StepSize";
        case expousreTime:
            return "ExposureTime";
        case temperatureStart:
            return "TStart";
        case temperatureEnd:
            return "TEnd";
        case temperatureStepSize:
            return "TStepSize";
        case nScans:
            return "NScans";
        case waitingTime:
            return "TWaitingTime";
        default:
            return "";
    }
}

QJsonArray intervals::createIntervalsJson(int type)
{
    /* returns the JSONArray of the table to be written in the config file, this function will be called in wizard.cpp */

    QJsonArray intervalsArray;
    QJsonObject intervalObj;

    int numColumns = (type == 2) ? 9 : 4;

    for(int i = 0; i < getRows(); ++i)
    {
        QJsonObject jsonObj;

        for(int j = 0; j < numColumns; ++j)
        {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);

            if(item and !item->text().isEmpty())
            {
                QString value = item->text();
                QString key = getColumnKey(j);
                jsonObj[key] = value;
            }
        }
        intervalsArray.append(jsonObj);
    }
    intervalObj["Intervals"] = intervalsArray;
    return intervalsArray;
}

void intervals::loadIntervalsFromJson(const QJsonArray& intervalsArray, int type)
{
    /* load the table data from config file, this function is called in wizard */

    disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int numColumns = (type == 2) ? 9 : 4;

    for(const QJsonValue& intervalsIndex : intervalsArray)
    {
        QJsonObject intervalObj = intervalsIndex.toObject();
        int row = getRows();
        ui->tableWidget->insertRow(row);

        for(int j = 0; j < numColumns; ++j)
        {
            QString key = getColumnKey(j);
            QString value = intervalObj[key].toString();
            QString PVName = getPVName(j);

            ui->tableWidget->setItem(row, j, new QTableWidgetItem(value));
            Client::writePV(PV_Prefix + QString("%1%2").arg(PVName).arg(row + 1), value.toDouble());
        }
    }

    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(on_tableWidget_itemChanged(QTableWidgetItem*)));
    validateTable();
}

void intervals::validateTable()
{
    bool validTable = validateTwoThetaTable() and (scanningType->get().toInt() == 2 ? validateTemperatureTable() : true);
    this->checkTable = validTable ? Yes : No;
}

void intervals::on_buttonBox_clicked()
{
    validateTable();
}

void intervals::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
