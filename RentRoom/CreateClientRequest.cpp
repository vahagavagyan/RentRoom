#include "CreateClientRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray CreateClientRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	QJsonObject clientObj;
	clientObj["first_name"] = getClient().getFirstName();
	clientObj["last_name"] = getClient().getLastName();
	clientObj["email"] = getClient().getEmail();

	jsonObj["client"] = clientObj;

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
