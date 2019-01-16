#include "ListRealtorsRequest.h"
#include <QJsonObject>
#include <QJsonDocument>

QByteArray ListRealtorsRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["role"] = getUserRole();
	jsonObj["key"] = getKey();
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}