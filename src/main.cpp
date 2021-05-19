#include "login_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database database;
    Login_window w(nullptr, &database);
    w.show();
    return a.exec();
}
