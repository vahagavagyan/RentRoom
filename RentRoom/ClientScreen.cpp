#include "ClientScreen.h"

#include <QBoxLayout>
#include <QMessageBox>

#include "MapsView.h"
#include "RentWidget.h"
#include "MarkerData.h"
#include "Apartment.h"

#include "Options.h"
#include "RentRequest.h"
#include "RentResponse.h"

ClientScreen::ClientScreen(QWidget *parent):QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();

}


ClientScreen::~ClientScreen()
{
}

void ClientScreen::removeMarkers()
{
	m_mapsView->removeMarkers();
}

void ClientScreen::setAvailableApartments(QMap<int , Apartment> availableApartments)
{
	m_availableApartments = availableApartments;
	for (auto& availableApartment : m_availableApartments){
		MarkerData data;
		data.setLatitude(availableApartment.getLocLatitude());
		data.setLongitude(availableApartment.getLocLongitude());
		data.setName(availableApartment.getName());
		data.setId(availableApartment.getId());
		m_mapsView->onAddMarker(data);
	}

}

void ClientScreen::createMembers()
{
	m_mapsView = new MapsView;
	m_rentWidget = new RentWidget;
}

void ClientScreen::setupMembers()
{
}

void ClientScreen::setupLayout()
{
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(m_mapsView, 2);
	hlay->addWidget(m_rentWidget);
	m_rentWidget->hide();
	setLayout(hlay);
}

void ClientScreen::makeConnections()
{

	connect(m_mapsView, &MapsView::markerClicked, [this](const MarkerData& data) {
		m_rentWidget->setApartment(m_availableApartments[data.getId()]);
		m_rentWidget->show();
	});
	connect(m_rentWidget, &RentWidget::rentClicked, [this]() {
		const Apartment& selectedApartment = m_rentWidget->getApartment();
		RentRequest request;
		request.setEmail(Options::getUserEmail());
		request.setKey(Options::getUserKey());
		request.setUserRole(Options::getUserRole());
		request.setApartment(selectedApartment);
		request.setStartDate(QDate::currentDate());
		request.setEndDate(QDate::currentDate().addDays(23));
		emit rentRequested(request);
	});
}


void ClientScreen::onRentResponseReady(const RentResponse& response)
{
	const Apartment& selectedApartment = m_rentWidget->getApartment();
	if (response.isSucceeded()) {
		QMessageBox::information(this, "Success", selectedApartment.getName() + " successfully rented.", QMessageBox::Ok);
		m_mapsView->removeMarker(selectedApartment.getId());
		m_rentWidget->hide();
	}
	else {
		QMessageBox::information(this, "Critical", "Failed to rent the "+ selectedApartment.getName()+ " : "+response.getMessage(), QMessageBox::Ok);
	}
}
