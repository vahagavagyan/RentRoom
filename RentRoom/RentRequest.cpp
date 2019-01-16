#include "RentRequest.h"

#include <QJsonObject>
#include <QJsonDocument>

QByteArray RentRequest::toJson()const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["role"] = getUserRole();
	jsonObj["key"] = getKey();
	jsonObj["apartment_id"] = getApartment().getId();
	jsonObj["start_date"] = getStartDate().toString("yyyy-MM-dd");
	jsonObj["end_date"] = getEndDate().toString("yyyy-MM-dd");
	QJsonDocument doc(jsonObj);	
	return doc.toJson();
}
