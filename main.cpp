#include <QCoreApplication>
#include <myserver.h>
#include <mysql.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer *myServer;
    myServer =new MyServer();
    myServer->startServer();
    return a.exec();
}
