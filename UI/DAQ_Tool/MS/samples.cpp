#include "samples.h"
#include "ui_samples.h"

using namespace std;

samples::samples(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::samples)
{
    ui->setupUi(this);

    /* create 3 vectors which contain checkButton & lineEdit & simpleshape for each object (40 objects (samples)) */

    checkButtons = {ui->Sample1_checkBox, ui->Sample2_checkBox, ui->Sample3_checkBox, ui->Sample4_checkBox, ui->Sample5_checkBox,
                    ui->Sample6_checkBox, ui->Sample7_checkBox, ui->Sample8_checkBox, ui->Sample9_checkBox, ui->Sample10_checkBox,
                    ui->Sample11_checkBox, ui->Sample12_checkBox, ui->Sample13_checkBox, ui->Sample14_checkBox, ui->Sample15_checkBox,
                    ui->Sample16_checkBox, ui->Sample17_checkBox, ui->Sample18_checkBox, ui->Sample19_checkBox, ui->Sample20_checkBox,
                    ui->Sample21_checkBox, ui->Sample22_checkBox, ui->Sample23_checkBox, ui->Sample24_checkBox, ui->Sample25_checkBox,
                    ui->Sample26_checkBox, ui->Sample27_checkBox, ui->Sample28_checkBox, ui->Sample29_checkBox, ui->Sample30_checkBox,
                    ui->Sample31_checkBox, ui->Sample32_checkBox, ui->Sample33_checkBox, ui->Sample34_checkBox, ui->Sample35_checkBox,
                    ui->Sample36_checkBox, ui->Sample37_checkBox, ui->Sample38_checkBox, ui->Sample39_checkBox, ui->Sample40_checkBox};

    lineEdits    = {ui->Sample1_lineEdit, ui->Sample2_lineEdit, ui->Sample3_lineEdit, ui->Sample4_lineEdit, ui->Sample5_lineEdit,
                    ui->Sample6_lineEdit, ui->Sample7_lineEdit, ui->Sample8_lineEdit, ui->Sample9_lineEdit, ui->Sample10_lineEdit,
                    ui->Sample11_lineEdit, ui->Sample12_lineEdit, ui->Sample13_lineEdit, ui->Sample14_lineEdit, ui->Sample15_lineEdit,
                    ui->Sample16_lineEdit, ui->Sample17_lineEdit, ui->Sample18_lineEdit, ui->Sample19_lineEdit, ui->Sample20_lineEdit,
                    ui->Sample21_lineEdit, ui->Sample22_lineEdit, ui->Sample23_lineEdit, ui->Sample24_lineEdit, ui->Sample25_lineEdit,
                    ui->Sample26_lineEdit, ui->Sample27_lineEdit, ui->Sample28_lineEdit, ui->Sample29_lineEdit, ui->Sample30_lineEdit,
                    ui->Sample31_lineEdit, ui->Sample32_lineEdit, ui->Sample33_lineEdit, ui->Sample34_lineEdit, ui->Sample35_lineEdit,
                    ui->Sample36_lineEdit, ui->Sample37_lineEdit, ui->Sample38_lineEdit, ui->Sample39_lineEdit, ui->Sample40_lineEdit};

    simpleShapes = {ui->Sample1_Shape, ui->Sample2_Shape, ui->Sample3_Shape, ui->Sample4_Shape, ui->Sample5_Shape,
                    ui->Sample6_Shape, ui->Sample7_Shape, ui->Sample8_Shape, ui->Sample9_Shape, ui->Sample10_Shape,
                    ui->Sample11_Shape, ui->Sample12_Shape, ui->Sample13_Shape, ui->Sample14_Shape, ui->Sample15_Shape,
                    ui->Sample16_Shape, ui->Sample17_Shape, ui->Sample18_Shape, ui->Sample19_Shape, ui->Sample20_Shape,
                    ui->Sample21_Shape, ui->Sample22_Shape, ui->Sample23_Shape, ui->Sample24_Shape, ui->Sample25_Shape,
                    ui->Sample26_Shape, ui->Sample27_Shape, ui->Sample28_Shape, ui->Sample29_Shape, ui->Sample30_Shape,
                    ui->Sample31_Shape, ui->Sample32_Shape, ui->Sample33_Shape, ui->Sample34_Shape, ui->Sample35_Shape,
                    ui->Sample36_Shape, ui->Sample37_Shape, ui->Sample38_Shape, ui->Sample39_Shape, ui->Sample40_Shape};

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setAutoDefault(false);     // disable default button (ignore enter key event)

    this->setFixedSize(this->size());      // fix the window size
    this->setModal(true);
}

samples::~samples()
{
    delete ui;
}

void samples::initializing()
{
    /* disable the unchecked buttons and set their color and text according to the conditions*/

    for(int i = 0; i < checkButtons.size(); i++)
    {
        QCheckBox* checkButton = checkButtons.at(i);
        QELineEdit* lineEdit = lineEdits.at(i);
        QSimpleShape* simpleShape = simpleShapes.at(i);

        if(!(checkButton->isChecked()))
        {
            lineEdit->setText("");
            lineEdit->setEnabled(false);
            simpleShape->setColour0Property(QColor(255,0,0));
        }
        else
        {
            lineEdit->setEnabled(true);
            simpleShape->setColour0Property(QColor(0,255,0));
        }
    }
}

void samples::on_Sample1_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample1_lineEdit, ui->Sample1_Shape);
}

void samples::on_Sample2_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample2_lineEdit, ui->Sample2_Shape);
}

void samples::on_Sample3_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample3_lineEdit, ui->Sample3_Shape);
}

void samples::on_Sample4_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample4_lineEdit, ui->Sample4_Shape);
}

void samples::on_Sample5_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample5_lineEdit, ui->Sample5_Shape);
}

void samples::on_Sample6_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample6_lineEdit, ui->Sample6_Shape);
}

void samples::on_Sample7_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample7_lineEdit, ui->Sample7_Shape);
}

void samples::on_Sample8_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample8_lineEdit, ui->Sample8_Shape);
}

void samples::on_Sample9_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample9_lineEdit, ui->Sample9_Shape);
}

void samples::on_Sample10_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample10_lineEdit, ui->Sample10_Shape);
}

void samples::on_Sample11_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample11_lineEdit, ui->Sample11_Shape);
}

void samples::on_Sample12_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample12_lineEdit, ui->Sample12_Shape);
}

void samples::on_Sample13_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample13_lineEdit, ui->Sample13_Shape);
}

void samples::on_Sample14_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample14_lineEdit, ui->Sample14_Shape);
}

void samples::on_Sample15_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample15_lineEdit, ui->Sample15_Shape);
}

void samples::on_Sample16_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample16_lineEdit, ui->Sample16_Shape);
}

void samples::on_Sample17_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample17_lineEdit, ui->Sample17_Shape);
}

void samples::on_Sample18_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample18_lineEdit, ui->Sample18_Shape);
}

void samples::on_Sample19_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample19_lineEdit, ui->Sample19_Shape);
}

void samples::on_Sample20_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample20_lineEdit, ui->Sample20_Shape);
}

void samples::on_Sample21_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample21_lineEdit, ui->Sample21_Shape);
}

void samples::on_Sample22_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample22_lineEdit, ui->Sample22_Shape);
}

void samples::on_Sample23_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample23_lineEdit, ui->Sample23_Shape);
}

void samples::on_Sample24_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample24_lineEdit, ui->Sample24_Shape);
}

void samples::on_Sample25_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample25_lineEdit, ui->Sample25_Shape);
}

void samples::on_Sample26_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample26_lineEdit, ui->Sample26_Shape);
}

void samples::on_Sample27_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample27_lineEdit, ui->Sample27_Shape);
}

void samples::on_Sample28_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample28_lineEdit, ui->Sample28_Shape);
}

void samples::on_Sample29_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample29_lineEdit, ui->Sample29_Shape);
}

void samples::on_Sample30_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample30_lineEdit, ui->Sample30_Shape);
}

void samples::on_Sample31_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample31_lineEdit, ui->Sample31_Shape);
}

void samples::on_Sample32_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample32_lineEdit, ui->Sample32_Shape);
}

void samples::on_Sample33_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample33_lineEdit, ui->Sample33_Shape);
}

void samples::on_Sample34_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample34_lineEdit, ui->Sample34_Shape);
}

void samples::on_Sample35_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample35_lineEdit, ui->Sample35_Shape);
}
void samples::on_Sample36_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample36_lineEdit, ui->Sample36_Shape);
}

void samples::on_Sample37_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample37_lineEdit, ui->Sample37_Shape);
}

void samples::on_Sample38_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample38_lineEdit, ui->Sample38_Shape);
}

void samples::on_Sample39_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample39_lineEdit, ui->Sample39_Shape);
}

void samples::on_Sample40_checkBox_stateChanged(int arg1)
{
    checkSamples(arg1, ui->Sample40_lineEdit, ui->Sample40_Shape);
}

void samples::checkSamples(int arg, QELineEdit* lineEdit, QSimpleShape* simpleShape)
{
    /* check the number of checked samples, if they exceeded the defined number, it will emit alert (from the main class wizard.cpp) */
    /* this function will be called for each check button (state changed) */

    int checkedCount = sample->get().toInt();     // get the number of samples
    int currentCheckedCount = 0;                  // initialize the counter

    for(QCheckBox *checkButton : checkButtons)
    {
        if(checkButton->isChecked())
        {
            if(currentCheckedCount >= checkedCount)
            {
                checkButton->setChecked(false);     // Uncheck the button if the limit is exceeded
            }
            else
            {
                currentCheckedCount++;

//                if(currentCheckedCount == checkedCount)
//                {
//                    Client::writePV(MS_CheckSamples, Yes);
//                    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
//                }
//                else
//                {
//                    Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
//                    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
//                }

                if(arg == Qt::Checked)
                {
                    lineEdit->setEnabled(true);
//                    if(lineEdit->text().isEmpty())
//                        lineEdit->setStyleSheet("border: 2.25px solid red;");
//                    else
//                        lineEdit->setStyleSheet("");
                    simpleShape->setColour0Property(QColor(0, 255, 0));
                }
            }
        }
        else if(arg == Qt::Unchecked)
        {
//            lineEdit->text().clear();
            lineEdit->setEnabled(false);
//            lineEdit->setStyleSheet("");
            simpleShape->setColour0Property(QColor(255, 0, 0));
        }

        // Disable unselected buttons if the limit is reached
//        if(currentCheckedCount >= checkedCount && !checkButton->isChecked())
//        {
//            checkButton->setEnabled(false);
//        }
//        else
//        {
//            checkButton->setEnabled(true);
//        }
    }
}

int samples::getCheckCount()
{
    int count = 0;

    for(QCheckBox* checkButton : checkButtons)          // this function is called from wizard class
    {
        if(checkButton->isChecked())
        {
            count++;
        }
    }
    return count;
}

void samples::clearContents()
{
    for(QELineEdit* lineEdit : lineEdits)
    {
        lineEdit->setText("");;
    }

    for(QCheckBox* checkBox : checkButtons)
    {
        checkBox->setChecked(false);
    }
}

QJsonArray samples::getSamplesData()
{
    /* get the data for checked buttons only */

    QJsonObject samplesDict;
    QJsonArray  samplesArray;

    for(int i = 0; i < lineEdits.size(); i++)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];

        if(checkButton->isChecked())
        {
            QString keyName = QString("Sample#%1").arg(i+1); // set the key name
            QString valueName = lineEdit->text();

            // put a default name if the field is empty
            if(valueName.isEmpty())
                valueName = "---";

            samplesDict[keyName] = valueName;
        }
    }

    samplesArray.append(samplesDict);

    return samplesArray;
}

void samples::loadSamplesData(const QJsonArray& samplesArray)
{
    clearContents();    // clear all fields and disable the check buttons before loading the data

    for(int i = 0; i < samplesArray.size(); i++)
    {
        QJsonObject sampleObject = samplesArray[i].toObject();

        for(int j = 0; j < lineEdits.size(); j++)
        {
            QELineEdit* lineEdit = lineEdits[j];
            QCheckBox* checkButton = checkButtons[j];

            QString keyName = QString("Sample#%1").arg(j+1);

            if(sampleObject.contains(keyName))
            {
                QString valueName = sampleObject[keyName].toString();
                lineEdit->setText(valueName);
                checkButton->setChecked(true);
            }
        }
    }

    on_buttonBox_clicked();
}

void samples::on_buttonBox_clicked()
{
    /* set the index of the sample checked positions in epics array */
    /* if the field is empty, it will emit alert (from the main class wizard.cpp) */

    int positionsArray[40] = {};
    int x = 0;

    for(int i = 0; i < lineEdits.size(); i++)
    {
        QCheckBox* checkButton = checkButtons[i];
        QELineEdit* lineEdit = lineEdits[i];

        if(checkButton->isChecked())
        {
            positionsArray[x] = i+1;
            x++;

            if(!(lineEdit->text().trimmed().isEmpty()))
            {
                lineEdit->setStyleSheet("");
                Client::writePV(MS_CheckSamples, Yes);

            }
            else
            {
                Client::writePV(MS_CheckSamples, MS_CheckSamples_val);
                lineEdit->setStyleSheet("border: 2.25px solid red;");
                break;
            }
        }
    }

    Client::writeArray("MS:SamplesPositions", positionsArray, x);
}

void samples::closeEvent(QCloseEvent *event)
{
    if(!(sender() == ui->OK))
        event->ignore();       // Ignore the close event except for ok button
}

void samples::on_OK_clicked()
{
    on_buttonBox_clicked();
    this->close();
}
