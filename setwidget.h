#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>
#include <QMap>

namespace Ui {
class SetWidget;
}

class SectionItem;

class SetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetWidget(QWidget *parent = 0);
    ~SetWidget();

private slots:
    void currentItemChanged(int index);
    void vedioEditBtnHandel();
    void vedioDeleteBtnHandel();
    void on_vedioAddBtn_clicked();
    void on_meterDeleteBtn_clicked();
    void on_meterAddBtn_clicked();
    void meterEditBtnHandel();
    void meterDefaultBtnHandel();
    void meterDeleteBtnHandel();
    void waterMeterSet();
    void waterMeterDefault();
    void on_infoAddBtn_clicked();
    void on_infoDel1Btn_clicked();
    void on_infoDel2Btn_clicked();
    void on_infoDel3Btn_clicked();
    void on_sectionAddBtn_clicked();
    void sectionEnableBtn();
    void sectionImportBtn();
    void sectionExportBtn();
    void sectionAddDataBtn();
    void sectionEditBtn();
    void sectionLineBtn();
    void sectionDeleteBtn();
    void receiveLineData(QVector<QPointF> data);

private:
    Ui::SetWidget *ui;
    QMap<int, QString> m_map;
    QVector<QString> m_sectionData;
    SectionItem* currentWid;
    void initWidget();
    void initTabel();
    void addVedioTableData(QString value);
    void addMeterTableData(QString value);
    void addWaterMeterTableData(QString value);
    void addSectionTableData(QString value);
};

#endif // SETWIDGET_H
