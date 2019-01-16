#pragma once
#include <QWidget>
#include <QMap>
#include "Client.h"
#include "Apartment.h"
#include "Realtor.h"

class QPushButton;
class QStackedLayout;
class ClientViewersContainter;
class ApartmentViewersContainter;
class RealtorViewersContainer;
class PowerToolMenu;

class SideMenu : public QWidget
{
	Q_OBJECT
public:
	SideMenu(QWidget* parent = nullptr);
	~SideMenu();
	void setClients(const QMap<int, Client>& clientsData);
	void setApartments(const QMap<int, Apartment>& apartmentsData);
	void setRealtors(const QMap<int, Realtor>& realtorsData);
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();

private:

	QPushButton* m_signout;
	QPushButton* m_clients;
	QPushButton* m_apartments;
	QPushButton* m_realtors;
	ClientViewersContainter* m_clientsViewerContainter;
	RealtorViewersContainer* m_realtorsViewerContainer;
	ApartmentViewersContainter* m_apartmentsViewerContainer;
	PowerToolMenu* m_powerToolMenu;
	QMap<int, Client> m_clientsData;
	QMap<int, Apartment> m_apartmentsData;
	QStackedLayout *m_stackLayout;


};

