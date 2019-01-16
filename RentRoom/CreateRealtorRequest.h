#pragma once
#include <QMetaType>Q_DECLARE_METATYPE()
#include "Request.h"
#include "Realtor.h"
class CreateRealtorRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Realtor getRealtor() const { return m_realtor; }
	void setRealtor(Realtor val) { m_realtor = val; }
private:
	Realtor m_realtor;
};
Q_DECLARE_METATYPE(CreateRealtorRequest)
