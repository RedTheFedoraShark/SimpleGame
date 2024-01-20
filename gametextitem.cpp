#include "gametextitem.h"
#include "qfont.h"

gameTextItem::gameTextItem(QGraphicsItem * parent)
{
    this->m_text = "Bayayega";
    this->setPlainText(this->text());
    this->setDefaultTextColor(Qt::white);
    this->setFont(QFont("Helvetica", 20, QFont::Bold));
}

QString gameTextItem::text()
{
    return this->m_text;
}

void gameTextItem::setText(QString text)
{
    this->m_text = text;
    this->setPlainText(this->m_text);
}
