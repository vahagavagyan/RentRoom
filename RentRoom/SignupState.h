#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

class SignupScreen;
class SignupRequest;

class SignupState :	public QState
{
	Q_OBJECT

public:
	SignupState(QState *parent=nullptr);
	~SignupState();
signals:
	void cancelRequested();
	void signupSuccess();
private slots:
	void onSignupRequested(const SignupRequest& data);
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
private:
	void connectSignals(SignupScreen* screen);
private:
	QVector<QMetaObject::Connection> m_connections;
};

