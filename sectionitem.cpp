#include "sectionitem.h"
#include <QPushButton>
#include <QHBoxLayout>


SectionItem::SectionItem(int row, QWidget *parent) :
    m_row(row),
    QWidget(parent)
{
    initWidget();
    m_sectionData.clear();
}

void SectionItem::addSectionData(QPointF data)
{
    m_sectionData.append(data);
}

void SectionItem::clearSectionData()
{
    m_sectionData.clear();
}

void SectionItem::setLineData(QVector<QPointF> data)
{
   m_lineData.clear();
   for(int i = 0; i < data.count(); i++)
   {
       Line item;
       item.start = data.at(i).x();
       item.bottom = data.at(i).y();
       item.x = 0;
       item.y = 0;
       m_lineData.append(item);
   }
}

QVector<QPointF> SectionItem::getSectionData()
{
    return m_sectionData;
}

void SectionItem::initWidget()
{
    btn1 = new QPushButton();
    btn2 = new QPushButton();
    btn3 = new QPushButton();
    btn4 = new QPushButton();
    btn5 = new QPushButton();
    btn6 = new QPushButton();
    btn7 = new QPushButton();
    btn1->setMinimumHeight(30);
    btn2->setMinimumHeight(30);
    btn3->setMinimumHeight(30);
    btn4->setMinimumHeight(30);
    btn5->setMinimumHeight(30);
    btn6->setMinimumHeight(30);
    btn7->setMinimumHeight(30);
    btn1->setMaximumWidth(100);
    btn2->setMaximumWidth(100);
    btn3->setMaximumWidth(100);
    btn4->setMaximumWidth(100);
    btn5->setMaximumWidth(100);
    btn6->setMaximumWidth(100);
    btn7->setMaximumWidth(100);

    btn1->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    btn2->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");


    btn3->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");


    btn4->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    btn5->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    btn6->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    btn7->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    btn1->setObjectName(QString::number(m_row));
    btn2->setObjectName(QString::number(m_row));
    btn3->setObjectName(QString::number(m_row));
    btn4->setObjectName(QString::number(m_row));
    btn5->setObjectName(QString::number(m_row));
    btn6->setObjectName(QString::number(m_row));
    btn7->setObjectName(QString::number(m_row));

    btn1->setText(QString("启用"));
    btn2->setText(QString("导入"));
    btn3->setText(QString("导出"));
    btn4->setText(QString("修改属性"));
    btn5->setText(QString("编辑断面"));
    btn6->setText(QString("测流垂线"));
    btn7->setText(QString("删除"));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);
    layout->addWidget(btn5);
    layout->addWidget(btn6);
    layout->addWidget(btn7);

    setLayout(layout);
}
