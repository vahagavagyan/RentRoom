#include "Admin.h"

Admin::~Admin()
{
}

int Admin::getId() const { return id; }
void Admin::setId(int val) { id = val; }
QString Admin::getFirstName() const { return m_firstName; }
void Admin::setFirstName(QString val) { m_firstName = val; }
QString Admin::getLastName() const { return m_lastName; }
void Admin::setLastName(QString val) { m_lastName = val; }
QString Admin::getEmail() const { return m_email; }
void Admin::setEmail(QString val) { m_email = val; }
