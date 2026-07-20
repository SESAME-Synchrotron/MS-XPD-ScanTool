#include "form.h"
#include "ui_form.h"
#include "aspectimage.h"
#include <QVBoxLayout>
#include <QELabel.h>
#include <QEImage.h>
#include <QEFileBrowser.h>
#include <iostream>
#include "client.h"
#include <QProcess>
#include <stdlib.h>

#include "camera.h"
#include "rois.h"
#include "form.h"

static const CameraInfo cameras[] = {
    CameraInfo(), // index 0: NA selected
    CameraInfo("ID09EH-DCA-FLIR02:AI-CAM2-SIDE"),
    CameraInfo("ID09EH-DCA-FLIR01:AI-CAM1-UP")
};

void Form::camSideView()
{
    base = side;
    ui->qeimage->setProperty("dimension1Variable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("dimension2Variable", QVariant(base + ":SizeY"));
    ui->qeimage->setProperty("widthVariable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("heightVariable", QVariant(base + ":SizeY"));
}

void Form::camSideDefSettings(){
    Client::writePV(cameras[1].pixelFormat, 0);
}

Form::Form(int &xDim, int &yDim, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->verticalLayout->setStretch(0,1);
    ui->verticalLayout->setStretch(1,0);
    this->formXDim = xDim;
    this->formYDim = yDim;

    ui->qeimage->setZoom(50);

    //this->setFixedWidth(0.3*formXDim);
    //this->setFixedHeight(0.3*formYDim);

    //ui->qeimage->resize(this->size());

    //ui->qeimage->setFixedSize(0.7*formXDim, 0.7*formYDim);
//    ui->qeimage->setResizeOption(QEImage::RESIZE_OPTION_FIT);
//    this->setFixedWidth(ui->qeimage->getXStretch()*formXDim);
//    this->setFixedHeight(ui->qeimage->getYStretch()*formYDim);

    ui->qeimage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->qeimage->setFixedSize(0.7*formXDim, 0.7*formYDim);

    //this->setBaseSize(ui->qeimage->)
    this->adjustSize();


//    AspectImage* aspectImage = new AspectImage(this);
//    //aspectImage->setGeometry(ui->qeimage->geometry());
//    ui->verticalLayout->replaceWidget(ui->qeimage, aspectImage);

//    ui->qeimage->deleteLater();
//    ui->qeimage = aspectImage;


//    ui->setupUi(this);
//    ui->verticalLayout->setStretch(0,1);
//    ui->verticalLayout->setStretch(1,0);

    base = side;
    ui->qeimage->setProperty("dimension1Variable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("dimension2Variable", QVariant(base + ":SizeY"));
    ui->qeimage->setProperty("widthVariable", QVariant(base + ":SizeX"));
    ui->qeimage->setProperty("heightVariable", QVariant(base + ":SizeY"));
    
    ui->qeimage->setVariableNameAndSubstitutions(cameras[1].image, QString(), 0);
    ui->stream->setVariableNameAndSubstitutions(cameras[1].acquire, QString(), 0);

    ui->qeimage->resize(this->size());

// new stuff here ; reference
//    QELabel* xDim = new QELabel(this);
//    QELabel* yDim = new QELabel(this);
//    xDim->hide();
//    yDim->hide();

//    xDim->setVariableNameAndSubstitutions(cameras[1].sizeX, QString(), 0);
//    yDim->setVariableNameAndSubstitutions(cameras[1].sizeY, QString(), 0);

//    connect(xDim, &QELabel::dbValueChanged, this, [=](const QString &val){
//        bool ok; int w = val.toInt(&ok);
//        if (ok) aspectImage->setAspectRatio(w, yDim->text().toInt());
//    });

//    connect(yDim, &QELabel::dbValueChanged, this, [=](const QString &val){
//        bool ok; int h = val.toInt(&ok);
//        if (ok) aspectImage->setAspectRatio(xDim->text().toInt(), h);
//     });

//    connect(xDim, SIGNAL(dbValueChanged(QString)), this, SLOT(on_qeimage_dbValueChanged(QString)));

//    connect(yDim, SIGNAL(dbValueChanged(QString)), this, SLOT(on_qeimage_dbValueChanged(QString)));

//    QTimer* timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, [=](){
////        int w = Client::readPV(cameras[1].sizeX).toInt();
////        int h = Client::readPV(cameras[1].sizeY).toInt();
////        if(h>0) aspectImage->setAspectRatio(static_cast<float>(w)/h);
//        int w = caget(base.toStdString() + ":SizeX"); // or however you read PV
//        int h = caget(base.toStdString() + ":SizeY");

//        if (w > 0 && h > 0) {
//            resize(w, h);  // makes window same as image
//        }

//    });
//    timer->start(200);

    resize(ui->qeimage->sizeHint());

}

Form::~Form()
{
    delete ui;
}

//void Form::on_qeimage_dbValueChanged(const QString &val, const QELabel *yDim, AspectImage *aspectImage)
//{
//    bool ok; int w = val.toInt(&ok);
//            if (ok) {
//                int h = yDim->text().toInt();
//                aspectImage->setAspectRatio(w, h);
//            }
//}

void Form::on_window_resize(){
    return;
}

void Form::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Resize qeimage to match the window
    ui->qeimage->resize(this->size());
}
