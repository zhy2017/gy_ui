#include "accountitem.h"
#include <QHBoxLayout>
#include "itemvalue.h"
#include <QDebug>

AccountItem::AccountItem(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

void AccountItem::setAccountInfo(int index, double x, double y)
{
    m_index = index;
    QString xValue = QString::number(x);
    QString yValue = QString::number(y);

    m_xValue->setText(xValue);
    m_yValue->setText(yValue);
}

int AccountItem::getItemWidgetIndex()
{
    return m_index;
}

void AccountItem::setChecked(bool status)
{
    m_checkBtn->setChecked(status);
}

bool AccountItem::getChecked()
{
    return m_checkBtn->isChecked();
}

QPointF AccountItem::getData()
{
    return QPointF(m_xValue->text().toDouble(), m_yValue->text().toDouble());
}

void AccountItem::setData(QPointF data)
{
    m_xValue->setText(QString::number(data.x()));
    m_yValue->setText(QString::number(data.y()));
}

void AccountItem::onRemoveAccount()
{
    emit signalRemoveAccount(m_index);
}

void AccountItem::onEditAccount()
{
    emit signalEditAccount(m_index);
}

void AccountItem::initWidget()
{
    m_checkBtn = new QCheckBox();
    m_xLabel = new QLabel();
    m_xValue = new QLabel();
    m_yLabel = new QLabel();
    m_yValue = new QLabel();
    m_editBtn = new QPushButton();
    m_deleteBtn = new QPushButton();

  //  m_xLabel->setBackgroundRole(QPalette::NoRole);

    m_xLabel->setText("X:");
    m_yLabel->setText("Y:");
    m_editBtn->setText(QString("编辑"));
    m_deleteBtn->setText(QString("删除"));

    m_editBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
     m_deleteBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

  //  m_checkBtn->setMinimumWidth(40);
  //  m_xLabel->setMinimumWidth(40);
   // m_xValue->setMinimumWidth(20);
    //m_yLabel->setMinimumWidth(20);
    //m_yValue->setMinimumWidth(20);
  //  m_editBtn->setMinimumHeight(40);
  //  m_deleteBtn->setMinimumHeight(40);

    connect(m_deleteBtn, SIGNAL(clicked()), this, SLOT(onRemoveAccount()));
    connect(m_editBtn, SIGNAL(clicked()), this, SLOT(onEditAccount()));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_checkBtn);
    mainLayout->addWidget(m_xLabel);
    mainLayout->addWidget(m_xValue);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(m_yLabel);
    mainLayout->addWidget(m_yValue);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(m_editBtn);
    mainLayout->addWidget(m_deleteBtn);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(6);
    setLayout(mainLayout);

    setFocusPolicy(Qt::NoFocus);
}
