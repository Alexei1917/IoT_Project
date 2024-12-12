#include "bluetooth.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setupConnections();
    }

private:
    QListWidget *deviceList;
    QPushButton *scanButton, *connectButton;
    QTextEdit *logOutput;
    BluetoothManager *bluetoothManager;
    QBluetoothDeviceInfo selectedDevice;

    void setupUI() {
        // 使用 QVBoxLayout 和 QHBoxLayout 布局（代码略）
    }

    void setupConnections() {
        bluetoothManager = new BluetoothManager(this);

        connect(scanButton, &QPushButton::clicked, this, &MainWindow::onScanClicked);
        connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);

        connect(bluetoothManager, &BluetoothManager::deviceFound, this, &MainWindow::addDeviceToList);
        connect(bluetoothManager, &BluetoothManager::logMessage, this, &MainWindow::appendLog);
    }

private slots:
    void onScanClicked() {
        bluetoothManager->startScan();
    }

    void onConnectClicked() {
        auto selectedItems = deviceList->selectedItems();
        if (!selectedItems.isEmpty()) {
            const QString &deviceName = selectedItems.first()->text();
            for (const auto &device : bluetoothManager->getDiscoveredDevices()) {
                if (device.name() == deviceName) {
                    selectedDevice = device;
                    bluetoothManager->connectToDevice(device);
                    break;
                }
            }
        }
    }

    void addDeviceToList(const QBluetoothDeviceInfo &deviceInfo) {
        deviceList->addItem(deviceInfo.name());
    }

    void appendLog(const QString &message) {
        logOutput->append(message);
    }
};
