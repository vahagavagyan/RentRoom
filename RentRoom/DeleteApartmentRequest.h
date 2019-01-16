#pragma once
#include <QMetaType>
#include "Request.h"
#include "Apartment.h"

class DeleteApartmentRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Apartment getApartment() const { return m_apartment; }
	void setApartment(const Apartment& val) { m_apartment = val; }
private:
	Apartment m_apartment;
};
Q_DECLARE_METATYPE(DeleteApartmentRequest)
