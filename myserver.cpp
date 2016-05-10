#include "myserver.h"
#include "qvector.h"

MyServer::MyServer(QObject *parent): QTcpServer(parent)
{
}

void MyServer::startServer()
{
    //服务器开始工作
    this->listen(QHostAddress::Any,22656);
    qDebug()<<"正在监听22656端口...";
}

void MyServer::incomingConnection(qintptr handle)
{
    //接收连接请求,并启动线程进行处理
    qDebug()<<handle<<"连接到服务器";
    MySocket *socket = new MySocket(handle,this);
    connect(socket,SIGNAL(addSocket(MySocket*)),this,SLOT(addSocket(MySocket*)));
    connect(socket,SIGNAL(deleteSocket(MySocket*)),this,SLOT(deleteSocket(MySocket*)));
    connect(socket,SIGNAL(dealChallenge(QString,QString,QString)),this,SLOT(dealChallenge(QString,QString,QString)));
    connect(socket,SIGNAL(agreeChallenge(QString,QString,QString)),this,SLOT(agreeChallenge(QString,QString,QString)));
    connect(socket,SIGNAL(initData(MySocket*,QString)),this,SLOT(initData(MySocket*,QString)));
    connect(socket,SIGNAL(transData(QString,QString,QString)),this,SLOT(transData(QString,QString,QString)));
}

MyServer::~MyServer()
{

}

void MyServer::transData(QString name, QString finished, QString accept)
{
    for (int i=0; i<=dataSockets.count()-1; i++)
    {
        if (dataSockets.at(i)->connectionName == name)
        {
            QByteArray datas;
            datas.append(finished);
            datas.append("%");
            datas.append(accept);
            dataSockets.at(i)->sendData(datas);
        }

    }

}

void MyServer::initData(MySocket *socket, QString myName)
{
    bool flag;
    flag = false;
    socket->connectionName = myName;
    for (int i=0; i<=dataSockets.count()-1; i++ )
    {
        if (dataSockets.at(i)->connectionID == socket->connectionID)
            flag =true;
    }
    if (!flag)
    dataSockets.append(socket);
}
void MyServer::agreeChallenge(QString myName,QString pkName, QString courseID)
{
    for (int i=0; i<=sockets.count()-1;i++)
    {
        if (sockets.at(i)->connectionName==pkName)
        {
            QByteArray datas;
            datas.append(myName);
            datas.append('/');
            datas.append(courseID);
            sockets.at(i)->sendData(datas);
            break;
        }

    }
}

void MyServer::dealChallenge(QString myName,QString pkName, QString courseID)
{
    for (int i=0; i<=sockets.count()-1; i++)
    {
        if (sockets.at(i)->connectionName == pkName)
        {
            QByteArray datas;
            datas.append(myName);
            datas.append('*');
            datas.append(courseID);
            sockets.at(i)->sendData(datas);
            break;
        }

    }

}

void MyServer::addSocket(MySocket *socket)
{
    bool flag;
    flag = false;
    for (int i=0; i<=sockets.count()-1; i++ )
    {
        if (sockets.at(i)->connectionID == socket->connectionID)
            flag =true;
    }
    if (!flag)
    sockets.append(socket);
    QByteArray datas;
    for (int i=0; i<=sockets.count()-1;i++)
    {
        if (sockets.at(i)->connectionID != socket->connectionID)
        {
            datas.append(sockets.at(i)->connectionName);
            datas.append('-');
            datas.append(sockets.at(i)->connectionMoney);
            datas.append('-');
        }

    }
    socket->sendData(datas);
}

void MyServer::deleteSocket(MySocket *socket)

{
    for (int i=0; i<= sockets.count()-1 ; i++)
    {
        if (sockets.at(i)->connectionID==socket->connectionID)
        {
            sockets.remove(i);
        }

    }
    for (int i=0; i<=dataSockets.count()-1;i++)
        {
        if(dataSockets.at(i)->connectionID == socket->connectionID)
        {
            dataSockets.remove(i);
        }
    }
}
