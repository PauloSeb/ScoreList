//SOURCE ADAPTED FROM http://www.developer.nokia.com/Community/Wiki/Creating_an_HTTP_network_request_in_Qt
//AND http://www.developer.nokia.com/Community/Wiki/QXmlStreamReader_to_parse_XML_in_Qt
#include "myhttpengine.h"

MyHttpEngine::MyHttpEngine(QObject *parent) :
    QObject(parent)
{
    scoreList.append(new ScoreInfo("init", "init", "init"));
    scoreList.append(new ScoreInfo("init2", "init", "init2"));
    scoreList.append(new ScoreInfo("init3", "init3", "init3"));
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));

    QUrl url("http://api.musescore.com/services/rest/score.xml&oauth_consumer_key=musichackday&part=0,73&sort=view_count");
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.
}

void MyHttpEngine::finishedSlot(QNetworkReply* reply)
{
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this
    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray result = reply->readAll();  // bytes

        /* QXmlStreamReader takes any QIODevice. */
        QXmlStreamReader xml(result);
        QList< QMap<QString,QString> > scores;
        /* We'll parse the XML until we reach end of it.*/
        while(!xml.atEnd() && !xml.hasError()) {
            /* Read next element.*/
            QXmlStreamReader::TokenType token = xml.readNext();
            /* If token is just StartDocument, we'll go to next.*/
            if(token == QXmlStreamReader::StartDocument) {
                continue;
            }
            /* If token is StartElement, we'll see if we can read it.*/
            if(token == QXmlStreamReader::StartElement) {
                /* If it's named persons, we'll go to the next.*/
                if(xml.name() == "scores") {
                    continue;
                }
                /* If it's named person, we'll dig the information from there.*/
                if(xml.name() == "score") {
                    this->parseScore(xml);
                }
            }
        }

    }
    // Some http error received
    else
    {
        // handle errors here
    }
    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}


void MyHttpEngine::parseScore(QXmlStreamReader& xml) {
    QString name;
    QString description;
    QString id;
    /* Let's check that we're really getting a score. */
    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "score") {
        return;
    }
    /* Let's get the attributes for person */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "score")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            /* We've found title. */
            if(xml.name() == "title") {
                xml.readNext();
                name = xml.text().toString();
            }
            /* We've found description. */
            if(xml.name() == "description") {
                xml.readNext();
                description = xml.text().toString();
            }
            /* We've found id. */
            if(xml.name() == "id") {
                xml.readNext();
                id = xml.text().toString();
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    scoreList.append(new ScoreInfo(name, description, id));
    QQuickView view;
    view.rootContext()->setContextProperty("listModelC",QVariant::fromValue(scoreList));
    qDebug() << "list updated with score id" << id;
}
