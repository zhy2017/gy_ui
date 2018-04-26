#pragma execution_character_set("utf-8")

#include "curvechart.h"
#include "qpainter.h"
#include "qdebug.h"

CurveChart::CurveChart(QWidget *parent) : QWidget(parent)
{
    minXValue = 988;
    maxXValue = 1002;
    minYValue = 0;
    maxYValue = 58.8;
    xStep = 7;
    yStep = 6;
    waterLevel = 992;

    sectionData.clear();
    sectionData.append(QPointF(0, 998.28));
    sectionData.append(QPointF(0.01, 992.63));
    sectionData.append(QPointF(2.3, 992.59));
    sectionData.append(QPointF(7.7, 990.67));
    sectionData.append(QPointF(9.9, 990.3));
    sectionData.append(QPointF(11, 989.97));
    sectionData.append(QPointF(13, 989.76));
    sectionData.append(QPointF(15, 989.88));
    sectionData.append(QPointF(17, 989.48));
    sectionData.append(QPointF(19, 989.67));
    sectionData.append(QPointF(21, 989.3));
    sectionData.append(QPointF(23, 989.39));
    sectionData.append(QPointF(25, 989.41));
    sectionData.append(QPointF(27, 989.43));
    sectionData.append(QPointF(29, 989.42));
    sectionData.append(QPointF(31, 989.83));
    sectionData.append(QPointF(33, 989.67));
    sectionData.append(QPointF(35, 989.69));
    sectionData.append(QPointF(38, 989.97));
    sectionData.append(QPointF(39.9, 990.49));
    sectionData.append(QPointF(42, 991.93));
    sectionData.append(QPointF(46.7, 992.3));
    sectionData.append(QPointF(52, 993.43));
    sectionData.append(QPointF(55.9, 997.86));
    sectionData.append(QPointF(58.6, 1000.49));
    sectionData.append(QPointF(58.6, 989.3));
    sectionData.append(QPointF(0, 989.3));
    sectionData.append(QPointF(0, 998.28));

    startPoint.setX(2);
    startPoint.setY(1000);

    endPoint.setX(56);
    endPoint.setY(1000);

    control1Point.setX(15);
    control1Point.setY(999);

    control2Point.setX(30);
    control2Point.setY(999);

    fishStartPoint.setX(44);
    fishStartPoint.setY(startPoint.y());

    fishEndPoint.setX(44);
    fishEndPoint.setY(996);

    radius = 5;

    borderStartPoint.setX(1);
    borderStartPoint.setY(999);

    borderEndPoint.setX(56);
    borderEndPoint.setY(989.5);

   // lineData.append(11);
   // lineData.append(13);
   // lineData.append(17);
   // lineData.append(19);
   // lineData.append(52);
    lineData.insert(11, 6);
    lineData.insert(13, 6);
    lineData.insert(17, 6);
    lineData.insert(19, 6);

    space = 50;
    title = "曲线图";
    showHLine = false;
    showPoint = true;
    showPointBg = true;
    showFish = true;
    showLine = true;

    bgColorStart = QColor(255, 255, 255);
    bgColorEnd = QColor(255, 255, 255);
    textColor = QColor(0, 0, 0);
    pointColor = QColor(38, 114, 179);
}

void CurveChart::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制盒子
    drawBox(&painter);
    //绘制文字
    drawText(&painter);
    //绘制水位
    drawWater(&painter);
    //绘制测流垂线
    if(showLine)
    {
        drawLine(&painter);
    }
    //绘制断面
    drawSection(&painter);
    //绘制铅鱼
    if(showFish)
    {
        drawFish(&painter);
    }
    //绘制缆道
    drawCableway(&painter);
    //绘制周界
    drawBorder(&painter);
    //绘制标题
    drawTitle(&painter);
    //绘制数据点
    drawPoint(&painter);
}

void CurveChart::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient topGradient(rect().topLeft(), rect().bottomLeft());
    topGradient.setColorAt(0.0, bgColorStart);
    topGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(topGradient);
    painter->drawRect(rect());
    painter->restore();
}

void CurveChart::drawBox(QPainter *painter)
{
    painter->save();

    QPointF topLeftPot(space, space);
    QPointF bottomRightPot(width() - space / 2, height() - space / 2);
    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    pointRect = QRectF(topLeftPot, bottomRightPot);
  //  painter->drawRect(pointRect);
    painter->drawLine(pointRect.topLeft(), pointRect.bottomLeft());
    painter->drawLine(pointRect.bottomLeft(), pointRect.bottomRight());

    //绘制横线
    if (showHLine) {
        QPen pen(textColor, 1, Qt::SolidLine);
        painter->setPen(pen);

        double increment = (double)pointRect.height() / xStep;
        double startY = pointRect.topLeft().y();

        double increment1 = (double)pointRect.width() / yStep;
        double startX = pointRect.topLeft().x();

        for (int i = 0; i < xStep - 1; i++)
        {
            startY += increment;
            QPointF leftPot(pointRect.topLeft().x(), startY);
            QPointF rightPot(pointRect.topRight().x(), startY);
            painter->drawLine(leftPot, rightPot);
        }

        for (int i = 0; i < yStep - 1; i++)
        {
            startX += increment1;
            QPointF leftPot(startX, pointRect.topLeft().y());
            QPointF rightPot(startX, pointRect.bottomRight().y());
            painter->drawLine(leftPot, rightPot);
        }
    }

    painter->restore();
}

void CurveChart::drawText(QPainter *painter)
{
    painter->save();

    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    double step = (maxXValue - minXValue) / xStep;
    double value = maxXValue;
    double increment = (double)pointRect.height() / xStep;
    double startY = pointRect.topLeft().y();
    QString strValue;

    for (int i = 0; i < xStep + 1; i++)
    {
        strValue = QString("%1").arg(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        QPointF textPot(pointRect.topLeft().x() - 5 - textWidth, startY + textHeight / 3);
        painter->drawText(textPot, strValue);
        value -= step;
        startY += increment;
    }

    step = (maxYValue - minYValue) / yStep;
    value = minYValue;
    increment = (double)pointRect.width() / yStep;
    double startX = pointRect.topLeft().x();
    for (int i = 0; i < yStep + 1; i++)
    {
        strValue = QString("%1").arg(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        QPointF textPot(startX - textWidth / 2, pointRect.bottomLeft().y() + textHeight + 5);
        painter->drawText(textPot, strValue);
        value += step;
        startX += increment;
    }

    painter->restore();
}

void CurveChart::drawWater(QPainter *painter)
{
    painter->save();
    QPointF realPoint1;
    QPointF realPoint2;
    double tmp1 = (double)pointRect.height() / (maxXValue - minXValue);
    double tmp2 = (double)pointRect.width() / (maxYValue - minYValue);
    realPoint1.setY(pointRect.topLeft().y() - (waterLevel - maxXValue) * tmp1);
    realPoint1.setX(pointRect.topLeft().x());
    realPoint2.setY(pointRect.topLeft().y() - (989.3 - maxXValue) * tmp1);
    realPoint2.setX((58.6 - 0) * tmp2 + pointRect.topLeft().x());
    QPainterPath path;
    //path.moveTo(realPoint1);
    path.addRect(QRectF(realPoint1, realPoint2));
    painter->setBrush(QColor(167, 210, 252));
    painter->drawPath(path);
    painter->restore();
}

void CurveChart::drawLine(QPainter *painter)
{
    painter->save();
    QPointF start;
    QPointF end;
    QPainterPath path;

    QMap<double, int>::iterator it;
    for(it = lineData.begin(); it != lineData.end(); ++it)
    {
        start.setX(it.key());
        start.setY((maxXValue - minXValue) / 2 + minXValue);
        end.setX(it.key());
        end.setY(minXValue);
        path.moveTo(conversionCoordinate(start));
        path.lineTo(conversionCoordinate(end));

        if(it.value() == 6)
        {
            double bottom;
            for(int i = 0; i < sectionData.size(); i++)
            {
                if(sectionData.at(i).x() == it.key())
                {
                    bottom = sectionData.at(i).y();
                    break;
                }
            }
            double depth = waterLevel - bottom;
            double center = depth *  0.6;
            QPointF centerPoint(it.key(), waterLevel - center);
            path.addEllipse(conversionCoordinate(centerPoint), 3, 3);
        }
    }

    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->fillPath(path, QColor(0, 0, 0));
    painter->restore();
}

void CurveChart::drawSection(QPainter *painter)
{
    painter->save();

    QPainterPath path;
    QPointF realPoint;
    QPen pen;

    double tmp1 = (double)pointRect.height() / (maxXValue - minXValue);
    double tmp2 = (double)pointRect.width() / (maxYValue - minYValue);
   // realPoint.y() = sectionData.at(0).y() - maxXValue + pointRect.topLeft().y();
    realPoint.setY(pointRect.topLeft().y() - (sectionData.at(0).y() - maxXValue) * tmp1);
    realPoint.setX((sectionData.at(0).x() - 0) * tmp2 + pointRect.topLeft().x());
    path.moveTo(realPoint);
    for(int i = 0; i < sectionData.size() - 1; i++)
    {
        realPoint.setY(pointRect.topLeft().y() - (sectionData.at(i + 1).y() - maxXValue) * tmp1);
        realPoint.setX((sectionData.at(i + 1).x() - 0) * tmp2 + pointRect.topLeft().x());
        path.lineTo(realPoint);
    }
    //path.setFillRule(Qt::OddEvenFill);
    painter->setRenderHint(QPainter::Antialiasing);//平滑直线
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(0);
    painter->setPen(pen);
    //painter->setPen(textColor);
    painter->setBrush(QColor(201, 167, 112));
    painter->drawPath(path);
    painter->restore();
}

void CurveChart::drawFish(QPainter *painter)
{
    painter->save();

    QPainterPath path;
    path.moveTo(conversionCoordinate(fishStartPoint));
    path.lineTo(conversionCoordinate(fishEndPoint));
    path.addEllipse(conversionCoordinate(fishEndPoint), radius, radius);

    painter->drawPath(path);
   // painter->setBrush(QColor(0, 0, 0));
    painter->fillPath(path, QColor(0, 0, 0));
    painter->restore();
}

void CurveChart::drawCableway(QPainter *painter)
{
    painter->save();

    QPainterPath path;
    path.moveTo(conversionCoordinate(startPoint));
    path.cubicTo(conversionCoordinate(control1Point), conversionCoordinate(control2Point), conversionCoordinate(endPoint));

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);//平滑直线
    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->restore();
}

void CurveChart::drawBorder(QPainter *painter)
{
    painter->save();
    QPainterPath path;
    path.addRect(QRectF(conversionCoordinate(borderStartPoint), conversionCoordinate(borderEndPoint)));

    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawPath(path);
    //path.addRect(QPointF());
    painter->restore();
}

void CurveChart::drawTitle(QPainter *painter)
{
    painter->save();

    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    double titleX = (double)width() / 2;
    double titleY = space;
    double textWidth = fontMetrics().width(title);
    double textHeight = fontMetrics().height();

    //标题加粗显示
    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(10);
    painter->setFont(titleFont);

    QPointF textPot(titleX - textWidth / 2, titleY / 2 + textHeight / 2);
    painter->drawText(textPot, title);

    painter->restore();
}

void CurveChart::drawPoint(QPainter *painter)
{
    painter->save();

    double startX = pointRect.topRight().x();
    QVector<QPointF> points;

    if (showPointBg) {
        points.push_back(QPointF(startX, pointRect.bottomRight().y()));
    }

    for (int i = 0; i < listData.count(); i++) {
        QPointF dataPot(startX, pointRect.bottomRight().y() - (double)listData.at(i) * (pointRect.height() / (maxXValue - minXValue)));
        points.push_back(dataPot);
        startX -= yStep;
    }

    if (showPointBg) {
        points.push_back(QPointF(startX, pointRect.bottomRight().y()));
    }

    //如果只有两个数据点不需要处理
    if (showPointBg && points.count() <= 2) {
        painter->restore();
        return;
    }

    painter->setPen(pointColor);

    if (showPointBg) {
        painter->setBrush(QColor(pointColor.red(), pointColor.green(), pointColor.blue(), 150));
        painter->drawPolygon(QPolygonF(points));
    } else {
        painter->setBrush(Qt::NoBrush);
        painter->drawPolyline(QPolygonF(points));
    }

    //绘制坐标点
    if (showPoint) {
        for (int i = 0; i < points.count(); i++) {
            QPointF dataPot = points.at(i);
            painter->setBrush(pointColor);
            painter->drawEllipse(dataPot, 3, 3);
        }
    }

    painter->restore();
}

void CurveChart::updateData()
{
    int count = pointRect.width() / yStep;
    int i = listData.count() - count;

    if (i > 0) {
        listData.remove(count, i);
    }

    update();
}

double CurveChart::getXMinValue() const
{
    return this->minXValue;
}

double CurveChart::getYMinValue() const
{
    return this->minYValue;
}

double CurveChart::getXMaxValue() const
{
    return this->maxXValue;
}

double CurveChart::getYMaxValue() const
{
    return this->maxYValue;
}

double CurveChart::getXStep() const
{
    return this->xStep;
}

double CurveChart::getYStep() const
{
    return this->yStep;
}

double CurveChart::getSpace() const
{
    return this->space;
}

QString CurveChart::getTitle() const
{
    return this->title;
}

bool CurveChart::getShowHLine() const
{
    return this->showHLine;
}

bool CurveChart::getShowPoint() const
{
    return this->showPoint;
}

bool CurveChart::getShowPointBg() const
{
    return this->showPointBg;
}

void CurveChart::setShowFish(bool value)
{
    showFish = value;
    update();
}

void CurveChart::setShowLine(bool value)
{
    showLine = value;
    update();
}

QColor CurveChart::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor CurveChart::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor CurveChart::getTextColor() const
{
    return this->textColor;
}

QColor CurveChart::getPointColor() const
{
    return this->pointColor;
}

QSize CurveChart::sizeHint() const
{
    return QSize(500, 300);
}

QSize CurveChart::minimumSizeHint() const
{
    return QSize(200, 70);
}

QPointF CurveChart::conversionCoordinate(QPointF point)
{
    QPointF realPoint;
    double tmp1 = (double)pointRect.height() / (maxXValue - minXValue);
    double tmp2 = (double)pointRect.width() / (maxYValue - minYValue);

    realPoint.setY(pointRect.topLeft().y() - (point.y() - maxXValue) * tmp1);
    realPoint.setX((point.x() - 0) * tmp2 + pointRect.topLeft().x());

    return realPoint;
}

void CurveChart::addData(double data)
{
    listData.push_front(data);
    updateData();
}

void CurveChart::setData(QVector<double> data)
{
    listData = data;
    updateData();
}

void CurveChart::clearData()
{
    listData.clear();
    update();
}

void CurveChart::addSectionData(QPointF data)
{
    sectionData.push_back(data);
    update();
}

void CurveChart::setSectionData(QVector<QPointF> data)
{
    sectionData = data;
    update();
}

void CurveChart::clearSectionData()
{
    sectionData.clear();
    update();
}

void CurveChart::addLineData(double key, int value)
{
    lineData.insert(key, value);
    update();
}

void CurveChart::setLineData(QMap<double, int> data)
{
    lineData = data;
    update();
}

void CurveChart::clearLineData()
{
    lineData.clear();
    update();
}

void CurveChart::setXMinValue(double minValue)
{
    if(this->minXValue != minValue)
    {
        this->minXValue = minValue;
        update();
    }
}

void CurveChart::setYMinValue(double minValue)
{
    if(this->minYValue != minValue)
    {
        this->minYValue = minValue;
        update();
    }
}

void CurveChart::setXMaxValue(double maxValue)
{
    if (this->maxXValue != maxValue)
    {
        this->maxXValue = maxValue;
        update();
    }
}

void CurveChart::setYMaxValue(double maxValue)
{
    if (this->maxYValue != maxValue)
    {
        this->maxYValue = maxValue;
        update();
    }
}

void CurveChart::setXStep(double xStep)
{
    if (this->xStep != xStep) {
        this->xStep = xStep;
        update();
    }
}

void CurveChart::setYStep(double yStep)
{
    if (this->yStep != yStep) {
        this->yStep = yStep;
        update();
    }
}

void CurveChart::setSpace(double space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void CurveChart::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        update();
    }
}

void CurveChart::setShowHLine(bool showHLine)
{
    if (this->showHLine != showHLine) {
        this->showHLine = showHLine;
        update();
    }
}

void CurveChart::setShowPoint(bool showPoint)
{
    if (this->showPoint != showPoint) {
        this->showPoint = showPoint;
        update();
    }
}

void CurveChart::setShowPointBg(bool showPointBg)
{
    if (this->showPointBg != showPointBg) {
        this->showPointBg = showPointBg;
        update();
    }
}

void CurveChart::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void CurveChart::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void CurveChart::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void CurveChart::setPointColor(const QColor &pointColor)
{
    if (this->pointColor != pointColor) {
        this->pointColor = pointColor;
        update();
    }
}

