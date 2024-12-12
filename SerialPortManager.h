#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H


#include <QSerialPort>
#include <QObject>
#include <QByteArray>

class SerialPortManager : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortManager(QObject *parent = nullptr);
    ~SerialPortManager();

    void openPort(const QString &portName, int baudRate);
    void closePort();
    void sendData(const QByteArray &data);
    QByteArray readData();

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);

private:
    QSerialPort *serialPort;
};


#endif // SERIALPORTMANAGER_H
