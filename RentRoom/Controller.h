#pragma once
#include <QObject>
#include <QStateMachine>
#include <QThread>

#include <memory>

#include "MainWindow.h"
#include "UserRole.h"
class QState;
class QFinalState;
class RoleSelectionState;
class SignupState;
class LoginState;
class ClientState;
class AdminState;
class RealtorState;
class NetworkManager;

class Controller : public QObject
{
	Q_OBJECT

public:
	static Controller *inst();

	Controller();
	~Controller();

	bool init();
	void release();
	MainWindow *getMainWnd()const;
	void setUserRole(UserRole role);
	UserRole getUserRole()const;
	NetworkManager* getNetworkManager();
private:
	void initQt();
	void initLogFile();
	void initUI();
	void initNetwork();
	void initStates();
	void createStates();
	void setupTransitions();
	void connectSignals();

	void start();
private:

	static Controller *s_ctrl;

	UserRole m_userRole;
	std::auto_ptr<MainWindow> m_mainWnd;

	QThread m_networkThread;
	NetworkManager *m_networkMgr;

	QStateMachine m_stateMachine;
	QState *m_stateGeneral;
	RoleSelectionState *m_stateRoleSelection;
	LoginState *m_stateLogin;
	SignupState *m_stateSignup;
	ClientState *m_stateClient;
	AdminState *m_stateAdmin;
	RealtorState *m_stateRealtor;
	QFinalState *m_stateEnd;

};


#define rentCtrl Controller::inst()

#define GETSCREEN(classType, screenType) qobject_cast<classType*>(rentCtrl->getMainWnd()->getScreen(screenType))

inline Controller *Controller::inst()
{
	return s_ctrl;
}

inline MainWindow *Controller::getMainWnd()const
{
	return m_mainWnd.get();
}

inline void Controller::setUserRole(UserRole role)
{
	m_userRole = role;
}

inline UserRole Controller::getUserRole() const
{
	return m_userRole;
}

inline NetworkManager * Controller::getNetworkManager()
{
	return m_networkMgr;
}
