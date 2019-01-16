#include "RoleSelectionScreen.h"
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QDebug>

#include "AuthenticationMethodUIElement.h"
#include "Controller.h"

RoleSelectionScreen::RoleSelectionScreen(QWidget *parent) :QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}


RoleSelectionScreen::~RoleSelectionScreen()
{
}

void RoleSelectionScreen::createMembers()
{
	m_adminModeBtn = new QLabel();
	m_clientModeBtn = new QLabel();
	m_realtorModeBtn = new QLabel();


	m_adminAuthMethod = new AuthenticationMethodUIElement();
	m_clientAuthMethod = new AuthenticationMethodUIElement();
	m_realtorAuthMethod = new AuthenticationMethodUIElement();
}

void RoleSelectionScreen::setupMembers()
{
	m_adminModeBtn->setText("<img src=:/images/admin><br>Admin");
	m_clientModeBtn->setText("<img src=:/images/client><br>Client");
	m_realtorModeBtn->setText("<img src=:/images/realtor><br>Realtor");
	m_adminModeBtn->setAlignment(Qt::AlignCenter);
	m_clientModeBtn->setAlignment(Qt::AlignCenter);
	m_realtorModeBtn->setAlignment(Qt::AlignCenter);
}


void RoleSelectionScreen::setupLayout()
{

	adminAuthMethod = new QWidget();
	clientAuthMethod = new QWidget();
	realtorAuthMethod = new QWidget();

	adminAuthMethod->installEventFilter(this);
	clientAuthMethod->installEventFilter(this);
	realtorAuthMethod->installEventFilter(this);
	adminAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240);");
	clientAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240);");
	realtorAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240);");


	m_adminModeBtn ->setStyleSheet(" background: transparent;  font: bold 15px; color: rgb(153,153,153);");
	m_clientModeBtn-> setStyleSheet(" background-color: transparent; font: bold 15px; color: rgb(153,153,153);");
	m_realtorModeBtn->setStyleSheet(" background-color: transparent; font: bold 15px; color: rgb(153,153,153);");

	m_adminAuthMethod->setStyleSheet(" background-color: rgb(153,153,153); ");
	m_clientAuthMethod->setStyleSheet(" background-color: rgb(153,153,153); ");
	m_realtorAuthMethod->setStyleSheet(" background-color: rgb(153,153,153); ");

	adminAuthMethod->setFixedSize(350, 350);
	clientAuthMethod->setFixedSize(350, 350);
	realtorAuthMethod->setFixedSize(350, 350);

	QHBoxLayout *hlay = new QHBoxLayout;
	{
		QVBoxLayout *vlay = new QVBoxLayout;
		vlay->addStretch(200);
		vlay->addWidget(m_adminModeBtn);
		vlay->addWidget(m_adminAuthMethod, 0, Qt::AlignCenter);
		vlay->addStretch(200);
		hlay->addWidget(adminAuthMethod);
		adminAuthMethod->setLayout(vlay);
	}
	{
		QVBoxLayout *vlay = new QVBoxLayout;
		vlay->addStretch(200);
		vlay->addWidget(m_clientModeBtn);
		vlay->addWidget(m_clientAuthMethod, 0, Qt::AlignCenter);
		vlay->addStretch(200);
		hlay->addWidget(clientAuthMethod);
		clientAuthMethod->setLayout(vlay);
	}
	{
		QVBoxLayout *vlay = new QVBoxLayout;
		vlay->addStretch(200);
		vlay->addWidget(m_realtorModeBtn);
		vlay->addWidget(m_realtorAuthMethod, 0, Qt::AlignCenter);
		vlay->addStretch(200);
		hlay->addWidget(realtorAuthMethod);
		realtorAuthMethod->setLayout(vlay);
	}
	setLayout(hlay);
}

void RoleSelectionScreen::makeConnections()
{
	connect(m_adminAuthMethod, &AuthenticationMethodUIElement::loginRequested, [this]() {
		rentCtrl->setUserRole(eAdmin);
		emit loginRequested();
	});

	connect(m_adminAuthMethod, &AuthenticationMethodUIElement::signupRequested, [this]() {
		rentCtrl->setUserRole(eAdmin);
		emit signupRequested();
	});

	connect(m_clientAuthMethod, &AuthenticationMethodUIElement::loginRequested, [this]() {
		rentCtrl->setUserRole(eClient);
		emit loginRequested();
	});

	connect(m_clientAuthMethod, &AuthenticationMethodUIElement::signupRequested, [this]() {
		rentCtrl->setUserRole(eClient);
		emit signupRequested();
	});
	connect(m_realtorAuthMethod, &AuthenticationMethodUIElement::loginRequested, [this]() {
		rentCtrl->setUserRole(eRealtor);
		emit loginRequested();
	});

	connect(m_realtorAuthMethod, &AuthenticationMethodUIElement::signupRequested, [this]() {
		rentCtrl->setUserRole(eRealtor);
		emit signupRequested();
	});
}

bool RoleSelectionScreen::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == adminAuthMethod && event->type() == QEnterEvent::Enter) {
		adminAuthMethod->setStyleSheet(" background-color: rgba(27,47,70,240);");
		//adminAuthMethod->setFixedSize(280, 280);
	}

	if (watched == adminAuthMethod && event->type() == QEnterEvent::Leave) {
		adminAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240); ");
		//adminAuthMethod->setFixedSize(250, 250);
	}


	if (watched == clientAuthMethod && event->type() == QEnterEvent::Enter) {
		clientAuthMethod->setStyleSheet(" background-color: rgba(27,47,70,240);");
		//clientAuthMethod->setFixedSize(280, 280);
	}

	if (watched == clientAuthMethod && event->type() == QEnterEvent::Leave) {
		clientAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240); ");
		//clientAuthMethod->setFixedSize(250, 250);
	}

	if (watched == realtorAuthMethod && event->type() == QEnterEvent::Enter) {
		realtorAuthMethod->setStyleSheet(" background-color: rgba(27,47,70,240);");
		//realtorAuthMethod->setFixedSize(280, 280);
	}

	if (watched == realtorAuthMethod && event->type() == QEnterEvent::Leave) {
		realtorAuthMethod->setStyleSheet(" background-color: rgba(27,64,93,240); ");
		//realtorAuthMethod->setFixedSize(250, 250);
	}


	return false;
}
