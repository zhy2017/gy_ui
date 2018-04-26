#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
#include <QEventLoop>
#include "type.h"

namespace Ui {
class LineWidget;
}


class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(QVector<Line> data, QWidget *parent = 0);
    ~LineWidget();

    QVector<Line>  static showMyMessageBox(QWidget* parent, QVector<Line> value);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

    QVector<Line> exec();

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void handle_remove();
    void handle_edit(struct Line);

private:
    Ui::LineWidget *ui;
    void addLineTableData(struct Line item);
    void initWidget();
    QEventLoop* m_eventLoop;
    QVector<Line> m_data;
};

#endif // LINEWIDGET_H
