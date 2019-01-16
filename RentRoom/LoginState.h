#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

class LoginScreen;
class LoginRequest;
class LoginResponse;

class LoginState :	public QState
{
	Q_OBJECT
public:
	LoginState(QState *parent=nullptr);
	~LoginState();
public slots:
	void onLoginRequested(const LoginRequest& data);
	void onLoginSuccess(const LoginResponse& data);
signals:
	void cancelRequested();
	void adminLoginSuccess();
	void clientLoginSuccess();
	void realtorLoginSuccess();
private:
	void connectSignals(LoginScreen* screen);
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
private:
	QVector<QMetaObject::Connection> m_connections;
};

