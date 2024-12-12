#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QLowEnergyController>
#include <QtBluetooth/QLowEnergyService>

class BluetoothManager : public QObject {
    Q_OBJECT

public:
    explicit BluetoothManager(QObject *parent = nullptr)
        : QObject(parent), discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)), controller(nullptr) {
        // 绑定设备扫描信号槽
        connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothManager::onDeviceDiscovered);
        connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothManager::onScanFinished);
    }

    void startScan() {
        discoveredDevices.clear();
        discoveryAgent->start();
        emit logMessage("Scanning for Bluetooth devices...");
    }

    void connectToDevice(const QBluetoothDeviceInfo &deviceInfo) {
        controller = QLowEnergyController::createCentral(deviceInfo, this);
        connect(controller, &QLowEnergyController::connected, this, &BluetoothManager::onConnected);
        connect(controller, &QLowEnergyController::disconnected, this, &BluetoothManager::onDisconnected);
        connect(controller, &QLowEnergyController::serviceDiscovered, this, &BluetoothManager::onServiceDiscovered);
        connect(controller, &QLowEnergyController::discoveryFinished, this, &BluetoothManager::onServiceDiscoveryFinished);
        controller->connectToDevice();
        emit logMessage("Connecting to device: " + deviceInfo.name());
    }

signals:
    void deviceFound(const QBluetoothDeviceInfo &deviceInfo);
    void logMessage(const QString &message);

private slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo) {
        discoveredDevices.append(deviceInfo);
        emit deviceFound(deviceInfo);
    }

    void onScanFinished() {
        emit logMessage("Device scan finished.");
    }

    void onConnected() {
        emit logMessage("Device connected.");
        controller->discoverServices();
    }

    void onDisconnected() {
        emit logMessage("Device disconnected.");
    }

    void onServiceDiscovered(const QBluetoothUuid &uuid) {
        emit logMessage("Service discovered: " + uuid.toString());
    }

    void onServiceDiscoveryFinished() {
        emit logMessage("Service discovery finished.");
    }

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QBluetoothDeviceInfo> discoveredDevices;
    QLowEnergyController *controller;
};


#endif // BLUETOOTH_H
