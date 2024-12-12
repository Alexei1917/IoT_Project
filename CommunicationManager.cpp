#include "CommunicationManager.h"

// TCP通信

CommunicationManager::CommunicationManager(Protocol protocol, QObject *parent)
    : QObject(parent), protocolType(protocol), tcpSocket(nullptr), udpSocket(nullptr), webSocket(nullptr) {
    if (protocol == TCP) {
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket, &QTcpSocket::readyRead, this, &CommunicationManager::onTcpReadyRead);
        connect(tcpSocket, &QTcpSocket::connected, this, [this]() {
            emit connectionStateChanged(true);
        });
        connect(tcpSocket, &QTcpSocket::disconnected, this, [this]() {
            emit connectionStateChanged(false);
        });
        connect(tcpSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError socketError) {
            emit errorOccurred(tcpSocket->errorString());
        });
    }
}

void CommunicationManager::connectToHost(const QString &address, quint16 port) {
    if (protocolType == TCP && tcpSocket) {
        tcpSocket->connectToHost(QHostAddress(address), port);
    }
}

void CommunicationManager::disconnect() {
    if (protocolType == TCP && tcpSocket) {
        tcpSocket->disconnectFromHost();
    }
}

void CommunicationManager::sendMessage(const QByteArray &message) {
    if (protocolType == TCP && tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(message);
    }
}

void CommunicationManager::onTcpReadyRead() {
    QByteArray data = tcpSocket->readAll();
    emit dataReceived(data);
}




// UPD通信

void CommunicationManager::connectToHost(const QString &address, quint16 port) {
    if (protocolType == UDP) {
        udpSocket = new QUdpSocket(this);
        udpSocket->bind(QHostAddress::Any, port);

        connect(udpSocket, &QUdpSocket::readyRead, this, &CommunicationManager::onUdpReadyRead);
    }
}

void CommunicationManager::sendMessage(const QByteArray &message) {
    if (protocolType == UDP && udpSocket) {
        udpSocket->writeDatagram(message, QHostAddress("255.255.255.255"), udpSocket->localPort());
    }
}

void CommunicationManager::onUdpReadyRead() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(data.data(), data.size());
        emit dataReceived(data);
    }
}

// WebSocket 通信功能

#include <QWebSocket>

void CommunicationManager::connectToHost(const QString &address, quint16 port) {
    if (protocolType == WebSocket) {
        webSocket = new QWebSocket();
        connect(webSocket, &QWebSocket::connected, this, [this]() {
            emit connectionStateChanged(true);
        });
        connect(webSocket, &QWebSocket::disconnected, this, [this]() {
            emit connectionStateChanged(false);
        });
        connect(webSocket, &QWebSocket::textMessageReceived, this, &CommunicationManager::onWebSocketMessageReceived);
        connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, [this](QAbstractSocket::SocketError error) {
            emit errorOccurred(webSocket->errorString());
        });

        webSocket->open(QUrl(QString("ws://%1:%2").arg(address).arg(port)));
    }
}

void CommunicationManager::disconnect() {
    if (protocolType == WebSocket && webSocket) {
        webSocket->close();
    }
}

void CommunicationManager::sendMessage(const QByteArray &message) {
    if (protocolType == WebSocket && webSocket) {
        webSocket->sendTextMessage(message);
    }
}

void CommunicationManager::onWebSocketMessageReceived(const QString &message) {
    emit dataReceived(message.toUtf8());
}


// 通信类通过 Protocol 枚举实现多种协议的灵活切换，简化上层调用
/*
CommunicationManager manager(CommunicationManager::TCP);
manager.connectToHost("192.168.1.100", 1883);  // MQTT Server
connect(&manager, &CommunicationManager::dataReceived, [](const QByteArray &data) {
    qDebug() << "Received Data:" << data;
});
manager.sendMessage("Hello, IoT!");
*/


/*
改进
支持 TLS/SSL：

可在 QTcpSocket 或 QWebSocket 上启用 SSL 支持，用于安全通信。
使用 QSslConfiguration 配置证书。
协议层解析：

在数据接收后调用协议解析器（如 MQTT、HTTP）。
重连机制：

实现断线自动重连逻辑，增强稳定性。
多线程支持：

使用 QThread 将通信模块与 GUI 分离，避免阻塞主线程。

*/
