#pragma once

#include <QMetaType>

#include "Request.h"

class LoginRequest : public Request
{
public:
	QString getPassword() const;
	void setPassword(QString val);

	bool getIsKey() const;
	void setIsKey(bool val);

	virtual QByteArray toJson()const override;
private:
	QString m_password = "";
	bool m_isKey = false;
};

Q_DECLARE_METATYPE(LoginRequest)

inline QString LoginRequest::getPassword() const { return m_password; }
inline void LoginRequest::setPassword(QString val) { m_password = val; }
inline bool LoginRequest::getIsKey() const { return m_isKey; }
inline void LoginRequest::setIsKey(bool val) { m_isKey = val; }

