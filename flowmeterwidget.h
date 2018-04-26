#ifndef FLOWMETERWIDGET_H
#define FLOWMETERWIDGET_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class FlowMeterWidget;
}

class FlowMeterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlowMeterWidget(QWidget *parent = 0);
    ~FlowMeterWidget();

    QString static showMyMessageBox(QWidget* parent, QString value);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::FlowMeterWidget *ui;
    QEventLoop* m_eventLoop;
    QString exec();
    QString m_resultStr;
    void initStyle();
};

#endif // FLOWMETERWIDGET_H
