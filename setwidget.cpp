#include "setwidget.h"
#include "ui_setwidget.h"
#include <QDebug>
#include <QHBoxLayout>
#include "vedioaddwidget.h"
#include "flowmeterwidget.h"
#include "itemvalue.h"
#include "sectionwidget.h"
#include <QStringList>
#include "sectionitem.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include "linewidget.h"

SetWidget::SetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWidget)
{
    ui->setupUi(this);
    m_map.clear();
    initWidget();
    initTabel();
}

SetWidget::~SetWidget()
{
    delete ui;
}

void SetWidget::currentItemChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void SetWidget::vedioEditBtnHandel()
{

}

void SetWidget::vedioDeleteBtnHandel()
{
    ui->vedioTabel->setFocus();
    int row = ui->vedioTabel->currentRow();
    ui->vedioTabel->removeRow(row);
}

void SetWidget::initWidget()
{
   // QString item = "视频参数设置;断面信息设置;缆道信息设置;常用参数设置;安装参数设置;测流法则管理;水位计管理;流速仪管理;站点管理;模板管理;白名单管理;用户管理;用户组管理;权限管理";
   // ui->widget->update();
    ui->widget->setRowHeight(50);
    ui->widget->addItem("视频参数设置");
    ui->widget->addItem("断面信息设置");
    ui->widget->addItem("缆道信息设置");
    ui->widget->addItem("常用参数设置");
    ui->widget->addItem("安装参数设置");
    ui->widget->addItem("测流法则管理");
    ui->widget->addItem("水位计管理");
    ui->widget->addItem("流速仪管理");
    ui->widget->addItem("站点管理");
    ui->widget->addItem("模板管理");
    ui->widget->addItem("白名单管理");
    ui->widget->addItem("用户管理");
    ui->widget->addItem("用户组管理");
    ui->widget->addItem("权限管理");

    //ui->vedioTabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //  ui->vedioTabel->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    connect(ui->widget, SIGNAL(currentItemChanged(int)), this, SLOT(currentItemChanged(int)));
    ui->vedioAddBtn->setObjectName("BlueButton");
    ui->meterAddBtn->setObjectName("BlueButton");
    ui->meterDeleteBtn->setObjectName("BlueButton");
    ui->nParaReadBtn->setObjectName("BlueButton");
    ui->nParaSaveBtn->setObjectName("BlueButton");
    ui->codeReadBtn->setObjectName("BlueButton");
    ui->codeSaveBtn->setObjectName("BlueButton");
    ui->infoDel1Btn->setObjectName("BlueButton");
    ui->infoDel2Btn->setObjectName("BlueButton");
    ui->infoDel3Btn->setObjectName("BlueButton");
    ui->infoAddBtn->setObjectName("BlueButton");
    ui->infoSaveBtn->setObjectName("BlueButton");
    ui->sectionAddBtn->setObjectName("BlueButton");
    ui->sectionMannageBtn->setObjectName("BlueButton");
    ui->ruleSaveBtn->setObjectName("BlueButton");

    ui->infoWidget->setShowFish(false);
    ui->infoWidget->setShowLine(false);
}

void SetWidget::initTabel()
{
    ui->vedioTabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vedioTabel->verticalHeader()->setHidden(true);
    ui->vedioTabel->setColumnCount(6);
    ui->vedioTabel->setRowCount(0);

    ui->vedioTabel->setColumnWidth(0, 180);
    ui->vedioTabel->setColumnWidth(1, 100);
    ui->vedioTabel->setColumnWidth(2, 100);
    ui->vedioTabel->setColumnWidth(3, 150);
    ui->vedioTabel->setColumnWidth(4, 150);
    ui->vedioTabel->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    QStringList header;
    header.append(QString("IP地址"));
    header.append(QString("RTSP端口号"));
    header.append(QString("服务端口号"));
    header.append(QString("登录用户"));
    header.append(QString("登录密码"));
    header.append(QString("操作"));
    ui->vedioTabel->setHorizontalHeaderLabels(header);

    //////////////////////////////////////////////////////

    ui->meterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->meterTable->verticalHeader()->setHidden(true);
    ui->meterTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->meterTable->setColumnCount(10);
    ui->meterTable->setRowCount(0);

    ui->meterTable->setColumnWidth(0, 90);
    ui->meterTable->setColumnWidth(1, 90);
    ui->meterTable->setColumnWidth(2, 90);
    ui->meterTable->setColumnWidth(3, 90);
    ui->meterTable->setColumnWidth(4, 130);
    ui->meterTable->setColumnWidth(5, 90);
    ui->meterTable->setColumnWidth(6, 90);
    ui->meterTable->setColumnWidth(7, 130);
    ui->meterTable->setColumnWidth(8, 90);
    ui->meterTable->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);

    header.clear();
    header.append(QString("流速仪编号"));
    header.append(QString("流速仪型号"));
    header.append(QString("常数K或B"));
    header.append(QString("常数C或A"));
    header.append(QString("常数K(转速/脉冲)"));
    header.append(QString("使用次数"));
    header.append(QString("校验时间"));
    header.append(QString("状态"));
    header.append(QString("默认"));
    header.append(QString("操作"));
    ui->meterTable->setHorizontalHeaderLabels(header);

    /////////////////////////////////////////////////////////////////
    ui->waterMeterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->waterMeterTable->verticalHeader()->setHidden(true);
    ui->waterMeterTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->waterMeterTable->setColumnCount(2);
    ui->waterMeterTable->setRowCount(0);

    ui->waterMeterTable->setColumnWidth(1, 200);
    ui->waterMeterTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    header.clear();
    header.append(QString("类型"));
    header.append(QString("操作"));
    ui->waterMeterTable->setHorizontalHeaderLabels(header);
    addWaterMeterTableData(QString("浮子水位计"));
    addWaterMeterTableData(QString("雷达水位计"));
    addWaterMeterTableData(QString("气泡水位计"));

    ////////////////////////////////////////////////////////////////////
    ui->sectionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sectionTable->verticalHeader()->setHidden(true);
    ui->sectionTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->sectionTable->setFocusPolicy(Qt::NoFocus);
    ui->sectionTable->setShowGrid(false);//隐藏线
    ui->sectionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sectionTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->sectionTable->setColumnCount(6);
    ui->sectionTable->setRowCount(0);

    ui->sectionTable->setColumnWidth(0, 80);
    ui->sectionTable->setColumnWidth(1, 80);
    ui->sectionTable->setColumnWidth(2, 180);
    ui->sectionTable->setColumnWidth(3, 180);
    ui->sectionTable->setColumnWidth(4, 80);
    ui->sectionTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    header.clear();
    header.append(QString("断面编号"));
    header.append(QString("断面类型"));
    header.append(QString("启用时间"));
    header.append(QString("停用时间"));
    header.append(QString("是否启用"));
    header.append(QString("操作"));
    ui->sectionTable->setHorizontalHeaderLabels(header);
}

void SetWidget::addVedioTableData(QString value)
{
    QWidget* buttonWidget = new QWidget(this);
    QPushButton *btn1 = new QPushButton();
    QPushButton *btn2 = new QPushButton();
    btn1->setMinimumHeight(30);
    btn2->setMinimumHeight(30);
    btn1->setMaximumWidth(100);
    btn2->setMaximumWidth(100);
    btn1->setObjectName("BlueButton");
    btn2->setObjectName("BlueButton");
    btn1->setText(QString("编辑"));
    btn2->setText(QString("删除"));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    buttonWidget->setLayout(layout);

    connect(btn1, SIGNAL(clicked()), this, SLOT(vedioEditBtnHandel()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(vedioDeleteBtnHandel()));
    int row = ui->vedioTabel->rowCount();
    ui->vedioTabel->setRowCount(row + 1);
    ui->vedioTabel->setRowHeight(row, 50);

    m_map.clear();
    QStringList list = value.split("&", QString::SkipEmptyParts);
    for(int i = 0; i < list.count(); i++)
    {
        m_map.insert(i, list.at(i));
    }

    for(int i = 0; i < m_map.size(); ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(m_map[i]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->vedioTabel->setItem(row, i, item);
    }
    ui->vedioTabel->setCellWidget(row, 5, buttonWidget);
}

void SetWidget::addMeterTableData(QString value)
{
    QWidget* buttonWidget = new QWidget(this);
    QPushButton *btn1 = new QPushButton();
    QPushButton *btn2 = new QPushButton();
    QPushButton *btn3 = new QPushButton();
    btn1->setMinimumHeight(30);
    btn2->setMinimumHeight(30);
    btn3->setMinimumHeight(30);
    btn1->setMaximumWidth(100);
    btn2->setMaximumWidth(100);
    btn3->setMaximumWidth(100);
    btn1->setObjectName("BlueButton");
    btn2->setObjectName("BlueButton");
    btn3->setObjectName("BlueButton");
    btn1->setText(QString("默认"));
    btn2->setText(QString("编辑"));
    btn3->setText(QString("删除"));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    buttonWidget->setLayout(layout);

    connect(btn1, SIGNAL(clicked()), this, SLOT(meterDefaultBtnHandel()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(meterEditBtnHandel()));
    connect(btn3, SIGNAL(clicked()), this, SLOT(meterDeleteBtnHandel()));
    int row = ui->meterTable->rowCount();
    ui->meterTable->setRowCount(row + 1);
    ui->meterTable->setRowHeight(row, 50);

    m_map.clear();
    QStringList list = value.split("&", QString::SkipEmptyParts);
    for(int i = 0; i < list.count(); i++)
    {
        m_map.insert(i, list.at(i));
    }

    for(int i = 0; i < m_map.size(); ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(m_map[i]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->meterTable->setItem(row, i, item);
    }
    ui->meterTable->setCellWidget(row, 9, buttonWidget);
}

void SetWidget::addWaterMeterTableData(QString value)
{
    QWidget* buttonWidget = new QWidget(this);
    QPushButton *btn1 = new QPushButton();
    QPushButton *btn2 = new QPushButton();
    btn1->setMinimumHeight(30);
    btn2->setMinimumHeight(30);
    btn1->setMaximumWidth(100);
    btn2->setMaximumWidth(100);
    btn1->setObjectName("BlueButton");
    btn2->setObjectName("BlueButton");
    btn1->setText(QString("配置"));
    btn2->setText(QString("默认"));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    buttonWidget->setLayout(layout);

    connect(btn1, SIGNAL(clicked()), this, SLOT(waterMeterSet()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(waterMeterDefault()));
    int row = ui->waterMeterTable->rowCount();
    ui->waterMeterTable->setRowCount(row + 1);
    ui->waterMeterTable->setRowHeight(row, 50);

     QTableWidgetItem *item = new QTableWidgetItem(value);
     item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
     ui->waterMeterTable->setItem(row, 0, item);
     ui->waterMeterTable->setCellWidget(row, 1, buttonWidget);
}

void SetWidget::addSectionTableData(QString value)
{
    int row = ui->sectionTable->rowCount();
    SectionItem *wid = new SectionItem(row, this);

    connect(wid->btn1, SIGNAL(clicked()), this, SLOT(sectionEnableBtn()));
    connect(wid->btn2, SIGNAL(clicked()), this, SLOT(sectionImportBtn()));
    connect(wid->btn3, SIGNAL(clicked()), this, SLOT(sectionExportBtn()));
    connect(wid->btn4, SIGNAL(clicked()), this, SLOT(sectionAddDataBtn()));
    connect(wid->btn5, SIGNAL(clicked()), this, SLOT(sectionEditBtn()));
    connect(wid->btn6, SIGNAL(clicked()), this, SLOT(sectionLineBtn()));
    connect(wid->btn7, SIGNAL(clicked()), this, SLOT(sectionDeleteBtn()));
    ui->sectionTable->setRowCount(row + 1);
    ui->sectionTable->setRowHeight(row, 50);

    m_sectionData.append(QString("&"));

    m_map.clear();
    QStringList list = value.split("&", QString::SkipEmptyParts);
    for(int i = 0; i < list.count(); i++)
    {
        m_map.insert(i, list.at(i));
    }

    for(int i = 0; i < m_map.size(); ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(m_map[i]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->sectionTable->setItem(row, i, item);
    }
    ui->sectionTable->setCellWidget(row, 5, wid);
}

void SetWidget::on_vedioAddBtn_clicked()
{
    QString result = VedioAddWidget::showMyMessageBox(this, NULL);
    if(result != QString("cancel"))
    {
        addVedioTableData(result);
    }
}

void SetWidget::on_meterDeleteBtn_clicked()
{

}

void SetWidget::on_meterAddBtn_clicked()
{
    QString result = FlowMeterWidget::showMyMessageBox(this, NULL);
    if(result != QString("cancel"))
    {
        addMeterTableData(result);
    }
}

void SetWidget::meterEditBtnHandel()
{

}

void SetWidget::meterDefaultBtnHandel()
{

}

void SetWidget::meterDeleteBtnHandel()
{
    ui->meterTable->setFocus();
    int row = ui->meterTable->currentRow();
    ui->meterTable->removeRow(row);
}

void SetWidget::waterMeterSet()
{

}

void SetWidget::waterMeterDefault()
{

}

void SetWidget::on_infoAddBtn_clicked()
{
    if(ui->infoDel1Widget->isHidden())
    {
        ui->infoDel1Widget->show();
        return;
    }
    if(ui->infoDel1Widget_2->isHidden())
    {
        ui->infoDel1Widget_2->show();
        return;
    }
    if(ui->infoDel1Widget_3->isHidden())
    {
        ui->infoDel1Widget_3->show();
        return;
    }
}

void SetWidget::on_infoDel1Btn_clicked()
{
    ui->infoDel1Widget->hide();
}

void SetWidget::on_infoDel2Btn_clicked()
{
    ui->infoDel1Widget_2->hide();
}

void SetWidget::on_infoDel3Btn_clicked()
{
    ui->infoDel1Widget_3->hide();
}

void SetWidget::on_sectionAddBtn_clicked()
{
    addSectionTableData(QString("2018-3&实测断面&2018-01-25 16:42:40&2018-02-27 21:16:52&启用"));
}

void SetWidget::sectionEnableBtn()
{
    QPushButton *act=qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();

    int row = Row.toInt();

    for(int i = 0; i < ui->sectionTable->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->sectionTable->item(i, 4);
        if(i == row)
        {
            item->setTextColor("green");
            item->setText("启用");
            QDateTime date = QDateTime::currentDateTime();
            QTableWidgetItem *item1 = ui->sectionTable->item(i, 2);
            item1->setText(date.toString("yyyy-MM-dd hh:mm:ss"));
        }
        else
        {
            item->setTextColor("red");
            item->setText("停用");
            QDateTime date = QDateTime::currentDateTime();
            QTableWidgetItem *item1 = ui->sectionTable->item(i, 3);
            item1->setText(date.toString("yyyy-MM-dd hh:mm:ss"));
        }
    }

    for(int i = 0; i < ui->sectionTable->rowCount(); i++)
    {
        SectionItem* wid = (SectionItem*)ui->sectionTable->cellWidget(i, 5);
        if(i == row)
        {
            wid->btn1->setEnabled(false);
            wid->btn1->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                         "QPushButton:enabled { background: rgb(208, 208, 208);color: white;}"
                                         "QPushButton:!enabled {background: rgb(208, 208, 208); color: white;}"
                                         "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                         "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
        }
        else
        {
            wid->btn1->setEnabled(true);
            wid->btn1->setStyleSheet("QPushButton{border-radius: 4px;border: none;width: 75px;height: 25px;}"
                                         "QPushButton:enabled { background: rgb(120, 170, 220);color: white;}"
                                         "QPushButton:!enabled {background: rgb(180, 180, 180); color: white;}"
                                         "QPushButton:enabled:hover{ background: rgb(100, 160, 220);}"
                                         "QPushButton:enabled:pressed{ background: rgb(0, 78, 161);}");
        }
    }
}

void SetWidget::sectionImportBtn()
{
    QString filepath = QFileDialog::getOpenFileName(this);
    if(filepath.isNull())
    {
        return;
    }

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QPushButton *act=qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();

    int row = Row.toInt();

    SectionItem* wid = (SectionItem*)ui->sectionTable->cellWidget(row, 5);

    QString line;

    QTextStream in(&file);
    line = in.readLine();
    QStringList list1 = line.split(',');
    QString key = list1.at(0);
    QString value = list1.at(1);
    wid->addSectionData(QPointF(key.toDouble(), value.toDouble()));
    while (!line.isNull())
    {
        line = in.readLine();
        if(!line.isNull())
        {
            list1.clear();
            list1 = line.split(',');
            key = list1.at(0);
            value = list1.at(1);
            wid->addSectionData(QPointF(key.toDouble(), value.toDouble()));
        }
    }

    file.close();
}

void SetWidget::sectionExportBtn()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出断面数据"),
                               "D:\data",
                               tr("断面数据 (*.csv)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QPushButton *act=qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();

    int row = Row.toInt();

    SectionItem* wid = (SectionItem*)ui->sectionTable->cellWidget(row, 5);

    QVector<QPointF> data = wid->getSectionData();
    QTextStream out(&file);
    QString item;

    for(int i = 0; i < data.size(); i++)
    {
        item = QString::number(data.at(i).x()) + "," + QString::number(data.at(i).y());
        out << item << '\n';
    }

    file.close();
}

void SetWidget::sectionAddDataBtn()
{
    QPushButton *act = qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();

    int row = Row.toInt();

    QTableWidgetItem *item = ui->sectionTable->item(row, 0);
    QTableWidgetItem *item1 = ui->sectionTable->item(row, 1);

    QString str;
    if(item1->text() == QString("实测断面"))
    {
        str = "&real";
    }
    else
    {
        str = "&borrow";
    }

    QString result = itemvalue::showMyMessageBox(this, item->text() + str);
    if(result != "cancel")
    {
        QStringList list = result.split("&");
        if(list.size() == 2)
        {
            item->setText(list.at(0));
            if(list.at(1) == "real")
            {
                item1->setText(QString("实测断面"));
            }
            else
            {
                item1->setText(QString("借用断面"));
            }
        }
    }
}

void SetWidget::sectionEditBtn()
{
    QPushButton *act=qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();
    int row = Row.toInt();

    SectionItem* wid = (SectionItem*)ui->sectionTable->cellWidget(row, 5);
    currentWid = wid;

    SectionWidget *myWidget = new SectionWidget(wid->m_sectionData, this);
    connect(myWidget, SIGNAL(chanLine(QVector<QPointF>)), this, SLOT(receiveLineData(QVector<QPointF>)));
    wid->m_sectionData = myWidget->exec();
    currentWid = NULL;
}

void SetWidget::sectionLineBtn()
{
    QPushButton *act=qobject_cast<QPushButton*>(sender());
    QString Row = act->objectName();
    int row = Row.toInt();

    SectionItem* wid = (SectionItem*)ui->sectionTable->cellWidget(row, 5);

    wid->m_lineData = LineWidget::showMyMessageBox(this, wid->m_lineData);
}

void SetWidget::sectionDeleteBtn()
{
    ui->sectionTable->setFocus();
    int row = ui->sectionTable->currentRow();
    ui->sectionTable->removeRow(row);
}

void SetWidget::receiveLineData(QVector<QPointF> data)
{
    if(currentWid != NULL)
    {
        currentWid->setLineData(data);
    }
}
