#ifndef MYSERVER_H
#define MYSERVER_H

#include <mysocket.h>
#include <QTcpServer>
class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    void startServer();    //服务器开始工作
    explicit MyServer(QObject *parent = 0);
    QVector<MySocket*> sockets;
    QVector<MySocket*> dataSockets;
    ~MyServer();

signals:

public slots:
    void addSocket(MySocket *socket);
    void deleteSocket(MySocket *socket);
    void dealChallenge(QString myName,QString pkName, QString courseID);
    void agreeChallenge(QString myName, QString pkName, QString courseID);
    void initData(MySocket *socket,QString myName);
    void transData(QString name,QString finished,QString accept);

private:
    void incomingConnection(qintptr handle);
};

#endif // MYSERVER_H
