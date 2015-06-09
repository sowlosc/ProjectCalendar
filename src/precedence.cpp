#include "precedence.h"
#include "projet.h"
#include "tache.h"

void Precedence::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("precedence");
    s.writeTextElement("projet",projet->getTitre());
    s.writeTextElement("pred",pred->getId());
    s.writeTextElement("succ",succ->getId());
    s.writeEndElement();
}
