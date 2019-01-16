#include "SignupScreen.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QEnterEvent>
#include <QMessageBox>

#include "SignupRequest.h"
#include "SignupResponse.h"

#include "Controller.h"

static const QString styleBtnSignup =
"QPushButton { font: bold 12px ; border: none; color: rgb(153, 153, 153) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 13px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(0, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}";

static const QString editStyle = "font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 1px solid rgb(255, 255, 255); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;";

SignupScreen::SignupScreen(QWidget *parent) :QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}


SignupScreen::~SignupScreen()
{
}

void SignupScreen::createMembers()
{
	m_widget = new QWidget(this);

	m_icon = new QLabel(this);
	m_signup = new QPushButton("Create", this);
	m_cancel = new QPushButton("Cancel", this);
	m_firstName = new QLineEdit(this);
	m_lastName = new QLineEdit(this);
	m_email = new QLineEdit(this);
	m_password = new QLineEdit(this);
	m_rPassword = new QLineEdit(this);
}

void SignupScreen::setupMembers()
{
	m_widget->setStyleSheet("background-color: rgba(27,64,93,240); ");
	m_widget->setFixedSize(450, 600);
	m_widget->installEventFilter(this);

	m_icon->setText("<img src=:/images/user><br>SignUp");
	m_icon->setStyleSheet(" background: transparent;  font: bold 15px; color: rgb(153,153,153);");
	m_icon->setAlignment(Qt::AlignCenter);

	m_firstName->setPlaceholderText("First Name:");
	m_lastName->setPlaceholderText("Last Name:");
	m_email->setPlaceholderText("Email address:");
	m_password->setPlaceholderText("Password:");
	m_rPassword->setPlaceholderText("Re-enter Password:");
	m_password->setEchoMode(QLineEdit::Password);
	m_rPassword->setEchoMode(QLineEdit::Password);


	m_firstName->setStyleSheet(editStyle);
	m_lastName->setStyleSheet(editStyle);
	m_email->setStyleSheet(editStyle);
	m_password->setStyleSheet(editStyle);
	m_rPassword->setStyleSheet(editStyle);

	m_signup->setStyleSheet(styleBtnSignup);
	m_cancel->setStyleSheet(styleBtnSignup);


}

void SignupScreen::setupLayout()
{
	QHBoxLayout* hlay1 = new QHBoxLayout;

	{
		hlay1->addWidget(m_cancel);
		hlay1->addWidget(m_signup);
	}

	QVBoxLayout* vlay = new QVBoxLayout;
	{
		vlay->addWidget(m_icon);
		vlay->addWidget(m_firstName);
		vlay->addWidget(m_lastName);
		vlay->addWidget(m_email);
		vlay->addWidget(m_password);
		vlay->addWidget(m_rPassword);

		vlay->addLayout(hlay1);
		vlay->setContentsMargins(90, 0, 90, 150);
		vlay->setSpacing(20);
	}
	m_widget->setLayout(vlay);

	QHBoxLayout* h = new QHBoxLayout;
	h->addWidget(m_widget);
	setLayout(h);

}

void SignupScreen::makeConnections()
{
	connect(m_cancel, &QPushButton::clicked, this, &SignupScreen::cancelRequested);
	connect(m_signup, &QPushButton::clicked, [this]() {

		SignupRequest data;
		data.setEmail(m_email->text());
		data.setFirstName(m_firstName->text());
		data.setLastName(m_lastName->text());
		data.setPassword(m_password->text());
		data.setUserRole(rentCtrl->getUserRole());
		emit signupRequested(data);

	});
}
bool SignupScreen::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == m_widget && event->type() == QEnterEvent::Enter) {
		m_widget->setStyleSheet(" background-color: rgba(27,47,70,240);");
		//m_widget->setFixedSize(500, 600);
	}

	if (watched == m_widget && event->type() == QEnterEvent::Leave) {
		m_widget->setStyleSheet(" background-color: rgba(27,64,93,240);");
		//m_widget->setFixedSize(450, 550);

	}
	return false;
}

void SignupScreen::onSignupResponseReady(const SignupResponse& data)
{
	if (data.isSucceeded()) {
		QMessageBox::information(this, "Success", "Your account successfully registered!", QMessageBox::Ok);
		emit signupSuccess();

	}
	else {
		QMessageBox::critical(this, "Failure", "Error during registration: " + data.getMessage(), QMessageBox::Ok);
	}

}