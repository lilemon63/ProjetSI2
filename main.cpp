/** @mainpage ... */

#include <QApplication>
#include "View/mainwindow.h"
#include "exception.h"
#include "Handle/Handle.h"
#include "Handle/handletools.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        a.setApplicationName( "Volcano" ); //évite un warning lors de l'exécution.

        volatile HandleTools t;

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
