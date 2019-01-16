#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

class ListApartmentsRequest;
class ListClientsRequest;
class ListRealtorsRequest;
class DeleteApartmentRequest;
class DeleteClientRequest;
class DeleteRealtorRequest;
class CreateApartmentRequest;
class CreateClientRequest;
class CreateRealtorRequest;
class UpdateApartmentRequest;
class UpdateClientRequest;
class UpdateRealtorRequest;

class AdminScreen;

class AdminState : public QState
{
	Q_OBJECT

public:
	AdminState(QState *parent = nullptr);
	~AdminState();
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
public slots:
	void onListClientsRequested(const ListClientsRequest& request);
	void onListApartmentsRequested(const ListApartmentsRequest& request);
	void onListRealtorsRequested(const ListRealtorsRequest& request);

	void onDeleteApartmentRequested(const DeleteApartmentRequest& request);
	void onDeleteClientRequested(const DeleteClientRequest& request);
	void onDeleteRealtorRequested(const DeleteRealtorRequest& request);

	void onUpdateApartmentRequested(const UpdateApartmentRequest& request);
	void onUpdateClientRequested(const UpdateClientRequest& request);
	void onUpdateRealtorRequested(const UpdateRealtorRequest& request);
	
	void onCreateApartmentRequested(const CreateApartmentRequest& request);
	void onCreateClientRequested(const CreateClientRequest& request);
	void onCreateRealtorRequested(const CreateRealtorRequest& request);

private:
	void connectSignals(AdminScreen* screen);
private:
	QVector<QMetaObject::Connection> m_connections;
};
