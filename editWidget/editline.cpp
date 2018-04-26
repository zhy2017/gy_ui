#include "editline.h"
#include "ui_editline.h"

EditLine::EditLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditLine)
{
    ui->setupUi(this);
}

EditLine::~EditLine()
{
    delete ui;
}
