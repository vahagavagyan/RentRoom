#pragma once
#include <QMetaType>
#include "Request.h"
#include "Realtor.h"

class UpdateRealtorRequest : public Request
{
public:
	virtual QByteArray toJson()const override;
	Realtor getRealtor() const { return m_realtor; }
	void setRealtor(const Realtor& val) { m_realtor = val; }
private:
	Realtor m_realtor;
};
Q_DECLARE_METATYPE(UpdateRealtorRequest)