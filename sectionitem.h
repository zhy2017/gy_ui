#ifndef SECTIONITEM_H
#define SECTIONITEM_H

#include <QWidget>
#include "type.h"

class QPushButton;

class SectionItem : public QWidget
{
    Q_OBJECT
public:
    explicit SectionItem(int row, QWidget *parent = nullptr);

    void addSectionData(QPointF data);
    void clearSectionData();
    void setLineData(QVector<QPointF> data);
    QVector<QPointF> getSectionData();

public:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QVector<QPointF> m_sectionData;
    QVector<Line> m_lineData;

private:
    int m_row;
    void initWidget();
};

#endif // SECTIONITEM_H
