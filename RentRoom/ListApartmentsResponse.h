#pragma once
#include <QMap>
#include <QMetaType>

#include "Response.h"
#include "Apartment.h"

class ListApartmentsResponse :	public Response
{
public:
	QMap<int, Apartment> getApartments() const { return m_apartments; }
	void setApartments(const QMap<int, Apartment>& val) { m_apartments = val; }
private:
	QMap<int, Apartment> m_apartments;
};

Q_DECLARE_METATYPE(ListApartmentsResponse)

