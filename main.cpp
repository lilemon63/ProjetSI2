/** @mainpage ... */

#include <QApplication>
#include "View/mainwindow.h"
#include "exception.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        a.setApplicationName( "Volcano" ); //évite un warning lors de l'exécution.
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch(Exception e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
