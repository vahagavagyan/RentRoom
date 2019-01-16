#include "PowerToolMenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

#include "MessageBox.h"
#include "RentRoomEnum.h"


static const QString s_powerTools = "QPushButton{border: none; font-family:  Regular  ; font:  10pt; background-color: rgb(255,255,255); color: rgb(80,80,80);} "
                                    "QPushButton:hover{color: rgb(0,0,0);"
                                    "background-color: rgb(200,200,200); font-family: Lato Regular  ; font: bold 10pt; "
                                    "padding: 1px; border-style: solid; border: 2px solid rgb(90,90,90); border-radius: 5px;}";


PowerToolMenu::PowerToolMenu(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(52,107,157));
    setAutoFillBackground(true);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowModality(Qt::ApplicationModal);
    setPalette(pal);
    setFixedSize(110,30);
    m_logout  = new QPushButton("Sign Out",this);

    m_logout->setFixedSize(100,20);
 
    m_logout->setStyleSheet(s_powerTools);


	m_messageBox = new MessageBox(RentRoom::eWarning);
	m_messageBox->reject();

    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(m_logout);
    vlay->setContentsMargins(2,2,2,2);
    setLayout(vlay);

    QObject::connect(m_logout,&QPushButton::clicked,[this](){
		m_messageBox->setMessage("Are you sure");
        if(m_messageBox->exec() == QDialog::Accepted){
			emit logout();
		}
		else {
			hide();
		}
    });

}

