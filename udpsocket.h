#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>
class UdpSocket : public QObject
{
    Q_OBJECT
signals:

    void closed();
public slots:
    virtual void playData()=0;
public:
    explicit UdpSocket(QObject *parent = nullptr):QObject(parent){}
    virtual void connectToHost(QString host, quint16 port)=0;
    virtual void bind(quint16 port)=0;
    virtual void close()=0;
    virtual ~UdpSocket(){}
};

#endif // UDPSOCKET_H
