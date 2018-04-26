#include "editsection.h"
#include "ui_editsection.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QCloseEvent>

EditSection::EditSection(QString str, QWidget *parent) :
    m_resultStr(str),
    QWidget(parent),
    ui(new Ui::EditSection)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 6);
    initStyle();
}

EditSection::~EditSection()
{
    delete ui;
}

QString EditSection::showMyMessageBox(QWidget *parent, QString value)
{
    EditSection *myWidget = new EditSection(value, parent);
    return myWidget->exec();
}

void EditSection::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void EditSection::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void EditSection::on_cancelBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

void EditSection::on_okBtn_clicked()
{
    m_resultStr = ui->xLineEdit->text() + "&" + ui->yLineEdit->text();
    close();
}

void EditSection::on_closeBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

QString EditSection::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_resultStr;
}

void EditSection::initStyle()
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
            ui->xLineEdit->setText(list.at(0));
            ui->yLineEdit->setText(list.at(1));
        }
    }
}
