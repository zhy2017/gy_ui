#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>

class AccountItem : public QWidget
{
    Q_OBJECT
public:
    explicit AccountItem(QWidget *parent = NULL);

public:
    void setAccountInfo(int index, double x, double y);
    int getItemWidgetIndex();
    void setChecked(bool status);
    bool getChecked();
    QPointF getData();
    void setData(QPointF data);

signals:
    void signalRemoveAccount(int index);
    void signalEditAccount(int index);

public slots:
    void onRemoveAccount();
    void onEditAccount();

private:
    void initWidget();
    QCheckBox *m_checkBtn;
    QLabel *m_xLabel;
    QLabel *m_xValue;
    QLabel *m_yLabel;
    QLabel *m_yValue;
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;
    int m_index;
};

#endif // ACCOUNTITEM_H
