#include "MessageBox.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "RentRoomEnum.h"


MessageBox::MessageBox(RentRoom::MessageType type, QWidget *parent) :
    QDialog(parent)
{

    setWindowFlags( Qt::FramelessWindowHint);
    //setWindowModality(Qt::ApplicationModal);
    setFixedSize(280,100);

    m_titleLabel =new QLabel(this);
    m_titleWidget = new QWidget(this);
    m_titleWidget->installEventFilter(this);
    m_titleWidget->setFixedSize(280,20);

    m_titleLabel->setPixmap(QPixmap(":/celseeTransp"));
    m_infoText = new QLabel(this);
    m_pushButtonYes = new QPushButton("Yes",this);
    m_pushButtonNo = new QPushButton("No",this);
    m_pushButtonNo->setFixedSize(60,20);
    m_pushButtonYes->setFixedSize(60,20);

    m_infoText->setStyleSheet("border:none; background-color: rgb(255,255,255);color: rgb(63,92,149);font:  11pt; ");

    if(type == RentRoom::eInfo){
        m_pushButtonNo->hide();
        m_pushButtonYes->setText("OK");

    }

    m_titleWidget->setStyleSheet("border:none; background-color: rgb(63,92,149);");

    m_pushButtonNo->setStyleSheet("QPushButton{border:none; background-color: rgb(63,92,149);color: rgb(255,255,255);font:  11pt;}"
                                  "QPushButton:hover{color: rgb(0,0,0);"
                                  "background-color: rgb(200,200,200); font-family: Lato Regular  ; font: bold 10pt; "
                                  "padding: 1px; border-style: solid; border: 2px solid rgb(90,90,90); border-radius: 5px;}"
                                  );
    m_pushButtonYes->setStyleSheet("QPushButton{border:none; background-color: rgb(63,92,149);color: rgb(255,255,255);font:  11pt;}"
                                  "QPushButton:hover{color: rgb(0,0,0);"
                                  "background-color: rgb(200,200,200); font-family: Lato Regular  ; font: bold 10pt; "
                                  "padding: 1px; border-style: solid; border: 2px solid rgb(90,90,90); border-radius: 5px;}"
                                  );

    QObject::connect(m_pushButtonYes,&QPushButton::clicked,[this](){
       this->accept();
    });

    QObject::connect(m_pushButtonNo,&QPushButton::clicked,[this](){
       this->reject();
    });


    QHBoxLayout* hlay = new QHBoxLayout;
    hlay->addWidget(m_titleLabel,0,Qt::AlignLeft);
    hlay->setContentsMargins(15,0,0,0);
    hlay->addStretch(1);
    m_titleWidget->setLayout(hlay);

    QWidget* wid = new QWidget(this);

    QHBoxLayout* hlay1 = new QHBoxLayout;
    hlay1->addWidget(m_infoText,0,Qt::AlignCenter);
   //hlay1->setContentsMargins(0,5,0,5);

    wid->setStyleSheet("border: 2px solid rgb(63,92,149); background-color: rgb(255,255,255);");

    QHBoxLayout* hlay2 = new QHBoxLayout;
    hlay2->addStretch(1);
    hlay2->addWidget(m_pushButtonYes,0,Qt::AlignRight);
    hlay2->addWidget(m_pushButtonNo,0,Qt::AlignRight);
    hlay2->setSpacing(10);
    hlay2->setContentsMargins(55,5,10,0);
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addLayout(hlay1);
    vl->addLayout(hlay2);
    wid->setLayout(vl);


    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(m_titleWidget);
    vlay->addWidget(wid);

    vlay->setSpacing(0);
    vlay->setContentsMargins(0,0,0,0);
    setLayout(vlay);
}

void MessageBox::setMessage(const QString &msg)
{
    m_infoText->setText(msg);
    m_infoText->setToolTip(msg);
}

void MessageBox::mousePressEvent(QMouseEvent *event)
{
    m_pressPos= event->pos();
    m_isMoving= true;
}

bool MessageBox::eventFilter(QObject *watch, QEvent *event)
{
    Q_UNUSED(event)
    if(watch == m_titleWidget){
        m_isMovinglab = true;
    }else{
        m_isMovinglab = false;
    }
    return false;
}

void MessageBox::keyPressEvent(QKeyEvent *event)
{

    if ( (event->key()==Qt::Key_Escape)) {
        hide();
    }
}

void MessageBox::mouseMoveEvent(QMouseEvent *event)
{

    if(m_isMoving && m_isMovinglab){

        QPoint diff= event->pos() - m_pressPos;
        move(window()->pos()+diff);
    }
}

void MessageBox::mouseReleaseEvent(QMouseEvent *)
{

}
