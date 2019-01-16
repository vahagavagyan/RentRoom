#include "SideMenu.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "PowerToolMenu.h"
#include "ClientViewersContainter.h"
#include "RealtorViewersContainer.h"
#include "ApartmentViewersContainter.h"

static const QString styleMenu =

"QPushButton { font: bold 12px ; border: none; color: rgb(153, 153, 153) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 11px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(0, 255, 255,80)); height: 28px; width: 158px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}";

static const QString styleActiveMenu =

"QPushButton { font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 11px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgba(27,64,93,180), stop:1 rgba(0, 255, 255,80)); height: 28px; width: 158px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgba(27,64,93,180), stop:1 rgba(255, 255, 255,80)); height: 25px; width: 150px;}";

SideMenu::SideMenu(QWidget* parent) : QWidget(parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
	m_powerToolMenu->move(m_signout->pos().x() + 90, 950);

}


SideMenu::~SideMenu()
{
}

void SideMenu::setClients(const QMap<int, Client>& clientsData)
{
	m_clientsData = clientsData;
	m_clientsViewerContainter->setClientsData(m_clientsData);
}

void SideMenu::setApartments(const QMap<int, Apartment>& apartmentsData)
{
	m_apartmentsData = apartmentsData;
	m_apartmentsViewerContainer->setApartmentsData(m_apartmentsData);
}

void SideMenu::setRealtors(const QMap<int, Realtor>& realtorsData)
{
	m_realtorsViewerContainer->setRealtorsData(realtorsData);
}

void SideMenu::createMembers()
{
	m_signout = new QPushButton("Sign Out", this);
	m_clients = new QPushButton("Clients", this);
	m_apartments = new QPushButton("Apartments", this);
	m_realtors = new QPushButton("Realtors", this);
	m_signout->setStyleSheet(styleMenu);
	m_clients->setStyleSheet(styleMenu);
	m_apartments->setStyleSheet(styleActiveMenu);
	m_realtors->setStyleSheet(styleMenu);
	m_powerToolMenu = new PowerToolMenu;
	m_powerToolMenu->hide();
	m_clientsViewerContainter = new ClientViewersContainter(this);
	m_realtorsViewerContainer = new RealtorViewersContainer(this);
	m_apartmentsViewerContainer = new ApartmentViewersContainter(this);


	m_stackLayout = new QStackedLayout();


}

void SideMenu::setupMembers()
{
	m_clientsViewerContainter->hide();
	m_realtorsViewerContainer->hide();
	m_apartmentsViewerContainer->hide();

}

void SideMenu::setupLayout()
{
	QVBoxLayout* vlay = new QVBoxLayout;

	{
		vlay->addWidget(m_clients, Qt::AlignCenter);
		vlay->addWidget(m_realtors, Qt::AlignCenter);
		vlay->addWidget(m_apartments, Qt::AlignCenter);
		vlay->addStretch(1);
		vlay->addWidget(m_signout, Qt::AlignCenter);
		vlay->setContentsMargins(10, 20, 10, 20);
	}

	QWidget* widget = new QWidget(this);
	widget->setLayout(vlay);
	widget->setFixedWidth(100);
	widget->setStyleSheet("background: rgb(21,95,188);");

	QHBoxLayout* hlay = new QHBoxLayout;

	{
		hlay->addWidget(widget);
		m_stackLayout->addWidget(m_apartmentsViewerContainer);
		m_stackLayout->addWidget(m_clientsViewerContainter);
		m_stackLayout->addWidget(m_realtorsViewerContainer);
		hlay->addLayout(m_stackLayout);
	}
	hlay->setContentsMargins(0, 0, 0, 0);
	setLayout(hlay);
}

void SideMenu::makeConnections()
{
	QObject::connect(m_apartments, &QPushButton::clicked, [this]() {
		m_stackLayout->setCurrentIndex(0);
		this->m_apartments->setStyleSheet(styleActiveMenu);
		this->m_clients->setStyleSheet(styleMenu);
		this->m_realtors->setStyleSheet(styleMenu);
	});

	QObject::connect(m_clients, &QPushButton::clicked, [this]() {
		m_stackLayout->setCurrentIndex(1);
		this->m_apartments->setStyleSheet(styleMenu);
		this->m_clients->setStyleSheet(styleActiveMenu);
		this->m_realtors->setStyleSheet(styleMenu);
	});


	QObject::connect(m_realtors, &QPushButton::clicked, [this]() {
		m_stackLayout->setCurrentIndex(2);
		this->m_apartments->setStyleSheet(styleMenu);
		this->m_clients->setStyleSheet(styleMenu);
		this->m_realtors->setStyleSheet(styleActiveMenu);
	});
	QObject::connect(m_signout, &QPushButton::clicked, [this]() {
		m_powerToolMenu->show();
	});
}
