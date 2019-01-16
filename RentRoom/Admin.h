#pragma once
#include <QString>
class Admin
{
public:
	~Admin();
	int getId() const;
	void setId(int val);
	QString getFirstName() const;
	void setFirstName(QString val);
	QString getLastName() const;
	void setLastName(QString val);
	QString getEmail() const;
	void setEmail(QString val);
private:
	int id;
	QString m_firstName;
	QString m_lastName;
	QString m_email;
};