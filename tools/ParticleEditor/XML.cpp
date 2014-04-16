#include "XML.h"
#include "mainwindow.h"
#include <ParticleModel.h>
#include "ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDataStream>
#include <QTextStream>
#include <QPushButton>
#include <QIcon>
#include<QString>
#include<QComboBox>
#include<QFileDialog>
#include<iostream>
#include<QMessageBox>

XML::XML(){

}


void XML::SaveXML(ParticleModel* model)
{
    //std::cout << "type: "<< model->getPathNameTexture() << std::endl;
    filename = QFileDialog::getSaveFileName(0,"Save Xml", ".",
                                            "Xml files (*.xml)");
    if ( filename.isEmpty() )
        return;
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Particle");
    xmlWriter.writeStartElement("Emitter");
    xmlWriter.writeTextElement("Type",QString::number(model->getEmitterType()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Aabbox");
    xmlWriter.writeTextElement("MaxX",QString::number(model->getAabbox().MaxEdge.X));
    xmlWriter.writeTextElement("MaxY",QString::number(model->getAabbox().MaxEdge.Y));
    xmlWriter.writeTextElement("MaxZ",QString::number(model->getAabbox().MaxEdge.Z));
    xmlWriter.writeTextElement("MinX",QString::number(model->getAabbox().MinEdge.X));
    xmlWriter.writeTextElement("MinY",QString::number(model->getAabbox().MinEdge.Y));
    xmlWriter.writeTextElement("MinZ",QString::number(model->getAabbox().MinEdge.Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Direction");
    xmlWriter.writeTextElement("X",QString::number(model->getDirection().X));
    xmlWriter.writeTextElement("Y",QString::number(model->getDirection().Y));
    xmlWriter.writeTextElement("Z",QString::number(model->getDirection().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Position");
    xmlWriter.writeTextElement("X",QString::number(model->getPosition().X));
    xmlWriter.writeTextElement("Y",QString::number(model->getPosition().Y));
    xmlWriter.writeTextElement("Z",QString::number(model->getPosition().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Center");
    xmlWriter.writeTextElement("X",QString::number(model->getCenter().X));
    xmlWriter.writeTextElement("Y",QString::number(model->getCenter().Y));
    xmlWriter.writeTextElement("Z",QString::number(model->getCenter().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Normal");
    xmlWriter.writeTextElement("X",QString::number(model->getNormal().X));
    xmlWriter.writeTextElement("Y",QString::number(model->getNormal().Y));
    xmlWriter.writeTextElement("Z",QString::number(model->getNormal().Z));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("AngleDegrees");
    xmlWriter.writeTextElement("Max",QString::number(model->getMaxAngleDegrees()));
    xmlWriter.writeEndElement();
/**
    xmlWriter.writeStartElement("MbNumber");
    xmlWriter.writeTextElement("MbNumber",QString::number(model->getgetMbNumber()));
    xmlWriter.writeEndElement();
*/
    xmlWriter.writeStartElement("LifeTime");
    xmlWriter.writeTextElement("Max",QString::number(model->getLifeTimeMax()));
    xmlWriter.writeTextElement("Min",QString::number(model->getLifeTimeMin()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("PPS");
    xmlWriter.writeTextElement("Max",QString::number(model->getMaxPPS()));
    xmlWriter.writeTextElement("Min",QString::number(model->getMinPPS()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("StartColor");
    xmlWriter.writeStartElement("Max");
    xmlWriter.writeTextElement("Alpha",QString::number(model->getMaxStartColor().getAlpha()));
    xmlWriter.writeTextElement("Red",QString::number(model->getMaxStartColor().getRed()));
    xmlWriter.writeTextElement("Blue",QString::number(model->getMaxStartColor().getBlue()));
    xmlWriter.writeTextElement("Green",QString::number(model->getMaxStartColor().getGreen()));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Min");
    xmlWriter.writeTextElement("Alpha",QString::number(model->getMinStartColor().getAlpha()));
    xmlWriter.writeTextElement("Red",QString::number(model->getMinStartColor().getRed()));
    xmlWriter.writeTextElement("Blue",QString::number(model->getMinStartColor().getBlue()));
    xmlWriter.writeTextElement("Green",QString::number(model->getMinStartColor().getGreen()));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("StartSize");
    xmlWriter.writeStartElement("Max");
    xmlWriter.writeTextElement("Height",QString::number(model->getMaxStartSize().Height));
    xmlWriter.writeTextElement("Width",QString::number(model->getMaxStartSize().Width));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Min");
    xmlWriter.writeTextElement("Height",QString::number(model->getMinStartSize().Height));
    xmlWriter.writeTextElement("Width",QString::number(model->getMinStartSize().Width));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Texture");
    xmlWriter.writeTextElement("PathName","TODO: Set PathNameTexture");
    xmlWriter.writeEndElement();

    xmlWriter.writeTextElement("NormalDirectionModifier",QString::number(model->getNormalDirectionModifier()));
    xmlWriter.writeTextElement("Radius",QString::number(model->getRadius()));
    xmlWriter.writeTextElement("LengthCylinder",QString::number(model->getLengthCylinder()));
    xmlWriter.writeTextElement("RingThickness",QString::number(model->getRingThickness()));
    xmlWriter.writeTextElement("UseNormalDirection",QString::number(model->getUseNormalDirection()));
    xmlWriter.writeTextElement("EveryMeshVertex",QString::number(model->getEveryMeshVertex()));
    xmlWriter.writeTextElement("OutLineOnly",QString::number(model->getOutLineOnly()));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}
XML::~XML(){

}
