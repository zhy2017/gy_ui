#ifndef EDITLINE_H
#define EDITLINE_H

#include <QWidget>

namespace Ui {
class EditLine;
}

class EditLine : public QWidget
{
    Q_OBJECT

public:
    explicit EditLine(QWidget *parent = 0);
    ~EditLine();

private:
    Ui::EditLine *ui;
};

#endif // EDITLINE_H
