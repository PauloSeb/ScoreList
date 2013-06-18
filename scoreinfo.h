#ifndef SCOREINFO_H
#define SCOREINFO_H

#include <QObject>
#include <QString>

#include "qtquick2applicationviewer.h"
#include <QQmlContext>

class ScoreInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
public:

    explicit ScoreInfo(QObject *parent = 0);

    ScoreInfo(QString name, QString category, QString number) {
        m_name = name;
        m_category = category;
        m_number = number;
    }


    void setName(QString name) {
        m_name = name;
        emit nameChanged(name);
    }

    void setCategory(QString category) {
        m_category = category;
        emit categoryChanged(category);
    }

    void setNumber(QString number) {
        m_number = number;
        emit numberChanged(number);
    }

    QString name() const
    { return m_name; }

    QString category() const
    { return m_category; }

    QString number() const
    { return m_number; }
    
signals:
    void nameChanged(QString);
    void categoryChanged(QString);
    void numberChanged(QString);
    
public slots:

private:
    QString m_name;
    QString m_category;
    QString m_number;
    
};

#endif // SCOREINFO_H
