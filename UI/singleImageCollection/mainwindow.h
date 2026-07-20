#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void noCamSelected();
    void camSelected(int index);
    void on_selectCamera_currentIndexChanged(int index);
    void camUPDefSettings();
    void camSideDefSettings();
    void camUpView();
    void camSideView();
    void on_restartIOC_clicked();
    void adjustImageAspect();
    void on_stop_clicked();
    void on_setDefaults_clicked();
    void on_saveROI_clicked();
    void setROIPVs(int index);
    void on_resetROI_clicked();

    void on_pushButton_clicked();

void onFileSelected(const QString &filePath);

private:
    Ui::MainWindow *ui;
    const QString side = "ID09EH-DCA-FLIR02:AI-CAM2-SIDE";
    const QString up = "ID09EH-DCA-FLIR01:AI-CAM1-UP";
    QString base;
};
#endif // MAINWINDOW_H
