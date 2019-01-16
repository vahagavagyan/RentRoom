#include "ListApartmentsRequest.h"

#include <QJsonDocument>
#include <QJsonObject>


QByteArray ListApartmentsRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["role"] = getUserRole();
	jsonObj["key"] = getKey();
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
