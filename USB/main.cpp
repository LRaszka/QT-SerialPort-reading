#include <QSerialPort>
QSerialPort serial;

#include <iostream>
#include <string>

using namespace std;

int main()
{
    serial.setPortName("com4");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);

    while(serial.isOpen())
    {
        if(!serial.waitForReadyRead(-1)) //blokace dokud nedorazi nova data
            cout << "Cekani na nová data" << endl;
        else{
            cout << "Dorazila nova data" << endl;
            QByteArray data = serial.readAll();
        }
    }


//ERROR - STACK https://stackoverflow.com/questions/42576537/qt-serial-port-reading

}
