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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_intervals
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;

    void setupUi(QDialog *intervals)
    {
        if (intervals->objectName().isEmpty())
            intervals->setObjectName(QString::fromUtf8("intervals"));
        intervals->resize(589, 317);
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
    } // retranslateUi

};

namespace Ui {
    class intervals: public Ui_intervals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALS_H
