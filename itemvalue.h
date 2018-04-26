#ifndef ITEMVALUE_H
#define ITEMVALUE_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class itemvalue;
}

class itemvalue : public QWidget
{
    Q_OBJECT

public:
    explicit itemvalue(QWidget *parent = 0, QString value = NULL);
    ~itemvalue();

    QString static showMyMessageBox(QWidget* parent, QString value);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::itemvalue *ui;
    QEventLoop* m_eventLoop;
    QString exec();
    QString m_resultStr;
    void initStyle();
};

#endif // ITEMVALUE_H
