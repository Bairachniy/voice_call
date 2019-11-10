#include "controller.h"

Controller::Controller(QQmlApplicationEngine* engine, QObject *parent)
    : QObject(parent),
      m_engine(engine),
      m_state(FREE)
{
    m_server = new Server(this);
    m_server->startServer(8000);
    connect(&m_client,SIGNAL(registered(QString)),this,SLOT(registered(QString)));
    connect(&m_client,SIGNAL(needReg()),this,SLOT(needRegistration()));
}
//server
bool Controller::acceptCall()
{
    m_state = TALKING;
    m_connector.connect(m_companion_adres,5000);
    writeToConnection("{\"result\":\"ANSWER\"}");
    return true;
}
//server
bool Controller::rejectCall()
{
    m_state = FREE;
    writeToConnection("{\"result\":\"DECLINED\"}");
    return true;
}
//server/client
bool Controller::finishCall()
{
    return true;
}

int Controller::logIn(QString name, QString host)
{
    try
    {
        m_my_name = name;
        m_client.connectToServer(host, 2000);//подключение к главному серверу
        m_client.write("{\"command\":\"LOG_IN\",\"name\":\"" + name + "\"}");
        return 0;
    }
    catch (std::runtime_error &)
    {
        return 1;
    }

}

QString Controller::getUsers()
{
    return m_users;
}

QString Controller::getCompanionName()
{
    return m_companion_name;
}
//server/client
void Controller::setCompanion(QString name, QString adress)
{
    m_companion_name = name;
    m_companion_adres = adress;
}
//client
bool Controller::call(QString name, QString adress)
{
    try {
        m_state = CALLING;
        setCompanion(name, adress);
        m_client.connectToServer(adress,6000);
        m_client.write("{\"command\":\"CALL\"}");
        return true;
    } catch (std::runtime_error&)
    {
        return false;
    }

}
//server
bool Controller::incomingCall(QString name, QString adress)
{

    if(m_state == FREE)
    {
        m_state = CALLING;
        isServer = true;
        setCompanion(name, adress);
        QMetaObject::invokeMethod(m_engine->rootObjects()[0],"showCall");
    }
    else
    {
        writeToConnection("{\"result\":\"USER_TALKING\"}");
        //TODO созранение входящих звонков

    }
    return true;
}
//server
void Controller::incomingCallCanceled()
{

}

void Controller::registered(QString data)
{
    m_users = data;
    QMetaObject::invokeMethod(m_engine->rootObjects()[0],"openCabinet");
}

void Controller::needRegistration()
{
    m_client.write("{\"command\":\"REG_ME\", \"name\":" + m_my_name + "\", \"pass\": \"\"}");
}
//client
void Controller::callAccepted()
{
    m_state = TALKING;
    m_connector.connect(m_companion_adres, 5000);
}
