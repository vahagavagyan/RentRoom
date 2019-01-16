#include "AuthenticationMethodUIElement.h"

#include <QPushButton>
#include <QBoxLayout>
static const QString styleBtn =
"QPushButton { font: bold 12px ; border: none; color: rgb(153, 153, 153) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 13px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(0, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}";

AuthenticationMethodUIElement::AuthenticationMethodUIElement(QWidget *parent):QWidget(parent)
{
	m_login = new QPushButton("Login");
	m_signup = new QPushButton("Signup");
	m_signup->setStyleSheet(styleBtn);
	m_login->setStyleSheet(styleBtn);

	m_login->setBackgroundRole(QPalette::ColorRole::Dark);
	m_signup->setBackgroundRole(QPalette::ColorRole::Dark);
	QVBoxLayout *vlay = new QVBoxLayout;
	vlay->addWidget(m_login);
	vlay->addWidget(m_signup);
	setLayout(vlay);

	connect(m_login, &QPushButton::clicked, this, &AuthenticationMethodUIElement::loginRequested);
	connect(m_signup, &QPushButton::clicked, this, &AuthenticationMethodUIElement::signupRequested);
}


AuthenticationMethodUIElement::~AuthenticationMethodUIElement()
{
}

