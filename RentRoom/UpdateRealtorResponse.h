#pragma once
#include <QMetaType>
#include "Response.h"
class UpdateRealtorResponse :	public Response
{
public:
	UpdateRealtorResponse();
	~UpdateRealtorResponse();
};

Q_DECLARE_METATYPE(UpdateRealtorResponse)