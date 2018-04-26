#ifndef EDITSECTION_H
#define EDITSECTION_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class EditSection;
}

class EditSection : public QWidget
{
    Q_OBJECT

public:
    explicit EditSection(QString str, QWidget *parent = 0);
    ~EditSection();

    QString static showMyMessageBox(QWidget* parent, QString value);

public:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
        QString exec();

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::EditSection *ui;
    QEventLoop* m_eventLoop;
    QString m_resultStr;
    void initStyle();
};

#endif // EDITSECTION_H
