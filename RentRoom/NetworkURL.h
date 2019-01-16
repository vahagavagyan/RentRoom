#pragma once
#include <QString>

class NetworkURL
{
public:
	static void initURLs();
	static QString SERVER_HOST;
	static int SERVER_PORT;
	static QString SERVER_URL;
	static QString SIGNUP_URL;
	static QString LOGIN_URL;
	static QString RENT_URL;
	static QString CREATE_APARTMENT_URL;
	static QString CREATE_CLIENT_URL;
	static QString CREATE_REALTOR_URL;
	static QString DELETE_APARTMENT_URL;
	static QString DELETE_CLIENT_URL;
	static QString DELETE_REALTOR_URL;
	static QString LIST_APARTMENTS_URL;
	static QString LIST_AVAILABLE_APARTMENTS_URL;
	static QString LIST_CLIENTS_URL;
	static QString LIST_REALTOR_APARTMENTS_URL;
	static QString LIST_REALTORS_URL;
	static QString UPDATE_APARTMENT_URL;
	static QString UPDATE_CLIENT_URL;
	static QString UPDATE_REALTOR_URL;
};