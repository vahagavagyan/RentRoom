#include "Request.h"
#include "Options.h"
Request::Request()
{
	setEmail(Options::getUserEmail());
	setKey(Options::getUserKey());
	setUserRole(Options::getUserRole());
}