#pragma once
#include <QWidget>
#include <QEvent>

class QPushButton;
class QLineEdit;
class QLabel;
class QVBoxLayout;

class SignupRequest;
class SignupResponse;

class SignupScreen : public QWidget
{
	Q_OBJECT

public:
	SignupScreen(QWidget *parent = nullptr);
	~SignupScreen();
public slots:
	void onSignupResponseReady(const SignupResponse& data);
signals:
	void  cancelRequested();
	void  signupSuccess();
	void  signupRequested(const SignupRequest& data);
protected:
	bool eventFilter(QObject * watched, QEvent * event);

private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
private:
	QWidget* m_widget;
	QLabel* m_icon;
	QPushButton* m_signup;
	QPushButton* m_cancel;
	QLineEdit * m_firstName;
	QLineEdit * m_lastName;
	QLineEdit * m_email;
	QLineEdit * m_password;
	QLineEdit * m_rPassword;


};

