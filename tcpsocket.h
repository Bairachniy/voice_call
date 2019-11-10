#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr): QObject(parent){}
    virtual void connectToServer(QString host,quint16 port)=0;
    virtual QString peerAdress()=0;
    virtual void write(QString data)=0;
    virtual bool setSocketDescriptor(qintptr descriptor)=0;
    virtual void close()=0;

public slots:
    void readData(){}
signals:
      void readyRead(QString data);
      void disconnect();
};

#endif // TCPSOCKET_H
