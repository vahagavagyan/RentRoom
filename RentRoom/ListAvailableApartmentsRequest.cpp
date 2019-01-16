#include "ListAvailableApartmentsRequest.h"

#include <QJsonDocument>
#include <QJsonObject>

QByteArray ListAvailableApartmentsRequest::toJson() const
{
	QJsonObject obj;
	obj["email"] = getEmail();
	obj["key"] = getKey();
	obj["role"] = getUserRole();
	QJsonDocument doc(obj);
	return doc.toJson();

}
