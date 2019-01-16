#include "Options.h"
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDataStream>

UserRole Options::m_userRole = eMaxRoles;
QString Options::m_email;
QString Options::m_key;
static QString s_DataPath;

void Options::init()
{
	auto  rentRoomDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	QDir().mkpath(rentRoomDir);
	s_DataPath = QDir(rentRoomDir).absoluteFilePath("l.cookie");
}

void Options::load()
{
	QFile f(s_DataPath);
	if (f.open(QIODevice::ReadOnly)) {
		{
			qint32 role;
			QDataStream dataStream(&f);
			dataStream.setVersion(QDataStream::Qt_5_1);
			dataStream >> m_email;
			dataStream >> m_key;
			dataStream >> role;
			m_userRole = static_cast<UserRole>(role);
		}
		f.close();
	}
}

void Options::store()
{
	QFile f(s_DataPath);
	if (f.open(QIODevice::WriteOnly)) {
		{
			QDataStream dataStream(&f);
			dataStream.setVersion(QDataStream::Qt_5_1);
			dataStream << m_email;
			dataStream << m_key;
			dataStream << static_cast<qint32>(m_userRole);
		}
		f.flush();
		f.close();		
	}	
}

void Options::reset()
{
	m_userRole = eMaxRoles;
	m_key = "";
	m_email = "";
}

void Options::setUserRole(const UserRole & role)
{
	m_userRole = role;
}

void Options::setUserEmail(const QString & email)
{
	m_email = email;
}

void Options::setUserKey(const QString & key)
{
	m_key = key;
}

UserRole Options::getUserRole()
{
	return m_userRole;
}

QString Options::getUserEmail()
{
	return m_email;
}

QString Options::getUserKey()
{
	return m_key;
}
