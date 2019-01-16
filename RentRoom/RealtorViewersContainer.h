#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>

#include "Realtor.h"


class RealtorViewer;
class ApartmentViewer;
class QScrollArea;
class QEvent;

class RealtorViewersContainer : public QWidget
{
    Q_OBJECT

public:
	RealtorViewersContainer(QWidget *parent = nullptr);
    ~RealtorViewersContainer();
    void setRealtorsData(const QMap<int, Realtor>& clientsData);
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
    QVector<RealtorViewer*> m_realtorViewers;
	QMap<int, Realtor> m_realtorsData;

    QScrollArea* m_area;
    QVBoxLayout* m_vLayout;
    bool m_isActive = true;
};
