#pragma once
#include <QState>
#include <QVector>
#include <QMetaObject>

#include "UserRole.h"
class RoleSelectionScreen;

class RoleSelectionState :	public QState
{
	Q_OBJECT

public:
	RoleSelectionState(QState *parent=nullptr);
	~RoleSelectionState();
signals:
	void loginRequested();
	void signupRequested();
private:
	void connectSignals(RoleSelectionScreen* screen);
protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);
private:
	QVector<QMetaObject::Connection> m_connections;
};

