#pragma once
#include <QMetaType>

#include "Request.h"

#include "Apartment.h"

class UpdateApartmentRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Apartment getUpdatedApartment() const { return m_updatedApartment; }
	void setUpdatedApartment(const Apartment& val) { m_updatedApartment = val; }
private:
	Apartment m_updatedApartment;
};

Q_DECLARE_METATYPE(UpdateApartmentRequest)

