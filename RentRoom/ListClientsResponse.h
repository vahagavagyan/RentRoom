#pragma once
#include <QMetaType>
#include <QMap>

#include "Response.h"
#include "Client.h"

class ListClientsResponse :	public Response
{
public:
	QMap<int, Client> getClients() const { return m_clients; }
	void setClients(const QMap<int, Client>& val) { m_clients = val; }
private:
	QMap<int, Client> m_clients;
};

Q_DECLARE_METATYPE(ListClientsResponse)
