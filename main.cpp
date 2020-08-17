#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Tester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI app;
    app.show();
    return a.exec();
}