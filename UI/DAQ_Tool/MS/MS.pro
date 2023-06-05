QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = /home/dcasu/MStest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    intervals.cpp \
    main.cpp \
    samples.cpp \
    wizard.cpp

HEADERS += \
    client.h \
    intervals.h \
    samples.h \
    wizard.h

FORMS += \
    intervals.ui \
    samples.ui \
    wizard.ui

unix:!macx: LIBS += -L$(QE_TARGET_DIR)/lib/linux-x86_64/ -lQEFramework
unix:!macx: LIBS += -L$$(QE_TARGET_DIR)/lib/linux-x86_64/designer -lQEPlugin
unix:!macx: LIBS += -L$$(QWT_ROOT)/lib/ -lqwt
unix:!macx: LIBS += -L$$(EPICS_BASE)/lib/linux-x86_64/ -lca
unix:!macx: LIBS += -L$$(EPICS_BASE)/lib/linux-x86_64/ -lCom

INCLUDEPATH += $$(QE_TARGET_DIR)/include
INCLUDEPATH += $$(QWT_ROOT)/include
INCLUDEPATH += $$(EPICS_BASE)/include
INCLUDEPATH += $$(EPICS_BASE)/include/os/Linux
INCLUDEPATH += $$(EPICS_BASE)/include/compiler/gcc/

DEPENDPATH  += $$(QE_TARGET_DIR)/include
DEPENDPATH  += $$(QWT_ROOT)/include
DEPENDPATH  += $$(EPICS_BASE)/include
DEPENDPATH  += $$(EPICS_BASE)/include/os/Linux

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sampleContainer.qrc
