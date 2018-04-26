#include "flowmeterwidget.h"
#include "ui_flowmeterwidget.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QCloseEvent>

FlowMeterWidget::FlowMeterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlowMeterWidget)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 6);
    QButtonGroup *grp1 = new QButtonGroup(this);
    grp1->addButton(ui->errorYesBtn);
    grp1->addButton(ui->errorNoBtn);
    QButtonGroup *grp2 = new QButtonGroup(this);
    grp2->addButton(ui->defaultYesBtn);
    grp2->addButton(ui->defaultNoBtn);
    initStyle();
}

FlowMeterWidget::~FlowMeterWidget()
{
    delete ui;
}

QString FlowMeterWidget::showMyMessageBox(QWidget *parent, QString value)
{
    FlowMeterWidget *myWidget = new FlowMeterWidget(parent);
    return myWidget->exec();
}

void FlowMeterWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FlowMeterWidget::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void FlowMeterWidget::on_cancelBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

void FlowMeterWidget::on_okBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = ui->numberEdit->text() + "&" + ui->modelEdit->text() + "&" + ui->kEdit->text() + "&" + ui->cEdit->text() + "&" + ui->nEdit->text() + "&" + ui->timesEdit->text() + "&" + ui->timeEdit->text() + "&";
    if(ui->errorYesBtn->isChecked())
    {
        m_resultStr = m_resultStr + "错误&";
    }
    else
    {
        m_resultStr = m_resultStr + "正常&";
    }
    if(ui->defaultYesBtn->isChecked())
    {
        m_resultStr = m_resultStr + "默认";
    }
    else
    {
        m_resultStr = m_resultStr + "-";
    }
    close();
}

void FlowMeterWidget::on_closeBtn_clicked()
{
    m_resultStr.clear();
    m_resultStr = QString("cancel");
    close();
}

QString FlowMeterWidget::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_resultStr;
}

void FlowMeterWidget::initStyle()
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
