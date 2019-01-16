#pragma once

#include <QString>
#include <QByteArray>

#include "UserRole.h"

class Request
{
public:
	Request();
	QString getEmail() const;
	void setEmail(const QString& val);
	UserRole getUserRole() const;
	void setUserRole(UserRole val);
	QString getKey()const;
	void setKey(const QString& key);
	virtual QByteArray toJson()const=0;
private:
	QString m_key="";
	QString m_email = "";
	UserRole m_userRole = eMaxRoles;
};

inline QString Request::getEmail() const { return m_email; }
inline void Request::setEmail(const QString& val) { m_email = val; }
inline UserRole Request::getUserRole() const { return m_userRole; }
inline void Request::setUserRole(UserRole val) { m_userRole = val; }
inline QString Request::getKey()const{	return m_key; }
inline void Request::setKey(const QString& key) { m_key = key; }