#ifndef FIRMWAREUPLOADER_H
#define FIRMWAREUPLOADER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include <QSerialPort>

class FirmwareUploader : public QObject
{
    Q_OBJECT

public:
    explicit FirmwareUploader(QSerialPort *serialPort, QObject *parent = nullptr);
    ~FirmwareUploader();

    bool loadFirmware(const QString &filePath);
    void startUpload();

signals:
    void uploadProgress(int percentage);  // 上传进度信号
    void uploadFinished(bool success);   // 上传完成信号
    void errorOccurred(const QString &error); // 错误信号

private slots:
    void sendNextChunk();  // 发送下一块数据

private:
    QFile firmwareFile;         // 固件文件
    QSerialPort *serialPort;    // 串口
    QByteArray currentChunk;    // 当前发送的数据块
    int totalBytes;             // 固件总字节数
    int bytesSent;              // 已发送字节数
    QTimer chunkTimer;          // 用于发送分块数据
    const int chunkSize = 256;  // 每块发送 256 字节
};

#endif // FIRMWAREUPLOADER_H
