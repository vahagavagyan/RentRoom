#include "DeleteClientRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray DeleteClientRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	jsonObj["client_id"] = getClient().getId();

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
