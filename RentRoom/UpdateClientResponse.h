#pragma once
#include <QMetaType>
#include "Response.h"
class UpdateClientResponse :	public Response
{
public:
	UpdateClientResponse();
	~UpdateClientResponse();
};

Q_DECLARE_METATYPE(UpdateClientResponse)