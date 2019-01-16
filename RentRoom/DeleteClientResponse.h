#pragma once
#include <QMetaType>
#include "Response.h"
class DeleteClientResponse :	public Response
{
public:
	DeleteClientResponse();
	~DeleteClientResponse();
};

Q_DECLARE_METATYPE(DeleteClientResponse)