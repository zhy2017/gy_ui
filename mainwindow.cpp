#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sliderbar.h"
#include <QPixmap>
#include "setwidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_setWidget = new SetWidget(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QString item = "模拟图;测流垂线设置;实时测流结果;断面-流速关系图";

    ui->sliderWidget_2->setLineWidth(2);
    ui->sliderWidget_2->setLineColor(QColor(24, 189, 155));
    ui->sliderWidget_2->setBgColorStart(Qt::transparent);
    ui->sliderWidget_2->setBgColorEnd(Qt::transparent);
    ui->sliderWidget_2->setBarColorStart(Qt::transparent);
    ui->sliderWidget_2->setBarColorEnd(Qt::transparent);
    ui->sliderWidget_2->setTextNormalColor(QColor(50, 50, 50));
    ui->sliderWidget_2->setTextSelectColor(QColor(255, 107, 107));
    ui->sliderWidget_2->setBarStyle(SliderBar::BarStyle_Line_Bottom);

    ui->sliderWidget_2->setItems(item);

    ui->sliderWidget_2->setCurrentIndex(0);
    connect(ui->sliderWidget_2, SIGNAL(currentItemChanged(int, QString)), this, SLOT(currentItemChanged(int, QString)));

    QPixmap pix(":/images/lamp1.png");
    ui->runLamp_2->setScaledContents(true);
    ui->waterLamp_2->setScaledContents(true);
    ui->speedLamp_2->setScaledContents(true);
    ui->bottomLamp_2->setScaledContents(true);
    ui->errorLamp_2->setScaledContents(true);
    ui->runLamp_2->setPixmap(pix);
    ui->waterLamp_2->setPixmap(pix);
    ui->speedLamp_2->setPixmap(pix);
    pix.load(":/images/lamp2.png");
    ui->bottomLamp_2->setPixmap(pix);
    pix.load(":/images/lamp3.png");
    ui->errorLamp_2->setPixmap(pix);

    ui->resetButton_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->clearBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->autoStartBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/whiteBtn.png); color:white}");
    ui->returnBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->handelStartBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->warnBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/yellowBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/yellowBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/yellowpress.png);}");

    ui->upBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/up.png);}"
                                   "QPushButton::hover{border-image:url(:/images/up.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/uppress.png);}");
    ui->downBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/down.png);}"
                                   "QPushButton::hover{border-image:url(:/images/down.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/downpress.png);}");
    ui->backBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/left.png);}"
                                   "QPushButton::hover{border-image:url(:/images/left.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/leftpress.png);}");
    ui->forwardBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/right.png);}"
                                   "QPushButton::hover{border-image:url(:/images/right.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/rightpress.png);}");
    ui->stopBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/stop.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/stop.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/stoppress.png);}");

    ui->titel1Label->setScaledContents(true);
    ui->titel2Label->setScaledContents(true);
    ui->titel3Label->setScaledContents(true);
    ui->titel4Label->setScaledContents(true);
    pix.load(":/images/titel1.png");
    ui->titel1Label->setPixmap(pix);
    pix.load(":/images/titel2.png");
    ui->titel2Label->setPixmap(pix);
    pix.load(":/images/titel3.png");
    ui->titel3Label->setPixmap(pix);
    pix.load(":/images/titel4.png");
    ui->titel4Label->setPixmap(pix);
    ui->zeroBtn->setStyleSheet("QPushButton{border-image:url(:/images/whiteBtn.png); color:white}");

    ui->cameraWidget_2->setAutoFillBackground(true);
    QPalette palette = ui->cameraWidget_2->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/images/black1.png").scaled(// 缩放背景图.
                ui->cameraWidget_2->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    ui->cameraWidget_2->setPalette(palette);

    ui->statusWidget_2->setAutoFillBackground(true);
    palette = ui->statusWidget_2->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/images/black2.png").scaled(// 缩放背景图.
                ui->statusWidget_2->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    ui->statusWidget_2->setPalette(palette);

    ui->zoomOutBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                  "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                  "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->zoomInBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                 "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                 "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->speedAddBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                   "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                   "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");
    ui->speedSmallBtn_2->setStyleSheet("QPushButton{border-image:url(:/images/blueBtn.png); color:white}"
                                     "QPushButton::hover{border-image:url(:/images/blueBtn.png);}"
                                     "QPushButton::pressed{border-image:url(:/images/bluepress.png);}");

    ui->up1Btn_2->setStyleSheet("QPushButton{border-image:url(:/images/up1.png);}"
                              "QPushButton::hover{border-image:url(:/images/up1.png);}"
                              "QPushButton::pressed{border-image:url(:/images/up1press.png);}");
    ui->down1Btn_2->setStyleSheet("QPushButton{border-image:url(:/images/down1.png);}"
                                "QPushButton::hover{border-image:url(:/images/down1.png);}"
                                "QPushButton::pressed{border-image:url(:/images/down1press.png);}");
    ui->left1Btn_2->setStyleSheet("QPushButton{border-image:url(:/images/left1.png);}"
                                "QPushButton::hover{border-image:url(:/images/left1.png);}"
                                "QPushButton::pressed{border-image:url(:/images/left1press.png);}");
    ui->right1Btn_2->setStyleSheet("QPushButton{border-image:url(:/images/right1.png);}"
                                 "QPushButton::hover{border-image:url(:/images/right1.png);}"
                                 "QPushButton::pressed{border-image:url(:/images/right1press.png);}");

    this->setWindowState(Qt::WindowMaximized);

    ui->stackedWidget->addWidget(m_setWidget);
 }


void MainWindow::on_mainBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tabelBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_setBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_homeBtn_clicked()
{
    return;
}

void MainWindow::currentItemChanged(int index, const QString &item)
{
    ui->stackedWidget_2->setCurrentIndex(index);
}
