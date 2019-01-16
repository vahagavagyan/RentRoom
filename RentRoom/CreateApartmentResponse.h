#pragma once
#include <QMetaType>
#include "Response.h"
class CreateApartmentResponse :	public Response
{
public:
	CreateApartmentResponse();
	~CreateApartmentResponse();
};
Q_DECLARE_METATYPE(CreateApartmentResponse)

