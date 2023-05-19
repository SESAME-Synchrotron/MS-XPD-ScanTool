#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <qepicspv.h>
#include <QFileInfo>
// #include <QRandomGenerator>

#include <fstream>
#include <iostream>
#include <string>

#include <cadef.h>
#include <db_access.h>

class Client : public QObject
{
    Q_OBJECT

public:
    static void writePV(QString name, QString value);
    static void writePV(QString name, int value);
    static void writePV(QString name, double value);
    static void writePV(QString name, unsigned value);
    static void writeArray(QString name, void* data, unsigned long size);
    static void writeStringToWaveform(QString name, QString value);

private:
    Client() {}
    ~Client() {}
    static bool _writePV(QString name, const void* value, int type);

public slots:
};

#define casearch(name, pv) SEVCHK( (pv).status = ( ca_search( (name), &(pv).channel ) ), name)

#define cainfo(pv, type) SEVCHK(\
    (pv).status = (ca_state((pv).channel) != cs_conn ? ECA_DISCONN : \
    ca_get(dbf_type_to_DBR_CTRL(type), (pv).channel, &(pv).info)), ca_name((pv).channel))

#define caget(pv, type) SEVCHK(\
    (pv).status = (ca_state((pv).channel) != cs_conn ? ECA_DISCONN : \
    ca_get(dbf_type_to_DBR_STS(type), (pv).channel, &(pv).data)), ca_name((pv).channel))

typedef struct {
    chid channel;
    int status;
    struct dbr_ctrl_double info;
    struct dbr_sts_double data;
} epicsDoublePV;

/* There is more than just double values, e.g. long integers */
typedef struct {
    chid channel;
    int status;
    struct dbr_ctrl_long info;
    struct dbr_sts_long data;
} epicsLongPV;

/* Enums are something special: they have a table of strings attached */
typedef struct {
    chid channel;
    int status;
    struct dbr_ctrl_enum info;
    struct dbr_sts_enum data;
} epicsEnumPV;

/* Strings don't have a dbr_ctrl_ structure. They are too primitive */
typedef struct {
    chid channel;
    int status;
    struct dbr_sts_string data;
} epicsStringPV;

typedef struct {
    chid channel;
    int  status;
    struct dbr_ctrl_char info;
    struct dbr_sts_char data;
} epicsCharacterPV;

#endif // CLIENT_H

//    static Client& GetInstance()
//    {
//        static Client newInstance;
//        p_instance = &newInstance;
//        return *p_instance;
//    }
//
// private:
//    static Client* p_instance;
//    Client(const Client& otherInstance) : QObject(0)
//    {
//        p_instance = otherInstance.p_instance;
//    }
//    Client& operator = (const Client& otherInstance)
//    {
//        if(this != &otherInstance)
//            p_instance = otherInstance.p_instance;

//        return *this;
//    }
