#include "database.h"

int main() {
    // 初始化数据库管理器，指定数据库文件路径
    DatabaseManager dbManager("logs.db");

    // 插入日志数据
    dbManager.logData("This is a log entry.");
    dbManager.logData("Another log entry.");

    return 0;
}
