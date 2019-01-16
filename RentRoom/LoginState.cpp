#include "LoginState.h"
#include "Controller.h"
#include "LoginScreen.h"
#include "LoginRequest.h"
#include "LoginResponse.h"
#include "NetworkManager.h"


LoginState::LoginState(QState *parent):QState(parent)
{
}


LoginState::~LoginState()
{
}

void LoginState::connectSignals(LoginScreen * screen)
{
	m_connections.push_back(connect(screen, &LoginScreen::cancelRequested, this, &LoginState::cancelRequested));
	m_connections.push_back(connect(screen, &LoginScreen::loginRequested, this, &LoginState::onLoginRequested));
	m_connections.push_back(connect(screen, &LoginScreen::loginSuccess, this, &LoginState::onLoginSuccess));
	m_connections.push_back(connect(rentCtrl->getNetworkManager(), &NetworkManager::loginResponseReady, screen, &LoginScreen::onLoginResponseReady));

}

void LoginState::onEntry(QEvent * event)
{
	QState::onEntry(event);
	auto screen = GETSCREEN(LoginScreen, ST_Login);
	screen->updateForUserRole();
	rentCtrl->getMainWnd()->setCurrentScreen(ST_Login);
	screen->updateForUserRole();
	connectSignals(screen);
}

void LoginState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}

void LoginState::onLoginRequested(const LoginRequest& data)
{
	auto networkMgr = rentCtrl->getNetworkManager();
	QMetaObject::invokeMethod(networkMgr, "postLoginRequest", Qt::QueuedConnection, Q_ARG(LoginRequest, data));
}

void LoginState::onLoginSuccess(const LoginResponse & data)
{
	switch (data.getUserRole()) {
	case eAdmin:
		emit adminLoginSuccess();
		break;
	case eClient:
		emit clientLoginSuccess();
		break;
	case eRealtor:
		emit realtorLoginSuccess();
		break;
	}
}