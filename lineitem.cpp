#include "lineitem.h"
#include <QPushButton>
#include <QHBoxLayout>

LineItem::LineItem(int row, QWidget *parent) :
    m_row(row),
    QWidget(parent)
{
    initWidget();
}

void LineItem::initWidget()
{
    btn1 = new QPushButton();
    btn2 = new QPushButton();
    btn1->setMinimumHeight(30);
    btn2->setMinimumHeight(30);
    btn1->setMaximumWidth(100);
    btn2->setMaximumWidth(100);

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

    btn1->setObjectName(QString::number(m_row));
    btn2->setObjectName(QString::number(m_row));

    btn1->setText(QString("编辑"));
    btn2->setText(QString("删除"));

    connect(btn1, SIGNAL(clicked()), this, SIGNAL(signalEditAccount()));
    connect(btn1, SIGNAL(clicked()), this, SIGNAL(signalRemoveAccount()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(btn1);
    layout->addWidget(btn2);

    setLayout(layout);
}
