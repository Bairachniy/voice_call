#include "connectionhandler.h"

#include <QJsonDocument>


ConnectionHandler::ConnectionHandler(Controller* controller,QObject *parent)
    :QThread(parent),
      m_controller(controller)
{

}

void ConnectionHandler::setsocketDescriptor(qintptr handler)
{
    soketDescriptor = handler;

    m_socket = new UsualTcpSocket();
    m_socket->setSocketDescriptor(soketDescriptor);
}

void ConnectionHandler::run()
{

    connect(m_socket,SIGNAL(ready(QString)), this, SLOT(read(QString)));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    exec();
}

ConnectionHandler::~ConnectionHandler()
{
    disconnect(m_controller,SIGNAL(writeToConnection(QString)), this, SLOT(write(QString)));
}

void ConnectionHandler::read(QString data)
{
    QJsonDocument request = QJsonDocument::fromJson(data.toUtf8());
    if(request["command"] == "CALL")
    {
        m_controller->incomingCall(request["name"].toString(), m_socket->peerAdress());
        connect(m_controller,SIGNAL(writeToConnection(QString)), this, SLOT(write(QString)));
    }
}

void ConnectionHandler::write(QString data)
{
    m_socket->write(data.toUtf8());
}

void ConnectionHandler::disconnected()
{
    m_controller->finishCall();
    exit(0);
}
