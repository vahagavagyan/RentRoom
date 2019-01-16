#include "MainWindow.h"
#include <QStackedLayout>
#include <QScrollArea>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>

#include "TitleBar.h"
#include "RoleSelectionScreen.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "ClientScreen.h"
#include "AdminScreen.h"
#include "RealtorScreen.h"


#define DARK_BOTTOM_LINE_HEIGHT 66

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setCentralWidget(new QWidget);
	setStyles();
	createMembers();
	setupLayout();
	setupMembers();
	connectSignals();
	setWindowFlags(Qt::FramelessWindowHint);
	setAutoFillBackground(true);
}

QWidget *MainWindow::getScreen(const ScreenType type)const
{
	const bool correctType = (type >= 0) && (type < m_layout->count());
	if (correctType)
	{
		return m_layout->widget(type);
	}
	else
	{
		return nullptr;
	}
}

void MainWindow::createMembers()
{
	m_titleBar = new TitleBar(this);
	m_layout = new QStackedLayout();
	m_mainArea = new QScrollArea(this);
	m_roleScreen = new RoleSelectionScreen(this);
	m_loginScreen = new LoginScreen(this);
	m_signupScreen = new SignupScreen(this);
	m_clientScreen = new ClientScreen(this);
	m_adminScreen = new AdminScreen(this);
	m_realtorScreen = new RealtorScreen(this);
}

void MainWindow::setupLayout()
{
	m_mainArea->setLayout(m_layout);

	QVBoxLayout *vlayCenter = new QVBoxLayout();
	vlayCenter->setMargin(0);
	vlayCenter->setContentsMargins(0, 0, 0, 0);
	vlayCenter->addWidget(m_mainArea);

	QVBoxLayout *vlayGlobal = new QVBoxLayout();
	vlayGlobal->setMargin(0);
	vlayGlobal->setContentsMargins(0, 0, 0, 0);
	vlayGlobal->addWidget(m_titleBar);
	vlayGlobal->addLayout(vlayCenter);
	centralWidget()->setLayout(vlayGlobal);
}

void MainWindow::setupMembers()
{
	m_mainArea->setObjectName("mainScrollArea");
	m_mainArea->setFocusPolicy(Qt::NoFocus);
	addScreens();
}
void MainWindow::addScreens()
{
	for (int i = ST_RoleSelector; i < ST_MaxScreens; ++i)
	{
		const ScreenType type = (ScreenType)i;
		switch (type)
		{
		case ST_RoleSelector:
			m_layout->addWidget(m_roleScreen);
			break;
		case ST_SignupScreen:
			m_layout->addWidget(m_signupScreen);
			break;
		case ST_Login:
			m_layout->addWidget(m_loginScreen);
			break;
		case ST_ClientScreen:
			m_layout->addWidget(m_clientScreen);
			break;
		case ST_RealtorScreen:
			m_layout->addWidget(m_realtorScreen);
			break;
		case ST_AdminScreen:
			m_layout->addWidget(m_adminScreen);
			break;
		}
	}
}
void MainWindow::setCurrentScreen(const ScreenType screen)
{
	qDebug() << "setCurrentScreen" << screen;
	m_layout->setCurrentIndex(screen);
}

void MainWindow::connectSignals()
{
}


void MainWindow::setStyles()
{
	setStyleSheet(QString() +
		"#mainScrollArea {"
		"background-color: transparent;"
		"border: none;"
		"}"
		"#titleBar {"
		"background-color: rgba(0,0,0,70%);"
		"}"

		"#titleBar QLabel {"
		"font: 18pt;"
		"font-weight: bold;"
		"color: rgb(220,220,220);"
		"}"

		"#minimizeButton {"
		"border-image: url(:/images/minimize);"
		"}"

		"#maximizeButton {"
		"border-image: url(:/images/maximize);"
		"}"

		"#closeButton {"
		"border-image: url(:/images/close);"
		"}"
	);
}
void MainWindow::setBackground(const QImage& img)
{
	m_backImage = img;
	update();
}
void MainWindow::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	if (m_backImage.isNull())
	{
		p.fillRect(rect(), m_backColor);
	}
	else
	{
		p.drawImage(rect(), m_backImage);
	}

	const QRect darkLine(
		QPoint(0, height() - DARK_BOTTOM_LINE_HEIGHT),
		QSize(width(), DARK_BOTTOM_LINE_HEIGHT));
	p.fillRect(darkLine, QColor(0, 0, 0, 100));
}
