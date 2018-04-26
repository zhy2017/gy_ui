#include "vedioaddwidget.h"
#include "ui_vedioaddwidget.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QCloseEvent>
#include <QFile>

VedioAddWidget::VedioAddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VedioAddWidget)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/4);
    initStyle();

}

VedioAddWidget::~VedioAddWidget()
{
    delete ui;
}

QString VedioAddWidget::showMyMessageBox(QWidget *parent, QString value)
{
    VedioAddWidget *myWidget = new VedioAddWidget(parent);
    return myWidget->exec();
}

void VedioAddWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void VedioAddWidget::closeEvent(QCloseEvent *event)
{
    // 关闭窗口时结束事件循环，在exec()方法中返回选择结果;
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void VedioAddWidget::on_cancelBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

void VedioAddWidget::on_okBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = ui->addressEdit->text() + "&" + ui->rtspPortEdit->text() + "&" + ui->serverPortEdit->text() + "&" + ui->userEdit->text() + "&" + ui->passwordEdit->text();
    close();
}

QString VedioAddWidget::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_resultStr;
}

void VedioAddWidget::initStyle()
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

}

void VedioAddWidget::on_closeBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}
