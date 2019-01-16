#pragma once
#include <QMetaType>
#include "Request.h"
#include "Client.h"
class UpdateClientRequest :	public Request
{
public:
	virtual QByteArray toJson()const override;
	Client getClient() const { return m_client; }
	void setClient(const Client& val) { m_client = val; }
private:
	Client m_client;
};
Q_DECLARE_METATYPE(UpdateClientRequest)
