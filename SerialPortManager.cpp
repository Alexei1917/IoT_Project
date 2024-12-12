#include "SerialPortManager.h"
#include <QSerialPortInfo>
#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent), serialPort(new QSerialPort(this))
{
    connect(serialPort, &QSerialPort::readyRead, this, [this]() {
        emit dataReceived(serialPort->readAll());
    });
    connect(serialPort, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
        if (error != QSerialPort::NoError) {
            emit errorOccurred(serialPort->errorString());
        }
    });
}

SerialPortManager::~SerialPortManager()
{
    closePort();
}

void SerialPortManager::openPort(const QString &portName, int baudRate)
{
    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadWrite)) {
        emit errorOccurred("Failed to open port");
    }
}

void SerialPortManager::closePort()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
}

void SerialPortManager::sendData(const QByteArray &data)
{
    if (serialPort->isOpen()) {
        serialPort->write(data);
    }
}

QByteArray SerialPortManager::readData()
{
    return serialPort->readAll();
}
