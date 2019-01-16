#include "NetworkManager.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

#include "NetworkURL.h"

#include "SignupRequest.h"
#include "SignupResponse.h"

#include "LoginRequest.h"
#include "LoginResponse.h"

#include "ListAvailableApartmentsRequest.h"
#include "ListAvailableApartmentsResponse.h"

#include "RentRequest.h"
#include "RentResponse.h"

#include "ListRealtorsRequest.h"
#include "ListRealtorsResponse.h"

#include "ListApartmentsRequest.h"
#include "ListApartmentsResponse.h"

#include "ListClientsRequest.h"
#include "ListClientsResponse.h"

#include "ListRealtorApartmentsRequest.h"
#include "ListRealtorApartmentsResponse.h"

#include "DeleteApartmentRequest.h"
#include "DeleteApartmentResponse.h"

#include "DeleteClientRequest.h"
#include "DeleteClientResponse.h"

#include "DeleteRealtorRequest.h"
#include "DeleteRealtorResponse.h"

#include "CreateApartmentRequest.h"
#include "CreateApartmentResponse.h"

#include "CreateClientRequest.h"
#include "CreateClientResponse.h"

#include "CreateRealtorRequest.h"
#include "CreateRealtorResponse.h"

#include "UpdateApartmentRequest.h"
#include "UpdateApartmentResponse.h"

#include "UpdateClientRequest.h"
#include "UpdateClientResponse.h"

#include "UpdateRealtorRequest.h"
#include "UpdateRealtorResponse.h"

#include "Apartment.h"
#include "Realtor.h"

NetworkManager::NetworkManager(QObject *parent)
{
	m_networkMgr = new QNetworkAccessManager();
	m_networkMgr->connectToHost(NetworkURL::SERVER_HOST, NetworkURL::SERVER_PORT);
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::postLoginRequest(const LoginRequest & data)
{
	QNetworkRequest request(NetworkURL::LOGIN_URL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		LoginResponse responseData;
		if (statusCode == 200) {
			//{
			//	"login_info": {
			//		"id": 4,
			//			"key" : "7EXk6/RMU7aWGLh2lnX2emQyffrfACMV3Se71E167Yc=",
			//			"message" : "Login succeeded",
			//			"success" : true
			//	},
			//		"role": 1,
			//			"status_code" : 200
			//}
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto loginInfoObj = jsonObj.value("login_info").toObject();

			responseData.setId(loginInfoObj["id"].toInt());
			responseData.setMessage(loginInfoObj["message"].toString());
			responseData.setEmail(loginInfoObj["email"].toString());
			responseData.setKey(loginInfoObj["key"].toString());
			responseData.setUserRole(static_cast<UserRole>(jsonObj["role"].toInt()));
			responseData.setStatus(statusCode);
		}
		else {
			QJsonParseError error;
			QJsonDocument doc = QJsonDocument::fromJson(readData, &error);
			if (error.error == QJsonParseError::NoError) {
				auto jsonObj = doc.object();
				auto loginInfoObj = jsonObj.value("login_info").toObject();
				responseData.setMessage(loginInfoObj["message"].toString());
			}
			else {
				responseData.setMessage("Unknown Error");
			}
			responseData.setStatus(statusCode);
		}

		emit loginResponseReady(responseData);
		reply->deleteLater();
	});
}

void NetworkManager::postSignupRequest(const SignupRequest & data)
{
	QNetworkRequest request(NetworkURL::SIGNUP_URL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		SignupResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
		}
		else {
			responseData.setStatus(statusCode);
			responseData.setMessage(readData);
		}
		emit signupResponseReady(responseData);
		reply->deleteLater();
	});
}

void NetworkManager::postUpdateApartment(const UpdateApartmentRequest &data)
{
	QNetworkRequest request(NetworkURL::UPDATE_APARTMENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		UpdateApartmentResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit updateApartmentResponseReady(responseData);
	});
}

void NetworkManager::postUpdateClient(const UpdateClientRequest &data)
{
	QNetworkRequest request(NetworkURL::UPDATE_CLIENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		UpdateClientResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit updateClientResponseReady(responseData);
	});
}

void NetworkManager::postUpdateRealtor(const UpdateRealtorRequest &data)
{
	QNetworkRequest request(NetworkURL::UPDATE_REALTOR_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		UpdateRealtorResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit updateRealtorResponseReady(responseData);
	});
}

void NetworkManager::postCreateApartment(const CreateApartmentRequest& data)
{
	QNetworkRequest request(NetworkURL::CREATE_APARTMENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		CreateApartmentResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit createApartmentResponseReady(responseData);
	});
}

void NetworkManager::postCreateClient(const CreateClientRequest &data)
{
	QNetworkRequest request(NetworkURL::CREATE_CLIENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		CreateClientResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {

		}
		else {
			responseData.setMessage(readData);
		}
		emit createClientResponseReady(responseData);
	});
}

void NetworkManager::postCreateRealtor(const CreateRealtorRequest &data)
{
	QNetworkRequest request(NetworkURL::CREATE_REALTOR_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		CreateRealtorResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit createRealtorResponseReady(responseData);
	});
}

void NetworkManager::postDeleteApartment(const DeleteApartmentRequest &data)
{
	QNetworkRequest request(NetworkURL::DELETE_APARTMENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		DeleteApartmentResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit deleteApartmentResponseReady(responseData);
	});
}

void NetworkManager::postDeleteClient(const DeleteClientRequest &data)
{
	QNetworkRequest request(NetworkURL::DELETE_CLIENT_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		DeleteClientResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit deleteClientResponseReady(responseData);
	});
}

void NetworkManager::postDeleteRealtor(const DeleteRealtorRequest &data)
{
	QNetworkRequest request(NetworkURL::DELETE_REALTOR_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		DeleteRealtorResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit deleteRealtorResponseReady(responseData);
	});
}

void NetworkManager::postListApartments(const ListApartmentsRequest&data )
{
	QNetworkRequest request(NetworkURL::LIST_APARTMENTS_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());

	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		ListApartmentsResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QMap<int, Apartment> apartments;
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto apartmentsArray = jsonObj["apartments"].toArray();

			for (int i = 0; i < apartmentsArray.size(); ++i) {
				QJsonObject apartmentObj = apartmentsArray[i].toObject();
				Apartment apartment;
				apartment.setDateAdded(QDate::fromString(apartmentObj["apartment_date_added"].toString(), "dd/MM/yyyy"));
				apartment.setId(apartmentObj["apartment_id"].toInt());
				apartment.setName(apartmentObj["apartment_name"].toString());
				apartment.setDescription(apartmentObj["description"].toString());
				apartment.setFloorSize(apartmentObj["floor_size"].toInt());
				apartment.setLocLatitude(apartmentObj["latitude"].toDouble());
				apartment.setLocLongitude(apartmentObj["longitude"].toDouble());
				apartment.setPrice(apartmentObj["price"].toDouble());
				apartment.setRoomsNum(apartmentObj["rooms_num"].toInt());
				apartment.setRented(apartmentObj["rented"].toBool());
				auto realtor = std::make_shared<Realtor>();
				realtor->setEmail(apartmentObj["realtor_email"].toString());
				realtor->setFirstName(apartmentObj["realtor_first_name"].toString());
				realtor->setLastName(apartmentObj["realtor_last_name"].toString());
				apartment.setRealtor(realtor);
				apartments.insert(apartment.getId(), apartment);
			}
			responseData.setApartments(apartments);
		}
		else {
			responseData.setMessage(readData);
		}
		emit listApartmentsResponseReady(responseData);
	});

}

void NetworkManager::postListAvailableApartments(const ListAvailableApartmentsRequest& data)
{
	QNetworkRequest request(NetworkURL::LIST_AVAILABLE_APARTMENTS_URL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());

	/*
		{
	  "apartment_date_added": "20/12/2018",
	  "apartment_id": 2,
	  "apartment_name": "Abovyan Apartment",
	  "description": "Apartment near Moscow Cinema ",
	  "floor_size": 80,
	  "latitude": 40.1811431,
	  "longitude": 44.5159907,
	  "price": 160.00,
	  "realtor_email": "realtor@realtor.com",
	  "realtor_first_name": "Name",
	  "realtor_last_name": "Surname",
	  "rooms_num": 2
	}
	*/
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		ListAvailableApartmentsResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QMap<int, Apartment> apartments;
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto apartmentsArray = jsonObj["apartments"].toArray();
			for (int i = 0; i < apartmentsArray.size(); ++i) {
				QJsonObject apartmentObj = apartmentsArray[i].toObject();
				Apartment apartment;
				apartment.setDateAdded(QDate::fromString(apartmentObj["apartment_date_added"].toString(), "dd/MM/yyyy"));
				apartment.setId(apartmentObj["apartment_id"].toInt());
				apartment.setName(apartmentObj["apartment_name"].toString());
				apartment.setDescription(apartmentObj["description"].toString());
				apartment.setFloorSize(apartmentObj["floor_size"].toInt());
				apartment.setLocLatitude(apartmentObj["latitude"].toDouble());
				apartment.setLocLongitude(apartmentObj["longitude"].toDouble());
				apartment.setPrice(apartmentObj["price"].toDouble());
				apartment.setRoomsNum(apartmentObj["rooms_num"].toInt());
				auto realtor = std::make_shared<Realtor>();
				realtor->setEmail(apartmentObj["realtor_email"].toString());
				realtor->setFirstName(apartmentObj["realtor_first_name"].toString());
				realtor->setLastName(apartmentObj["realtor_last_name"].toString());
				apartment.setRealtor(realtor);
				apartments.insert(apartment.getId(), apartment);
			}
			responseData.setApartments(apartments);
		}
		else {
			responseData.setMessage(readData);
		}
		emit listAvailableApartmentsResponseReady(responseData);
		reply->deleteLater();
	});
}

void NetworkManager::postListClients(const ListClientsRequest &data)
{
	QNetworkRequest request(NetworkURL::LIST_CLIENTS_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		ListClientsResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto clientsArray = jsonObj["clients"].toArray();
			QMap<int, Client> clients;
			for (int i = 0; i < clientsArray.size(); ++i) {
				QJsonObject clientObj = clientsArray[i].toObject();
				Client client;

				client.setEmail(clientObj["email"].toString());
				client.setFirstName(clientObj["first_name"].toString());
				client.setLastName(clientObj["last_name"].toString());
				client.setId(clientObj["id"].toInt());

				clients.insert(client.getId(), client);
			}
			responseData.setClients(clients);
		}
		else {
			responseData.setMessage(readData);
		}
		emit listClientsResponseReady(responseData);
	});
}

void NetworkManager::postRentRequest(const RentRequest& data)
{
	QNetworkRequest request(NetworkURL::RENT_URL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		RentResponse responseData;
		responseData.setStatus(statusCode);
		responseData.setMessage(readData);
		emit rentResponseReady(responseData);
	});
}

void NetworkManager::postListRealtorApartments(const ListRealtorApartmentsRequest &data)
{
	QNetworkRequest request(NetworkURL::LIST_REALTOR_APARTMENTS_URL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());

	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		ListRealtorApartmentsResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QMap<int, Apartment> apartments;
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto apartmentsArray = jsonObj["apartments"].toArray();

			for (int i = 0; i < apartmentsArray.size(); ++i) {
				QJsonObject apartmentObj = apartmentsArray[i].toObject();
				Apartment apartment;
				apartment.setDateAdded(QDate::fromString(apartmentObj["apartment_date_added"].toString(), "dd/MM/yyyy"));
				apartment.setId(apartmentObj["apartment_id"].toInt());
				apartment.setName(apartmentObj["apartment_name"].toString());
				apartment.setDescription(apartmentObj["description"].toString());
				apartment.setFloorSize(apartmentObj["floor_size"].toInt());
				apartment.setLocLatitude(apartmentObj["latitude"].toDouble());
				apartment.setLocLongitude(apartmentObj["longitude"].toDouble());
				apartment.setPrice(apartmentObj["price"].toDouble());
				apartment.setRoomsNum(apartmentObj["rooms_num"].toInt());
				apartment.setRented(apartmentObj["rented"].toBool());
				auto realtor = std::make_shared<Realtor>();
				realtor->setEmail(apartmentObj["realtor_email"].toString());
				realtor->setFirstName(apartmentObj["realtor_first_name"].toString());
				realtor->setLastName(apartmentObj["realtor_last_name"].toString());
				apartment.setRealtor(realtor);
				apartments.insert(apartment.getId(), apartment);
			}
			responseData.setApartments(apartments);
		}
		else {
			responseData.setMessage(readData);
		}
		emit listRealtorApartmentsResponseReady(responseData);
	});

}

void NetworkManager::postListRealtors(const ListRealtorsRequest& data)
{
	QNetworkRequest request(NetworkURL::LIST_REALTORS_URL);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = m_networkMgr->post(request, data.toJson());
	connect(reply, &QNetworkReply::finished, [this, reply]() {
		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray readData = reply->readAll();
		ListRealtorsResponse responseData;
		responseData.setStatus(statusCode);
		if (responseData.isSucceeded()) {
			QJsonDocument doc = QJsonDocument::fromJson(readData);
			auto jsonObj = doc.object();
			auto realtorsArray = jsonObj["realtors"].toArray();
			QMap<int, Realtor> realtors;
			for (int i = 0; i < realtorsArray.size(); ++i) {
				QJsonObject realtorObj = realtorsArray[i].toObject();
				Realtor realtor;
				realtor.setEmail(realtorObj["email"].toString());
				realtor.setFirstName(realtorObj["first_name"].toString());
				realtor.setLastName(realtorObj["last_name"].toString());
				realtor.setId(realtorObj["id"].toInt());
				realtors.insert(realtor.getId(), realtor);
			}
			responseData.setRealtors(realtors);
		}
		else {
			responseData.setMessage(readData);
		}
		emit listRealtorsResponseReady(responseData);
	});

}
