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
#include <QtWidgets/QGroupBox>
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
    QLabel *caution;
    QGridLayout *note4L;
    QLabel *note4;
    QSimpleShape *note4S;
    QGridLayout *note1L;
    QSimpleShape *note1S;
    QLabel *intervalsWarning;
    QSimpleShape *intervalsWarningS1;
    QSimpleShape *intervalsWarningS2;
    QLabel *note1;
    QGridLayout *note3L;
    QLabel *note3;
    QSimpleShape *note3S;
    QGridLayout *note2L;
    QLabel *note2;
    QSimpleShape *note2S;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_6;
    QGridLayout *tempCautionsL;
    QGridLayout *note3L_2;
    QLabel *note3_2;
    QSimpleShape *note3S_2;
    QGridLayout *note2L_2;
    QLabel *note2_2;
    QSimpleShape *note2S_2;
    QLabel *tempCaution;
    QGridLayout *note1L_2;
    QSimpleShape *note1S_2;
    QLabel *intervalsWarning2;
    QSimpleShape *intervalsWarningS1_2;
    QSimpleShape *intervalsWarningS2_2;
    QLabel *note1_2;
    QGridLayout *note4L_2;
    QLabel *note4_2;
    QSimpleShape *note4S_2;

    void setupUi(QDialog *intervals)
    {
        if (intervals->objectName().isEmpty())
            intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->resize(1220, 489);
        buttonBox = new QDialogButtonBox(intervals);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(1131, 9, 80, 54));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        tableWidget = new QTableWidget(intervals);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(9, 9, 1111, 301));
        tableWidget->setMouseTracking(false);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setColumnCount(9);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        gridLayoutWidget_5 = new QWidget(intervals);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(9, 320, 591, 160));
        notesL = new QGridLayout(gridLayoutWidget_5);
        notesL->setObjectName(QString::fromUtf8("notesL"));
        notesL->setContentsMargins(0, 0, 0, 0);
        caution = new QLabel(gridLayoutWidget_5);
        caution->setObjectName(QString::fromUtf8("caution"));
        QFont font;
        font.setFamily(QString::fromUtf8("Nimbus Mono PS [urw]"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferDefault);
        caution->setFont(font);
        caution->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));
        caution->setFrameShape(QFrame::StyledPanel);

        notesL->addWidget(caution, 0, 0, 1, 1);

        note4L = new QGridLayout();
        note4L->setObjectName(QString::fromUtf8("note4L"));
        note4 = new QLabel(gridLayoutWidget_5);
        note4->setObjectName(QString::fromUtf8("note4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Nimbus Mono PS [urw]"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        note4->setFont(font1);
        note4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note4L->addWidget(note4, 0, 0, 1, 1);

        note4S = new QSimpleShape(gridLayoutWidget_5);
        note4S->setObjectName(QString::fromUtf8("note4S"));
        note4S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note4S->setProperty("flash0", QVariant(false));

        note4L->addWidget(note4S, 0, 1, 1, 1);


        notesL->addLayout(note4L, 4, 0, 1, 1);

        note1L = new QGridLayout();
        note1L->setObjectName(QString::fromUtf8("note1L"));
        note1S = new QSimpleShape(gridLayoutWidget_5);
        note1S->setObjectName(QString::fromUtf8("note1S"));
        note1S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note1S->setProperty("flash0", QVariant(false));

        note1L->addWidget(note1S, 1, 2, 1, 1);

        intervalsWarning = new QLabel(gridLayoutWidget_5);
        intervalsWarning->setObjectName(QString::fromUtf8("intervalsWarning"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Nimbus Mono PS [urw]"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        intervalsWarning->setFont(font2);
        intervalsWarning->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));
        intervalsWarning->setFrameShape(QFrame::StyledPanel);
        intervalsWarning->setAlignment(Qt::AlignCenter);

        note1L->addWidget(intervalsWarning, 0, 1, 1, 1);

        intervalsWarningS1 = new QSimpleShape(gridLayoutWidget_5);
        intervalsWarningS1->setObjectName(QString::fromUtf8("intervalsWarningS1"));
        intervalsWarningS1->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        intervalsWarningS1->setProperty("flash0", QVariant(false));

        note1L->addWidget(intervalsWarningS1, 0, 2, 1, 1);

        intervalsWarningS2 = new QSimpleShape(gridLayoutWidget_5);
        intervalsWarningS2->setObjectName(QString::fromUtf8("intervalsWarningS2"));
        intervalsWarningS2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        intervalsWarningS2->setProperty("flash0", QVariant(false));

        note1L->addWidget(intervalsWarningS2, 0, 0, 1, 1);

        note1 = new QLabel(gridLayoutWidget_5);
        note1->setObjectName(QString::fromUtf8("note1"));
        note1->setFont(font1);
        note1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note1L->addWidget(note1, 1, 0, 1, 2);


        notesL->addLayout(note1L, 1, 0, 1, 1);

        note3L = new QGridLayout();
        note3L->setObjectName(QString::fromUtf8("note3L"));
        note3 = new QLabel(gridLayoutWidget_5);
        note3->setObjectName(QString::fromUtf8("note3"));
        note3->setFont(font1);
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
        note2->setFont(font1);
        note2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note2L->addWidget(note2, 0, 0, 1, 1);

        note2S = new QSimpleShape(gridLayoutWidget_5);
        note2S->setObjectName(QString::fromUtf8("note2S"));
        note2S->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note2S->setProperty("flash0", QVariant(false));

        note2L->addWidget(note2S, 0, 1, 1, 1);


        notesL->addLayout(note2L, 2, 0, 1, 1);

        groupBox = new QGroupBox(intervals);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(610, 320, 601, 161));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0);\n"
"border-color: rgba(0, 0, 0, 0);"));
        gridLayoutWidget_6 = new QWidget(groupBox);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 0, 601, 161));
        tempCautionsL = new QGridLayout(gridLayoutWidget_6);
        tempCautionsL->setObjectName(QString::fromUtf8("tempCautionsL"));
        tempCautionsL->setContentsMargins(0, 0, 0, 0);
        note3L_2 = new QGridLayout();
        note3L_2->setObjectName(QString::fromUtf8("note3L_2"));
        note3_2 = new QLabel(gridLayoutWidget_6);
        note3_2->setObjectName(QString::fromUtf8("note3_2"));
        note3_2->setFont(font1);
        note3_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note3L_2->addWidget(note3_2, 0, 0, 1, 1);

        note3S_2 = new QSimpleShape(gridLayoutWidget_6);
        note3S_2->setObjectName(QString::fromUtf8("note3S_2"));
        note3S_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note3S_2->setProperty("flash0", QVariant(false));

        note3L_2->addWidget(note3S_2, 0, 1, 1, 1);


        tempCautionsL->addLayout(note3L_2, 3, 0, 1, 1);

        note2L_2 = new QGridLayout();
        note2L_2->setObjectName(QString::fromUtf8("note2L_2"));
        note2_2 = new QLabel(gridLayoutWidget_6);
        note2_2->setObjectName(QString::fromUtf8("note2_2"));
        note2_2->setFont(font1);
        note2_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note2L_2->addWidget(note2_2, 0, 0, 1, 1);

        note2S_2 = new QSimpleShape(gridLayoutWidget_6);
        note2S_2->setObjectName(QString::fromUtf8("note2S_2"));
        note2S_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note2S_2->setProperty("flash0", QVariant(false));

        note2L_2->addWidget(note2S_2, 0, 1, 1, 1);


        tempCautionsL->addLayout(note2L_2, 2, 0, 1, 1);

        tempCaution = new QLabel(gridLayoutWidget_6);
        tempCaution->setObjectName(QString::fromUtf8("tempCaution"));
        tempCaution->setFont(font);
        tempCaution->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));
        tempCaution->setFrameShape(QFrame::StyledPanel);

        tempCautionsL->addWidget(tempCaution, 0, 0, 1, 1);

        note1L_2 = new QGridLayout();
        note1L_2->setObjectName(QString::fromUtf8("note1L_2"));
        note1S_2 = new QSimpleShape(gridLayoutWidget_6);
        note1S_2->setObjectName(QString::fromUtf8("note1S_2"));
        note1S_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note1S_2->setProperty("flash0", QVariant(false));

        note1L_2->addWidget(note1S_2, 1, 2, 1, 1);

        intervalsWarning2 = new QLabel(gridLayoutWidget_6);
        intervalsWarning2->setObjectName(QString::fromUtf8("intervalsWarning2"));
        intervalsWarning2->setFont(font2);
        intervalsWarning2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));
        intervalsWarning2->setFrameShape(QFrame::StyledPanel);
        intervalsWarning2->setAlignment(Qt::AlignCenter);

        note1L_2->addWidget(intervalsWarning2, 0, 1, 1, 1);

        intervalsWarningS1_2 = new QSimpleShape(gridLayoutWidget_6);
        intervalsWarningS1_2->setObjectName(QString::fromUtf8("intervalsWarningS1_2"));
        intervalsWarningS1_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        intervalsWarningS1_2->setProperty("flash0", QVariant(false));

        note1L_2->addWidget(intervalsWarningS1_2, 0, 2, 1, 1);

        intervalsWarningS2_2 = new QSimpleShape(gridLayoutWidget_6);
        intervalsWarningS2_2->setObjectName(QString::fromUtf8("intervalsWarningS2_2"));
        intervalsWarningS2_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        intervalsWarningS2_2->setProperty("flash0", QVariant(false));

        note1L_2->addWidget(intervalsWarningS2_2, 0, 0, 1, 1);

        note1_2 = new QLabel(gridLayoutWidget_6);
        note1_2->setObjectName(QString::fromUtf8("note1_2"));
        note1_2->setFont(font1);
        note1_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note1L_2->addWidget(note1_2, 1, 0, 1, 2);


        tempCautionsL->addLayout(note1L_2, 1, 0, 1, 1);

        note4L_2 = new QGridLayout();
        note4L_2->setObjectName(QString::fromUtf8("note4L_2"));
        note4_2 = new QLabel(gridLayoutWidget_6);
        note4_2->setObjectName(QString::fromUtf8("note4_2"));
        note4_2->setFont(font1);
        note4_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 150);"));

        note4L_2->addWidget(note4_2, 0, 0, 1, 1);

        note4S_2 = new QSimpleShape(gridLayoutWidget_6);
        note4S_2->setObjectName(QString::fromUtf8("note4S_2"));
        note4S_2->setProperty("colour0", QVariant(QColor(255, 0, 0)));
        note4S_2->setProperty("flash0", QVariant(false));

        note4L_2->addWidget(note4S_2, 0, 1, 1, 1);


        tempCautionsL->addLayout(note4L_2, 4, 0, 1, 1);

        groupBox->raise();
        tableWidget->raise();
        gridLayoutWidget_5->raise();
        buttonBox->raise();

        retranslateUi(intervals);
        QObject::connect(buttonBox, SIGNAL(accepted()), intervals, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), intervals, SLOT(reject()));

        QMetaObject::connectSlotsByName(intervals);
    } // setupUi

    void retranslateUi(QDialog *intervals)
    {
        intervals->setWindowTitle(QCoreApplication::translate("intervals", "Intervals", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("intervals", "2\316\270 start", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("intervals", "2\316\270 end", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("intervals", "2\316\270 step", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("intervals", "exposure time(s)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("intervals", "T start(\302\260c)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("intervals", "T end(\302\260c)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("intervals", "T step(\302\260c)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("intervals", "N scans", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("intervals", "T settlingTime(s)", nullptr));
        caution->setText(QCoreApplication::translate("intervals", "<html><head/><body><p>Notes!</p></body></html>", nullptr));
        note4->setText(QCoreApplication::translate("intervals", "4. The step size must be > 0 and <= (end point - start point) ", nullptr));
        intervalsWarning->setText(QString());
        note1->setText(QCoreApplication::translate("intervals", "1. The start point must be >= 5 ", nullptr));
        note3->setText(QCoreApplication::translate("intervals", "3. The end point must be >= start point ", nullptr));
        note2->setText(QCoreApplication::translate("intervals", "2. The end point must be <= 90 ", nullptr));
        groupBox->setTitle(QString());
        note3_2->setText(QCoreApplication::translate("intervals", "3. The end point must be >= start point ", nullptr));
        note2_2->setText(QCoreApplication::translate("intervals", "2. The min temperature must be >= 25 \302\260C", nullptr));
        tempCaution->setText(QCoreApplication::translate("intervals", "<html><head/><body><p>Temperature Cautions!</p></body></html>", nullptr));
        intervalsWarning2->setText(QString());
        note1_2->setText(QCoreApplication::translate("intervals", "1. The max temperature must be <=  1000 \302\260C", nullptr));
        note4_2->setText(QCoreApplication::translate("intervals", "4. The step size must be > 0 and <= (end point - start point) ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class intervals: public Ui_intervals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALS_H
