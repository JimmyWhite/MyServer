#include "mysocket.h"

MySocket::MySocket(int ID, QObject *parent) : QObject(parent)
{
    this->connectionID=ID;
    this->run();

}

void MySocket::run()
{
    //启动一个线程进行通信并连接相应的信号和槽
    qDebug()<<"启动"<<this->connectionID<<"线程进行通信";
    socket = new QTcpSocket();
    socket->setSocketDescriptor(this->connectionID);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnect()),Qt::DirectConnection);
}

MySocket::~MySocket()
{

}

void MySocket::readyRead()
{
    //读取从客户端发来的数据并做出相应的处理
    QByteArray data = socket->readAll();
    qDebug()<<this->connectionID<<"连接发来信息:"<<data;
    QString datas = QString::fromLatin1(data);

    //处理登录信息
    if (datas.indexOf('+')!=-1)
    {
    int index = datas.indexOf('+');
    QString username = datas.left(index);
    QString password = datas.mid(index+1);
    MySql mySql;
    QVector<QByteArray> userData = mySql.login(username,password);
    if (userData.at(0)!="")
    {
        socket->write(userData.at(1)+'+'+userData.at(0));
    }
    else
    {
        socket->write("请输入正确的账号和密码!");
    }

    }

    //处理PK场用户列表
    if (data.indexOf('-')!=-1)
    {
        int index = data.indexOf('-');
        QString chinesename = data.left(index);
        QString money = data.mid(index+1);
        this->connectionName = chinesename;
        this->connectionMoney = money;
        emit addSocket(this);
    }

    //处理邀请对战请求
    if (data.indexOf('*')!=-1)
    {
        int index = data.indexOf('*');
        QString chinesename = data.left(index);
        QString courseID = data.mid(index+1);
        emit dealChallenge(this->connectionName,chinesename,courseID);
    }

    //处理同意对战请求
    if (data.indexOf('/')!=-1)
    {
        int index = data.indexOf('/');
        QString chinesename = data.left(index);
        QString courseID = data.mid(index+1);
        emit agreeChallenge(this->connectionName,chinesename,courseID);
    }

    //处理传输数据初始化
    if (data.indexOf('=')!=-1)
    {
        int index= data.indexOf('=');
        QString chinesename = data.left(index);
        emit initData(this,chinesename);
    }

    //处理对战数据

    if (data.indexOf('%')!=-1)
    {
        int index = data.indexOf('%');
        QString chinesename = data.left(index);
        data = data.mid(index+1);
        index = data.indexOf('%');
        QString finished = data.left(index);
        QString accept = data.mid(index+1);
        emit transData(chinesename,finished,accept);
    }

}
void MySocket::sendData(QByteArray datas)
{
    this->socket->write(datas);

}
void MySocket::disconnect()
{
    //断开连接处理
    qDebug()<<this->connectionID<<"连接已断开";
    emit deleteSocket(this);
    socket->deleteLater();
}

