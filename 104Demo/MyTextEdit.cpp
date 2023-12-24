#include "MyTextEdit.h"

#include "qdebug.h"

MyTextEdit::MyTextEdit(QObject* parent)
    : QTextEdit{dynamic_cast<QWidget*>(parent)} {
  connect(this, &QTextEdit::textChanged, this, &MyTextEdit::handleTextChanged,
          Qt::UniqueConnection);
  timer = new QTimer(this);
  timer->setSingleShot(true);
  connect(timer, &QTimer::timeout, this, &MyTextEdit::checkIfTextChanged,
          Qt::UniqueConnection);
}

void MyTextEdit::handleTextChanged() {
  if (timer) {
    timer->start(100);
  } else {
    qDebug() << "timer is Empty!";
  }
}

void MyTextEdit::checkIfTextChanged() {
  if (this->document()->isModified()) {
    emit manualTextChanged();
    this->document()->setModified(false);
  }
}
