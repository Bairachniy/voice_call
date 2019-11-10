#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include<QObject>

#include "tcpsocket.h"
#include "usualtcpsocket.h"
class Controller;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(Controller* controller, QObject *parent = nullptr)
        :QTcpServer(parent),
         m_controller(controller){}
    void startServer(quint16 port);

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    Controller* m_controller;
};

#endif // SERVER_H
