#pragma once
#include <QWidget>

class QWebEngineView;
class QWebChannel;
class MapsBridge;
class MarkerData;

class MapsView :	public QWidget
{
	Q_OBJECT

public:
	MapsView(QWidget *parent=nullptr);
	~MapsView();
public slots:
	void onAddMarker(const MarkerData& data);
	void removeMarker(int id);
	void removeMarkers();
signals:
	void markerClicked(const MarkerData& data);
	void locationPicked(double latitude, double longitude);
private:
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();

private:
	QWebEngineView *m_webView;
	QWebChannel *m_webChannel;
	MapsBridge *m_mapBridge;
};

