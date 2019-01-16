#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>

#include "Apartment.h"


class ApartmentViewer;
class QScrollArea;

class ApartmentViewersContainter : public QWidget
{
    Q_OBJECT

public:
	ApartmentViewersContainter(QWidget *parent = nullptr);
    ~ApartmentViewersContainter();
	void setApartmentsData(const QMap<int, Apartment>& clientsData);
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
	QVector<ApartmentViewer*> m_apartmentViewers;
	QMap<int, Apartment> m_apartmentsData;
    QScrollArea* m_area;
    QVBoxLayout* m_vLayout;
    bool m_isActive = true;
};
