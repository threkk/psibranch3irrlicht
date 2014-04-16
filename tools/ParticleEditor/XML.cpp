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


void XML::SaveXML()
{
    filename = QFileDialog::getSaveFileName(0,"Save Xml", ".",
                                            "Xml files (*.xml)");
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("LAMPS");

    xmlWriter.writeStartElement("LIGHT1");
    xmlWriter.writeTextElement("State", "On" );
    xmlWriter.writeTextElement("Room","5");
    xmlWriter.writeTextElement("Potencial","5");
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("LIGHT4");
    xmlWriter.writeTextElement("State", "On" );
    xmlWriter.writeTextElement("Room","5");
    xmlWriter.writeTextElement("Potencial","5");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}
XML::~XML(){

}
