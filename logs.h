/*
 *@author: 缪庆瑞
 *@date:   2019.7.10
 *@update:  2020.3.28
 *@brief:  写日志文件的工具类，采用单例模式，内部通过加锁实现线程安全
 * 该类自动以当前日期作为日志文件名，格式形如“yyyy-MM-dd.log”，统一保存在指定的logsDir下。
 * 为了避免随着时间增长日志文件越来越多，可以在每次程序启动时调用rmLogsFile(int retainDays)，
 * 只保留最近几天的日志而删去其他无用的日志。除了写日志文件外，该类也提供了一些仅打印输出
 * 信息的接口，方便调用。
 *
 */
#ifndef LOGS_H
#define LOGS_H

#include <QDir>
#include <QMutex>
#include <QDebug>

class Logs
{
public:
    //日志级别
    enum LogsLevel
    {
        DEBUG_LEVEL=0,
        INFO_LEVEL,
        WARN_LEVEL,
        ERROR_LEVEL,
    };
    //单例模式
    static Logs* getInstance();

    void setLogsDir(const QString &dirPath);//设置日志文件目录
    void rmLogsFile(int retainDays=0);//删除日志文件
    void writeLogs(const QString &content,LogsLevel logsLevel=INFO_LEVEL);//写日志
    static void printCurrentTime(const QString &title);//打印当前时间

private:
    Logs();//私有构造函数

    static QMutex mutex;//互斥锁
    QDir logsDir;//日志文件目录

};

#endif // LOGS_H
