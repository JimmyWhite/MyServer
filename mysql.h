#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <qsqldatabase.h>
#include <qsqlquery.h>
class MySql : public QObject
{
    Q_OBJECT
public:
    explicit MySql(QObject *parent = 0);
    QSqlDatabase db;   //数据库实例
    QSqlQuery query;   //用于对数据库操作
    QVector<QByteArray> login(QString username, QString password); //验证用户登陆信息
    ~MySql();

signals:

public slots:
};

#endif // MYSQL_H
