#ifndef CLIENT_H
#define CLIENT_H

#include "tcpsocket.h"
#include "usualtcpsocket.h"
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer(QString host,quint16 port);
    void write(QString data);
    void close();
    ~Client();

signals:
    void registered(QString data);
    void needReg();
    void callAccepted();
    void callDismissed();
public slots:
    void readData(QString data);
private:
    TcpSocket* m_socket;
};

#endif // CLIENT_H
