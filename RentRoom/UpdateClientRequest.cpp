#include "UpdateClientRequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray UpdateClientRequest::toJson() const
{
	QJsonObject jsonObj;
	jsonObj["email"] = getEmail();
	jsonObj["key"] = getKey();
	jsonObj["role"] = getUserRole();
	QJsonObject clientObj;
	clientObj["id"] = m_client.getId();
	clientObj["first_name"] = m_client.getFirstName();
	clientObj["last_name"] = m_client.getLastName();
	clientObj["email"] = m_client.getEmail();

	jsonObj["client"] = clientObj;

	QJsonDocument doc(jsonObj);
	return doc.toJson();
}
