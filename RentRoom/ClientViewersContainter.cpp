#include "ClientViewersContainter.h"
#include "ClientViewer.h"

#include <QScrollArea>
#include <QEvent>

ClientViewersContainter::ClientViewersContainter(QWidget *parent)
	: QWidget(parent)
{
	setFixedWidth(350);
	m_vLayout = new QVBoxLayout;
	m_vLayout->addStretch();

	QWidget* widget = new QWidget(this);
	widget->setLayout(m_vLayout);
	widget->setFixedWidth(300);

	m_area = new QScrollArea(this);
	m_area->setWidgetResizable(true);
	m_area->setWidget(widget);
	m_area->setStyleSheet("border: none;");
	QVBoxLayout* vlay = new QVBoxLayout;
	vlay->addWidget(m_area);
	setLayout(vlay);
}

ClientViewersContainter::~ClientViewersContainter()
{

}

void ClientViewersContainter::setClientsData(const QMap<int, Client>& clientsData)
{
	m_clientsData = clientsData;

	for (auto client : m_clientsData) {
		ClientViewer* clientViewer = new ClientViewer(client, this);
		m_clientViewers.push_back(clientViewer);
		m_vLayout->insertWidget(0, m_clientViewers.back());
		clientViewer->installEventFilter(this);
		connect(clientViewer, &ClientViewer::updateClient, [this](const Client& client){});
		connect(clientViewer, &ClientViewer::removeClient, [this](const Client& client){});

	}

}


bool ClientViewersContainter::eventFilter(QObject *obj, QEvent *event)
{
	for (int i = 0; i < m_clientViewers.size(); ++i) {
		if (obj == m_clientViewers[i] && event->type() == QEvent::MouseButtonPress)
		{
			if (m_isActive) {
				m_clientViewers[i]->setActive(m_isActive);
				m_isActive = false;
			}
			else {
				m_clientViewers[i]->setActive(m_isActive);
				m_isActive = true;
			}
		}
	}
	return  false;
}
