#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setActionsForButton();

    void createSelectionMenu();

private slots:

    void on_actioninit_triggered();

    void on_action_clean_triggered();

    void on_chkBoxListEditable_clicked(bool checked);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_action_insert_triggered();

    void on_action_add_triggered();

    void on_action_delete_triggered();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_action_SelAll_triggered();

    void on_action_SelNone_triggered();

    void on_action_SelInvs_triggered();

    void on_tBtnSortAsc_clicked();

    void on_tBtnSortDes_clicked();

    void on_chkBoxSorting_clicked(bool checked);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemEntered(QListWidgetItem *item);

    void on_listWidget_itemPressed(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_tBtnClearText_clicked();

    void on_tBtnAddLine_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_action_exit_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
