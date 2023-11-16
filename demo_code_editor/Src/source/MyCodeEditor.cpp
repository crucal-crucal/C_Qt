#include "Src/include/MyCodeEditor.h"

#include "Src/include/MyHighlighter.h"

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit{parent} {
  lineNumberWidget = new LineNumberWidget(this);
  this->initFont();
  this->highlightCurrentLine();
  this->initConnection();
  this->initHighlighter();
  this->updateLineNumberWidgetWidth();
}

MyCodeEditor::~MyCodeEditor() { delete lineNumberWidget; }

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QPainter painter(lineNumberWidget);
  // 绘制行号区域
  painter.fillRect(event->rect(), QColor(100, 100, 100, 20));

  // 拿到 block
  QTextBlock block = this->firstVisibleBlock();
  // 拿到行号
  int blockNumber = block.blockNumber();
  // 拿到当前的 block 的 top
  int cursorTop = this->blockBoundingGeometry(this->textCursor().block())
                      .translated(this->contentOffset())
                      .top();
  // 拿到 block 的 top
  int top = this->blockBoundingGeometry(block)
                .translated(this->contentOffset())
                .top();

  int bottom = top + this->blockBoundingRect(block).height();

  while (block.isValid() && top <= event->rect().bottom()) {
    // 绘制画笔颜色
      painter.setPen(cursorTop == top ? Qt::black : Qt::gray);
    // 绘制文字
    painter.drawText(0, top, this->getLineNumberWidgetWidth(), bottom - top,
                     Qt::AlignRight, QString::number(blockNumber + 1));

    // 拿到下一个 block
    block = block.next();
    top = bottom;
    bottom = top + this->blockBoundingRect(block).height();
    blockNumber++;
  }
}

void MyCodeEditor::highlightCurrentLine() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QList<QTextEdit::ExtraSelection> extraSelections;

  QTextEdit::ExtraSelection selection;
  selection.format.setBackground(QColor(0, 100, 100, 20));
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = this->textCursor();

  extraSelections.append(selection);

  this->setExtraSelections(extraSelections);
}

void MyCodeEditor::updateLineNumberWidget(const QRect &rect, int dy) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  if (dy) {
    lineNumberWidget->scroll(0, dy);
  } else {
    lineNumberWidget->update(0, rect.y(), this->getLineNumberWidgetWidth(),
                             rect.height());
  }
}

void MyCodeEditor::updateLineNumberWidgetWidth() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 设置边距
  this->setViewportMargins(this->getLineNumberWidgetWidth(), 0, 0, 0);
}

void MyCodeEditor::initFont() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->setFont(QFont("Consolas", 14));
}

void MyCodeEditor::initConnection() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // cursor
  connect(this, &QPlainTextEdit::cursorPositionChanged, this,
          &MyCodeEditor::highlightCurrentLine, Qt::UniqueConnection);
  // blockCount
  connect(this, &QPlainTextEdit::blockCountChanged, this,
          &MyCodeEditor::updateLineNumberWidgetWidth, Qt::UniqueConnection);
  // updateRequest
  connect(this, &QPlainTextEdit::updateRequest, this,
          &MyCodeEditor::updateLineNumberWidget, Qt::UniqueConnection);
}

void MyCodeEditor::initHighlighter() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  new MyHighlighter(this->document());
}

int MyCodeEditor::getLineNumberWidgetWidth() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取宽度
  int t = this->fontMetrics().horizontalAdvance(QChar('0'));
  return 8 + QString::number(this->blockCount() + 1).size() * t;
}

void MyCodeEditor::resizeEvent(QResizeEvent *event) {
  QPlainTextEdit::resizeEvent(event);
  lineNumberWidget->setGeometry(0, 0, this->getLineNumberWidgetWidth(),
                                this->contentsRect().height());
}
