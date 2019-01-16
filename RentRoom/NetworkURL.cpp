#include "NetworkURL.h"


QString	NetworkURL::SERVER_HOST = "http://localhost";
int		NetworkURL::SERVER_PORT = 5555;
QString NetworkURL::SERVER_URL = "";
QString NetworkURL::SIGNUP_URL = "";
QString NetworkURL::LOGIN_URL = "";
QString NetworkURL::RENT_URL = "";
QString NetworkURL::CREATE_APARTMENT_URL = "";
QString NetworkURL::CREATE_CLIENT_URL = "";
QString NetworkURL::CREATE_REALTOR_URL = "";
QString NetworkURL::DELETE_APARTMENT_URL = "";
QString NetworkURL::DELETE_CLIENT_URL = "";
QString NetworkURL::DELETE_REALTOR_URL = "";
QString NetworkURL::LIST_APARTMENTS_URL = "";
QString NetworkURL::LIST_AVAILABLE_APARTMENTS_URL = "";
QString NetworkURL::LIST_CLIENTS_URL = "";
QString NetworkURL::LIST_REALTOR_APARTMENTS_URL = "";
QString NetworkURL::LIST_REALTORS_URL = "";
QString NetworkURL::UPDATE_APARTMENT_URL = "";
QString NetworkURL::UPDATE_CLIENT_URL = "";
QString NetworkURL::UPDATE_REALTOR_URL = "";


void NetworkURL::initURLs()
{
	SERVER_URL = SERVER_HOST + ":" + QString::number(SERVER_PORT) + "/";

	LOGIN_URL = NetworkURL::SERVER_URL + "login";

	CREATE_APARTMENT_URL = NetworkURL::SERVER_URL + "create_apartment";
	CREATE_CLIENT_URL = NetworkURL::SERVER_URL + "create_client";
	CREATE_REALTOR_URL = NetworkURL::SERVER_URL + "create_realtor";
	DELETE_APARTMENT_URL = NetworkURL::SERVER_URL + "delete_apartment";
	DELETE_CLIENT_URL = NetworkURL::SERVER_URL + "delete_client";
	DELETE_REALTOR_URL = NetworkURL::SERVER_URL + "delete_realtor";
	LIST_AVAILABLE_APARTMENTS_URL = NetworkURL::SERVER_URL + "list_available";
	LIST_APARTMENTS_URL = NetworkURL::SERVER_URL + "list_apartments";
	LIST_CLIENTS_URL = NetworkURL::SERVER_URL + "list_clients";
	LIST_REALTOR_APARTMENTS_URL = NetworkURL::SERVER_URL + "list_realtor_apartments";
	LIST_REALTORS_URL = NetworkURL::SERVER_URL + "list_realtors";
	LOGIN_URL = NetworkURL::SERVER_URL + "login";
	RENT_URL = NetworkURL::SERVER_URL + "rent";
	SIGNUP_URL = NetworkURL::SERVER_URL + "signup";
	UPDATE_APARTMENT_URL = NetworkURL::SERVER_URL + "update_apartment";
	UPDATE_CLIENT_URL = NetworkURL::SERVER_URL + "update_client";
	UPDATE_REALTOR_URL = NetworkURL::SERVER_URL + "update_realtor";

}
