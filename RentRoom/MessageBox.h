#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include <QEvent>
#include <QMouseEvent>

class QLabel;
class QPushButton;
#include "RentRoomEnum.h"

class MessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit MessageBox(RentRoom::MessageType type, QWidget *parent = nullptr);
    void setMessage(const QString& msg);

signals:

protected:
    void mousePressEvent(QMouseEvent* event);
    bool eventFilter(QObject *watch, QEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* /*event*/);

private:
      bool m_isMoving = false;
      bool m_isMovinglab = false;
      QPoint m_pressPos;
      QLabel* m_titleLabel;
      QLabel* m_infoText;
      QWidget* m_titleWidget;
      QPushButton* m_pushButtonYes;
      QPushButton* m_pushButtonNo;
};

#endif // MESSAGEBOX_H
