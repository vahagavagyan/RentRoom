#pragma once

#include <QWidget>
#include "Client.h"

class QLabel;
class QPushButton;
class QLineEdit;


class ClientViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ClientViewer(const Client & client, QWidget *parent = nullptr);	
	Client getClient() const { return m_client; }
	void setClient(const Client& client);
	void setActive(bool isActive);

signals:
    void removeClient(const Client& client);
    void updateClient(const Client& client);
private:
    void createMembers();
    void setupLayout();
    void setupMembers();
    void makeConnections();

private:

    QLabel* m_infoLab;
    QLineEdit* m_lastName;
    QLineEdit* m_firstName;
    QLineEdit* m_email;

    QPushButton* m_update;
    QPushButton* m_remove;

	Client m_client;
    QWidget* m_widget;
};
