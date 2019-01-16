#pragma once

#include <QMetaType>

#include "Request.h"

class SignupRequest : public Request
{
public:
	QString getFirstName() const;
	void setFirstName(QString val);

	QString getLastName() const;
	void setLastName(QString val);

	QString getPassword() const;
	void setPassword(QString val);

	virtual QByteArray toJson()const override;
private:
	QString m_firstName;
	QString m_lastName;
	QString m_password;	
};

Q_DECLARE_METATYPE(SignupRequest)

inline QString SignupRequest::getFirstName() const		{ return m_firstName; }
inline void SignupRequest::setFirstName(QString val)	{ m_firstName = val; }

inline QString SignupRequest::getLastName() const		{ return m_lastName; }
inline void SignupRequest::setLastName(QString val)		{ m_lastName = val; }

inline QString SignupRequest::getPassword() const		{ return m_password; }
inline void SignupRequest::setPassword(QString val)		{ m_password = val; }
