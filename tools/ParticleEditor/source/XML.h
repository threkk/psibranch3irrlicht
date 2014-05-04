#ifndef XML_H
#define XML_H
#include <QString>
#include <ParticleModel.h>
#include <QXmlStreamReader>

class XML
{
public:
    /**
     * Create a constructor XML
     */
    XML();

    /**
     * Save the model in XML function
     */
    void SaveXML(ParticleModel* model);

    ~XML();
private:
    /**
     * URL/Link to the file
     */
    QString filename;
};

#endif // XML_H
