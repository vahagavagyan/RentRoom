#include "Controller.h"
#include <QDir>
#include <QMutex>
#include <QMutexLocker>
#include <QMap>
#include <QDateTime>
#include <QTextStream>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QState>
#include <QFinalState>

#include "LoginState.h"
#include "SignupState.h"
#include "RoleSelectionState.h"
#include "ClientState.h"
#include "AdminState.h"
#include "RealtorState.h"
#include "NetworkManager.h"
#include "NetworkURL.h"


#include "SignupRequest.h"
#include "SignupResponse.h"
#include "LoginRequest.h"
#include "LoginResponse.h"
#include "ListAvailableApartmentsRequest.h"
#include "ListAvailableApartmentsResponse.h"
#include "RentRequest.h"
#include "RentResponse.h"
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


#include "MarkerData.h"
#include "Options.h"


#define LOG_FILE            QString("RentRoom_log.txt")

#define DEFAULT_DEBUG_VERBOSITY QtWarningMsg

QMutex g_debugMutex;
int g_debugVerbosity = DEFAULT_DEBUG_VERBOSITY;

void stopThread(QThread* thread)
{
	static const int waitMsec = 10 * 1000;
	thread->quit();
	if (!thread->wait(waitMsec))
	{
		thread->terminate();
	}
}
void debugMessagehandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	if (type > g_debugVerbosity) return;

	QMutexLocker lock(&g_debugMutex);

	static const QMap<QtMsgType, QString> prefixMap = []() {
		QMap<QtMsgType, QString> map;
		map.insert(QtWarningMsg, QString("Warning"));
		map.insert(QtCriticalMsg, QString("Critical"));
		map.insert(QtFatalMsg, QString("Fatal"));
		return map;
	}();
	static const QString defaultPrefix("Debug");
	static const QString dateTimeFormat("yyyy/MM/dd-HH:mm:ss.zzz");
	static const QString messageFormat("[%1]%2: %3 (%4:%5, %6)\n");

	const QString prefix = ((prefixMap.contains(type)) ? prefixMap.value(type, defaultPrefix) : QString("Unknown"));
	const QString finalMsg = messageFormat
		.arg(QDateTime::currentDateTime().toString(dateTimeFormat))
		.arg(prefix)
		.arg(msg)
		.arg(context.file)
		.arg(context.line)
		.arg(context.function);

	fprintf(stderr, "%s", finalMsg.toLocal8Bit().constData());

	QFile file(QDir::homePath() + QDir::separator() + LOG_FILE);
	const QFile::OpenMode mode = QFile::Text | (file.exists() ? QFile::Append : QFile::WriteOnly);
	if (file.open(mode))
	{
		QTextStream(&file) << finalMsg;
		file.close();
	}
}


Controller *Controller::s_ctrl = 0;

Controller::Controller()
{
}


Controller::~Controller()
{
}

bool Controller::init()
{
	s_ctrl = this;
	initQt();
	initLogFile();

	initUI();
	initNetwork();
	initStates();
	connectSignals();
	start();
	return true;
}
void Controller::release()
{
	m_mainWnd.reset(nullptr);
	stopThread(&m_networkThread);
	s_ctrl = nullptr;
}
void Controller::initQt()
{
	//Register meta types 
	qRegisterMetaType<SignupRequest>();
	qRegisterMetaType<SignupResponse>();
	qRegisterMetaType<LoginRequest>();
	qRegisterMetaType<LoginResponse>();
	qRegisterMetaType<MarkerData>();
	qRegisterMetaType<ListAvailableApartmentsRequest>();
	qRegisterMetaType<ListAvailableApartmentsResponse>();
	qRegisterMetaType<RentRequest>();
	qRegisterMetaType<RentResponse>();
	qRegisterMetaType<ListRealtorsRequest>();
	qRegisterMetaType<ListRealtorsResponse>();
	qRegisterMetaType<ListClientsRequest>();
	qRegisterMetaType<ListClientsResponse>();
	qRegisterMetaType<ListApartmentsRequest>();
	qRegisterMetaType<ListApartmentsResponse>();
	qRegisterMetaType<DeleteApartmentRequest>();
	qRegisterMetaType<DeleteApartmentResponse>();
	qRegisterMetaType<DeleteClientRequest>();
	qRegisterMetaType<DeleteClientResponse>();
	qRegisterMetaType<DeleteRealtorRequest>();
	qRegisterMetaType<DeleteRealtorResponse>();
	qRegisterMetaType<CreateApartmentRequest>();
	qRegisterMetaType<CreateApartmentResponse>();
	qRegisterMetaType<CreateClientRequest>();
	qRegisterMetaType<CreateClientResponse>();
	qRegisterMetaType<CreateRealtorRequest>();
	qRegisterMetaType<CreateRealtorResponse>();
	qRegisterMetaType<UpdateApartmentRequest>();
	qRegisterMetaType<UpdateApartmentResponse>();
	qRegisterMetaType<UpdateClientRequest>();
	qRegisterMetaType<UpdateClientResponse>();
	qRegisterMetaType<UpdateRealtorRequest>();
	qRegisterMetaType<UpdateRealtorResponse>();

	qInstallMessageHandler(debugMessagehandler);
}

void Controller::initLogFile()
{
	static const int maxLogSize = 1 * 1024 * 1024;
	const QString logName = QDir::homePath() + QDir::separator() + LOG_FILE;
	QFile file(logName);
	if (file.size() > maxLogSize)
	{
		file.remove();
	}
}

void Controller::initUI()
{
	m_mainWnd.reset(new MainWindow);
	m_mainWnd->setMinimumSize(1280, 800);
	//QPoint centerPoint = qApp->desktop()->availableGeometry().topLeft();
	//centerPoint.setX((qApp->desktop()->availableGeometry().width() - m_mainWnd->width()) / 2);
	//centerPoint.setY((qApp->desktop()->availableGeometry().height() - m_mainWnd->height()) / 2);
	//m_mainWnd->move(centerPoint);
	m_mainWnd->resize(qApp->desktop()->availableGeometry().size());
	//m_mainWnd->resize(m_mainWnd->minimumSize());
	m_mainWnd->move(qApp->desktop()->availableGeometry().topLeft());;
	m_mainWnd->setBackground(QImage(":/images/skyline"));
}

void Controller::initNetwork()
{

	NetworkURL::initURLs();
	m_networkMgr = new NetworkManager;
	m_networkMgr->moveToThread(&m_networkThread);
	m_networkThread.start();
}

void Controller::initStates()
{
	createStates();
	setupTransitions();

	UserRole role = Options::getUserRole();
	
	switch (role)
	{
	case eAdmin:		
	case eClient:
	case eRealtor:
		setUserRole(role);
		m_stateGeneral->setInitialState(m_stateLogin);
		break;
	case eMaxRoles:
	default:
		m_stateGeneral->setInitialState(m_stateRoleSelection);
		break;
	}

	m_stateMachine.addState(m_stateGeneral);
	m_stateMachine.addState(m_stateEnd);
	m_stateMachine.setInitialState(m_stateGeneral);
}

void Controller::connectSignals()
{
}
void Controller::start()
{
	m_mainWnd->show();
	m_stateMachine.start();
}
void Controller::createStates()
{
	m_stateGeneral = new QState();
	m_stateEnd = new QFinalState();

	m_stateRoleSelection = new RoleSelectionState(m_stateGeneral);
	m_stateLogin = new LoginState(m_stateGeneral);
	m_stateSignup = new SignupState(m_stateGeneral);
	m_stateClient = new ClientState(m_stateGeneral);
	m_stateAdmin = new AdminState(m_stateGeneral);
	m_stateRealtor = new RealtorState(m_stateGeneral);

}
void Controller::setupTransitions()
{
	m_stateRoleSelection->addTransition(m_stateRoleSelection, &RoleSelectionState::loginRequested, m_stateLogin);
	m_stateRoleSelection->addTransition(m_stateRoleSelection, &RoleSelectionState::signupRequested, m_stateSignup);

	m_stateLogin->addTransition(m_stateLogin, &LoginState::cancelRequested, m_stateRoleSelection);
	m_stateLogin->addTransition(m_stateLogin, &LoginState::clientLoginSuccess, m_stateClient);
	m_stateLogin->addTransition(m_stateLogin, &LoginState::adminLoginSuccess, m_stateAdmin);
	m_stateLogin->addTransition(m_stateLogin, &LoginState::realtorLoginSuccess, m_stateRealtor);

	m_stateSignup->addTransition(m_stateSignup, &SignupState::cancelRequested, m_stateRoleSelection);
	m_stateSignup->addTransition(m_stateSignup, &SignupState::signupSuccess, m_stateLogin);
}

