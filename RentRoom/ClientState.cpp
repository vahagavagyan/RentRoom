#include "ClientState.h"

#include <QMetaObject>

#include "Options.h"
#include "Controller.h"
#include "ClientScreen.h"
#include "NetworkManager.h"
#include "ListAvailableApartmentsRequest.h"
#include "ListAvailableApartmentsResponse.h"
#include "RentRequest.h"
#include "RentResponse.h"

ClientState::ClientState(QState *parent):QState(parent)
{
}


ClientState::~ClientState()
{
}

void ClientState::connectSignals(ClientScreen * clientScreen)
{
	m_connections.push_back(connect(rentCtrl->getNetworkManager(), &NetworkManager::listAvailableApartmentsResponseReady, this, &ClientState::onListAvailableApartmetsReady));
	m_connections.push_back(connect(clientScreen, &ClientScreen::rentRequested, this, &ClientState::onRentRequested));
	m_connections.push_back(connect(rentCtrl->getNetworkManager(), &NetworkManager::rentResponseReady, clientScreen, &ClientScreen::onRentResponseReady));
}


void ClientState::onEntry(QEvent * event)
{
	QState::onEntry(event);
	rentCtrl->getMainWnd()->setCurrentScreen(ST_ClientScreen);
	ClientScreen * screen = GETSCREEN(ClientScreen, ST_ClientScreen);
	screen->removeMarkers();
	onMakeListAvailableApartmetsRequest();
	connectSignals(screen);
}

void ClientState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}


void ClientState::onListAvailableApartmetsReady(const ListAvailableApartmentsResponse& response)
{
	GETSCREEN(ClientScreen, ST_ClientScreen)->setAvailableApartments(response.getApartments());
}
void ClientState::onListAvailableApartmetsRequested(const ListAvailableApartmentsRequest& request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postListAvailableApartments", Q_ARG(ListAvailableApartmentsRequest, request));
}

void ClientState::onMakeListAvailableApartmetsRequest()
{
	ListAvailableApartmentsRequest request;
	request.setUserRole(Options::getUserRole());
	request.setKey(Options::getUserKey());
	request.setEmail(Options::getUserEmail());
	onListAvailableApartmetsRequested(request);
}

void ClientState::onRentRequested(const RentRequest& request)
{
	QMetaObject::invokeMethod(rentCtrl->getNetworkManager(), "postRentRequest", Q_ARG(RentRequest, request));
}
