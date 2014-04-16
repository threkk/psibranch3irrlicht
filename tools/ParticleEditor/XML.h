#ifndef XML_H
#define XML_H
#include <QVariant>
#include <QString>
#include<QXmlStreamReader>

class XML
{
public:
    XML();
    void SaveXML();
    ~XML();
private:
    QString filename;
    QXmlStreamReader Rxml;
};

#endif // XML_H
