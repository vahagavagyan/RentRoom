#include "SignupState.h"
#include "Controller.h"
#include "SignupScreen.h"
#include "Controller.h"
#include "NetworkManager.h"

SignupState::SignupState(QState *parent):QState(parent)
{
}


SignupState::~SignupState()
{
}

void SignupState::onEntry(QEvent * event)
{

	QState::onEntry(event);
	rentCtrl->getMainWnd()->setCurrentScreen(ST_SignupScreen);
	connectSignals(GETSCREEN(SignupScreen, ST_SignupScreen));
}

void SignupState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}

void SignupState::connectSignals(SignupScreen * screen)
{
	m_connections.push_back(connect(screen, &SignupScreen::cancelRequested, this, &SignupState::cancelRequested));
	m_connections.push_back(connect(screen, &SignupScreen::signupRequested, this, &SignupState::onSignupRequested));
	m_connections.push_back(connect(screen, &SignupScreen::signupSuccess, this, &SignupState::signupSuccess));
	m_connections.push_back(connect(rentCtrl->getNetworkManager(), &NetworkManager::signupResponseReady, screen, &SignupScreen::onSignupResponseReady));
}



void SignupState::onSignupRequested(const SignupRequest& data)
{
	auto networkMgr = rentCtrl->getNetworkManager();
	QMetaObject::invokeMethod(networkMgr, "postSignupRequest", Qt::QueuedConnection, Q_ARG(SignupRequest, data));
}