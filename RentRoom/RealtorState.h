#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

class RealtorScreen;
class DeleteApartmentRequest;
class UpdateApartmentRequest;
class CreateApartmentRequest;
class ListRealtorApartmentsRequest;

class RealtorState : public QState
{
	Q_OBJECT

public:
	RealtorState(QState *parent = nullptr);
	~RealtorState();
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
public slots:
	void onDeleteApartmentRequested(const DeleteApartmentRequest& request);	
	void onUpdateApartmentRequested(const UpdateApartmentRequest& request);	
	void onCreateApartmentRequested(const CreateApartmentRequest& request);
	void onListRealtorApartmentsRequested(const ListRealtorApartmentsRequest& request);
	
private:
	void connectSignals(RealtorScreen* screen);
private:
	QVector<QMetaObject::Connection> m_connections;
};

