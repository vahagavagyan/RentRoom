#include "RealtorState.h"

#include "RealtorScreen.h"

#include "Controller.h"
#include "NetworkManager.h"

#include "RealtorScreen.h"
#include "DeleteApartmentRequest.h"
#include "DeleteApartmentResponse.h"
#include "CreateApartmentRequest.h"
#include "CreateApartmentResponse.h"
#include "UpdateApartmentRequest.h"
#include "UpdateApartmentResponse.h"
#include "ListRealtorApartmentsRequest.h"
#include "ListRealtorApartmentsResponse.h"


RealtorState::RealtorState(QState *parent):QState(parent)
{
}


RealtorState::~RealtorState()
{
}

void RealtorState::onEntry(QEvent * event)
{
	QState::onEntry(event);
	rentCtrl->getMainWnd()->setCurrentScreen(ST_RealtorScreen);
	connectSignals(GETSCREEN(RealtorScreen, ST_RealtorScreen));
}

void RealtorState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}

void RealtorState::onDeleteApartmentRequested(const DeleteApartmentRequest & request)
{

	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postDeleteApartment", Q_ARG(DeleteApartmentRequest, request));
}

void RealtorState::onUpdateApartmentRequested(const UpdateApartmentRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postUpdateApartment", Q_ARG(UpdateApartmentRequest, request));
}

void RealtorState::onCreateApartmentRequested(const CreateApartmentRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postCreateApartment", Q_ARG(CreateApartmentRequest, request));
}

void RealtorState::onListRealtorApartmentsRequested(const ListRealtorApartmentsRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postListRealtorApartments", Q_ARG(ListRealtorApartmentsRequest, request));
}

void RealtorState::connectSignals(RealtorScreen * screen)
{

	auto networkMgr = rentCtrl->getNetworkManager();

	m_connections.push_back(connect(networkMgr, &NetworkManager::listRealtorApartmentsResponseReady, screen, &RealtorScreen::onListRealtorApartmentsResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::createApartmentResponseReady, screen, &RealtorScreen::onCreateApartmentResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::updateApartmentResponseReady, screen, &RealtorScreen::onUpdateApartmentResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::deleteApartmentResponseReady, screen, &RealtorScreen::onDeleteApartmentResponseReady));


	m_connections.push_back(connect(screen, &RealtorScreen::createApartmentRequested, this, &RealtorState::onCreateApartmentRequested));
	m_connections.push_back(connect(screen, &RealtorScreen::updateApartmentRequested, this, &RealtorState::onUpdateApartmentRequested));
	m_connections.push_back(connect(screen, &RealtorScreen::deleteApartmentRequested, this, &RealtorState::onDeleteApartmentRequested));
	m_connections.push_back(connect(screen, &RealtorScreen::listRealtorApartmentsRequested, this, &RealtorState::onListRealtorApartmentsRequested));






}
