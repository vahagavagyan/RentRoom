#pragma once
#include <QWidget>
#include <QMap>
#include "Apartment.h"

class MapsView;
class SideMenu;

class ListClientsRequest;
class ListClientsResponse;

class ListApartmentsRequest;
class ListApartmentsResponse;

class ListRealtorsRequest;
class ListRealtorsResponse;

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


class DeleteApartmentRequest;
class DeleteApartmentResponse;

class DeleteClientRequest;
class DeleteClientResponse;

class DeleteRealtorRequest;
class DeleteRealtorResponse;


class AdminScreen : public QWidget
{
	Q_OBJECT

public:
	AdminScreen(QWidget* parent=nullptr);
	~AdminScreen();
	void removeMarkers();
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
signals:
	void listClientsRequested(const ListClientsRequest& request);
	void listApartmentsRequested(const ListApartmentsRequest& request);
	void listRealtorsRequested(const ListRealtorsRequest& request);
	void createApartmentRequested(const CreateApartmentRequest& request);
	void createClientRequested(const CreateClientRequest& request);
	void createRealtorRequested(const CreateRealtorRequest& request);
	void updateApartmentRequested(const UpdateApartmentRequest& request);
	void updateClientRequested(const UpdateClientRequest& request);
	void updateRealtorRequested(const UpdateRealtorRequest& request);
	void deleteApartmentRequested(const DeleteApartmentRequest& request);
	void deleteClientRequested(const DeleteClientRequest& request);
	void deleteRealtorRequested(const DeleteRealtorRequest& request);
public slots:

	void onListClientsResponseReady(const ListClientsResponse& response);
	void onListApartmentsResponseReady(const ListApartmentsResponse& response);
	void onListRealtorsResponseReady(const ListRealtorsResponse& response);

	void onCreateApartmentResponseReady(const CreateApartmentResponse& response);
	void onCreateClientResponseReady(const CreateClientResponse& response);
	void onCreateRealtorResponseReady(const CreateRealtorResponse& response);

	void onUpdateApartmentResponseReady(const UpdateApartmentResponse& response);
	void onUpdateClientResponseReady(const UpdateClientResponse& response);
	void onUpdateRealtorResponseReady(const UpdateRealtorResponse& response);
	
	void onDeleteApartmentResponseReady(const DeleteApartmentResponse& response);
	void onDeleteClientResponseReady(const DeleteClientResponse& response);
	void onDeleteRealtorResponseReady(const DeleteRealtorResponse& response);
private:
	MapsView *m_mapsView;
	SideMenu* m_sideMenu;
	QMap<int, Apartment> m_apartments;
};

