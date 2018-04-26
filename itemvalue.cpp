#include "itemvalue.h"
#include "ui_itemvalue.h"
#include <QPainter>
#include <QDesktopWidget>
#include <QCloseEvent>

itemvalue::itemvalue(QWidget *parent, QString value) :
    QWidget(parent),
    m_resultStr(value),
    ui(new Ui::itemvalue)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 6);
    initStyle();
}

itemvalue::~itemvalue()
{
    delete ui;
}

QString itemvalue::showMyMessageBox(QWidget *parent, QString value)
{
    itemvalue *myWidget = new itemvalue(parent, value);
    return myWidget->exec();
}

void itemvalue::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void itemvalue::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void itemvalue::on_cancelBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

void itemvalue::on_okBtn_clicked()
{
    m_resultStr.clear();
    if(ui->radioButton->isChecked())
    {
        m_resultStr = ui->lineEdit->text() + "&real";
    }
    else
    {
        m_resultStr = ui->lineEdit->text() + "&borrow";
    }
    close();
}

void itemvalue::on_closeBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

QString itemvalue::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_resultStr;
}

void itemvalue::initStyle()
{
    ui->closeBtn->setObjectName("closeButton");
    ui->cancelBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
    ui->okBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    if(m_resultStr != NULL)
    {
       QStringList list = m_resultStr.split("&");
       if(list.size() == 2)
       {
           ui->lineEdit->setText(list.at(0));
           if(list.at(1) == "real")
           {
               ui->radioButton->setChecked(true);
           }
           else
           {
               ui->radioButton_2->setChecked(true);
           }
       }
    }
}
