#include "CreateRealtorRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray CreateRealtorRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	QJsonObject realtorObj;
	realtorObj["first_name"] = getRealtor().getFirstName();
	realtorObj["last_name"] = getRealtor().getLastName();
	realtorObj["email"] = getRealtor().getEmail();

	jsonObj["realtor"] = realtorObj;

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
