#include "UpdateRealtorRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray UpdateRealtorRequest::toJson() const
{
	QJsonObject jsonObj, realtorObj;
	jsonObj["email"] = getEmail() ;
	jsonObj["key"] = getKey() ;
	jsonObj["role"] = getUserRole();
	realtorObj["id"] = m_realtor.getId();
	realtorObj["first_name"] = m_realtor.getFirstName();
	realtorObj["last_name"] = m_realtor.getLastName();
	realtorObj["email"] = m_realtor.getEmail();
	jsonObj["realtor"] = realtorObj;
	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
