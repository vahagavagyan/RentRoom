#pragma once
#include <QMetaType>
#include "Response.h"
class CreateClientResponse :	public Response
{
public:
	CreateClientResponse();
	~CreateClientResponse();
};

Q_DECLARE_METATYPE(CreateClientResponse)