#pragma execution_character_set("utf-8")

#include "navprogressbar.h"
#include "qpainter.h"
#include "qdebug.h"
#include "qfontdatabase.h"

NavProgressBar::NavProgressBar(QWidget *parent) : QWidget(parent)
{
    //引入图形字体
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);

    maxStep = 8;
    currentStep = 1;

  //  topInfo << "step1" << "step2" << "step3" << "step4" << "step5";
   // bottomInfo << "2016-11-24 20:57:58" << "2016-11-24 21:55:56";
  //  navStyle = NavStyle_JD;

    background = QColor(100, 100, 100);
    foreground = QColor(255, 255, 255);
    currentBackground = QColor(100, 184, 255);
    currentForeground = QColor(255, 255, 255);

    setFont(QFont("Microsoft Yahei", 10));
}

void NavProgressBar::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawBg_GY(&painter);
    drawText_GY(&painter);
    drawCurrentBg_GY(&painter);
}

void NavProgressBar::drawBg_GY(QPainter *painter)
{
    painter->save();

    int height = this->height() / maxStep;

}

/*void NavProgressBar::drawBg_ZFB(QPainter *painter)
{
    painter->save();

    //圆半径为高度一定比例,计算宽度,将宽度等分
    int width = this->width() / maxStep;
    int height = this->height() / 3;
    int radius = height / 3;
    int initX = 0;
    int initY = this->height() / 2;

    //逐个绘制连接线条
    initX = width / 2;
    QPen pen = painter->pen();
    pen.setWidthF((double)radius / 4);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(background);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    for (int i = 0; i < maxStep - 1; i++) {
        painter->drawLine(QPoint(initX, initY), QPoint(initX + width, initY));
        initX += width;
    }

    //逐个绘制圆
    initX = width / 2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);

    for (int i = 0; i < maxStep; i++) {
        painter->drawEllipse(QPoint(initX, initY), radius, radius);
        initX += width;
    }

    painter->restore();
}

void NavProgressBar::drawText_ZFB(QPainter *painter)
{
    int width = this->width() / maxStep;
    int height = this->height() / 3;
    int initX = 0;
    int initY = 0;

    painter->save();
    QFont font = painter->font();
    font.setPixelSize(height / 3);
    painter->setFont(font);
    painter->setPen(background);
    painter->setBrush(Qt::NoBrush);

    //绘制上部分文字
    for (int i = 0; i < maxStep; i++) {
        QRect textRect(initX, initY, width, height);
        painter->drawText(textRect, Qt::AlignCenter, topInfo.at(i));
        initX += width;
    }

    //绘制下部分文字
    initX = 0;
    initY = this->height() / 3 * 2;

    for (int i = 0; i < maxStep; i++) {
        QRect textRect(initX, initY, width, height);

        if (i == 0) {
            painter->drawText(textRect, Qt::AlignCenter, bottomInfo.first());
        } else if (i == maxStep - 1) {
            painter->drawText(textRect, Qt::AlignCenter, bottomInfo.last());
        }

        initX += width;
    }

    painter->restore();
}

void NavProgressBar::drawCurrentBg_ZFB(QPainter *painter)
{
    painter->save();

    //圆半径为高度一定比例,计算宽度,将宽度等分
    int width = this->width() / maxStep;
    int height = this->height() / 3;
    int radius = height / 3;
    int initX = 0;
    int initY = this->height() / 2;

    //绘制当前圆
    initX = width / 2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(currentBackground);

    for (int i = 0; i < currentStep - 1; i++) {
        initX += width;
    }

    painter->drawEllipse(QPoint(initX, initY), radius, radius);


    initX = initX - width / 4;
    initY = 0;
    height = this->height() / 4;

    //绘制当前上部提示信息背景
    QRect bgRect(initX, initY, width / 2, height);
    painter->setBrush(currentBackground);
    painter->drawRoundedRect(bgRect, height / 2, height / 2);

    //绘制当前上部提示信息
    QFont font = painter->font();
    font.setPixelSize((double)height / 1.6);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(currentForeground);
    painter->drawText(bgRect, Qt::AlignCenter, topInfo.at(currentStep - 1));

    //绘制倒三角
    int centerX = initX + width / 4;
    int offset = 10;
    QPolygon pts;
    pts.append(QPoint(centerX - offset, height));
    pts.append(QPoint(centerX + offset, height));
    pts.append(QPoint(centerX, height + offset));

    painter->setPen(Qt::NoPen);
    painter->drawPolygon(pts);

    painter->restore();
}*/


int NavProgressBar::getMaxStep() const
{
    return this->maxStep;
}

int NavProgressBar::getCurrentStep() const
{
    return this->currentStep;
}

QColor NavProgressBar::getBackground() const
{
    return this->background;
}

QColor NavProgressBar::getForeground() const
{
    return this->foreground;
}

QColor NavProgressBar::getCurrentBackground() const
{
    return this->currentBackground;
}

QColor NavProgressBar::getCurrentForeground() const
{
    return this->currentForeground;
}

QSize NavProgressBar::sizeHint() const
{
    return QSize(500, 80);
}

QSize NavProgressBar::minimumSizeHint() const
{
    return QSize(50, 20);
}

/*void NavProgressBar::setMaxStep(int maxStep)
{
    if (this->maxStep != maxStep && maxStep <= topInfo.count()) {
        this->maxStep = maxStep;
        update();
    }
}*/

void NavProgressBar::setCurrentStep(int currentStep)
{
    if (this->currentStep != currentStep && currentStep <= maxStep && currentStep > 0) {
        this->currentStep = currentStep;
        update();
    }
}

void NavProgressBar::setBackground(QColor background)
{
    if (this->background != background) {
        this->background = background;
        update();
    }
}

void NavProgressBar::setForeground(QColor foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        update();
    }
}

void NavProgressBar::setCurrentBackground(QColor currentBackground)
{
    if (this->currentBackground != currentBackground) {
        this->currentBackground = currentBackground;
        update();
    }
}

void NavProgressBar::setCurrentForeground(QColor currentForeground)
{
    if (this->currentForeground != currentForeground) {
        this->currentForeground = currentForeground;
        update();
    }
}
