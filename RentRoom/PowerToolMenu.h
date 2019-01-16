#pragma once

#include <QWidget>
class QPushButton;
class MessageBox;

class PowerToolMenu:public QWidget
{
    Q_OBJECT
public:
    PowerToolMenu(QWidget *parent = nullptr);
signals:
   void logout();

private:
    QPushButton* m_logout;
    MessageBox * m_messageBox;

};

