#include "connectionhandler.h"
#include "server.h"
#include "controller.h"

void Server::startServer(quint16 port)
{
    this->listen(QHostAddress::Any, port);
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    ConnectionHandler* handler = new ConnectionHandler(m_controller);
    handler->setsocketDescriptor(socketDescriptor);
    connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
    handler->start();
}
