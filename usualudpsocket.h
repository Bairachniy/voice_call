#ifndef USUALUDPSOCKET_H
#define USUALUDPSOCKET_H
#include "udpsocket.h"

class UsualUdpSocket : public UdpSocket
{
    Q_OBJECT

public:
    UsualUdpSocket(QObject *parent = nullptr);
    void connectToHost(QString host, quint16 port);
    void bind(quint16 port);
    void close();

signals:
    void play(QByteArray);
    void read(QUdpSocket*);
    void closed();

public slots:
    void playData();

private:
    QUdpSocket* m_socket;
};

#endif // USUALUDPSOCKET_H
