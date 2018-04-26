#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class SetWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mainBtn_clicked();
    void on_tabelBtn_clicked();
    void on_setBtn_clicked();
    void on_homeBtn_clicked();
    void currentItemChanged(int index, const QString &item);

private:
    Ui::MainWindow *ui;
    void init();
    SetWidget *m_setWidget;
};

#endif // MAINWINDOW_H
