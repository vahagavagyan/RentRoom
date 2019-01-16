#include "Apartment.h"
#include "Realtor.h"


int Apartment::getId() const { return id; }
void Apartment::setId(int val) { id = val; }
QString Apartment::getName() const { return m_name; }
void Apartment::setName(QString val) { m_name = val; }
QString Apartment::getDescription() const { return m_description; }
void Apartment::setDescription(QString val) { m_description = val; }
int Apartment::getFloorSize() const { return m_floorSize; }
void Apartment::setFloorSize(int val) { m_floorSize = val; }
float Apartment::getPrice() const { return m_price; }
void Apartment::setPrice(float val) { m_price = val; }
int Apartment::getRoomsNum() const { return m_roomsNum; }
void Apartment::setRoomsNum(int val) { m_roomsNum = val; }
double Apartment::getLocLatitude() const { return m_locLatitude; }
void Apartment::setLocLatitude(double val) { m_locLatitude = val; }
double Apartment::getLocLongitude() const { return m_locLongitude; }
void Apartment::setLocLongitude(double val) { m_locLongitude = val; }
QDate Apartment::getDateAdded() const { return m_dateAdded; }
void Apartment::setDateAdded(const QDate& val) { m_dateAdded = val; }
std::shared_ptr<Realtor> Apartment::getRealtor() const { return m_realtor; }
void Apartment::setRealtor(std::shared_ptr<Realtor>  val) { m_realtor = val; }
bool Apartment::getRented() const { return m_isRented; }
void Apartment::setRented(bool val) { m_isRented = val; }