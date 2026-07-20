#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "QEImage.h"
#include <iostream>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(int &xDim, int &yDim, QWidget *parent = nullptr);
    ~Form();

    Ui::Form *ui;
    int formXDim;
    int formYDim;
    const QString side = "ID09EH-DCA-FLIR02:AI-CAM2-SIDE";
    const QString up = "ID09EH-DCA-FLIR01:AI-CAM1-UP";
    QString base;
public slots:
    void on_window_resize();
    void camSideView();
    void camSideDefSettings();
    void resizeEvent(QResizeEvent *event);
signals:
    void dbValueChanged(const QString &out);

};

#endif // FORM_H
