#ifndef UDPCONNECTOR_H
#define UDPCONNECTOR_H

#include "audiodevice.h"
#include "udpsocket.h"

#include <QObject>

class UdpConnector : public QObject
{
    Q_OBJECT
public:
    explicit UdpConnector(QObject *parent = nullptr);
    void disconnect();
    void connect(QString host, quint16 port);
    ~UdpConnector();
private:
    UdpSocket* m_client_socket;
    UdpSocket* m_servert_socket;
    AudioDevice* m_audou_device;
};

#endif // UDPCONNECTOR_H
