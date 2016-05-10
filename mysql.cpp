#include "mysql.h"
#include "qvector.h"
#include "qvariant.h"
MySql::MySql(QObject *parent) : QObject(parent)
{
    //创建一个数据库实例
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

}

MySql::~MySql()
{
}

QVector<QByteArray> MySql::login(QString username, QString password)
{
    //验证账号密码是否在数据库中存在，并返回结果，结果用flag标记
    QVector <QByteArray>   data;
    data.resize(4);
    db.setDatabaseName("SERVER.db");
    db.open();
    query = QSqlQuery(db);
    QString sql=tr("select * from USER where USERNAME='%1' and PASSWORD='%2'").arg(username).arg(password);
    query.prepare(sql);
    query.exec();
    while (query.next())
    {
        data[0]=(query.value(2).toByteArray());
        data[1]=(query.value(3).toByteArray());
        data[2]=(query.value(4).toByteArray());
        db.close();
        return data;
    }
    db.close();
    return data;
}
