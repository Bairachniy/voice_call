#include "client.h"

#include <QJsonArray>
#include <QJsonDocument>

Client::Client(QObject *parent) : QObject(parent)
{
    m_socket = new UsualTcpSocket();
}

void Client::connectToServer(QString host, quint16 port)
{
    m_socket->connectToServer(host, port);
    connect(m_socket,SIGNAL(ready(QString)),this,SLOT(readData(QString)));
}

void Client::write(QString data)
{
    m_socket->write(data);
}

void Client::close()
{
    m_socket->close();
}

Client::~Client()
{
    close();
    delete m_socket;
}

void Client::readData(QString data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QString result = doc["result"].toString();
    if(result == "LOG_OK")
    {
        QJsonArray users = doc["users"].toArray();
        QJsonDocument tmp;
        tmp.setArray(users);
        registered(tmp.toJson());
    }
    if(result == "REG_NEED")
    {
        needReg();
    }
    if(result == "ANSWER")
    {
        callAccepted();
    }
    if(result == "DISMIS")
    {
        callDismissed();
    }
    if(result == "USER_TALKING")
        {
            //callDismissed();
        }
}
