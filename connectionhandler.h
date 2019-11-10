#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "controller.h"
#include "usualtcpsocket.h"
#include <QThread>



class ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    ConnectionHandler(Controller* controller, QObject *parent = nullptr);
    void setsocketDescriptor(qintptr handler);
    void run();
    ~ConnectionHandler();
public slots:
    void read(QString data);
    void write(QString data);
    void disconnected();

private:
    Controller* m_controller;
    TcpSocket* m_socket;
    qintptr soketDescriptor;
};

#endif // CONNECTIONHANDLER_H
