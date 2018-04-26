#ifndef SECTIONWIDGET_H
#define SECTIONWIDGET_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class SectionWidget;
}

class SectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SectionWidget(QVector<QPointF> &data, QWidget *parent = 0);
    ~SectionWidget();

    QVector<QPointF> static showMyMessageBox(QWidget* parent, QVector<QPointF> &data);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

    QVector<QPointF> exec();

signals:
    void chanLine(QVector<QPointF> data);

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void onRemoveAccount(int index);
    void onEditAccountInfo(int index);

    void on_allSelectBtn_clicked();

    void on_addBtn_clicked();

    void on_changeBtn_clicked();

private:
    Ui::SectionWidget *ui;
    QEventLoop* m_eventLoop;
    QString m_resultStr;
    QVector<QPointF> m_data;
    void initStyle();
};

#endif // SECTIONWIDGET_H
