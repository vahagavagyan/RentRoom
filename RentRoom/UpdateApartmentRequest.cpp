#include "UpdateApartmentRequest.h"
#include "Realtor.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray UpdateApartmentRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();

	QJsonObject apartmentJson;
	apartmentJson["apartment_id"] = m_updatedApartment.getId();
	apartmentJson["apartment_name"] = m_updatedApartment.getName();
	apartmentJson["description"] = m_updatedApartment.getDescription();
	apartmentJson["floor_size"] = m_updatedApartment.getFloorSize();
	apartmentJson["price"] = m_updatedApartment.getPrice();
	apartmentJson["rooms_num"] = m_updatedApartment.getRoomsNum();
	apartmentJson["latitude"] = m_updatedApartment.getLocLatitude();
	apartmentJson["longitude"] = m_updatedApartment.getLocLongitude();
	apartmentJson["realtor_id"] = m_updatedApartment.getRealtor()->getId();

	jsonObj["apartment"] = apartmentJson;

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
