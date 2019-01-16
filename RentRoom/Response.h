#pragma once
#include <QString>

class Response
{
public:
	bool isSucceeded()const
	{
		return getStatus() == 200;
	}
	int getStatus() const { return m_status; }
	void setStatus(int val) { m_status = val; }
	QString getMessage() const { return m_message; }
	void setMessage(const QString& val) { m_message = val; }
private:
	int m_status;
	QString m_message;
};


