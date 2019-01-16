#pragma once
#include <QMetaType>
#include "Response.h"
class UpdateApartmentResponse :	public Response
{
public:
	UpdateApartmentResponse();
	~UpdateApartmentResponse();
};

Q_DECLARE_METATYPE(UpdateApartmentResponse)