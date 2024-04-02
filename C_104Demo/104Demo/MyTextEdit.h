#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QDebug>
#include <QObject>
#include <QTextEdit>
#include <QTimer>

class MyTextEdit : public QTextEdit {
    Q_OBJECT
  public:
    explicit MyTextEdit(QObject* parent = nullptr);

  signals:
    void manualTextChanged();

  protected slots:
    void handleTextChanged();
    void checkIfTextChanged();

  private:
    QTimer* timer;
};

#endif  // MYTEXTEDIT_H
