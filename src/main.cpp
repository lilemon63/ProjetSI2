/** @mainpage ... */

#include <QApplication>
#include <memory>
#include "View/mainwindow.h"
#include "exception.h"
#include "Handle/Handle.h"
#include "Handle/handletools.h"

//voir commit

//mettre const, déclaration anticipée, ordonner les inclusions, mettres commentaires

//rédiger wiki/utilisation

//rédiger diagrammes

int main(int argc, char *argv[])
{

    try
    {
        QApplication a(argc, argv);
        a.setApplicationName( "Volcano" ); //évite un warning lors de l'exécution.

        HandleTools t;

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
