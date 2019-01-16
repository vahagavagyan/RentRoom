#pragma once
#include <QMetaType>
#include "Request.h"
class ListRealtorApartmentsRequest : public Request
{
public:
	virtual QByteArray toJson()const;

};

Q_DECLARE_METATYPE(ListRealtorApartmentsRequest)