#pragma once
#include <QString>
#include <QDate>
#include <memory>
#include <memory>
class Realtor;

class Apartment
{
public:
	int getId() const;
	void setId(int val);

	QString getName() const;
	void setName(QString val);

	QString getDescription() const;
	void setDescription(QString val);

	int getFloorSize() const;
	void setFloorSize(int val);

	float getPrice() const;
	void setPrice(float val);

	int getRoomsNum() const;
	void setRoomsNum(int val);

	double getLocLatitude() const;
	void setLocLatitude(double val);

	double getLocLongitude() const;
	void setLocLongitude(double val);

	QDate getDateAdded() const;
	void setDateAdded(const QDate& val);

	std::shared_ptr<Realtor> getRealtor() const;
	void setRealtor(std::shared_ptr<Realtor> val);

	bool getRented() const;
	void setRented(bool val);
private:
	int id;
	bool m_isRented;
	QString m_name;
	QString m_description;
	int m_floorSize;
	float m_price;
	int m_roomsNum;
	double m_locLatitude;
	double m_locLongitude;
	QDate m_dateAdded;
	std::shared_ptr<Realtor> m_realtor=nullptr;
};

