#include "usualtcpsocket.h"
#include<QHostAddress>

UsualTcpSocket::UsualTcpSocket(QObject *parent):TcpSocket(parent)
{
    m_socket = new QTcpSocket(this);
    QObject::connect(m_socket,SIGNAL(readyRead()), this, SLOT(readData()));
}

void UsualTcpSocket::connectToServer(QString host,quint16 port)
{
    m_socket->connectToHost(host,port);
    if(!m_socket->waitForConnected(10000))
        throw std::runtime_error(m_socket->errorString().toUtf8());
}

bool UsualTcpSocket::setSocketDescriptor(qintptr descriptor)
{
    return m_socket->setSocketDescriptor(descriptor);
}

QString UsualTcpSocket::peerAdress()
{
    return m_socket->peerAddress().toString();
}

void UsualTcpSocket::write(QString data)
{
    m_socket->write(data.toUtf8());
    m_socket->waitForBytesWritten();
}

void UsualTcpSocket::close()
{
    QObject::disconnect(m_socket,SIGNAL(readyRead()), this, SLOT(readData()));
    disconnected();
    m_socket->disconnectFromHost();
    m_socket->close();
}

void UsualTcpSocket::readData()
{
    QString data = "";
    data = m_socket->readAll();
    ready(data);
}
