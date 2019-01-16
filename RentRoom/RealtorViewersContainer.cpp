#include "RealtorViewersContainer.h"
#include "RealtorViewer.h"
#include <QScrollArea>
#include <QEvent>

RealtorViewersContainer::RealtorViewersContainer(QWidget *parent)
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

RealtorViewersContainer::~RealtorViewersContainer()
{

}

void RealtorViewersContainer::setRealtorsData(const QMap<int, Realtor>& realtorsData)
{
	m_realtorsData = realtorsData;

	for (auto realtor : m_realtorsData) {
		RealtorViewer* realtorViewer = new RealtorViewer(realtor, this);
		m_realtorViewers.push_back(realtorViewer);
		m_vLayout->insertWidget(0, m_realtorViewers.back());
		realtorViewer->installEventFilter(this);
		connect(realtorViewer, &RealtorViewer::removeRealtor, [this](const Realtor& realtor) {});
		connect(realtorViewer, &RealtorViewer::updateRealtor, [this](const Realtor& realtor) {});

    }

}

bool RealtorViewersContainer::eventFilter(QObject *obj, QEvent *event)
{
    for (int i = 0; i < m_realtorViewers.size(); ++i) {
        if (obj == m_realtorViewers[i] && event->type() == QEvent::MouseButtonPress)
        {
            if(m_isActive){
				m_realtorViewers[i]->setActive(m_isActive);
                m_isActive = false;
            }else{
				m_realtorViewers[i]->setActive(m_isActive);
                m_isActive = true;

            }
        }
    }
    return  false;
}