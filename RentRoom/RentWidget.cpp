#include "RentWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QPalette>
#include <QToolTip>

#include "Apartment.h"
#include "Realtor.h"

static const QString styleButton =

"QPushButton { font: bold 12px ; border: none; color: rgb(0, 0, 0) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); height: 25px; width: 150px;}"
"QPushButton:pressed {font: bold 12px ;border: none; color: rgb(0, 0, 0) ; border: 0px solid rgb(30, 112, 170); border-radius: 11px; background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(180, 255, 255)); height: 28px; width: 158px;}"
"QPushButton:hover:!pressed {font: bold 12px ;border: none; color: rgb(80, 80, 80) ; border: 0px solid rgb(30, 112, 170); border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0 x2:0, y1:1 y2:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); height: 25px; width: 150px;}";

static const QString labelStyle = " background-color: qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(255, 255, 255), stop:1  rgb(27,64,93));";
static const QString labelStyle1 = "QLabel {background-color: transparent;  font: 10pt; font-family: Times New Roman, Times, serif; color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgb(255, 255, 255), stop:1  rgb(27,64,93));"
"border-top: 0px;"
"border-right:  0px;"
"border-left: 0px;}"
"QToolTip { color: rgb(0,0,0); background-color: rgb(255,255,255); border: 1px solid qlineargradient(spread:pad, x2:0 x1:0, y2:1 y1:0, stop:0 rgb(149,202,255), stop:1 rgb(255, 255, 255)); }";

static const QString labelStyle2 = "background-color: transparent;  font: 10pt; font-family: Times New Roman, Times, serif; color: rgb(27,64,93);"
"border-bottom: 1px solid qlineargradient(spread:pad, x2:0 y1:0, x1:1 y2:0,  stop:0 rgb(255, 255, 255), stop:1  rgb(27,64,93));"
"border-top: 0px;"
"border-right: 1px dotted rgb(27,64,93);"
"border-left: 0px;";


RentWidget::RentWidget(QWidget *parent)
{
	createMembers();
	setupMembers();
	setupLayout();
	makeConnections();
}


RentWidget::~RentWidget()
{
}

const Apartment& RentWidget::getApartment()const {
	return m_apartment;
}

void RentWidget::setApartment(const Apartment& apartment)
{
	m_apartment = apartment;
	updateViews();
}

void RentWidget::updateViews()
{
	m_name->setText(m_apartment.getName());
	m_name->setToolTip(m_apartment.getName());

	m_description->setText(m_apartment.getDescription());
	m_description->setToolTip(m_apartment.getDescription());

	m_floorSize->setText(QString::number(m_apartment.getFloorSize()));
	m_floorSize->setToolTip(QString::number(m_apartment.getFloorSize()));

	m_price->setText(QString::number(m_apartment.getPrice()));
	m_price->setToolTip(QString::number(m_apartment.getPrice()));

	m_roomsNum->setText(QString::number(m_apartment.getRoomsNum()));
	m_roomsNum->setToolTip(QString::number(m_apartment.getRoomsNum()));

	m_dateAdded->setText(m_apartment.getDateAdded().toString(Qt::LocaleDate));
	m_dateAdded->setToolTip(m_apartment.getDateAdded().toString(Qt::LocaleDate));

	m_realtorEmail->setText(  m_apartment.getRealtor()->getEmail());
	m_realtorEmail->setToolTip(m_apartment.getRealtor()->getEmail());

	m_realtorFirstName->setText( m_apartment.getRealtor()->getFirstName());
	m_realtorFirstName->setToolTip(m_apartment.getRealtor()->getFirstName());

	m_realtorLastName->setText(m_apartment.getRealtor()->getLastName());
	m_realtorLastName->setToolTip(m_apartment.getRealtor()->getLastName());

}

void RentWidget::createMembers()
{
	m_nameLbl = new QLabel;
	m_descriptionLbl = new QLabel;
	m_floorSizeLbl = new QLabel;
	m_priceLbl = new QLabel;
	m_roomsNumLbl = new QLabel;
	m_dateAddedLbl = new QLabel;
	m_name = new QLabel;
	m_description = new QLabel;
	m_floorSize = new QLabel;
	m_price = new QLabel;
	m_roomsNum = new QLabel;
	m_dateAdded = new QLabel;

	m_realtorEmailLbl      = new QLabel;
	m_realtorFirstNamelLbl = new QLabel;
	m_realtorLastNamelLbl  = new QLabel;

	m_realtorEmail = new QLabel;
	m_realtorFirstName = new QLabel;
	m_realtorLastName = new QLabel;

	m_rentBtn = new QPushButton;

}

void RentWidget::setupMembers()
{

	m_nameLbl->setText("Name:");
	m_descriptionLbl->setText("Description:");
	m_floorSizeLbl->setText("Floor Size:");
	m_priceLbl->setText("Price:");
	m_roomsNumLbl->setText("Rooms:");
	m_dateAddedLbl->setText("Date Added:");
	m_realtorEmailLbl->setText("Email:");
    m_realtorFirstNamelLbl->setText("First Name:");
    m_realtorLastNamelLbl->setText("Last Name:");

	m_rentBtn->setText("Rent");
	m_rentBtn->setStyleSheet(styleButton);

	m_nameLbl			   ->setStyleSheet(labelStyle2); 
	m_descriptionLbl	   ->setStyleSheet(labelStyle2);
	m_floorSizeLbl		   ->setStyleSheet(labelStyle2);
	m_priceLbl			   ->setStyleSheet(labelStyle2);
	m_roomsNumLbl		   ->setStyleSheet(labelStyle2);
	m_dateAddedLbl		   ->setStyleSheet(labelStyle2);
	m_realtorEmailLbl	   ->setStyleSheet(labelStyle2);
	m_realtorFirstNamelLbl ->setStyleSheet(labelStyle2);
	m_realtorLastNamelLbl  ->setStyleSheet(labelStyle2);
	m_nameLbl              ->setFixedSize(90, 25);
	m_descriptionLbl	   ->setFixedSize(90, 25);
	m_floorSizeLbl		   ->setFixedSize(90, 25);
	m_priceLbl			   ->setFixedSize(90, 25);
	m_roomsNumLbl		   ->setFixedSize(90, 25);
	m_dateAddedLbl		   ->setFixedSize(90, 25);
	m_realtorEmailLbl	   ->setFixedSize(90, 25);
	m_realtorFirstNamelLbl ->setFixedSize(90, 25);
	m_realtorLastNamelLbl  ->setFixedSize(90, 25);


	m_name->setFixedSize(150, 25);
	m_description->setFixedSize(150, 25);
	m_floorSize->setFixedSize(150, 25);
	m_price->setFixedSize(150, 25);
	m_roomsNum->setFixedSize(150, 25);
	m_dateAdded->setFixedSize(150, 25);
	m_realtorEmail->setFixedSize(150, 25);
	m_realtorFirstName->setFixedSize(150, 25);
	m_realtorLastName->setFixedSize(150, 25);


   m_name		            ->setStyleSheet(labelStyle1);
   m_description			->setStyleSheet(labelStyle1);
   m_floorSize				->setStyleSheet(labelStyle1);
   m_price					->setStyleSheet(labelStyle1);
   m_roomsNum	    		->setStyleSheet(labelStyle1);
   m_dateAdded				->setStyleSheet(labelStyle1);
   m_realtorEmail			->setStyleSheet(labelStyle1);
   m_realtorFirstName		->setStyleSheet(labelStyle1);
   m_realtorLastName 		->setStyleSheet(labelStyle1);

}

void RentWidget::setupLayout()
{


	QWidget* widget = new QWidget(this);
	widget->setStyleSheet(labelStyle);

	QHBoxLayout* hlay = new QHBoxLayout;
	{
		QVBoxLayout* vlay1 = new QVBoxLayout;
		{

			vlay1->addWidget(m_nameLbl			    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_descriptionLbl	    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_floorSizeLbl		    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_priceLbl			    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_roomsNumLbl		    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_dateAddedLbl		    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_realtorEmailLbl	    ,0,Qt::AlignLeft);
			vlay1->addWidget(m_realtorFirstNamelLbl ,0,Qt::AlignLeft);
			vlay1->addWidget(m_realtorLastNamelLbl  ,0,Qt::AlignLeft);
		}
		vlay1->addStretch(1);
		vlay1->setSpacing(0);
		QVBoxLayout* vlay2 = new QVBoxLayout;
		{
			vlay2->addWidget(m_name,			 0, Qt::AlignLeft);
			vlay2->addWidget(m_description,		 0, Qt::AlignLeft);
			vlay2->addWidget(m_floorSize,		 0, Qt::AlignLeft);
			vlay2->addWidget(m_price,			 0, Qt::AlignLeft);
			vlay2->addWidget(m_roomsNum,	     0, Qt::AlignLeft);
			vlay2->addWidget(m_dateAdded,		 0, Qt::AlignLeft);
			vlay2->addWidget(m_realtorEmail,	 0, Qt::AlignLeft);
			vlay2->addWidget(m_realtorFirstName ,0, Qt::AlignLeft);
			vlay2->addWidget(m_realtorLastName  ,0, Qt::AlignLeft);
		}
		vlay2->addStretch(1);
		vlay2->setSpacing(0);
		hlay->addStretch(1);
		hlay->addLayout(vlay1);
		hlay->addLayout(vlay2);
		hlay->addStretch(1);

		hlay->setSpacing(0);
		hlay->setContentsMargins(5, 0, 5, 0);
	}
	QVBoxLayout* vla = new QVBoxLayout;
	vla->addLayout(hlay);
	vla->setSpacing(15);
	vla->addWidget(m_rentBtn, 0, Qt::AlignCenter);
	vla->addStretch(10);

	widget->setLayout(vla);
	
	QVBoxLayout* vl = new QVBoxLayout;
	vl->addWidget(widget);

	setLayout(vl);
}

void RentWidget::makeConnections()
{
	connect(m_rentBtn, &QPushButton::clicked, this, &RentWidget::rentClicked);
}
