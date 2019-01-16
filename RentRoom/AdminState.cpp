#include "AdminState.h"


#include <QMetaObject>

#include "Controller.h"
#include "AdminScreen.h"
#include "NetworkManager.h"
#include "ListClientsRequest.h"
#include "ListClientsResponse.h"

#include "ListRealtorsRequest.h"
#include "ListRealtorsResponse.h"

#include "ListApartmentsRequest.h"
#include "ListApartmentsResponse.h"

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


AdminState::AdminState(QState *parent):QState(parent)
{
}


AdminState::~AdminState()
{
}

void AdminState::onEntry(QEvent * event)
{
	QState::onEntry(event);
	rentCtrl->getMainWnd()->setCurrentScreen(ST_AdminScreen);
	connectSignals(GETSCREEN(AdminScreen, ST_AdminScreen));
	GETSCREEN(AdminScreen, ST_AdminScreen)->removeMarkers();
	onListApartmentsRequested(ListApartmentsRequest());
	onListClientsRequested(ListClientsRequest());
	onListRealtorsRequested(ListRealtorsRequest());
}

void AdminState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}

void AdminState::connectSignals(AdminScreen * screen)
{
	auto networkMgr = rentCtrl->getNetworkManager();
	m_connections.push_back(connect(networkMgr, &NetworkManager::listApartmentsResponseReady, screen, &AdminScreen::onListApartmentsResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::listClientsResponseReady, screen, &AdminScreen::onListClientsResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::listRealtorsResponseReady, screen, &AdminScreen::onListRealtorsResponseReady));

	m_connections.push_back(connect(networkMgr, &NetworkManager::deleteApartmentResponseReady, screen, &AdminScreen::onDeleteApartmentResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::deleteClientResponseReady, screen, &AdminScreen::onDeleteClientResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::deleteRealtorResponseReady, screen, &AdminScreen::onDeleteRealtorResponseReady));

	m_connections.push_back(connect(networkMgr, &NetworkManager::updateApartmentResponseReady, screen, &AdminScreen::onUpdateApartmentResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::updateClientResponseReady, screen, &AdminScreen::onUpdateClientResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::updateRealtorResponseReady, screen, &AdminScreen::onUpdateRealtorResponseReady));

	m_connections.push_back(connect(networkMgr, &NetworkManager::createApartmentResponseReady, screen, &AdminScreen::onCreateApartmentResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::createClientResponseReady, screen, &AdminScreen::onCreateClientResponseReady));
	m_connections.push_back(connect(networkMgr, &NetworkManager::createRealtorResponseReady, screen, &AdminScreen::onCreateRealtorResponseReady));

	m_connections.push_back(connect(screen, &AdminScreen::listClientsRequested, this, &AdminState::onListClientsRequested));
	m_connections.push_back(connect(screen, &AdminScreen::listApartmentsRequested, this, &AdminState::onListApartmentsRequested));
	m_connections.push_back(connect(screen, &AdminScreen::listRealtorsRequested, this, &AdminState::onListRealtorsRequested));

	m_connections.push_back(connect(screen, &AdminScreen::deleteApartmentRequested, this, &AdminState::onDeleteApartmentRequested));
	m_connections.push_back(connect(screen, &AdminScreen::deleteClientRequested, this, &AdminState::onDeleteClientRequested));
	m_connections.push_back(connect(screen, &AdminScreen::deleteRealtorRequested, this, &AdminState::onDeleteRealtorRequested));

	m_connections.push_back(connect(screen, &AdminScreen::updateApartmentRequested, this, &AdminState::onUpdateApartmentRequested));
	m_connections.push_back(connect(screen, &AdminScreen::updateClientRequested, this, &AdminState::onUpdateClientRequested));
	m_connections.push_back(connect(screen, &AdminScreen::updateRealtorRequested, this, &AdminState::onUpdateRealtorRequested));

	m_connections.push_back(connect(screen, &AdminScreen::createApartmentRequested, this, &AdminState::onCreateApartmentRequested));
	m_connections.push_back(connect(screen, &AdminScreen::createClientRequested, this, &AdminState::onCreateClientRequested));
	m_connections.push_back(connect(screen, &AdminScreen::createRealtorRequested, this, &AdminState::onCreateRealtorRequested));
}



void AdminState::onListClientsRequested(const ListClientsRequest& request)
{

	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postListClients", Q_ARG(ListClientsRequest, request));
}
void AdminState::onListApartmentsRequested(const ListApartmentsRequest& request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postListApartments", Q_ARG(ListApartmentsRequest, request));
}
void AdminState::onListRealtorsRequested(const ListRealtorsRequest& request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postListRealtors", Q_ARG(ListRealtorsRequest, request));
}

void AdminState::onDeleteApartmentRequested(const DeleteApartmentRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postDeleteApartment", Q_ARG(DeleteApartmentRequest, request));
}

void AdminState::onDeleteClientRequested(const DeleteClientRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postDeleteClient", Q_ARG(DeleteClientRequest, request));
}

void AdminState::onDeleteRealtorRequested(const DeleteRealtorRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postDeleteRealtor", Q_ARG(DeleteRealtorRequest, request));
}

void AdminState::onUpdateApartmentRequested(const UpdateApartmentRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postUpdateApartment", Q_ARG(UpdateApartmentRequest, request));
}

void AdminState::onUpdateClientRequested(const UpdateClientRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postUpdateClient", Q_ARG(UpdateClientRequest, request));
}

void AdminState::onUpdateRealtorRequested(const UpdateRealtorRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postUpdateRealtor", Q_ARG(UpdateRealtorRequest, request));
}

void AdminState::onCreateApartmentRequested(const CreateApartmentRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postCreateApartment", Q_ARG(CreateApartmentRequest, request));
}

void AdminState::onCreateClientRequested(const CreateClientRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postCreateClient", Q_ARG(CreateClientRequest, request));
}

void AdminState::onCreateRealtorRequested(const CreateRealtorRequest & request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postCreateRealtor", Q_ARG(CreateRealtorRequest, request));
}
