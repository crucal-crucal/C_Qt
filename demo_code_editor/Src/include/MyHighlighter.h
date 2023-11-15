#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

// #define NDEBUG

#include <qglobal.h>

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QSyntaxHighlighter>

class MyHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
 public:
  explicit MyHighlighter(QTextDocument *parent = nullptr,
                         QString fontFamily = "Consolas", int fontSize = 14);
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void setFormats();

 signals:

  // QSyntaxHighlighter interface
 protected:
  void highlightBlock(const QString &text);

 private:
  QString mFontFamily;
  int mFontSize;

  struct HighlightRule {
    QRegExp pattern;
    QTextCharFormat format;
  };

  QVector<HighlightRule> highlightRules;

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void addNormalTextFormat();
  void addNumberFormat();
  void addStringFormat();
  void addCommentFormat();
  void addKeywordsFormat();
  void addClassNameFormat();
  void addFunctionFormat();

  // 多行注释
  void addMultiLineCommentFormat(const QString &text);
};

#endif  // MYHIGHLIGHTER_H
