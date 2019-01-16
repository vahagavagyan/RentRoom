#pragma once

#include <QWidget>
#include <QMap>

#include "Apartment.h"
class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

class ApartmentViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ApartmentViewer(const Apartment& apartment, QWidget *parent = nullptr);
    void setApartment(const Apartment& apartment);
    void setActive(bool isActive);
    Apartment getApartment()const;

signals:
    void removeApartment(const Apartment& apartment);
    void updateApartment(const Apartment& apartment);
private:
    void createMembers();
    void setupLayout();
    void setupMembers();
    void makeConnections();

private:
    QLabel* m_infoLab;
	QComboBox* m_realtorName;

    QLineEdit* m_isRented;
    QLineEdit* m_name;
    QLineEdit* m_description;
    QLineEdit* m_floorSize;
    QLineEdit* m_price;
    QLineEdit* m_roomsNum;
    QLineEdit* m_locLatitude;
    QLineEdit* m_locLongitude;
    QLineEdit* m_dateAdded;


    QPushButton* m_updateBtn;
    QPushButton* m_removeBtn;

    Apartment m_apartment;

    QWidget* m_widget;
};
