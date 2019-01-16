
#include "ApartmentViewer.h"
#include <QLabel>
#include <QLineEdit>
#include <QToolTip>
#include <QPushButton>
#include <QVBoxLayout>
#include <QEvent>
#include <QComboBox>
#include "Realtor.h"

static const QString btnStyle  =

"QPushButton { font: bold 12px ; border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(27,64,93), stop:1 rgb(127,164,193));}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(27,64,93), stop:1 rgb(0, 255, 255)); }"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(255, 255, 255) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgb(27,64,93), stop:1 rgb(127,164,193)); }";


static const QString labelSty = "background-color: transparent;  font: %1pt;  color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x2:0 y1:0, x1:1 y2:0,  stop:0 rgb(255, 255, 255), stop:1  rgb(27,64,93));"
"border-top: 0px;"
"border-right: 0px dotted rgb(27,64,93);"
"border-left: 0px;"
"QToolTip { color: rgb(0,0,0); background-color: rgb(255,255,255); border: 1px solid qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); }";
static const QString labelStyActive = "QLabel {background-color: transparent;  font: %1pt; color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x2:0 y1:0, x1:1 y2:0,  stop:0 rgb(255, 255, 255), stop:1  rgb(255,0,0));"
"border-top: 0px;"
"border-right: 0px dotted rgb(27,64,93);"
"border-left: 0px;}"
"QToolTip { color: rgb(0,0,0); background-color: rgb(255,255,255); border: 1px solid qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); }";

ApartmentViewer::ApartmentViewer(const Apartment& apartment, QWidget *parent)
    : QWidget(parent)

{
    createMembers();
    setupLayout();
    setupMembers();
    makeConnections();
    setApartment(apartment);
    setActive(false);
    setStyleSheet(labelSty.arg(QString::number(10)));
    setFixedWidth(300);

}

void ApartmentViewer::setApartment(const Apartment& apartment)
{
	m_apartment = apartment;

	m_infoLab->setText(m_apartment.getName());
	m_realtorName->addItem(QString("%1 %2").arg(apartment.getRealtor()->getFirstName(), apartment.getRealtor()->getLastName()));
    m_realtorName->setCurrentText(QString("%1 %2").arg(apartment.getRealtor()->getFirstName(),apartment.getRealtor()->getLastName()));

    m_isRented    ->setText(m_apartment.getRented() == true ? "Yes":"No" );
    m_name        ->setText(m_apartment.getName());
    m_description ->setText(m_apartment.getDescription());
    m_floorSize   ->setText(QString::number(m_apartment.getFloorSize()   ));
    m_price       ->setText(QString::number(m_apartment.getPrice()       ));
    m_roomsNum    ->setText(QString::number(m_apartment.getRoomsNum()    ));
    m_locLatitude ->setText(QString::number(m_apartment.getLocLatitude() ));
    m_locLongitude->setText(QString::number(m_apartment.getLocLongitude()));
    m_dateAdded   ->setText(m_apartment.getDateAdded().toString(Qt::ISODate));

    m_realtorName->setToolTip(QString("%1 %2").arg(apartment.getRealtor()->getFirstName(), apartment.getRealtor()->getLastName()));

    m_isRented    ->setToolTip(m_isRented    ->text());
    m_name        ->setToolTip(m_name        ->text());
    m_description ->setToolTip(m_description ->text());
    m_floorSize   ->setToolTip(m_floorSize   ->text());
    m_price       ->setToolTip(m_price       ->text());
    m_roomsNum    ->setToolTip(m_roomsNum    ->text());
    m_locLatitude ->setToolTip(m_locLatitude ->text());
    m_locLongitude->setToolTip(m_locLongitude->text());
    m_dateAdded   ->setToolTip(m_dateAdded   ->text());
}

void ApartmentViewer::setActive(bool isActive)
{
    m_widget->setVisible(isActive);
    if(isActive){
        m_widget->setStyleSheet(labelStyActive.arg(QString::number(10)));
        m_infoLab->setStyleSheet(labelStyActive.arg(QString::number(13)));

    }else{
        m_widget->setStyleSheet(labelSty.arg(QString::number(10)));
        m_infoLab->setStyleSheet(labelSty.arg(QString::number(13)));
    }
}

void ApartmentViewer::createMembers()
{
    m_infoLab = new QLabel(this);

    m_realtorName = new QComboBox(this);



   m_isRented    = new QLineEdit(this);
   m_name        = new QLineEdit(this);
   m_description = new QLineEdit(this);
   m_floorSize   = new QLineEdit(this);
   m_price       = new QLineEdit(this);
   m_roomsNum    = new QLineEdit(this);
   m_locLatitude = new QLineEdit(this);
   m_locLongitude= new QLineEdit(this);
   m_dateAdded   = new QLineEdit(this);


    m_updateBtn = new QPushButton("Update",this);
    m_removeBtn = new QPushButton("Remove",this);
    m_widget = new QWidget(this);

}

void ApartmentViewer::setupLayout()
{
    QVBoxLayout* vlay1  = new QVBoxLayout;
    {
        vlay1->addWidget(new QLabel("Realtor:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Rented:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Name:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Description:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Floor Size:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Price:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Rooms Num:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Latitude:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Longitude:"),0,Qt::AlignLeft);
        vlay1->addWidget(new QLabel("Date Added:"),0,Qt::AlignLeft);
    }

    QVBoxLayout* vlay2  = new QVBoxLayout;
    {
        vlay2->addWidget(m_realtorName,0,Qt::AlignLeft);

        vlay2->addWidget(m_isRented    ,0,Qt::AlignLeft);
        vlay2->addWidget(m_name        ,0,Qt::AlignLeft);
        vlay2->addWidget(m_description ,0,Qt::AlignLeft);
        vlay2->addWidget(m_floorSize   ,0,Qt::AlignLeft);
        vlay2->addWidget(m_price       ,0,Qt::AlignLeft);
        vlay2->addWidget(m_roomsNum    ,0,Qt::AlignLeft);
        vlay2->addWidget(m_locLatitude ,0,Qt::AlignLeft);
        vlay2->addWidget(m_locLongitude,0,Qt::AlignLeft);
        vlay2->addWidget(m_dateAdded   ,0,Qt::AlignLeft);

    }



    QHBoxLayout* hlay  = new QHBoxLayout;
    {
        hlay->addLayout(vlay1);
        hlay->addLayout(vlay2);
    }

    QHBoxLayout* hlay1  = new QHBoxLayout;
    {
        hlay1->addWidget(m_updateBtn);
        hlay1->addWidget(m_removeBtn);
    }

    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addLayout(hlay);
    vlay->addLayout(hlay1);

    m_widget->setLayout(vlay);

    QVBoxLayout* mainLay = new QVBoxLayout;
    mainLay->addWidget(m_infoLab);
    mainLay->addWidget(m_widget);
    mainLay->setSpacing(0);

    setLayout(mainLay);
}

void ApartmentViewer::setupMembers()
{
    m_updateBtn->setStyleSheet(btnStyle);
    m_removeBtn->setStyleSheet(btnStyle);
    m_updateBtn->setFixedSize(60,20);
    m_removeBtn->setFixedSize(60,20);
    m_realtorName->setFixedWidth(200);
    m_isRented    ->setFixedWidth(200);
    m_name        ->setFixedWidth(200);
    m_description ->setFixedWidth(200);
    m_floorSize   ->setFixedWidth(200);
    m_price       ->setFixedWidth(200);
    m_roomsNum    ->setFixedWidth(200);
    m_locLatitude ->setFixedWidth(200);
    m_locLongitude->setFixedWidth(200);
    m_dateAdded   ->setFixedWidth(200);

}

void ApartmentViewer::makeConnections()
{
  connect(m_removeBtn,SIGNAL(clicked()),this,SIGNAL(onRemove()));
  connect(m_updateBtn,SIGNAL(clicked()),this,SIGNAL(onUpdate()));
  connect(m_updateBtn,&QPushButton::clicked,[this](){/*
      m_tools.m_lastName = m_lastName->text();
      m_tools.m_firstName = m_firstName->text();
      m_tools.m_email = m_email->text();
      m_tools.m_isRented     =m_isRented    ->text().toStdString() == "Yes";
      m_tools.m_name         =m_name        ->text();
      m_tools.m_description  =m_description ->text();
      m_tools.m_floorSize    =m_floorSize   ->text().toInt();
      m_tools.m_price        =m_price       ->text().toFloat();
      m_tools.m_roomsNum     =m_roomsNum    ->text().toInt();
      m_tools.m_locLatitude  =m_locLatitude ->text().toDouble();
      m_tools.m_locLongitude =m_locLongitude->text().toDouble();
      m_tools.m_dateAdded    =m_dateAdded   ->text();
      m_lastName->setToolTip(m_lastName->text());
      m_firstName->setToolTip(m_firstName->text());
      m_email->setToolTip(m_email->text());
      m_isRented    ->setToolTip(m_isRented    ->text());
      m_name        ->setToolTip(m_name        ->text());
      m_description ->setToolTip(m_description ->text());
      m_floorSize   ->setToolTip(m_floorSize   ->text());
      m_price       ->setToolTip(m_price       ->text());
      m_roomsNum    ->setToolTip(m_roomsNum    ->text());
      m_locLatitude ->setToolTip(m_locLatitude ->text());
      m_locLongitude->setToolTip(m_locLongitude->text());
      m_dateAdded   ->setToolTip(m_dateAdded   ->text());
      m_infoLab->setText(m_tools.m_firstName +" "+m_tools.m_lastName);
      m_infoLab->setStyleSheet(labelStyActive.arg(QString::number(13)));*/
  });

}

Apartment ApartmentViewer::getApartment() const
{
    return m_apartment;
}
