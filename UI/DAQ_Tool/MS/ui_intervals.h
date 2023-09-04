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
    QWidget *gridLayoutWidget_5;
    QGridLayout *notesL;
    QGridLayout *note3L;
    QLabel *note3;
    QSimpleShape *note3S;
    QGridLayout *note2L;
    QLabel *note2;
    QSimpleShape *note2S;
    QLabel *caution;
    QGridLayout *note1L;
    QSimpleShape *note1S;
    QLabel *note1;
    QGridLayout *note4L;
    QLabel *note4;
    QSimpleShape *note4S;

    void setupUi(QDialog *intervals)
    {
        if (intervals->objectName().isEmpty())
            intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->resize(601, 456);
        buttonBox = new QDialogButtonBox(intervals);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(500, 10, 91, 301));
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
        gridLayoutWidget_5 = new QWidget(intervals);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(10, 320, 584, 131));
        notesL = new QGridLayout(gridLayoutWidget_5);
        notesL->setObjectName(QString::fromUtf8("notesL"));
        notesL->setContentsMargins(0, 0, 0, 0);
        note3L = new QGridLayout();
        note3L->setObjectName(QString::fromUtf8("note3L"));
        note3 = new QLabel(gridLayoutWidget_5);
        note3->setObjectName(QString::fromUtf8("note3"));
        QFont font;
        font.setFamily(QString::fromUtf8("Nimbus Mono PS [urw]"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        note3->setFont(font);
        note3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note3L->addWidget(note3, 0, 0, 1, 1);

        note3S = new QSimpleShape(gridLayoutWidget_5);
        note3S->setObjectName(QString::fromUtf8("note3S"));
        note3S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note3S->setProperty("flash0", QVariant(false));

        note3L->addWidget(note3S, 0, 1, 1, 1);


        notesL->addLayout(note3L, 3, 0, 1, 1);

        note2L = new QGridLayout();
        note2L->setObjectName(QString::fromUtf8("note2L"));
        note2 = new QLabel(gridLayoutWidget_5);
        note2->setObjectName(QString::fromUtf8("note2"));
        note2->setFont(font);
        note2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note2L->addWidget(note2, 0, 0, 1, 1);

        note2S = new QSimpleShape(gridLayoutWidget_5);
        note2S->setObjectName(QString::fromUtf8("note2S"));
        note2S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note2S->setProperty("flash0", QVariant(false));

        note2L->addWidget(note2S, 0, 1, 1, 1);


        notesL->addLayout(note2L, 2, 0, 1, 1);

        caution = new QLabel(gridLayoutWidget_5);
        caution->setObjectName(QString::fromUtf8("caution"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Nimbus Mono PS [urw]"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStyleStrategy(QFont::PreferDefault);
        caution->setFont(font1);
        caution->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));
        caution->setFrameShape(QFrame::StyledPanel);

        notesL->addWidget(caution, 0, 0, 1, 1);

        note1L = new QGridLayout();
        note1L->setObjectName(QString::fromUtf8("note1L"));
        note1S = new QSimpleShape(gridLayoutWidget_5);
        note1S->setObjectName(QString::fromUtf8("note1S"));
        note1S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note1S->setProperty("flash0", QVariant(false));

        note1L->addWidget(note1S, 0, 1, 1, 1);

        note1 = new QLabel(gridLayoutWidget_5);
        note1->setObjectName(QString::fromUtf8("note1"));
        note1->setFont(font);
        note1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note1L->addWidget(note1, 0, 0, 1, 1);


        notesL->addLayout(note1L, 1, 0, 1, 1);

        note4L = new QGridLayout();
        note4L->setObjectName(QString::fromUtf8("note4L"));
        note4 = new QLabel(gridLayoutWidget_5);
        note4->setObjectName(QString::fromUtf8("note4"));
        note4->setFont(font);
        note4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note4L->addWidget(note4, 0, 0, 1, 1);

        note4S = new QSimpleShape(gridLayoutWidget_5);
        note4S->setObjectName(QString::fromUtf8("note4S"));
        note4S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note4S->setProperty("flash0", QVariant(false));

        note4L->addWidget(note4S, 0, 1, 1, 1);


        notesL->addLayout(note4L, 4, 0, 1, 1);


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
        note3->setText(QCoreApplication::translate("intervals", "3. The end point must be > start point ", nullptr));
        note2->setText(QCoreApplication::translate("intervals", "2. The end point must be <= 90 ", nullptr));
        caution->setText(QCoreApplication::translate("intervals", "<html><head/><body><p>Notes!</p></body></html>", nullptr));
        note1->setText(QCoreApplication::translate("intervals", "1. The start point must be >= 5 ", nullptr));
        note4->setText(QCoreApplication::translate("intervals", "4. The step size must be > 0 and <= (end point - start point) ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class intervals: public Ui_intervals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALS_H
