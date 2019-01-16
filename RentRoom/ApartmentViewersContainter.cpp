#include "ApartmentViewersContainter.h"
#include "ApartmentViewer.h"
#include <QScrollArea>
#include <QEvent>

ApartmentViewersContainter::ApartmentViewersContainter(QWidget *parent)
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

ApartmentViewersContainter::~ApartmentViewersContainter()
{

}

void ApartmentViewersContainter::setApartmentsData(const QMap<int, Apartment>& apartmentsData)
{
	m_apartmentsData = apartmentsData;

	for (auto apartment : m_apartmentsData) {
		ApartmentViewer* apartmentViewer = new ApartmentViewer(apartment, this);
		m_apartmentViewers.push_back(apartmentViewer);
		m_vLayout->insertWidget(0, m_apartmentViewers.back());
		apartmentViewer->installEventFilter(this);
		connect(apartmentViewer, &ApartmentViewer::removeApartment, [this](const Apartment& apartment) {

		});
		connect(apartmentViewer, &ApartmentViewer::updateApartment, [this](const Apartment& apartment) {

		});

	}
}

bool ApartmentViewersContainter::eventFilter(QObject *obj, QEvent *event)
{
	for (int i = 0; i < m_apartmentViewers.size(); ++i) {
		if (obj == m_apartmentViewers[i] && event->type() == QEvent::MouseButtonPress)
		{
			if (m_isActive) {
				m_apartmentViewers[i]->setActive(m_isActive);
				m_isActive = false;
			}
			else {
				m_apartmentViewers[i]->setActive(m_isActive);
				m_isActive = true;
			}
		}
	}
    return  false;
}
