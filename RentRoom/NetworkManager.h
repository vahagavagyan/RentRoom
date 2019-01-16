#pragma once
#include <QObject>

class QNetworkAccessManager;

class SignupRequest;
class SignupResponse;

class LoginRequest;
class LoginResponse;

class ListAvailableApartmentsRequest;
class ListAvailableApartmentsResponse;

class RentRequest;
class RentResponse;

class ListRealtorsRequest;
class ListRealtorsResponse;

class ListClientsRequest;
class ListClientsResponse;

class ListApartmentsRequest;
class ListApartmentsResponse;

class ListRealtorApartmentsRequest;
class ListRealtorApartmentsResponse;

class DeleteApartmentRequest;
class DeleteApartmentResponse;

class DeleteClientRequest;
class DeleteClientResponse;

class DeleteRealtorRequest;
class DeleteRealtorResponse;

class CreateApartmentRequest;
class CreateApartmentResponse;

class CreateClientRequest;
class CreateClientResponse;

class CreateRealtorRequest;
class CreateRealtorResponse;

class UpdateApartmentRequest;
class UpdateApartmentResponse;

class UpdateClientRequest;
class UpdateClientResponse;

class UpdateRealtorRequest;
class UpdateRealtorResponse;

class NetworkManager : public QObject
{
	Q_OBJECT
public:
	NetworkManager(QObject *parent = nullptr);
	~NetworkManager();
	/*
create_apartment                                   POST,OPTIONS         /create_apartment
create_client                                      POST,OPTIONS         /create_client
create_realtor                                     POST,OPTIONS         /create_realtor
delete_apartment                                   POST,OPTIONS         /delete_apartment
delete_client                                      POST,OPTIONS         /delete_client
delete_realtor                                     POST,OPTIONS         /delete_realtor
list_apartments                                    POST,OPTIONS         /list_apartments
+list_available_apartments                          POST,OPTIONS         /list_available
list_clients                                       POST,OPTIONS         /list_clients
list_realtor_apartments                            POST,OPTIONS         /list_realtor_apartments
list_realtors                                      POST,OPTIONS         /list_realtors
+login                                              POST,OPTIONS         /login
+rent                                               POST,OPTIONS         /rent
+signup                                             POST,OPTIONS         /signup
update_apartment                                   POST,OPTIONS         /update_apartment
update_client                                      POST,OPTIONS         /update_client
update_realtor                                     POST,OPTIONS         /update_realtor








	*/
private slots:

	void postCreateApartment(const CreateApartmentRequest&);
	void postCreateClient(const CreateClientRequest&);
	void postCreateRealtor(const CreateRealtorRequest&);

	void postDeleteApartment(const DeleteApartmentRequest&);
	void postDeleteClient(const DeleteClientRequest&);
	void postDeleteRealtor(const DeleteRealtorRequest&);

	void postListApartments(const ListApartmentsRequest&);
	void postListAvailableApartments(const ListAvailableApartmentsRequest&);
	void postListClients(const ListClientsRequest&);
	void postListRealtorApartments(const ListRealtorApartmentsRequest&);
	void postListRealtors(const ListRealtorsRequest& data);
	void postLoginRequest(const LoginRequest& data);
	void postRentRequest(const RentRequest& data);
	void postSignupRequest(const SignupRequest& data);

	void postUpdateApartment(const UpdateApartmentRequest&);
	void postUpdateClient(const UpdateClientRequest&);
	void postUpdateRealtor(const UpdateRealtorRequest&);

signals:
	void signupResponseReady(const SignupResponse& data);
	void loginResponseReady(const LoginResponse& data);
	void listAvailableApartmentsResponseReady(const ListAvailableApartmentsResponse& data);
	void rentResponseReady(const RentResponse& data);
	void listRealtorsResponseReady(const ListRealtorsResponse& data);
	void listClientsResponseReady(const ListClientsResponse& data);
	void listApartmentsResponseReady(const ListApartmentsResponse& data);
	void listRealtorApartmentsResponseReady(const ListRealtorApartmentsResponse& data);

	void deleteApartmentResponseReady(const DeleteApartmentResponse&);
	void deleteClientResponseReady(const DeleteClientResponse&);
	void deleteRealtorResponseReady(const DeleteRealtorResponse&);

	void createApartmentResponseReady(const CreateApartmentResponse&);
	void createClientResponseReady(const CreateClientResponse&);
	void createRealtorResponseReady(const CreateRealtorResponse&);


	void updateApartmentResponseReady(const UpdateApartmentResponse&);
	void updateClientResponseReady(const UpdateClientResponse&);
	void updateRealtorResponseReady(const UpdateRealtorResponse&);
private:
	QNetworkAccessManager *m_networkMgr;
};

