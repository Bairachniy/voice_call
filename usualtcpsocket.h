#ifndef USUALTCPSOCKET_H
#define USUALTCPSOCKET_H

#include "tcpsocket.h"
#include <QObject>


class UsualTcpSocket : public TcpSocket
{

    Q_OBJECT
public:
    UsualTcpSocket(QObject* parent = nullptr);
    void connectToServer(QString host,quint16 port) override;
    bool setSocketDescriptor(qintptr descriptor) override;
    QString peerAdress() override;
    void write(QString data) override;
    void close() override;

public slots:
    void readData();

signals:
    void ready(QString data);
    void disconnected();

private:
    QTcpSocket* m_socket;
};

#endif // USUALTCPSOCKET_H
