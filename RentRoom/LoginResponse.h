#pragma once
#include <QString>
#include <QMetaType>
#include "Response.h"
#include "UserRole.h"

class LoginResponse: public Response
{
public:
	int getId() const;
	void setId(int val);
	QString getEmail() const;
	void setEmail(QString val);
	QString getKey() const;
	void setKey(QString val);
	UserRole getUserRole() const;
	void setUserRole(UserRole val);
private:
	int m_status;
	int m_id;
	QString m_email;
	QString m_key;
	QString m_message;
	UserRole m_userRole;

};
inline int		LoginResponse::getId() const				{ return m_id; }
inline void		LoginResponse::setId(int val)				{ m_id = val; }
inline QString	LoginResponse::getEmail() const				{ return m_email; }
inline void		LoginResponse::setEmail(QString val)		{ m_email = val; }
inline QString	LoginResponse::getKey() const				{ return m_key; }
inline void		LoginResponse::setKey(QString val)			{ m_key = val; }
inline UserRole	LoginResponse::getUserRole() const			{ return m_userRole; }
inline void		LoginResponse::setUserRole(UserRole val)	{ m_userRole = val; }

Q_DECLARE_METATYPE(LoginResponse)