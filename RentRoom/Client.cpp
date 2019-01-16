#include "Client.h"

Client::~Client()
{
}

int Client::getId() const { return id; }
void Client::setId(int val) { id = val; }
QString Client::getFirstName() const { return m_firstName; }
void Client::setFirstName(QString val) { m_firstName = val; }
QString Client::getLastName() const { return m_lastName; }
void Client::setLastName(QString val) { m_lastName = val; }
QString Client::getEmail() const { return m_email; }
void Client::setEmail(QString val) { m_email = val; }
