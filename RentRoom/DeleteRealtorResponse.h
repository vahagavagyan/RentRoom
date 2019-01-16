#pragma once
#include <QMetaType>
#include "Response.h"
class DeleteRealtorResponse :	public Response
{
public:
	DeleteRealtorResponse();
	~DeleteRealtorResponse();
};

Q_DECLARE_METATYPE(DeleteRealtorResponse)