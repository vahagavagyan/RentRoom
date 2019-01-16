#pragma once
#include <QMetaType>
#include "Request.h"
class ListApartmentsRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
};

Q_DECLARE_METATYPE(ListApartmentsRequest)

