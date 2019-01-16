#include "RealtorScreen.h"

#include <QBoxLayout>

#include "MapsView.h"

#include "DeleteApartmentRequest.h"
#include "DeleteApartmentResponse.h"
#include "CreateApartmentRequest.h"
#include "CreateApartmentResponse.h"
#include "UpdateApartmentRequest.h"
#include "UpdateApartmentResponse.h"
#include "ListRealtorApartmentsRequest.h"
#include "ListRealtorApartmentsResponse.h"


RealtorScreen::RealtorScreen(QWidget* parent):QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();

}


RealtorScreen::~RealtorScreen()
{
}

void RealtorScreen::createMembers()
{
	m_mapsView = new MapsView;
}

void RealtorScreen::setupMembers()
{
}

void RealtorScreen::setupLayout()
{
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(m_mapsView);
	setLayout(hlay);
}

void RealtorScreen::makeConnections()
{
}

void RealtorScreen::onCreateApartmentResponseReady(const CreateApartmentResponse & response)
{
}

void RealtorScreen::onUpdateApartmentResponseReady(const UpdateApartmentResponse & response)
{
}

void RealtorScreen::onDeleteApartmentResponseReady(const DeleteApartmentResponse & response)
{
}

void RealtorScreen::onListRealtorApartmentsResponseReady(const ListRealtorApartmentsResponse & response)
{
}
