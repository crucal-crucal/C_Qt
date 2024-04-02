#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QLabel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createItemsARow(int rowNo,QString name,QString sex,QDate birth,QString nation,bool isPM,int score);
    void init();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnSetRows_clicked();

    void on_btnIniData_clicked();

    void on_chkBoxTabEditable_clicked(bool checked);

    void on_chkBoxHeaderH_clicked(bool checked);

    void on_chkBoxHeaderV_clicked(bool checked);

    void on_chkBoxRowColor_clicked(bool checked);

    void on_rBtnSelectItem_clicked();

    void on_rBtnSelectRow_clicked();

    void on_btnReadToEdit_clicked();

    void on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_btnAutoHeght_clicked();

    void on_btnAutoWidth_clicked();

private:
    Ui::MainWindow *ui;

private:
    //  自定义单元格Type的类型，在创建单元格的Item时使用
    enum    CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore}; //各单元格的类型

    //  各字段在表格中的列号
    enum    FieldColNum{colName=0, colSex,colBirth,colNation,colScore,colPartyM};

    QLabel *labCellIndex, *labCellType, *labStudID;

};
#endif // MAINWINDOW_H
