#pragma once

#include <QString>
#include "UserRole.h"

class Options
{
public:
	static void init();
	static void load();
	static void store();
	static void reset();
	static void setUserRole(const UserRole& role);
	static void setUserEmail(const QString& email);
	static void setUserKey(const QString& key);
	static UserRole getUserRole();
	static QString getUserEmail();
	static QString getUserKey();
private:
	static UserRole m_userRole;
	static QString m_email;
	static QString m_key;
};

