#include "LoginScreen.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QEnterEvent>
#include <QBoxLayout>
#include <QMessageBox>

#include "Options.h"
#include "Controller.h"
#include "LoginResponse.h"
#include "LoginRequest.h"

static const QString styleBtnLog =
"QPushButton { font: bold 12px ; border: none; color: rgb(153, 153, 153) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 13px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(0, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}";

LoginScreen::LoginScreen(QWidget *parent):QWidget(parent)

{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}


LoginScreen::~LoginScreen()
{

}

void LoginScreen::updateForUserRole()
{
	UserRole currentUserRole = rentCtrl->getUserRole();
	UserRole storedUserRole = Options::getUserRole();
	switch (currentUserRole)
	{
	case  UserRole::eAdmin:
		m_icon->setText("<img src=:/images/admin><br>Login");
		break;
	case  UserRole::eClient:
		m_icon->setText("<img src=:/images/client><br>Login");
		break;
	case  UserRole::eRealtor:
		m_icon->setText("<img src=:/images/realtor><br>Login");
		break;
	}
	if (storedUserRole == currentUserRole) {
		m_username->setText(Options::getUserEmail());
		m_password->setText(Options::getUserKey());
		m_requestData.setIsKey(true);
	}
	else {
		m_username->setText("");
		m_password->setText("");
		m_requestData.setIsKey(false);

	}
}

void LoginScreen::createMembers()
{
	 m_login = new QPushButton("Login",this);
	 m_cancel = new QPushButton("Cancel",this);
	 m_username = new QLineEdit(this);
	 m_password = new QLineEdit(this);
	 m_widget = new QWidget(this);
	 m_icon = new QLabel(this);

}

void LoginScreen::setupMembers()
{
	m_username->setPlaceholderText("Username");
	m_password->setPlaceholderText("Password");
	m_password->setEchoMode(QLineEdit::Password);
	m_login->setStyleSheet(styleBtnLog);
	m_cancel->setStyleSheet(styleBtnLog);
	m_icon->setText("<img src=:/images/user><br>Login");
	m_icon->setStyleSheet(" background: transparent;  font: bold 15px; color: rgb(153,153,153);");
	m_icon->setAlignment(Qt::AlignCenter);
	m_widget->setStyleSheet("background-color: rgba(27,64,93,240); ");
	m_widget->setFixedSize(450, 600);
	m_widget->installEventFilter(this);
	m_username->setStyleSheet(
		"font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(255, 255, 255); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;"
	);
	m_password->setStyleSheet(
		"font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(255, 255, 255); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;"
	);
	m_username->setAlignment(Qt::AlignCenter);
	m_password->setAlignment(Qt::AlignCenter);

}

void LoginScreen::setupLayout()
{
	QHBoxLayout* hlay1 = new QHBoxLayout;

	{
		hlay1->addWidget(m_cancel);
		hlay1->addWidget(m_login);
	}

	QVBoxLayout* vlay = new QVBoxLayout;
	{
		vlay->addWidget(m_icon);
		vlay->addWidget(m_username);
		vlay->addWidget(m_password);
		vlay->addLayout(hlay1);
		vlay->setContentsMargins(90, 0, 90, 250);
		vlay->setSpacing(20);
	}
	m_widget->setLayout(vlay);

	QHBoxLayout* h = new QHBoxLayout;
	h->addWidget(m_widget);
	setLayout(h);

}

void LoginScreen::makeConnections()
{
	connect(m_cancel, &QPushButton::clicked, this, &LoginScreen::cancelRequested);
	connect(m_login, &QPushButton::clicked, [this]() {
		m_requestData.setEmail(m_username->text());
		m_requestData.setPassword(m_password->text());
		m_requestData.setUserRole(rentCtrl->getUserRole());
		emit loginRequested(m_requestData);
	});
	connect(m_password, &QLineEdit::textChanged, [this](QString) {
		m_requestData.setIsKey(false);
	});
	connect(m_username, &QLineEdit::textChanged, [this](QString) {
		m_requestData.setIsKey(false);
	});
}

bool LoginScreen::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == m_widget && event->type() == QEnterEvent::Enter) {
		m_widget->setStyleSheet(" background-color: rgba(27,47,70,240);");
	}

	if (watched == m_widget && event->type() == QEnterEvent::Leave) {
		m_widget->setStyleSheet(" background-color: rgba(27,64,93,240);");

	}
	return false;
}

void LoginScreen::onLoginResponseReady(const LoginResponse& data)
{
	if (data.isSucceeded()) {
		Options::setUserRole(data.getUserRole());
		Options::setUserKey(data.getKey());
		Options::setUserEmail(data.getEmail());
		Options::store();
		emit loginSuccess(data);
	}
	else {
		QMessageBox::critical(this, "Failure", "Login failed: " + data.getMessage());
	}
}