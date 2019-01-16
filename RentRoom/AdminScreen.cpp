#include "AdminScreen.h"
#include <QBoxLayout>
#include <QMessageBox>

#include "MapsView.h"
#include "SideMenu.h"
#include "MarkerData.h"

#include "ListRealtorsRequest.h"
#include "ListRealtorsResponse.h"
#include "ListClientsRequest.h"
#include "ListClientsResponse.h"
#include "ListApartmentsRequest.h"
#include "ListApartmentsResponse.h"
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


AdminScreen::AdminScreen(QWidget* parent):QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}

AdminScreen::~AdminScreen()
{
}

void AdminScreen::removeMarkers()
{
}

void AdminScreen::createMembers()
{
	m_mapsView = new MapsView;
	m_sideMenu = new SideMenu(this);
}

void AdminScreen::setupMembers()
{
}

void AdminScreen::setupLayout()
{
	QHBoxLayout* hlay = new QHBoxLayout;
	hlay->addWidget(m_sideMenu,0);
	hlay->addWidget(m_mapsView,10);
	hlay->setSpacing(0);
	hlay->setContentsMargins(5, 5, 5, 5);
	hlay->setSpacing(10);
	setLayout(hlay);
}

void AdminScreen::makeConnections()
{
	connect(m_mapsView, &MapsView::locationPicked, [this](double latitude, double longitude) {

		QMessageBox::information(this, "Picked", QString("Location Selected: %1 %2").arg(latitude).arg(longitude), QMessageBox::Ok);
	});
}
void AdminScreen::onListClientsResponseReady(const ListClientsResponse & response)
{
	m_sideMenu->setClients(response.getClients());
}


void AdminScreen::onListApartmentsResponseReady(const ListApartmentsResponse & response)
{
	m_apartments = response.getApartments();
	for (auto& apartment : m_apartments) {
		MarkerData data;
		data.setLatitude(apartment.getLocLatitude());
		data.setLongitude(apartment.getLocLongitude());
		data.setName(apartment.getName());
		data.setId(apartment.getId());
		data.setRented(apartment.getRented());
		m_mapsView->onAddMarker(data);
	}
	m_sideMenu->setApartments(m_apartments);
}

void AdminScreen::onListRealtorsResponseReady(const ListRealtorsResponse & response)
{
	m_sideMenu->setRealtors(response.getRealtors());
}

void AdminScreen::onCreateApartmentResponseReady(const CreateApartmentResponse & response)
{
}

void AdminScreen::onCreateClientResponseReady(const CreateClientResponse & response)
{
}

void AdminScreen::onCreateRealtorResponseReady(const CreateRealtorResponse & response)
{
}

void AdminScreen::onUpdateApartmentResponseReady(const UpdateApartmentResponse & response)
{
}

void AdminScreen::onUpdateClientResponseReady(const UpdateClientResponse & response)
{
}

void AdminScreen::onUpdateRealtorResponseReady(const UpdateRealtorResponse & response)
{
}

void AdminScreen::onDeleteApartmentResponseReady(const DeleteApartmentResponse & response)
{
}

void AdminScreen::onDeleteClientResponseReady(const DeleteClientResponse & response)
{
}

void AdminScreen::onDeleteRealtorResponseReady(const DeleteRealtorResponse & response)
{
}
