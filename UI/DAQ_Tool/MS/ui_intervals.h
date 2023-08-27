/********************************************************************************
** Form generated from reading UI file 'intervals.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERVALS_H
#define UI_INTERVALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "QSimpleShape.h"

QT_BEGIN_NAMESPACE

class Ui_intervals
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;
    QLabel *caution;
    QWidget *gridLayoutWidget;
    QGridLayout *note1L;
    QLabel *note1;
    QSimpleShape *note1S;
    QWidget *gridLayoutWidget_2;
    QGridLayout *note2L;
    QLabel *note2;
    QSimpleShape *note2S;
    QWidget *gridLayoutWidget_3;
    QGridLayout *note3L;
    QLabel *note3;
    QSimpleShape *note3S;
    QWidget *gridLayoutWidget_4;
    QGridLayout *note4L;
    QLabel *note4;
    QSimpleShape *note4S;

    void setupUi(QDialog *intervals)
    {
        if (intervals->objectName().isEmpty())
            intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->resize(589, 439);
        buttonBox = new QDialogButtonBox(intervals);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(500, 10, 81, 301));
        buttonBox->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        tableWidget = new QTableWidget(intervals);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 481, 301));
        tableWidget->setMouseTracking(false);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        caution = new QLabel(intervals);
        caution->setObjectName(QString::fromUtf8("caution"));
        caution->setGeometry(QRect(10, 320, 61, 21));
        QFont font;
        font.setPointSize(11);
        font.setStyleStrategy(QFont::PreferDefault);
        caution->setFont(font);
        caution->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);\n"
"line-height: 1; padding: 0;"));
        caution->setFrameShape(QFrame::StyledPanel);
        gridLayoutWidget = new QWidget(intervals);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 350, 271, 21));
        note1L = new QGridLayout(gridLayoutWidget);
        note1L->setObjectName(QString::fromUtf8("note1L"));
        note1L->setContentsMargins(0, 0, 0, 0);
        note1 = new QLabel(gridLayoutWidget);
        note1->setObjectName(QString::fromUtf8("note1"));
        QFont font1;
        font1.setPointSize(11);
        note1->setFont(font1);
        note1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        note1L->addWidget(note1, 0, 0, 1, 1);

        note1S = new QSimpleShape(gridLayoutWidget);
        note1S->setObjectName(QString::fromUtf8("note1S"));
        note1S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note1S->setProperty("flash0", QVariant(false));

        note1L->addWidget(note1S, 0, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(intervals);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 370, 281, 21));
        note2L = new QGridLayout(gridLayoutWidget_2);
        note2L->setObjectName(QString::fromUtf8("note2L"));
        note2L->setContentsMargins(0, 0, 0, 0);
        note2 = new QLabel(gridLayoutWidget_2);
        note2->setObjectName(QString::fromUtf8("note2"));
        note2->setFont(font1);
        note2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        note2L->addWidget(note2, 0, 0, 1, 1);

        note2S = new QSimpleShape(gridLayoutWidget_2);
        note2S->setObjectName(QString::fromUtf8("note2S"));
        note2S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note2S->setProperty("flash0", QVariant(false));

        note2L->addWidget(note2S, 0, 1, 1, 1);

        gridLayoutWidget_3 = new QWidget(intervals);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 390, 321, 20));
        note3L = new QGridLayout(gridLayoutWidget_3);
        note3L->setObjectName(QString::fromUtf8("note3L"));
        note3L->setContentsMargins(0, 0, 0, 0);
        note3 = new QLabel(gridLayoutWidget_3);
        note3->setObjectName(QString::fromUtf8("note3"));
        note3->setFont(font1);
        note3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        note3L->addWidget(note3, 0, 0, 1, 1);

        note3S = new QSimpleShape(gridLayoutWidget_3);
        note3S->setObjectName(QString::fromUtf8("note3S"));
        note3S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note3S->setProperty("flash0", QVariant(false));

        note3L->addWidget(note3S, 0, 1, 1, 1);

        gridLayoutWidget_4 = new QWidget(intervals);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 410, 491, 21));
        note4L = new QGridLayout(gridLayoutWidget_4);
        note4L->setObjectName(QString::fromUtf8("note4L"));
        note4L->setContentsMargins(0, 0, 0, 0);
        note4 = new QLabel(gridLayoutWidget_4);
        note4->setObjectName(QString::fromUtf8("note4"));
        note4->setFont(font1);
        note4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        note4L->addWidget(note4, 0, 0, 1, 1);

        note4S = new QSimpleShape(gridLayoutWidget_4);
        note4S->setObjectName(QString::fromUtf8("note4S"));
        note4S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note4S->setProperty("flash0", QVariant(false));

        note4L->addWidget(note4S, 0, 1, 1, 1);


        retranslateUi(intervals);
        QObject::connect(buttonBox, SIGNAL(accepted()), intervals, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), intervals, SLOT(reject()));

        QMetaObject::connectSlotsByName(intervals);
    } // setupUi

    void retranslateUi(QDialog *intervals)
    {
        intervals->setWindowTitle(QCoreApplication::translate("intervals", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("intervals", "start", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("intervals", "end", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("intervals", "step", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("intervals", "exposure time(s)", nullptr));
        caution->setText(QCoreApplication::translate("intervals", "<html><head/><body><p>Notes!</p></body></html>", nullptr));
        note1->setText(QCoreApplication::translate("intervals", "1. The start point must be >= 5 ", nullptr));
        note2->setText(QCoreApplication::translate("intervals", "2. The end point must be <= 90 ", nullptr));
        note3->setText(QCoreApplication::translate("intervals", "3. The end point must be > start point ", nullptr));
        note4->setText(QCoreApplication::translate("intervals", "4. The step size must be > 0 and <= (end point - start point) ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class intervals: public Ui_intervals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALS_H
