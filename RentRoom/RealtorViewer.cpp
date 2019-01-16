#include "RealtorViewer.h"
#include <QLabel>
#include <QLineEdit>
#include <QToolTip>
#include <QPushButton>
#include <QVBoxLayout>

static const QString btnStyle =

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

RealtorViewer::RealtorViewer(const Realtor& realtor, QWidget *parent)
	: QWidget(parent)
{
	createMembers();
	setupLayout();
	setupMembers();
	makeConnections();
	setRealtor(realtor);
	setActive(false);
	setStyleSheet(labelSty.arg(QString::number(10)));
	setFixedWidth(300);

}

void RealtorViewer::setRealtor(const Realtor& realtor)
{
	m_realtor = realtor;
	m_lastName->setText(m_realtor.getFirstName());
	m_firstName->setText(m_realtor.getFirstName());
	m_email->setText(m_realtor.getEmail());
	m_infoLab->setText(QString("%1 %2").arg(m_realtor.getFirstName(), m_realtor.getFirstName()));
	m_lastName->setToolTip(m_lastName->text());
	m_firstName->setToolTip(m_firstName->text());
	m_email->setToolTip(m_email->text());
}

void RealtorViewer::setActive(bool isActive)
{
	m_widget->setVisible(isActive);
	if (isActive) {
		m_widget->setStyleSheet(labelStyActive.arg(QString::number(10)));
		m_infoLab->setStyleSheet(labelStyActive.arg(QString::number(13)));

	}
	else {
		m_widget->setStyleSheet(labelSty.arg(QString::number(10)));
		m_infoLab->setStyleSheet(labelSty.arg(QString::number(13)));
	}
}

void RealtorViewer::createMembers()
{
	m_infoLab = new QLabel(this);

	m_lastName = new QLineEdit(this);
	m_firstName = new QLineEdit(this);
	m_email = new QLineEdit(this);
	m_update = new QPushButton("Update", this);
	m_remove = new QPushButton("Remove", this);
	m_widget = new QWidget(this);

}

void RealtorViewer::setupLayout()
{
	QVBoxLayout* vlay1 = new QVBoxLayout;
	{
		vlay1->addWidget(new QLabel("Last Name:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("First Name:"), 0, Qt::AlignLeft);
		vlay1->addWidget(new QLabel("Email:"), 0, Qt::AlignLeft);
	}

	QVBoxLayout* vlay2 = new QVBoxLayout;
	{
		vlay2->addWidget(m_lastName, 0, Qt::AlignLeft);
		vlay2->addWidget(m_firstName, 0, Qt::AlignLeft);
		vlay2->addWidget(m_email, 0, Qt::AlignLeft);
	}



	QHBoxLayout* hlay = new QHBoxLayout;
	{
		hlay->addLayout(vlay1);
		hlay->addLayout(vlay2);
	}

	QHBoxLayout* hlay1 = new QHBoxLayout;
	{
		hlay1->addWidget(m_update);
		hlay1->addWidget(m_remove);
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

void RealtorViewer::setupMembers()
{
	m_update->setStyleSheet(btnStyle);
	m_remove->setStyleSheet(btnStyle);
	m_update->setFixedSize(60, 20);
	m_remove->setFixedSize(60, 20);
	m_lastName->setFixedWidth(200);
	m_firstName->setFixedWidth(200);
	m_email->setFixedWidth(200);
}

void RealtorViewer::makeConnections()
{
	connect(m_remove, &QPushButton::clicked, [this]() {});
	connect(m_update, &QPushButton::clicked, [this]() {});

}