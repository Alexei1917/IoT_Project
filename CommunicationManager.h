#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QtWebSockets/QWebSocket>
#include <QHostAddress>

class CommunicationManager : public QObject {
    Q_OBJECT

public:
    enum Protocol {
        TCP,
        UDP,
        WebSocket
    };

    explicit CommunicationManager(Protocol protocol, QObject *parent = nullptr);
    ~CommunicationManager();

    // 通用接口
    void connectToHost(const QString &address, quint16 port);
    void disconnect();
    void sendMessage(const QByteArray &message);

signals:
    void dataReceived(const QByteArray &data);
    void connectionStateChanged(bool connected);
    void errorOccurred(const QString &error);

private slots:
    void onTcpReadyRead();
    void onUdpReadyRead();
    void onWebSocketMessageReceived(const QString &message);

private:
    Protocol protocolType;
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
    QWebSocket *webSocket;
};



#endif // COMMUNICATIONMANAGER_H
