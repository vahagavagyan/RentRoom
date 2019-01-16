#pragma once
#include <QWidget>
#include "Realtor.h"

class QLabel;
class QPushButton;
class QLineEdit;


class RealtorViewer : public QWidget
{
    Q_OBJECT
public:
    explicit RealtorViewer(const Realtor& realtor, QWidget *parent = nullptr);
	Realtor getRealtor() const { return m_realtor; }
	void setRealtor(const Realtor& realtor);

	void setActive(bool isActive);

signals:
    void removeRealtor(const Realtor& realtor);
    void updateRealtor(const Realtor& realtor);
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

	Realtor m_realtor;
    QWidget* m_widget;
};
