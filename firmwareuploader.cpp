#include "firmwareuploader.h"
#include <QDebug>

FirmwareUploader::FirmwareUploader(QSerialPort *serialPort, QObject *parent)
    : QObject(parent), serialPort(serialPort), bytesSent(0), totalBytes(0)
{
    connect(&chunkTimer, &QTimer::timeout, this, &FirmwareUploader::sendNextChunk);
}

FirmwareUploader::~FirmwareUploader()
{
    if (firmwareFile.isOpen()) {
        firmwareFile.close();
    }
}

bool FirmwareUploader::loadFirmware(const QString &filePath)
{
    firmwareFile.setFileName(filePath);
    if (!firmwareFile.open(QIODevice::ReadOnly)) {
        emit errorOccurred("Failed to open firmware file.");
        return false;
    }
    totalBytes = firmwareFile.size();
    bytesSent = 0;
    return true;
}

void FirmwareUploader::startUpload()
{
    if (!firmwareFile.isOpen() || !serialPort->isOpen()) {
        emit errorOccurred("Firmware file or serial port is not ready.");
        return;
    }

    // 开始上传
    chunkTimer.start(50); // 每隔 50ms 发送一块
}

void FirmwareUploader::sendNextChunk()
{
    if (bytesSent >= totalBytes) {
        chunkTimer.stop();
        emit uploadFinished(true); // 上传完成
        return;
    }

    // 读取下一块数据
    currentChunk = firmwareFile.read(chunkSize);
    if (currentChunk.isEmpty()) {
        chunkTimer.stop();
        emit errorOccurred("Failed to read firmware file.");
        return;
    }

    // 发送数据块
    serialPort->write(currentChunk);
    if (!serialPort->waitForBytesWritten(100)) {
        chunkTimer.stop();
        emit errorOccurred("Failed to send data to device.");
        return;
    }

    // 更新进度
    bytesSent += currentChunk.size();
    int progress = static_cast<int>((static_cast<double>(bytesSent) / totalBytes) * 100);
    emit uploadProgress(progress);
}
