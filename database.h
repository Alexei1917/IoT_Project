#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManager {
public:
    DatabaseManager(const QString &dbPath) {
        //QSQLITE：指定数据库驱动为 SQLite。Qt 支持多种数据库驱动，如 MySQL、PostgreSQL 等。
        //db.setDatabaseName(dbPath)：设置 SQLite 数据库的文件路径。
        //db.open()：尝试打开数据库。如果文件不存在且路径有效，会创建数据库文件。
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError();
        } else {
            QSqlQuery query;
            query.exec("CREATE TABLE IF NOT EXISTS logs (id INTEGER PRIMARY KEY, timestamp TEXT, data TEXT)");
        }
    }

    void logData(const QString &data) {
        QSqlQuery query;
        query.prepare("INSERT INTO logs (timestamp, data) VALUES (datetime('now'), ?)");
        query.addBindValue(data);
        query.exec();
        //datetime('now')：SQLite 内置函数，获取当前时间的 UTC 格式时间戳。
        //占位符 ?：防止 SQL 注入，将用户输入的数据绑定到查询。
        //query.addBindValue(data)：将日志内容绑定到 SQL 查询中的占位符。
        //query.exec()：执行插入操作。
    }

    // 查询日志
    QStringList fetchLogs() {
        QStringList logs;
        QSqlQuery query("SELECT timestamp, data FROM logs");
        while (query.next()) {
            QString log = query.value(0).toString() + ": " + query.value(1).toString();
            logs << log;
        }
        return logs;
    }

    // 删除日志
    void clearLogs() {
        QSqlQuery query("DELETE FROM logs");
        query.exec();
    }

    //多线程支持： 在多线程环境中，每个线程需要独立的 QSqlDatabase 实例。
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "ThreadConnection");
    db.setDatabaseName(dbPath);
    db.open();
    */


private:
    QSqlDatabase db;
};


#endif // DATABASE_H
