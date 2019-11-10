#include "usualudpsocket.h"

UsualUdpSocket::UsualUdpSocket(QObject *parent):UdpSocket(parent)
{
    m_socket = new QUdpSocket();
}

void UsualUdpSocket::connectToHost(QString host, quint16 port)
{
    m_socket->connectToHost(host, port);
    if(m_socket->waitForConnected())
        read(&(*m_socket));
}

void UsualUdpSocket::bind(quint16 port)
{
    m_socket->bind(port);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(playData()));
}


void UsualUdpSocket::close()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(playData()));
    m_socket->disconnect();
    m_socket->disconnectFromHost();
}

void UsualUdpSocket::playData()
{
    while (m_socket->hasPendingDatagrams())
    {

        QByteArray data;
        data.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(data.data(), data.size());
        play(data);
    }

}
