#ifndef WIDGET_H
#define WIDGET_H

#include <QCheckBox>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Font;
    QHBoxLayout *horizontalLayout;
    QCheckBox *Xiahuaxian;
    QCheckBox *Xieti;
    QCheckBox *Cuti;
    QGroupBox *groupBox_Color;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Black;
    QRadioButton *Red;
    QRadioButton *Blue;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *Clear;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exit;
    QPushButton *confirm;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Xiahuaxian_clicked(bool checked);

    void on_Xieti_clicked(bool checked);

    void on_Cuti_clicked(bool checked);

    void on_Black_clicked();

    void on_Red_clicked();

    void on_Blue_clicked();

};
#endif // WIDGET_H
