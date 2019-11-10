#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "client.h"
#include "server.h"
#include "udpconnector.h"
#include<mutex>
#include <QObject>
#include <QQmlApplicationEngine>
enum states{
    FREE,
    CALLING,
    TALKING
};
static std::mutex* companion_mutex = new std::mutex();
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QQmlApplicationEngine *engine,QObject *parent = nullptr);

    Q_INVOKABLE bool acceptCall();
    Q_INVOKABLE bool rejectCall();
    Q_INVOKABLE bool finishCall();
    Q_INVOKABLE int logIn(QString name, QString host);
    Q_INVOKABLE QString getUsers();
    Q_INVOKABLE QString getCompanionName();
    Q_INVOKABLE bool call(QString name, QString adress);
    bool incomingCall(QString name, QString adress);
    void incomingCallCanceled();

signals:
    void writeToConnection(QString data);
public slots:
    void registered(QString data);
    void needRegistration();
    void callAccepted();


private:
    bool isServer = false;
    UdpConnector m_connector;
    QString m_users;
    Server* m_server;
    Client m_client;
    QHash<QString, QString> m_missed_calls;
    QString m_my_name;
    QString m_companion_name;
    QString m_companion_adres;
    QQmlApplicationEngine* m_engine;
    states m_state;
    void setCompanion(QString name, QString adress);
};

#endif // CONTROLLER_H
