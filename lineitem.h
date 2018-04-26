#ifndef LINEITEM_H
#define LINEITEM_H

#include <QWidget>

class QPushButton;

class LineItem : public QWidget
{
    Q_OBJECT
public:
    explicit LineItem(int row, QWidget *parent = nullptr);

public:
    QPushButton* btn1;
    QPushButton* btn2;

signals:
    void signalRemoveAccount();
    void signalEditAccount();


private:
    int m_row;
    void initWidget();
};

#endif // LINEITEM_H
