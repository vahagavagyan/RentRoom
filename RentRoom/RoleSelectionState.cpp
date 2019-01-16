#include "RoleSelectionState.h"
#include "Controller.h"
#include "RoleSelectionScreen.h"


RoleSelectionState::RoleSelectionState(QState *parent):QState(parent)
{

}


RoleSelectionState::~RoleSelectionState()
{
}

void RoleSelectionState::connectSignals(RoleSelectionScreen * screen)
{
	m_connections.push_back(connect(screen, &RoleSelectionScreen::loginRequested, this, &RoleSelectionState::loginRequested));
	m_connections.push_back(connect(screen, &RoleSelectionScreen::signupRequested, this, &RoleSelectionState::signupRequested));

}

void RoleSelectionState::onEntry(QEvent * event)
{
	QState::onEntry(event);
	rentCtrl->getMainWnd()->setCurrentScreen(ST_RoleSelector);
	connectSignals(GETSCREEN(RoleSelectionScreen, ST_RoleSelector));
}

void RoleSelectionState::onExit(QEvent * event)
{
	QState::onExit(event);
	for (int i = 0; i < m_connections.count(); ++i)
	{
		disconnect(m_connections.at(i));
	}
	m_connections.clear();
}
