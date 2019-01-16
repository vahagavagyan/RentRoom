#include "TitleBar.h"
#include <QLabel>
#include <QToolButton>
#include <QBoxLayout>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "Controller.h"
#include "MainWindow.h"
TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	createMembers();
	setupUi();
	setupMembers();
	connectSignals();
	setObjectName("titleBar");
}

TitleBar::~TitleBar()
{
}

void TitleBar::createMembers()
{
	m_lblIcon = new QLabel;
	m_lblTitle = new QLabel;
	m_btnMinimize = new QToolButton;
	m_btnMaximize = new QToolButton;
	m_btnClose = new QToolButton;
}

void TitleBar::setupUi()
{
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(m_lblIcon, 0, Qt::AlignVCenter);
	hlay->addSpacing(5);
	hlay->addWidget(m_lblTitle, 0, Qt::AlignVCenter);
	hlay->addWidget(m_btnMinimize, 0, Qt::AlignVCenter);
	hlay->addWidget(m_btnMaximize, 0, Qt::AlignVCenter);
	hlay->addWidget(m_btnClose, 0, Qt::AlignVCenter);

	setLayout(hlay);
}

void TitleBar::setupMembers()
{
	const int h = m_lblTitle->fontMetrics().height() * 2;

	m_btnMinimize->setFixedSize(h, h);
	m_btnMaximize->setFixedSize(h, h);
	m_btnClose->setFixedSize(h, h);

	m_btnMinimize->setObjectName("minimizeButton");
	m_btnMaximize->setObjectName("maximizeButton");
	m_btnClose->setObjectName("closeButton");

	m_lblTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	m_lblTitle->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_lblTitle->setText(qApp->applicationName());
	m_lblIcon->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_lblIcon->setPixmap(qApp->windowIcon().pixmap(h, h));
}

void TitleBar::connectSignals()
{
	connect(m_btnMinimize, SIGNAL(clicked()), SLOT(onMinimizeClicked()));
	connect(m_btnMaximize, SIGNAL(clicked()), SLOT(onMaximizeClicked()));
	connect(m_btnClose, SIGNAL(clicked()), SLOT(onCloseClicked()));
}

void TitleBar::setIcon(const QPixmap icon)
{
	m_lblIcon->setPixmap(icon);
}

void TitleBar::setText(const QString title)
{
	m_lblTitle->setText(title);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
	m_clickPos = mapToParent(event->pos());
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
	Controller::inst()->getMainWnd()->move(event->globalPos() - m_clickPos);
}

void TitleBar::onMinimizeClicked()
{
	Controller::inst()->getMainWnd()->showMinimized();
}

void TitleBar::onMaximizeClicked()
{
}

void TitleBar::onCloseClicked()
{
	Controller::inst()->getMainWnd()->close();
}

void TitleBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}