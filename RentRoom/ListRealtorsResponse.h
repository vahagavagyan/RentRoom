#pragma once
#include <QMetaType>
#include <QMap>

#include "Realtor.h"
#include "Response.h"
class ListRealtorsResponse :	public Response
{
public:
	void setRealtors(const QMap<int, Realtor>& realtors) { m_realtors = realtors; }
	const QMap<int, Realtor>& getRealtors()const { return m_realtors; }
private:
	QMap<int, Realtor> m_realtors;
};

Q_DECLARE_METATYPE(ListRealtorsResponse)