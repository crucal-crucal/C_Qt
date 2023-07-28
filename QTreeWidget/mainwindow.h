#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QTreeWidgetItem>
#include <QSpinBox>
#include <QFileDialog>
#include <QFileInfo>
#include <type_traits>
#include <QToolTip>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildTreeHeader();

    void iniTree();

    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);

    QString getFinalFolderName(const QString &fullPathName);

    void addImageItem(QTreeWidgetItem *parItem, QString aFilename);

    void displayImage(QTreeWidgetItem *item);

    void changeItemCaption(QTreeWidgetItem *item);

    void deleteItem(QTreeWidgetItem *parItem, QTreeWidgetItem *item);

    void setactionToolTip();

    void connectActions();

protected:
    void eventFilter(QEvent* event);

    void leaveEvent(QEvent* event);

private slots:
    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomFitW_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomRealSize_triggered();

    void on_actDeleteItem_triggered();

    void on_actScanItems_triggered();

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_actDockVisible_triggered(bool checked);

    void on_actDockFloat_triggered(bool checked);

    void on_treeFiles_itemChanged(QTreeWidgetItem *item, int column);

    void on_treeFiles_itemCollapsed(QTreeWidgetItem *item);

    void on_treeFiles_itemExpanded(QTreeWidgetItem *item);

    void on_treeFiles_itemSelectionChanged();

    void on_treeFiles_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeFiles_itemPressed(QTreeWidgetItem *item, int column);

    void on_exit_triggered();

    void updateStatusbarText();

    void clearStatusbarText();

private:
    Ui::MainWindow *ui;

private:
    enum{
        itTopItem, itGroupItem, itImageItem
    };
    enum{
        colItem, colItemType, colDate
    };
    QPixmap m_pixmap;
    QLabel *labNodeText, *labFileName;
    QSpinBox *spinRatio;
    float m_ratio;
    bool isfloating, isdocked;
    QString ActionName = "节点标题";
};
#endif // MAINWINDOW_H
