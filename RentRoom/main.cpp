#include <QtWidgets/QApplication>
#include "Controller.h"
#include "Options.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QApplication::setOrganizationName("Toptal Inc.");
	QApplication::setOrganizationDomain("https://www.toptal.com/");
	QApplication::setApplicationName("RentRoom");
	QApplication::setApplicationVersion("0.1");

	Options::init();
	Options::load();

	Controller ctrl;

	int result = 0;
	if (ctrl.init())
	{
		result = app.exec();
	}
	ctrl.release();

	return result;
}
