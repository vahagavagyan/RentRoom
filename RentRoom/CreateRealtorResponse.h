#pragma once
#include <QMetaType>
#include "Response.h"
class CreateRealtorResponse :	public Response
{
public:
	CreateRealtorResponse();
	~CreateRealtorResponse();
};

Q_DECLARE_METATYPE(CreateRealtorResponse)