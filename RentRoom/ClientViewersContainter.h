#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>

#include "Client.h"


class ClientViewer;
class QScrollArea;

class ClientViewersContainter : public QWidget
{
    Q_OBJECT

public:
	ClientViewersContainter(QWidget *parent = nullptr);
    ~ClientViewersContainter();
    void setClientsData(const QMap<int, Client>& clientsData);
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private:
    QVector<ClientViewer*> m_clientViewers;
	QMap<int, Client> m_clientsData;

    QScrollArea* m_area;
    QVBoxLayout* m_vLayout;
    bool m_isActive = true;
};

#endif // WIDGET_H
