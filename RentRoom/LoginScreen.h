#pragma once
#include <QWidget>
#include <QEvent>
#include "LoginRequest.h"

class QPushButton;
class QLineEdit;
class QLabel;

class LoginRequest;
class LoginResponse;

class LoginScreen :	public QWidget
{
	Q_OBJECT

public:
	LoginScreen(QWidget *parent=nullptr);
	~LoginScreen();
	void updateForUserRole();
public slots:
	void onLoginResponseReady(const LoginResponse& data);
signals:
	void cancelRequested();
	void loginRequested(const LoginRequest& data);
	void loginSuccess(const LoginResponse& data);
protected:
	bool eventFilter(QObject * watched, QEvent * event);

private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
private:
	QPushButton* m_login;
	QPushButton* m_cancel;
	QLineEdit * m_username;
	QLineEdit* m_password;
	QWidget* m_widget;
	QLabel* m_icon;
	LoginRequest m_requestData;

};

