#include "linewidget.h"
#include "ui_linewidget.h"
#include "lineitem.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QCloseEvent>

LineWidget::LineWidget(QVector<Line> data, QWidget *parent) :
    m_data(data),
    QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 6);
    initWidget();
}

LineWidget::~LineWidget()
{
    delete ui;
}

QVector<Line> LineWidget::showMyMessageBox(QWidget *parent, QVector<Line> value)
{
    LineWidget *myWidget = new LineWidget(value, parent);
    return myWidget->exec();
}

void LineWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LineWidget::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

QVector<Line> LineWidget::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_data;
}

void LineWidget::initWidget()
{
    QStringList header;

    ui->lineTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lineTable->verticalHeader()->setHidden(true);
    ui->lineTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lineTable->setFocusPolicy(Qt::NoFocus);
    ui->lineTable->setShowGrid(false);//隐藏线
    ui->lineTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lineTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->lineTable->setColumnCount(6);
    ui->lineTable->setRowCount(0);

    ui->lineTable->setColumnWidth(0, 60);
    ui->lineTable->setColumnWidth(1, 60);
    ui->lineTable->setColumnWidth(2, 80);
    ui->lineTable->setColumnWidth(3, 80);
    ui->lineTable->setColumnWidth(4, 80);
    ui->lineTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    header.clear();
    header.append(QString("垂线编号"));
    header.append(QString("起点距"));
    header.append(QString("河底高程"));
    header.append(QString("水平补偿"));
    header.append(QString("垂直补偿"));
    header.append(QString("操作"));
    ui->lineTable->setHorizontalHeaderLabels(header);

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

    for(int i = 0; i < m_data.size(); i++)
    {
        addLineTableData(m_data.at(i));
    }

}

void LineWidget::on_cancelBtn_clicked()
{
    close();
}

void LineWidget::on_okBtn_clicked()
{
    close();
}

void LineWidget::handle_remove()
{

}

void LineWidget::handle_edit(Line)
{

}

void LineWidget::addLineTableData(Line item)
{
    int row = ui->lineTable->rowCount();
    LineItem* wid = new LineItem(row, this);

    ui->lineTable->setRowCount(row + 1);
    ui->lineTable->setRowHeight(row, 50);

    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row + 1));
    item1->setTextAlignment(Qt::AlignCenter);
    ui->lineTable->setItem(row, 0, item1);

    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(item.start));
    item2->setTextAlignment(Qt::AlignCenter);
    ui->lineTable->setItem(row, 1, item2);

    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(item.bottom));
    item3->setTextAlignment(Qt::AlignCenter);
    ui->lineTable->setItem(row, 2, item3);

    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(item.x));
    item4->setTextAlignment(Qt::AlignCenter);
    ui->lineTable->setItem(row, 3, item4);

    QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(item.y));
    item5->setTextAlignment(Qt::AlignCenter);
    ui->lineTable->setItem(row, 4, item5);

    ui->lineTable->setCellWidget(row, 5, wid);
}
