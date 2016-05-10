#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <qtcpsocket.h>
#include <mysql.h>

class MySocket : public QObject
{
    Q_OBJECT
public:
    explicit MySocket(int ID,QObject *parent = 0);
    void run();
    int connectionID; //记录连接SOCKET的标识
    QString connectionName; // 记录连接SOCKET的名字
    QString connectionMoney; // 记录连接SOCKET的金币
    QTcpSocket *socket; //SOCKET实例
    void sendData(QByteArray datas); //发送数据
    ~MySocket();

signals:
    void addSocket(MySocket *socket);
    void deleteSocket(MySocket *socket);
    void dealChallenge(QString myName,QString pkName, QString courseID);
    void agreeChallenge(QString myName,QString pkName, QString courseID);
    void initData(MySocket *socket,QString myName);
    void transData(QString name,QString finished,QString accept);
public slots:
    void readyRead();
    void disconnect();
};

#endif // MYSOCKET_H
