#pragma once
#include <QWidget>

class MapsView;
class ListRealtorApartmentsResponse;
class ListRealtorApartmentsRequest;
class CreateApartmentResponse;
class CreateApartmentRequest;
class UpdateApartmentResponse;
class UpdateApartmentRequest;
class DeleteApartmentResponse;
class DeleteApartmentRequest;

class RealtorScreen :public QWidget
{
	Q_OBJECT

public:
	RealtorScreen(QWidget* parent=nullptr);
	~RealtorScreen();

private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
signals:
	void createApartmentRequested(const CreateApartmentRequest& request);
	void updateApartmentRequested(const UpdateApartmentRequest& request);
	void deleteApartmentRequested(const DeleteApartmentRequest& request);
	void listRealtorApartmentsRequested(const ListRealtorApartmentsRequest& request);
public slots:
	void onCreateApartmentResponseReady(const CreateApartmentResponse& response);
	void onUpdateApartmentResponseReady(const UpdateApartmentResponse& response);
	void onDeleteApartmentResponseReady(const DeleteApartmentResponse& response);
	void onListRealtorApartmentsResponseReady(const ListRealtorApartmentsResponse& response);
private:
	MapsView *m_mapsView;
};

