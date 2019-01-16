#include "LoginRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray LoginRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["password"] = getPassword();
	jsonObj["role"] = QString::number(static_cast<int>(getUserRole()));
	jsonObj["is_key"] = getIsKey();
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
