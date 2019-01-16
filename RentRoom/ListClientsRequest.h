#pragma once
#include "Request.h"
#include <QMetaType>
class ListClientsRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
};

Q_DECLARE_METATYPE(ListClientsRequest)