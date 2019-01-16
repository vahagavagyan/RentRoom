#pragma once
#include <QMetaType>
#include <QMap>

#include "Apartment.h"
#include "Response.h"
class ListAvailableApartmentsResponse :	public Response
{
public:
	QMap<int, Apartment> getApartments()const { return m_apartments; }
	void setApartments(const QMap<int, Apartment>& apartments){ m_apartments = apartments; }
private:
	QMap<int, Apartment> m_apartments;
};

Q_DECLARE_METATYPE(ListAvailableApartmentsResponse)
