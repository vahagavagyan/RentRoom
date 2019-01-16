#pragma once

#include <QObject>
#include <QString>

class MarkerData;

class MapsBridge :	public QObject
{
	Q_OBJECT
public:
	MapsBridge(QObject  *parent=nullptr);
	~MapsBridge();
signals:
	void markerClicked(const MarkerData& data);
	void locationPicked(double lat, double lng);
public slots:
	void onMarkerClicked(QString idStr, QString latitudeStr, QString longitudeStr);
	void onLocationPick(QString lat, QString lng);
};

