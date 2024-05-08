#include "samples.h"
#include "ui_samples.h"

samples::samples(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::samples)
{
    ui->setupUi(this);

    /* create 3 vectors which contain checkButton & lineEdit & simpleshape for each object (40 objects (samples)) */
    for(int i = 1; i <= container; ++i) {

        QCheckBox* checkBox = findChild<QCheckBox*>(QString("Sample%1_checkBox").arg(i));
        if(checkBox) checkButtons.push_back(checkBox);

        QELineEdit* lineEdit = findChild<QELineEdit*>(QString("Sample%1_lineEdit").arg(i));
        if(lineEdit) lineEdits.push_back(lineEdit);

        QSimpleShape* simpleShape = findChild<QSimpleShape*>(QString("Sample%1_Shape").arg(i));
        if(simpleShape) simpleShapes.push_back(simpleShape);
    }

    ui->buttonBox->button(QDialogButtonBox::Close)->setAutoDefault(false);
    this->setFixedSize(this->size());
    this->setModal(true);
    ui->pickingOrder->setEnabled(false);

    this->Nsamples = 0;
    this->checkSample = 0;
}

samples::~samples()
{
    delete ui;
}

void samples::initializing()
{
    /* disable the unchecked buttons and as well their color and text according to the conditions*/

    for(int i = 0; i < container; ++i)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];

        if(!checkedButtons.contains(checkButton))
        {
            lineEdit->setText("");
            lineEdit->setEnabled(false);
            checkButton->setChecked(false);
        }
    }
}

void samples::on_Sample1_checkBox_stateChanged(int state)
{
    checkSamples(state, 1);
}

void samples::on_Sample2_checkBox_stateChanged(int state)
{
    checkSamples(state, 2);
}

void samples::on_Sample3_checkBox_stateChanged(int state)
{
    checkSamples(state, 3);
}

void samples::on_Sample4_checkBox_stateChanged(int state)
{
    checkSamples(state, 4);
}

void samples::on_Sample5_checkBox_stateChanged(int state)
{
    checkSamples(state, 5);
}

void samples::on_Sample6_checkBox_stateChanged(int state)
{
    checkSamples(state, 6);
}

void samples::on_Sample7_checkBox_stateChanged(int state)
{
    checkSamples(state, 7);
}

void samples::on_Sample8_checkBox_stateChanged(int state)
{
    checkSamples(state, 8);
}

void samples::on_Sample9_checkBox_stateChanged(int state)
{
    checkSamples(state, 9);
}

void samples::on_Sample10_checkBox_stateChanged(int state)
{
    checkSamples(state, 10);
}

void samples::on_Sample11_checkBox_stateChanged(int state)
{
    checkSamples(state, 11);
}

void samples::on_Sample12_checkBox_stateChanged(int state)
{
    checkSamples(state, 12);
}

void samples::on_Sample13_checkBox_stateChanged(int state)
{
    checkSamples(state, 13);
}

void samples::on_Sample14_checkBox_stateChanged(int state)
{
    checkSamples(state, 14);
}

void samples::on_Sample15_checkBox_stateChanged(int state)
{
    checkSamples(state, 15);
}

void samples::on_Sample16_checkBox_stateChanged(int state)
{
    checkSamples(state, 16);
}

void samples::on_Sample17_checkBox_stateChanged(int state)
{
    checkSamples(state, 17);
}

void samples::on_Sample18_checkBox_stateChanged(int state)
{
    checkSamples(state, 18);
}

void samples::on_Sample19_checkBox_stateChanged(int state)
{
    checkSamples(state, 19);
}

void samples::on_Sample20_checkBox_stateChanged(int state)
{
    checkSamples(state, 20);
}

void samples::on_Sample21_checkBox_stateChanged(int state)
{
    checkSamples(state, 21);
}

void samples::on_Sample22_checkBox_stateChanged(int state)
{
    checkSamples(state, 22);
}

void samples::on_Sample23_checkBox_stateChanged(int state)
{
    checkSamples(state, 23);
}

void samples::on_Sample24_checkBox_stateChanged(int state)
{
    checkSamples(state, 24);
}

void samples::on_Sample25_checkBox_stateChanged(int state)
{
    checkSamples(state, 25);
}

void samples::on_Sample26_checkBox_stateChanged(int state)
{
    checkSamples(state, 26);
}

void samples::on_Sample27_checkBox_stateChanged(int state)
{
    checkSamples(state, 27);
}

void samples::on_Sample28_checkBox_stateChanged(int state)
{
    checkSamples(state, 28);
}

void samples::on_Sample29_checkBox_stateChanged(int state)
{
    checkSamples(state, 29);
}

void samples::on_Sample30_checkBox_stateChanged(int state)
{
    checkSamples(state, 30);
}

void samples::on_Sample31_checkBox_stateChanged(int state)
{
    checkSamples(state, 31);
}

void samples::on_Sample32_checkBox_stateChanged(int state)
{
    checkSamples(state, 32);
}

void samples::on_Sample33_checkBox_stateChanged(int state)
{
    checkSamples(state, 33);
}

void samples::on_Sample34_checkBox_stateChanged(int state)
{
    checkSamples(state, 34);
}

void samples::on_Sample35_checkBox_stateChanged(int state)
{
    checkSamples(state, 35);
}
void samples::on_Sample36_checkBox_stateChanged(int state)
{
    checkSamples(state, 36);
}

void samples::on_Sample37_checkBox_stateChanged(int state)
{
    checkSamples(state, 37);
}

void samples::on_Sample38_checkBox_stateChanged(int state)
{
    checkSamples(state, 38);
}

void samples::on_Sample39_checkBox_stateChanged(int state)
{
    checkSamples(state, 39);
}

void samples::on_Sample40_checkBox_stateChanged(int state)
{
    checkSamples(state, 40);
}

void samples::checkSamples(int state, int location)
{
    /* check the number of checked samples, if they exceeded the defined number, it will emit alert*/
    /* this function is called for each check button (state changed) */

    int currentCheckedCount = checkedButtons.size();

    QCheckBox* checkButton = checkButtons[location - 1];
    QELineEdit* lineEdit = lineEdits[location - 1];
    QSimpleShape* simpleShape = simpleShapes[location - 1];

    if(state == Qt::Checked and currentCheckedCount >= 0 and currentCheckedCount < this->Nsamples)
    {
        lineEdit->setEnabled(true);
        simpleShape->setColour0Property(QColor(0, 255, 0));
        if(!checkedButtons.contains(checkButton)) checkedButtons.push_back(checkButton);
    }
    else if(state == Qt::Unchecked)
    {
        lineEdit->setEnabled(false);
        simpleShape->setColour0Property(QColor(255, 0, 0));
        if(checkedButtons.contains(checkButton)) checkedButtons.removeOne(checkButton);
    }
}

int samples::getSamplesCount()
{
    return checkedButtons.size();
}

void samples::clearContents()
{
    checkedButtons.clear();
    for(int i = 0; i < container; ++i)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];
        lineEdit->setText("");
        lineEdit->setEnabled(false);
        checkButton->setChecked(false);
    }
}

QJsonArray samples::getSamplesData()
{
    /* get the data for checked buttons only */

    QJsonObject samplesDict;
    QJsonArray  samplesArray;

    for(int i = 0; i < container; ++i)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];

        if(checkedButtons.contains(checkButton))
        {
            QString keyName = QString("Sample#%1").arg(i+1);
            QString valueName = lineEdit->text();
            samplesDict[keyName] = valueName;
        }
    }
    samplesArray.append(samplesDict);
    return samplesArray;
}

QJsonValue samples::getPickingOrder()
{
    /* get picking order of the samples (serial, random) */

    QJsonObject orderDict;
    QJsonArray pickingOrder;

    for(int item : ordering)
        pickingOrder.append(item);

    orderDict[pickingOrderS] = pickingOrder;
    QJsonValue orderValue(orderDict);
    return orderValue;
}

void samples::loadSamplesData(const QJsonArray& samplesArray, const QJsonValue& OrderArray)
{
    for(int i = 0; i < samplesArray.size(); ++i)
    {
        QJsonObject sampleObject = samplesArray[i].toObject();

        for(int j = 0; j < container; ++j)
        {
            QString keyName = QString("Sample#%1").arg(j+1);

            if(sampleObject.contains(keyName))
            {
                QELineEdit* lineEdit = lineEdits[j];
                QCheckBox* checkButton = checkButtons[j];
                QString valueName = sampleObject[keyName].toString();
                lineEdit->setText(valueName);
                checkButton->setChecked(true);
                Client::writePV(PV_Prefix + QString("Sample%1").arg(j+1), valueName);
            }
        }
    }

    QJsonObject orderDict = OrderArray.toObject();

    if(orderDict.contains("Random"))
    {
        QJsonArray pickingArray = orderDict["Random"].toArray();
        QString order;
        int size = pickingArray.size();

        for(int i = 0; i < size; ++i)
        {
            int value = pickingArray[i].toInt();
            (i+1 == size) ? order = order + QString::number(value) : order = order + QString::number(value) + ",";
        }

        ui->pickingOrder->setText(order);
        Client::writePV(MS_PickingOrder, "Random");
        on_pickingOrder_textEdited(order);
    }
    else
        Client::writePV(MS_PickingOrder, "Serial");

    on_buttonBox_clicked();
    this->checkSample = 0;
}

void samples::on_buttonBox_clicked()
{
    /* set the index of the sample checked positions in epics array */
    /* if the field is empty, it will emit alert (from the main class wizard.cpp) */
    /* check the picking order if it is random */

    bool val = !(this->Nsamples == getSamplesCount());
    if(val)
    {
        this->checkSample = 0;
        return;
    }

    int positionsArray[80] = {};
    ordering.clear();
    int x = 0;

    for(int i = 0; i < container; ++i)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];

        if(checkedButtons.contains(checkButton))
        {
            bool val = !lineEdit->text().trimmed().isEmpty() and regex_match(lineEdit->text().toStdString(), std::regex("^[a-z|A-Z|0-9]*[a-z|A-Z|0-9|_]+"));
            setBorderLineEdit(!val, lineEdit);
            if(!val)
            {
                this->checkSample = 0;
                return;
            }

            positionsArray[x] = i+1;
            ordering.push_back(i+1);
            ++x;
        }
        else
        {
            lineEdit->setText("");
            lineEdit->setEnabled(false);
            checkButton->setChecked(false);
        }
    }

   if(pickingOrder)
    {
        if(!ui->pickingOrder->text().trimmed().isEmpty() and validOrder)
        {
            ordering.clear();
            std::stringstream in(ui->pickingOrder->text().toStdString());
            std::string val;

            while(getline(in, val, ','))
            {
                int order = stoi(val);
                ordering.push_back(order);
            }

            bool allInArray = true;

            for(int item : ordering)
            {
                bool found = (std::find(positionsArray, positionsArray + x, item) != positionsArray + x);
                if(!found)
                {
                    allInArray = false;
                    break;
                }
            }

            setBorderLineEdit(!allInArray, ui->pickingOrder);

            if(allInArray)
            {
                int positionsArray[80] = {};
                for(int i = 0; i < ordering.size(); ++i)
                    positionsArray[i] = ordering[i];

                Client::writeArray(MS_SamplesPositions, positionsArray, ordering.size());
            }
            else
            {
                this->checkSample = 0;
                return;
            }
        }
        else
        {
            setBorderLineEdit(Yes, ui->pickingOrder);
            this->checkSample = 0;
            return;
        }
   }
   else
   {
       Client::writeArray(MS_SamplesPositions, positionsArray, x);
       setBorderLineEdit(No, ui->pickingOrder);
   }
   this->checkSample = 1;
}

void samples::on_pickingOrderRBV_dbValueChanged(bool out)
{
    out ? ui->pickingOrder->setEnabled(true) : ui->pickingOrder->setEnabled(false);
    pickingOrder = out;
}

void samples::on_pickingOrderRBV_dbValueChanged(const QString &out)
{
    pickingOrderS = out;
}

void samples::on_pickingOrder_textEdited(const QString &arg)
{
    /* check if the random picking order is valid (splitted by commas, and input range from 1 to 40) */

    bool val = regex_match(arg.toStdString(), std::regex("^([1-9]|[1-3][0-9]|40)(,([1-9]|[1-3][0-9]|40))*$"));
    setBorderLineEdit(!val, ui->pickingOrder);
    validOrder = val;
}

void samples::setBorderLineEdit(bool val, QLineEdit *lineEdit)
{
    val ? lineEdit->setStyleSheet("border: 2.25px solid red;") : lineEdit->setStyleSheet("");
}

void samples::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
