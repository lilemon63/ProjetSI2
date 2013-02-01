#include "folderreader.h"
#include <QStringList>

FolderReader::FolderReader()
{
}


QDateTime* FolderReader::parseFileName(QString fileName){
    QDateTime *time = new QDateTime();
    QStringList firstList,secondList;
    int i;

    firstList = fileName.split('_');

    if(firstList[firstList.size() - 1][0] < '0' ||
            firstList[firstList.size() - 1][0] > '9')
        throw new parseException("The file's name must be like that :\n"
                                 "*_[year]-[month]-[day]-[hours]h[minute]m[sec]s[msec].*\n"
                                 "The character '*' means every chain of car. the first '_' is optionnel if no previous text is entered."
                                 "The first character of the file's name mustn't be a number.");

    secondList = firstList[firstList.size() - 1].split('-');

    for(i = 0; i < secondList.size() ; i++)
        if(firstList[secondList.size() - 1][0] < '0' ||
                firstList[secondList.size() - 1][0] > '9')
            throw new parseException("Wrong date(yyyy-mm-dd) or hours.");

    time->addYears(secondList[0].toInt());
    time->addMonths(secondList[1].toInt());
    time->addDays(secondList[2].toInt());

    firstList = secondList[3].split('h');

    if(firstList.size() != 2)
        throw new parseException("Can't find the field of minutes.");

    time->addSecs(firstList[0].toInt() * 3600);

    if(firstList[1][0] < '0' ||
       firstList[1][0] > '9')
            throw new parseException("The field of minutes isn't a number.");

    secondList = firstList[1].split('m');


    if(secondList.size() != 2)
        throw new parseException("Can't find the field of seconds.");


    time->addSecs(secondList[0].toInt() * 60);

    if(secondList[1][0] < '0' ||
       secondList[1][0] > '9')
            throw new parseException("The field of second isn't a number.");

    firstList = secondList[1].split('s');

    if(firstList.size() != 2)
        throw new parseException("Can't find the field of miliseconds.");

    time->addSecs(firstList[0].toInt());

    if(firstList[1][0] < '0' ||
       firstList[1][0] > '9')
            throw new parseException("The field of milisecond isn't a number.");

    secondList = firstList[1].split('.');

    if(secondList.size() != 2)
        throw new parseException("The file have no extention");

    return time;
}
