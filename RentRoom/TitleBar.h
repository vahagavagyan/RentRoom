#pragma once
#include <QWidget>

class QLabel;
class QToolButton;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent = 0);
	~TitleBar();

public slots:
	void setIcon(const QPixmap icon);
	void setText(const QString title);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

private slots:
	void onMinimizeClicked();
	void onMaximizeClicked();
	void onCloseClicked();

private:
	QLabel *m_lblIcon;
	QLabel *m_lblTitle;
	QToolButton *m_btnMinimize;
	QToolButton *m_btnMaximize;
	QToolButton *m_btnClose;

	QPoint m_clickPos;

	void createMembers();
	void setupUi();
	void setupMembers();
	void connectSignals();
};