//SOURCE ADAPTED FROM http://www.developer.nokia.com/Community/Wiki/Creating_an_HTTP_network_request_in_Qt
//AND http://www.developer.nokia.com/Community/Wiki/QXmlStreamReader_to_parse_XML_in_Qt

#ifndef MYHTTPENGINE_H
#define MYHTTPENGINE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QList>
#include "scoreinfo.h"

#include <QDebug>

class MyHttpEngine : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpEngine(QObject *parent = 0);

    void parseScore(QXmlStreamReader& xml);
    QList<QObject *> scoreList;

signals:
    
public slots:
    void finishedSlot(QNetworkReply* reply);
private:
    QNetworkAccessManager* nam;
    
};

#endif // MYHTTPENGINE_H
