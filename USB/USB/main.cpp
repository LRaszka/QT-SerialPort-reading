#include <QSerialPort>
#include <QSerialPortInfo>
QSerialPort serial;

#include <iostream>
#include <string>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

using namespace std;

void txt(QByteArray data)
{
    QFile file("test.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not open file!";
        qCritical() << file.errorString();
        return;
    }

    qInfo() <<  "Writing file ..";
    file.write(data);
    file.flush(); //pushes the data to the disk

    qInfo() << "Reading file ..";
    file.seek(0);
    qInfo() << file.readAll();

    file.close();
}


int main()
{
    //Vypis portu
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator i;
    for(i = ports.begin(); i != ports.end(); i++)
    {
        printf(" - Name: %s\n", (*i).portName().toStdString().data());
    }

    //Nastavení portu
    serial.setPortName("com4");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);

    //Vyčitání dat
    while(serial.isOpen())
    {
        if(!serial.waitForReadyRead(-1)) //blokace dokud nedorazi nova data
            cout << "Cekani na nová data" << endl;
        else{
            cout << "Dorazila nova data" << endl;
            QByteArray data = serial.readAll();
            txt(data);
        }
    }

//ERROR - STACK https://stackoverflow.com/questions/42576537/qt-serial-port-reading
//Port info https://stackoverflow.com/questions/26222822/cannot-compile-due-to-undefined-qserialportinfo-method-references
}
