#include "CreateApartmentRequest.h"

#include <QJsonDocument>
#include <QJsonObject>

#include "Realtor.h"

QByteArray CreateApartmentRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();

	QJsonObject apartmentJson;	
	apartmentJson["apartment_name"] = m_apartment.getName();
	apartmentJson["description"] = m_apartment.getDescription();
	apartmentJson["floor_size"] = m_apartment.getFloorSize();
	apartmentJson["price"] = m_apartment.getPrice();
	apartmentJson["rooms_num"] = m_apartment.getRoomsNum();
	apartmentJson["latitude"] = m_apartment.getLocLatitude();
	apartmentJson["longitude"] = m_apartment.getLocLongitude();
	apartmentJson["realtor_id"] = m_apartment.getRealtor()->getId();

	jsonObj["apartment"] = apartmentJson;

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
