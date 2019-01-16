#pragma once

#include <QMainWindow>
#include <QImage>
#include <QColor>

class QStackedLayout;
class QScrollArea;
class QPaintEvent;

class RoleSelectionScreen;
class LoginScreen;
class TitleBar;
class SignupScreen;
class ClientScreen;
class RealtorScreen;
class AdminScreen;

enum ScreenType {
	ST_RoleSelector = 0,
	ST_SignupScreen,
	ST_Login,
	ST_ClientScreen,
	ST_RealtorScreen,
	ST_AdminScreen,
	ST_MaxScreens
};


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	QWidget* getScreen(ScreenType screen)const;
	void setBackground(const QImage& img);
	void setCurrentScreen(const ScreenType screen);
private:
	TitleBar *m_titleBar;
	QStackedLayout *m_layout;
	QScrollArea *m_mainArea;
	RoleSelectionScreen *m_roleScreen;
	LoginScreen *m_loginScreen;
	SignupScreen *m_signupScreen;
	ClientScreen *m_clientScreen;
	RealtorScreen *m_realtorScreen;
	AdminScreen *m_adminScreen;

	QImage m_backImage;
	QColor m_backColor;


	void createMembers();
	void setupLayout();
	void setupMembers();
	void connectSignals();
	void addScreens();
	void setStyles();
	void paintEvent(QPaintEvent *event);

};
