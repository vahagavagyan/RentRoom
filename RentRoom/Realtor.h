#pragma once
#include <QString>
#include <vector>
class Apartment;
class Realtor
{
public:
	QString getFirstName() const;
	void setFirstName(QString val);
	QString getLastName() const;
	void setLastName(QString val);
	QString getEmail() const;
	void setEmail(QString val);
	int getId() const;
	void setId(int id);
private:
	int m_id;
	QString m_firstName;
	QString m_lastName;
	QString m_email;
};

