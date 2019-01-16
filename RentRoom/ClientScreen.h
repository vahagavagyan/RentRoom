#pragma once
#include <QWidget>
#include <QMap>
#include "Apartment.h"

class MapsView;
class RentWidget;
class RentRequest;
class RentResponse;

class ClientScreen : public QWidget
{
	Q_OBJECT
public:
	ClientScreen(QWidget *parent=nullptr);
	~ClientScreen();
	void removeMarkers();
	void setAvailableApartments(QMap<int, Apartment> availableApartmens);
signals:
	void rentRequested(const RentRequest& data);
public slots:
	void onRentResponseReady(const RentResponse& response);
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
private:
	MapsView *m_mapsView;
	RentWidget *m_rentWidget;
	QMap<int, Apartment> m_availableApartments;
};

