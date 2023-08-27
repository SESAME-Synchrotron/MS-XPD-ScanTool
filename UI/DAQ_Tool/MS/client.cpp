#include "client.h"

// Client* Client::p_instance = NULL;

void Client::writePV(QString name, QString value)
{
    if(!_writePV(name, value.toStdString().c_str(), DBF_STRING))
    {
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }
}

void Client::writePV(QString name, int value)
{
    if(!_writePV(name, &value, DBF_INT))
    {
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }
}

void Client::writePV(QString name, double value)
{
    if(!_writePV(name, &value, DBF_DOUBLE))
    {
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }
}

void Client::writePV(QString name, unsigned value)
{
    if(!_writePV(name, &value, DBF_LONG))
    {
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }
}

void Client::writeArray(QString name, void *data, unsigned long size)
{
    int status;
    chid pvID;

    ca_search(name.toStdString().c_str(), &pvID);
    status = ca_pend_io(1);
    if(status != ECA_NORMAL)
    {
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }

    ca_array_put(DBF_LONG, size, pvID, data);
//    ca_array_put(DBF_DOUBLE, size, pvID, data);
    return;
}

void Client::writeStringToWaveform(QString name, QString value)
{
    int status;
    chid pvID;

    ca_search(name.toStdString().c_str(), &pvID);
    status = ca_pend_io(1);
    if (status != ECA_NORMAL)
    {
        QMessageBox::warning(nullptr, "Error writing to PV", "Could not write the value to PV: " + name);
        return;
    }

    ca_array_put(DBR_CHAR, value.length() + 1, pvID, const_cast<char*>(value.toStdString().c_str()));
    return;
}

bool Client::_writePV(QString name, const void* value, int type)
{
    int status;
    chid pvID;

    ca_search(name.toStdString().c_str(), &pvID);
    status = ca_pend_io(1);
    if(status != ECA_NORMAL)
    {
        return false;
    }

    ca_put(type, pvID, value);
    return true;
}
