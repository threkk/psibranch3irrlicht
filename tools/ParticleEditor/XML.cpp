#include "XML.h"
#include "mainwindow.h"
#include <ParticleModel.h>
#include "ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>


XML::XML()
{
}

void XML::SaveXML(ParticleModel* model)
{

    //Set location and the name of the XML file
    filename = QFileDialog::getSaveFileName(0,"Save Xml", ".",
                                            "Xml files (*.xml)");
    //Check of the file is made
    if ( filename.isEmpty() )
        return;

    //Create the file
    QFile file(filename);

    std::cout << "File: "<< filename.toUtf8().constData() << std::endl;

    //Open the file
    file.open(QIODevice::WriteOnly);

    //Start Write the file
    QXmlStreamWriter xmlWriter(&file);
    //Set format in XML
    xmlWriter.setAutoFormatting(true);
    //Set data in XML from ParticleModel
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Particle");
    xmlWriter.writeStartElement("Emitter");
    xmlWriter.writeAttribute("Type",QString::number(model->getEmitterType()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Aabbox");
    xmlWriter.writeAttribute("MaxX",QString::number(model->getAabbox().MaxEdge.X));
    xmlWriter.writeAttribute("MaxY",QString::number(model->getAabbox().MaxEdge.Y));
    xmlWriter.writeAttribute("MaxZ",QString::number(model->getAabbox().MaxEdge.Z));
    xmlWriter.writeAttribute("MinX",QString::number(model->getAabbox().MinEdge.X));
    xmlWriter.writeAttribute("MinY",QString::number(model->getAabbox().MinEdge.Y));
    xmlWriter.writeAttribute("MinZ",QString::number(model->getAabbox().MinEdge.Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Direction");
    xmlWriter.writeAttribute("X",QString::number(model->getDirection().X));
    xmlWriter.writeAttribute("Y",QString::number(model->getDirection().Y));
    xmlWriter.writeAttribute("Z",QString::number(model->getDirection().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Position");
    xmlWriter.writeAttribute("X",QString::number(model->getPosition().X));
    xmlWriter.writeAttribute("Y",QString::number(model->getPosition().Y));
    xmlWriter.writeAttribute("Z",QString::number(model->getPosition().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Center");
    xmlWriter.writeAttribute("X",QString::number(model->getCenter().X));
    xmlWriter.writeAttribute("Y",QString::number(model->getCenter().Y));
    xmlWriter.writeAttribute("Z",QString::number(model->getCenter().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Normal");
    xmlWriter.writeAttribute("X",QString::number(model->getNormal().X));
    xmlWriter.writeAttribute("Y",QString::number(model->getNormal().Y));
    xmlWriter.writeAttribute("Z",QString::number(model->getNormal().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("AngleDegrees");
    xmlWriter.writeAttribute("Max",QString::number(model->getMaxAngleDegrees()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("LifeTime");
    xmlWriter.writeAttribute("Max",QString::number(model->getLifeTimeMax()));
    xmlWriter.writeAttribute("Min",QString::number(model->getLifeTimeMin()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("PPS");
    xmlWriter.writeAttribute("Max",QString::number(model->getMaxPPS()));
    xmlWriter.writeAttribute("Min",QString::number(model->getMinPPS()));
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("MaxStartColor");
    xmlWriter.writeAttribute("Alpha",QString::number(model->getMaxStartColor().getAlpha()));
    xmlWriter.writeAttribute("Red",QString::number(model->getMaxStartColor().getRed()));
    xmlWriter.writeAttribute("Blue",QString::number(model->getMaxStartColor().getBlue()));
    xmlWriter.writeAttribute("Green",QString::number(model->getMaxStartColor().getGreen()));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("MinStartColor");
    xmlWriter.writeAttribute("Alpha",QString::number(model->getMinStartColor().getAlpha()));
    xmlWriter.writeAttribute("Red",QString::number(model->getMinStartColor().getRed()));
    xmlWriter.writeAttribute("Blue",QString::number(model->getMinStartColor().getBlue()));
    xmlWriter.writeAttribute("Green",QString::number(model->getMinStartColor().getGreen()));
    xmlWriter.writeEndElement();



    xmlWriter.writeStartElement("MaxStartSize");
    xmlWriter.writeAttribute("Height",QString::number(model->getMaxStartSize().Height));
    xmlWriter.writeAttribute("Width",QString::number(model->getMaxStartSize().Width));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("MinStartSize");
    xmlWriter.writeAttribute("Height",QString::number(model->getMinStartSize().Height));
    xmlWriter.writeAttribute("Width",QString::number(model->getMinStartSize().Width));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Texture");
    QFileInfo pathTex(model->getPathNameTexture().c_str());
    xmlWriter.writeAttribute("PathName",pathTex.fileName().toUtf8().constData());
    if (QFile::exists(model->getPathNameTexture().c_str()))
    {
        QFileInfo pathXML(filename);
        QFile::copy(model->getPathNameTexture().c_str(), pathXML.path() + "/" + pathTex.fileName());

    }else{

        QString QstringPathNameTexture = model->getPathNameTexture().c_str();
        QMessageBox::information(0,"Texture moved/not found",QstringPathNameTexture+" is moved/not found. \nPlace Texture in the same folder as this XML file");
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Rest");
    xmlWriter.writeAttribute("MbNumber",QString::number(model->getMbNumber()));
    xmlWriter.writeAttribute("NormalDirectionModifier",QString::number(model->getNormalDirectionModifier()));
    xmlWriter.writeAttribute("Radius",QString::number(model->getRadius()));
    xmlWriter.writeAttribute("LengthCylinder",QString::number(model->getLengthCylinder()));
    xmlWriter.writeAttribute("RingThickness",QString::number(model->getRingThickness()));
    xmlWriter.writeAttribute("UseNormalDirection",QString::number(model->getUseNormalDirection()));
    xmlWriter.writeAttribute("EveryMeshVertex",QString::number(model->getEveryMeshVertex()));
    xmlWriter.writeAttribute("OutLineOnly",QString::number(model->getOutLineOnly()));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    //Close the file
    file.close();
}
XML::~XML()
{
}
