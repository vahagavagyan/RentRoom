#pragma once
#include <QMetaType>
#include "Response.h"
class DeleteApartmentResponse :	public Response
{
public:
	DeleteApartmentResponse();
	~DeleteApartmentResponse();
};

Q_DECLARE_METATYPE(DeleteApartmentResponse)