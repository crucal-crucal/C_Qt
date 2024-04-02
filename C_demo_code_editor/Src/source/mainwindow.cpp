#include "Src/include/mainwindow.h"

#include "qaction.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->init();
  m_Settings =
      std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);

  this->initMenu();
  this->initFont();
  this->initAction();
#if !QT_CONFIG(printer)
  ui->action_print->setEnabled(false);
#endif
}

MainWindow::~MainWindow() { delete ui; }

QList<QString> MainWindow::getHistory() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 打开开始读入
  int size = m_Settings.get()->beginReadArray("history");

  QList<QString> list;
  for (int i = 0; i < size; i++) {
    m_Settings.get()->setArrayIndex(i);
    list.append(m_Settings.get()->value("path").toString());
  }

  // 关闭读入
  m_Settings.get()->endArray();

  return list;
}

void MainWindow::saveHistory(QString path) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取历史
  QList<QString> list = getHistory();
  list.append(path);
  QSet<QString> set(list.begin(), list.end());
  QList<QString> uniqueList(set.begin(), set.end());
  // 打开开始写入
  m_Settings.get()->beginWriteArray("history");
  for (int i = 0; i < uniqueList.size(); i++) {
    m_Settings.get()->setArrayIndex(i);
    // 保存字符串
    m_Settings.get()->setValue("path", uniqueList[i]);
  }
  // 关闭开始写入
  m_Settings.get()->endArray();
}

void MainWindow::createTab(QString fileName) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法打开此文件:" + file.errorString());
    return;
  }
  this->setWindowTitle(fileName);

  QTextStream in(&file);
  QString text = in.readAll();
  MyCodeEditor *codeEditor =
      new MyCodeEditor(this, QFont(mfontFamily, mfontSize));
  codeEditor->setPlainText(text);
  codeEditor->setFileName(fileName);

  ui->tabWidget->addTab(codeEditor, fileName);
  ui->tabWidget->setCurrentWidget(codeEditor);

  file.close();

  this->saveHistory(fileName);
  this->initMenu();
  this->initAction();
}

void MainWindow::closeEvent(QCloseEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  if (ui->tabWidget->count() > 0) {
    QMessageBox::StandardButton btn =
        QMessageBox::question(this, "警告", "有未保存的文件，确定要退出吗",
                              QMessageBox::Yes | QMessageBox::No);
    btn == QMessageBox::Yes ? event->accept() : event->ignore();
  }
}

void MainWindow::init() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->setWindowTitle("CodeEditor");
  this->setWindowIcon(QIcon(":/images/pencil.png"));
  this->setCentralWidget(ui->tabWidget);

  {
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::about,
            Qt::UniqueConnection);
    connect(ui->action_print, &QAction::triggered, this, &MainWindow::print,
            Qt::UniqueConnection);
    connect(ui->action_copy, &QAction::triggered, this, &MainWindow::copy,
            Qt::UniqueConnection);
    connect(ui->action_cut, &QAction::triggered, this, &MainWindow::cut,
            Qt::UniqueConnection);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::exit,
            Qt::UniqueConnection);
    connect(ui->action_font, &QAction::triggered, this, &MainWindow::font,
            Qt::UniqueConnection);
    connect(ui->action_new, &QAction::triggered, this, &MainWindow::newFile,
            Qt::UniqueConnection);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::openFile,
            Qt::UniqueConnection);
    connect(ui->action_paste, &QAction::triggered, this, &MainWindow::paste,
            Qt::UniqueConnection);
    connect(ui->action_undo, &QAction::triggered, this, &MainWindow::undo,
            Qt::UniqueConnection);
    connect(ui->action_save_as, &QAction::triggered, this,
            &MainWindow::saveAsFile, Qt::UniqueConnection);
    connect(ui->action_redo, &QAction::triggered, this, &MainWindow::redo,
            Qt::UniqueConnection);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::saveFile,
            Qt::UniqueConnection);
  }
}

void MainWindow::saveSuccessAction(MyCodeEditor *codeEditor) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName = codeEditor->getFileName();
  // 保存历史
  this->saveHistory(fileName);
  // 设置 tab 标题
  ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), fileName);
  // 初始化菜单
  this->initMenu();
}

void MainWindow::newFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif

#ifdef NOUI
#if NOUI == 1
  MyTextEditByCode *myEdit = new MyTextEditByCode(this);
#else
  MyCodeEditor *myEdit = new MyCodeEditor(this, QFont(mfontFamily, mfontSize));
#endif
#else
  MyTextEdit *myEdit = new MyTextEdit(this);
#endif
  ui->tabWidget->addTab(myEdit, "NewTab");
  this->initAction();
}

void MainWindow::openFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->createTab(QFileDialog::getOpenFileName(this, "打开文件"));
}

void MainWindow::openRecentFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取发送者
  QAction *action = static_cast<QAction *>(this->sender());
  this->createTab(action->text());
}

void MainWindow::saveFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 把保存交给 CodeEditor
  auto codeEditor = this->getCodeEditor();
  if (codeEditor != nullptr) {
    if (codeEditor->saveFile()) {
      this->saveSuccessAction(codeEditor);
    }
  }
}

void MainWindow::saveAsFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 把保存交给 CodeEditor
  auto codeEditor = this->getCodeEditor();
  if (codeEditor != nullptr) {
    if (codeEditor->saveAsFile()) {
      this->saveSuccessAction(codeEditor);
    }
  }
}

void MainWindow::print() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 把打印交给 codeEditor
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    // 如果用户在打印对话框中点击了 Cancel
    if (dialog.exec() == QDialog::Rejected) {
      return;
    }
#endif
    codeEditor->print(&printDev);
#endif
  }
}

void MainWindow::font() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  bool fontSelected;
  QFont font =
      QFontDialog::getFont(&fontSelected, QFont(mfontFamily, mfontSize), this);
  if (fontSelected) {
    auto codeEditor = this->getCodeEditor();
    if (codeEditor) {
      codeEditor->setAllFont(font);
    }
    m_Settings.get()->beginWriteArray("font");
    m_Settings.get()->setValue("font_family", font.family());
    m_Settings.get()->setValue("font_size", font.pointSize());
    m_Settings.get()->endArray();
  }
}

void MainWindow::copy() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
    codeEditor->copy();
  }
}

void MainWindow::paste() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
    codeEditor->paste();
  }
}

void MainWindow::cut() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
    codeEditor->cut();
  }
}

void MainWindow::undo() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
    codeEditor->undo();
  }
}

void MainWindow::redo() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (codeEditor) {
    codeEditor->redo();
  }
}

void MainWindow::exit() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QCoreApplication::exit();
}

void MainWindow::about() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QMessageBox::about(this, "这是我的 Notepad...",
                     "这是我的 Notepad，欢迎使用...");
}

void MainWindow::clearHistory() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  m_Settings.get()->remove("history");
  this->initMenu();
}

MyCodeEditor *MainWindow::getCodeEditor() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  MyCodeEditor *codeEditor =
      static_cast<MyCodeEditor *>(ui->tabWidget->currentWidget());
  if (codeEditor) {
    return codeEditor;
  }
  return nullptr;
}

void MainWindow::initMenu() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QMenu *recent = this->findChild<QMenu *>("recent");
  auto arr = recent->children().toVector();
  QSet<QObject *> set(arr.begin(), arr.end());
  foreach (QObject *ch, set) {
    QAction *action = static_cast<QAction *>(ch);
    recent->removeAction(action);
  }

  QList<QString> list = getHistory();

  for (int i = list.size() - 1; i >= 0; i--) {
    recent->addAction(list[i], this, &MainWindow::openRecentFile);
  }
  if (list.size()) {
    recent->addAction("清除历史记录", this, &MainWindow::clearHistory,
                      QKeySequence("Ctrl+Alt+Shift+C"));
  }
}

void MainWindow::initFont() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mfontFamily = m_Settings.get()->value("font_family", "Consolas").toString();
  mfontSize = m_Settings.get()->value("font_size", 14).toInt();
}

void MainWindow::initAction() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  bool t = ui->tabWidget->count() > 0;
  ui->action_save->setEnabled(t);
  ui->action_save_as->setEnabled(t);
  ui->action_copy->setEnabled(t);
  ui->action_cut->setEnabled(t);
  ui->action_paste->setEnabled(t);
  ui->action_undo->setEnabled(t);
  ui->action_redo->setEnabled(t);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  auto codeEditor = this->getCodeEditor();
  if (!codeEditor->checkSaved()) {
    QMessageBox::StandardButton btn = QMessageBox::question(
        this, "警告", "您还没有保存文档...，是否保存",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (btn == QMessageBox::Yes) {
      if (codeEditor->saveFile()) {
        this->saveSuccessAction(codeEditor);
      }
      return;
    } else if (btn == QMessageBox::Cancel) {
      return;
    }
  }
  ui->tabWidget->removeTab(index);
  delete codeEditor;
  this->initAction();
}
