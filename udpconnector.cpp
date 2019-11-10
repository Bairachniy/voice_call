#include "udpconnector.h"
#include "usualudpsocket.h"

UdpConnector::UdpConnector(QObject *parent)
    : QObject(parent),
      m_client_socket(new UsualUdpSocket()),
      m_servert_socket(new UsualUdpSocket()),
      m_audou_device(new AudioDevice()){}

void UdpConnector::connect(QString host, quint16 port)
{
    m_servert_socket->bind(port);
    QObject::connect(m_servert_socket,SIGNAL(play(QByteArray)), m_audou_device, SLOT(play(QByteArray)));

    m_client_socket->connectToHost(host, port);
    QObject::connect(m_client_socket,SIGNAL(read(QUdpSocket*)),m_audou_device,SLOT(read(QUdpSocket*)));
}

UdpConnector::~UdpConnector()
{
    delete m_client_socket;
    delete m_servert_socket;
    delete m_audou_device;
}


void UdpConnector::disconnect()
{
    QObject::disconnect(m_servert_socket,SIGNAL(play(QByteArray)), m_audou_device, SLOT(play(QByteArray)));
    QObject::disconnect(m_client_socket,SIGNAL(read(QUdpSocket*)),m_audou_device,SLOT(read(QUdpSocket*)));

    m_servert_socket->close();
    m_client_socket->close();

    m_audou_device->stop();
}
