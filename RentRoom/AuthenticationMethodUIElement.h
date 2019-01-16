#pragma once
#include <QWidget>
class QPushButton;

class AuthenticationMethodUIElement :	public QWidget
{
	Q_OBJECT

public:
	AuthenticationMethodUIElement(QWidget *parent=nullptr);
	~AuthenticationMethodUIElement();
signals:
	void loginRequested();
	void signupRequested();
private:
	QPushButton *m_signup;
	QPushButton *m_login;
};

