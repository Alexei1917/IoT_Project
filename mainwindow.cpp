#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("串口工具");
    serialPortSelection_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//搜索可用的串口，并添加到串口组合框
void MainWindow::serialPortSelection_init()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serialPortComboBox->addItem(info.portName());
    }
}

//打开串口
void MainWindow::serialPort_configure()
{

}

//数据发送功能

//数据接收功能

//十六进制/ASCII显示

//日志保存功能

//串口UI
/*
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportmanager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      serialPortManager(new SerialPortManager(this))
{
    ui->setupUi(this);

    connect(serialPortManager, &SerialPortManager::dataReceived, this, &MainWindow::onDataReceived);
    connect(serialPortManager, &SerialPortManager::errorOccurred, this, &MainWindow::onErrorOccurred);

    ui->sendButton->setEnabled(false);

    // Populate the port list
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->portComboBox->addItem(info.portName());
    }

    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenButtonClicked()
{
    QString portName = ui->portComboBox->currentText();
    int baudRate = ui->baudRateComboBox->currentText().toInt();
    serialPortManager->openPort(portName, baudRate);
    ui->sendButton->setEnabled(true);
}

void MainWindow::onSendButtonClicked()
{
    QByteArray data = ui->sendTextEdit->toPlainText().toUtf8();
    serialPortManager->sendData(data);
}

void MainWindow::onDataReceived(const QByteArray &data)
{
    ui->receiveTextEdit->append(data);
}

void MainWindow::onErrorOccurred(const QString &error)
{
    QMessageBox::critical(this, "Error", error);
}
*/
