#include "DeleteRealtorRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray DeleteRealtorRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	jsonObj["realtor_id"] = getRealtor().getId();
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
