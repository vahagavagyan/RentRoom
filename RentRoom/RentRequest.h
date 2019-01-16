#pragma once

#include <QMetaType>

#include "Request.h"

#include "Apartment.h"

class RentRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Apartment getApartment() const { return m_apartment; }
	void setApartment(const Apartment& val) { m_apartment = val; }
	QDate getStartDate() const { return m_startDate; }
	void setStartDate(const QDate& val) { m_startDate = val; }
	QDate getEndDate() const { return m_endDate; }
	void setEndDate(const QDate& val) { m_endDate = val; }
private:
	Apartment m_apartment;
	QDate m_startDate;
	QDate m_endDate;
};
Q_DECLARE_METATYPE(RentRequest)

