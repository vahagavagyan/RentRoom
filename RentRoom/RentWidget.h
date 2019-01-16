#pragma once
#include <QWidget>
#include "Apartment.h"

class QLabel;
class QPushButton;

class RentWidget :	public QWidget
{
	Q_OBJECT
public:
	RentWidget(QWidget *parent=nullptr);
	~RentWidget();
	void setApartment(const Apartment& apartment);
	const Apartment& getApartment()const;
private:
	void updateViews();
	void createMembers();
	void setupMembers();
	void setupLayout();
	void makeConnections();
signals:
	void rentClicked();
private:
	Apartment m_apartment;
	QLabel *m_nameLbl;
	QLabel *m_descriptionLbl;
	QLabel *m_floorSizeLbl;
	QLabel *m_priceLbl;
	QLabel *m_roomsNumLbl;
	QLabel *m_dateAddedLbl;
	QLabel *m_realtorEmailLbl;
	QLabel *m_realtorFirstNamelLbl;
	QLabel *m_realtorLastNamelLbl;

	QLabel *m_name;
	QLabel *m_description;
	QLabel *m_floorSize;
	QLabel *m_price;
	QLabel *m_roomsNum;
	QLabel *m_dateAdded;
	QLabel *m_realtorEmail;
	QLabel *m_realtorFirstName;
	QLabel *m_realtorLastName;

	QPushButton *m_rentBtn;
};

