#pragma once
#include <QMetaType>
#include "Request.h"
#include "Apartment.h"
class CreateApartmentRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Apartment setApartment() const { return m_apartment; }
	void getApartment(const Apartment& val) { m_apartment = val; }
private:
	Apartment m_apartment;
};
Q_DECLARE_METATYPE(CreateApartmentRequest)

