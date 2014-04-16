#ifndef XML_H
#define XML_H
#include <QVariant>
#include <QString>
#include <ParticleModel.h>
#include<QXmlStreamReader>

class XML
{
public:
    XML();
    void SaveXML(ParticleModel* model);
    ~XML();
private:
    QString filename;
    QXmlStreamReader Rxml;
};

#endif // XML_H
