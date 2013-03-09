#include <QFile>
#include <QFileDialog>
#include <QPlainTextEdit>

#include "submdiwindowsresults.h"


SubMdiWindowsResults::SubMdiWindowsResults(const QString &titre, Mdi *area, QWidget *parent)
    : SubMdiWindows(titre, area, parent),
      m_textEdit(new QPlainTextEdit() )
{
    setWidget(m_textEdit);
    m_textEdit->setDisabled(true);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SubMdiWindowsResults::addText(const QString & text)
{
    m_textEdit->insertPlainText(text);
    m_textEdit->verticalScrollBar()->setValue( m_textEdit->verticalScrollBar()->maximum() );
}


void SubMdiWindowsResults::attach(void)
{
    m_attach( m_textEdit );
}


void SubMdiWindowsResults::changeText(const QString & text)
{
    m_textEdit->setPlainText( text );
    m_textEdit->verticalScrollBar()->setValue( m_textEdit->verticalScrollBar()->maximum() );
}


void SubMdiWindowsResults::detach(void)
{
    m_detach( m_textEdit );
}


void SubMdiWindowsResults::extractInformationFromImage(ImageDataPtr img)
{
    addText( "Nombre de pixels compte :" + QString::number( (*img)["CountPixel"].toInt() ) + "\n" );
    //extract what you want
}


void SubMdiWindowsResults::saveIntoFile(const QString & filename)
{
    bool result = true;
    QString message = "Sauvegarde des donnees reussie";
    QFile file(filename);

    file.open(QFile::WriteOnly);
    if( ! file.isOpen() )
    {
        message = file.errorString();
        result = false;
    }
    else
    {
        file.write( m_textEdit->toPlainText().toUtf8() ); //bon encodage ??
        file.close();
    }
    emit resultFile(message, result);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOT------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SubMdiWindowsResults::saveIntoFile(void)
{
    QString file = QFileDialog::getSaveFileName();
    if(file != "")
        saveIntoFile(file);
}
