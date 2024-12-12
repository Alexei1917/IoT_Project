#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtBluetooth/QBluetoothSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void serialPortSelection_init();
    void serialPort_configure();
    void serialPort_();
    void save_log();//保存日志文件
    void receive();//文本接收
    void receive16();//十六进制接收
    void pause();//暂停接收
    void serialPort_close();//断开串口
    void send();//串口发送
    void sendText();//文本发送
    void send16();//十六进制发送
    void clear_Send();//清除发送区
    void clear_Receive();//清除接收区

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
