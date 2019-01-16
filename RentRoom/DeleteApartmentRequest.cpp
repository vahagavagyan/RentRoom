#include "DeleteApartmentRequest.h"

#include <QJsonDocument>
#include <QJsonObject>

QByteArray DeleteApartmentRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	jsonObj["apartment_id"] = getApartment().getId();
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
