#ifndef VEDIOADDWIDGET_H
#define VEDIOADDWIDGET_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class VedioAddWidget;
}

class VedioAddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VedioAddWidget(QWidget *parent = 0);
    ~VedioAddWidget();

    QString static showMyMessageBox(QWidget* parent, QString value);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

private:
    void loadStyleSheet(const QString &sheetName);

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::VedioAddWidget *ui;
    QEventLoop* m_eventLoop;
    QString exec();
    QString m_resultStr;
    void initStyle();
};

#endif // VEDIOADDWIDGET_H
