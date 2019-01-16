#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

class ListAvailableApartmentsResponse;
class ListAvailableApartmentsRequest;
class RentRequest;
class RentResponse;

class ClientScreen;
class ClientState : public QState
{
	Q_OBJECT

public:
	ClientState(QState *parent=nullptr);
	~ClientState();
private:
	void connectSignals(ClientScreen *clientScreen);
public slots:
	void onListAvailableApartmetsReady(const ListAvailableApartmentsResponse& response);
	void onListAvailableApartmetsRequested(const ListAvailableApartmentsRequest& request);
	void onMakeListAvailableApartmetsRequest();
	void onRentRequested(const RentRequest& request);	
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
private:
	QVector<QMetaObject::Connection> m_connections;
};

