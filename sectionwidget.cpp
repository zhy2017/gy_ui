#include "sectionwidget.h"
#include "ui_sectionwidget.h"
#include "accountitem.h"
#include <QPainter>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QDebug>
#include "editWidget/editsection.h"

SectionWidget::SectionWidget(QVector<QPointF> &data, QWidget *parent) :
    QWidget(parent),
    m_data(data),
    ui(new Ui::SectionWidget)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 6);
    initStyle();
}

SectionWidget::~SectionWidget()
{
    delete ui;
}

QVector<QPointF> SectionWidget::showMyMessageBox(QWidget *parent, QVector<QPointF> &data)
{
    SectionWidget *myWidget = new SectionWidget(data, parent);
    return myWidget->exec();
}

void SectionWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SectionWidget::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

void SectionWidget::on_cancelBtn_clicked()
{
    close();
}

void SectionWidget::on_okBtn_clicked()
{
    close();
}

void SectionWidget::onRemoveAccount(int index)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        AccountItem* it = (AccountItem *)ui->listWidget->itemWidget(item);
        if(it->getItemWidgetIndex() == index)
        {
            int row = ui->listWidget->row(item);
            ui->listWidget->takeItem(row);
            m_data.remove(row);
            delete item;
        }
    }
}

void SectionWidget::onEditAccountInfo(int index)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        AccountItem* it = (AccountItem *)ui->listWidget->itemWidget(item);
        if(it->getItemWidgetIndex() == index)
        {
            QPointF point = it->getData();
            EditSection* wid = new EditSection(QString::number(point.x()) + "&" + QString::number(point.y()), (QWidget*)this->parent());
            QString result = wid->exec();
            if(result != "cancel")
            {
                QStringList list = result.split("&");
                if(list.size() == 2)
                {
                    QString x = list.at(0);
                    QString y = list.at(1);
                    QPointF p(x.toDouble(), y.toDouble());
                    it->setData(p);
                    int row = ui->listWidget->row(item);
                    m_data.replace(row, p);
                }
            }
        }
    }
}

QVector<QPointF> SectionWidget::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_data;
}

void SectionWidget::initStyle()
{
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
    ui->allSelectBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
    ui->addBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
    ui->changeBtn->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                 "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                 "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                 "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                 "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");

    for(int i = 0; i < m_data.size(); i++)
    {
        AccountItem* item = new AccountItem();
        item->setAccountInfo(i, m_data.at(i).x(), m_data.at(i).y());
        item->setMinimumWidth(40);
        connect(item, SIGNAL(signalRemoveAccount(int)), this, SLOT(onRemoveAccount(int)));
        connect(item, SIGNAL(signalEditAccount(int)), this, SLOT(onEditAccountInfo(int)));
        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(QSize(420, 40));
        ui->listWidget->setItemWidget(listItem, item);
    }
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
}

void SectionWidget::on_allSelectBtn_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        AccountItem* it = (AccountItem *)ui->listWidget->itemWidget(item);
        it->setChecked(true);
    }
}

void SectionWidget::on_addBtn_clicked()
{
    int row = m_data.size();
    m_data.append(QPointF(ui->xEdit->text().toDouble(), ui->yEdit->text().toDouble()));

    AccountItem* item = new AccountItem();
    item->setAccountInfo(row, ui->xEdit->text().toDouble(), ui->yEdit->text().toDouble());
    item->setMinimumWidth(40);
    connect(item, SIGNAL(signalRemoveAccount(int)), this, SLOT(onRemoveAccount(int)));
    connect(item, SIGNAL(signalEditAccount(int, QString)), this, SLOT(onEditAccountInfo(int, QString)));
    QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
    listItem->setSizeHint(QSize(420, 40));
    ui->listWidget->setItemWidget(listItem, item);
}

void SectionWidget::on_changeBtn_clicked()
{
    QVector<QPointF> data;
    data.clear();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        AccountItem* it = (AccountItem *)ui->listWidget->itemWidget(item);
        if(it->getChecked())
        {
            QPointF point = it->getData();
            data.append(point);
        }
    }

    emit chanLine(data);
}
