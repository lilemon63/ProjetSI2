/** @mainpage
**
**  Programme réalisé dans le cadre de la deuxième année SI en IUT informatique en 2013.
**  Ce programme a pour but de permettre l'acquisition d'images puis d'effectuer des traitements divers et
    variés.
**  Vous pouvez éditer et rajouter vous-même et de manière simple vos propres traitements avec du code openCV.
**  Vous pouvez aussi effectuer des actions plus avancées comme éditer les paramètres graphiques, rajouter des
    zones d'intérêts...
**
**  La documentation (française) est présente à cette adresse : https://github.com/Neckara/ProjetSI2/wiki
**  Les sources (commentaires anglais) sont disponibles à cette adresse : https://github.com/Neckara/ProjetSI2/
**  Pour tout problèmes, vous pouvez me contacter via Neckara.LastDungeon@gmail.com
**
**  Programme réalisé par :
**  - Alexandro960
**  - Lilemon
**  - Neckara
**  - Majacquet3
**
**  Ce programme est sous Licence LGPL
**
**  Utilisez doxygen >= 1.8.3.1 pour générer la documentation
**
**  Use doxygen >= 1.8.3.1 to generate the documentation
*/

#include <QApplication>

#include "exception.h"
#include "Handle/Handle.h"
#include "Handle/handletools.h"
#include "View/mainwindow.h"

//mettre commentaires

//rédiger wiki/utilisation

//rédiger diagrammes

int main(int argc, char *argv[])
{

    try
    {
        QApplication a(argc, argv);
        a.setApplicationName( "Volcano" ); //avoid a warning [durant] the runtime

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
