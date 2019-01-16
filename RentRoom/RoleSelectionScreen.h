#pragma once
#include <QWidget>
#include <QEvent>
#include "UserRole.h"
class QLabel;
class AuthenticationMethodUIElement;

class RoleSelectionScreen :	public QWidget
{
	Q_OBJECT

public:
	RoleSelectionScreen(QWidget *parent=nullptr);
	~RoleSelectionScreen();
signals:
	void loginRequested();
	void signupRequested();
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
private:
	QLabel *m_adminModeBtn;
	QLabel *m_clientModeBtn;
	QLabel *m_realtorModeBtn;


	QWidget* adminAuthMethod;
	QWidget* clientAuthMethod;
	QWidget* realtorAuthMethod;

	AuthenticationMethodUIElement *m_adminAuthMethod;
	AuthenticationMethodUIElement *m_clientAuthMethod;
	AuthenticationMethodUIElement *m_realtorAuthMethod;

	
};

