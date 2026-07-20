#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QELabel.h>
#include <QEImage.h>
#include <QEFileBrowser.h>
#include <iostream>
#include "client.h"
#include <QProcess>
#include <stdlib.h>

#include "camera.h"
#include "rois.h"

static const CameraInfo cameras[] = {
    CameraInfo(), // index 0: NA selected
    CameraInfo("ID09EH-DCA-FLIR02:AI-CAM2-SIDE"),
    CameraInfo("ID09EH-DCA-FLIR01:AI-CAM1-UP")
};

static const ROIInfo camROI[]={
    ROIInfo("noCam"),
    ROIInfo("sideCam"),
    ROIInfo("upCam")
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->fileListing, &QEFileBrowser::selected,
            this, &MainWindow::onFileSelected);

    noCamSelected();
    ui->cameraSelected->setStyleSheet(
                "background-color: yellow;"
                "color: black;"
                );

}

MainWindow::~MainWindow(){
    delete  ui;
}

void MainWindow::adjustImageAspect()
{
    const int index = ui->selectCamera->currentIndex();
    if (index == 0)
        return;
    else{
        int x=1024;
        int y=1024;
        //        x=1024;
        //        y=1024;
        if (x == 0 || y == 0) {
            return;
        }
        const double camAR = x / y;
        int h = ui->qeimage->height();
        ui->qeimage->setResizeOption(QEImage::RESIZE_OPTION_FIT);
        //        ui->qeimage->
    }


}

void MainWindow::on_selectCamera_currentIndexChanged(int index)
{
    if (index== 0)
        noCamSelected();
    else
        camSelected(index);
    statusBar()->showMessage(
                tr("Now monitoring PV %1").arg(cameras[index].deliveredFrameCount), 2000);
}

void MainWindow::onFileSelected(const QString &filePath)
{
    if (!QFile::exists(filePath)) {
        QMessageBox::warning(this, "File Not Found", "File does not exist:\n" + filePath);
        return;
    }

    // Launch external viewer (Eye of GNOME)
    QProcess::startDetached("eog", QStringList() << filePath);
}

void MainWindow::noCamSelected() {
    ui->status->setVariableNameAndSubstitutions(cameras[0].deliveredFrameCount, QString(), 0);
    ui->imgCounter->setVariableNameAndSubstitutions(cameras[0].deliveredFrameCount, QString(), 0);
    ui->pixelFormat->setVariableNameAndSubstitutions(cameras[0].pixelFormatRBV, QString(), 0);
    ui->qeimage->setVariableNameAndSubstitutions(cameras[0].image, QString(), 0);
    ui->expTime->setVariableNameAndSubstitutions(cameras[0].acquireTime, QString(), 0);
    ui->cameraSelected->setText("N/A");
    ui->stream->setVariableNameAndSubstitutions(cameras[0].acquire, QString(), 0);
    ui->xDim->setVariableNameAndSubstitutions(cameras[0].sizeX, QString(), 0);
    ui->yDim->setVariableNameAndSubstitutions(cameras[0].sizeY, QString(), 0);
    setROIPVs(0);
}

void MainWindow::camSelected(int index){
    ui->status->setVariableNameAndSubstitutions(cameras[index].acquireBusy, QString(), 0);
    ui->imgCounter->setVariableNameAndSubstitutions(cameras[index].deliveredFrameCount, QString(), 0);
    ui->pixelFormat->setVariableNameAndSubstitutions(cameras[index].pixelFormatRBV, QString(), 0);
    ui->qeimage->setVariableNameAndSubstitutions(cameras[index].image, QString(), 0);

    if (index == 1)
        camSideView();
    else
        camUpView();
    ui->expTime->setVariableNameAndSubstitutions(cameras[index].acquireTime, QString(), 0);
    ui->cameraSelected->setText(index == 1 ? "FLIR2 SIDE" : "FLIR1 UP");
    ui->stream->setVariableNameAndSubstitutions(cameras[index].acquire, QString(), 0);

    // Set defaults as needed...
    if (index == 1) camSideDefSettings();
    else if (index == 2) camUPDefSettings();

    ui->xDim->setVariableNameAndSubstitutions(cameras[index].sizeX, QString(), 0);
    ui->yDim->setVariableNameAndSubstitutions(cameras[index].sizeY, QString(), 0);
    adjustImageAspect();
    setROIPVs(index);
}

void MainWindow::setROIPVs(int index){
    ui->r1x1->setVariableNameAndSubstitutions((camROI[index].ROI[0].x1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest1XVariable", camROI[index].ROI[0].x1);
    ui->r1y1->setVariableNameAndSubstitutions((camROI[index].ROI[0].y1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest1YVariable", camROI[index].ROI[0].y1);
    ui->r1x2->setVariableNameAndSubstitutions((camROI[index].ROI[0].x2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest1WVariable", camROI[index].ROI[0].x2);
    ui->r1y2->setVariableNameAndSubstitutions((camROI[index].ROI[0].y2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest1HVariable", camROI[index].ROI[0].y2);

    ui->r2x1->setVariableNameAndSubstitutions((camROI[index].ROI[1].x1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest2XVariable", camROI[index].ROI[1].x1);
    ui->r2y1->setVariableNameAndSubstitutions((camROI[index].ROI[1].y1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest2YVariable", camROI[index].ROI[1].y1);
    ui->r2x2->setVariableNameAndSubstitutions((camROI[index].ROI[1].x2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest2WVariable", camROI[index].ROI[1].x2);
    ui->r2y2->setVariableNameAndSubstitutions((camROI[index].ROI[1].y2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest2HVariable", camROI[index].ROI[1].y2);

    ui->r3x1->setVariableNameAndSubstitutions((camROI[index].ROI[2].x1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest3XVariable", camROI[index].ROI[2].x1);
    ui->r3y1->setVariableNameAndSubstitutions((camROI[index].ROI[2].y1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest3YVariable", camROI[index].ROI[2].y1);
    ui->r3x2->setVariableNameAndSubstitutions((camROI[index].ROI[2].x2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest3WVariable", camROI[index].ROI[2].x2);
    ui->r3y2->setVariableNameAndSubstitutions((camROI[index].ROI[2].y2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest3HVariable", camROI[index].ROI[2].y2);

    ui->r4x1->setVariableNameAndSubstitutions((camROI[index].ROI[3].x1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest4XVariable", camROI[index].ROI[3].x1);
    ui->r4y1->setVariableNameAndSubstitutions((camROI[index].ROI[3].y1), QString(),0);
    ui->qeimage->setProperty("regionOfInterest4YVariable", camROI[index].ROI[3].y1);
    ui->r4x2->setVariableNameAndSubstitutions((camROI[index].ROI[3].x2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest4WVariable", camROI[index].ROI[3].x2);
    ui->r4y2->setVariableNameAndSubstitutions((camROI[index].ROI[3].y2), QString(),0);
    ui->qeimage->setProperty("regionOfInterest4HVariable", camROI[index].ROI[3].y2);
}

void MainWindow::on_saveROI_clicked()
{

    std::string command = "python3.9 /home/control/MS-XPD-ScanTool/UI/singleImageCollection/singleShotImage.py --detectorPVPrefix ";
    command += base.toStdString();
    system(command.c_str());
    const int index = ui->selectCamera->currentIndex();
    Client::writePV(cameras[index].acquire, 1);

}

void MainWindow::camUpView()
{
    base = up;
    ui->qeimage->setProperty("dimension1Variable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("dimension2Variable", QVariant(base + ":SizeY"));
    ui->qeimage->setProperty("widthVariable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("heightVariable", QVariant(base + ":SizeY"));
    qWarning()<< "base ::"<<QVariant(base + ":SizeY");

}

void MainWindow::camSideView()
{
    base = side;
    ui->qeimage->setProperty("dimension1Variable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("dimension2Variable", QVariant(base + ":SizeY"));
    ui->qeimage->setProperty("widthVariable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("heightVariable", QVariant(base + ":SizeY"));
}

void MainWindow::camSideDefSettings(){
    Client::writePV(cameras[1].pixelFormat, 0);
}


void MainWindow::camUPDefSettings(){
    Client::writePV(cameras[2].pixelFormat, 0);
}


void MainWindow::on_restartIOC_clicked()
{
    const int index = ui->selectCamera->currentIndex();
    if (index == 0)
        return;

    QStringList args{ "stop" };
    switch (index) {
    case 1:  args << "ms-flir-cam-side"; break;
    case 2:  args << "ms-flir-cam-up";   break;
    default: return;
    }
    const QString script = "cameraDockerIOC.sh";
    QProcess::execute(script, args);
}


void MainWindow::on_stop_clicked()
{
    const int index = ui->selectCamera->currentIndex();
    if (index == 0)
        return;
    Client::writePV(cameras[index].acquire,0);
}


void MainWindow::on_setDefaults_clicked()
{
    const int index = ui->selectCamera->currentIndex();
    if (index == 0)
        return;

    switch (index) {
    case 1:  camSideDefSettings(); break;
    case 2:  camUPDefSettings(); break;
    default: return;
    }
}


void MainWindow::on_resetROI_clicked()
{
    size_t length = sizeof(camROI) / sizeof(camROI[0]);

    for (int i =0; i<length; i++)
        for (int j =0; j<4; j++)
        {
            Client::writePV(camROI[i].ROI[j].x1, 0);
            Client::writePV(camROI[i].ROI[j].y1, 0);
            Client::writePV(camROI[i].ROI[j].x2, 0);
            Client::writePV(camROI[i].ROI[j].y2, 0);
        }
}



void MainWindow::on_pushButton_clicked()
{
//    qWarning()<<"ffff:::: "<<ui->fileListing->selected();
}
