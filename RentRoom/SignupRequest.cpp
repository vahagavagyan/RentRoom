#include "SignupRequest.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

QByteArray SignupRequest::toJson() const
{
	QJsonObject json;
	json["email"] = getEmail();
	json["password"] = getPassword();
	json["first_name"] = getFirstName();
	json["last_name"] = getLastName();
	json["role"] = QString::number(static_cast<int>(getUserRole()));
	QJsonDocument doc(json);
	return doc.toJson();
}
