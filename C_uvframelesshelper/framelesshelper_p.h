#ifndef FRAMELESSHELPERPRIVATE_H
#define FRAMELESSHELPERPRIVATE_H

#include "qxframeless_global.h"
#include <QObject>
#include <QHash>

QX_FRAMELESS_BEGIN_NAMESPACE

class FramelessHelper;
class FramelessWidgetData;

class FramelessHelperPrivate : public QObject {
 Q_OBJECT
  QX_DECLARE_PUBLIC(FramelessHelper)
 public:
  explicit FramelessHelperPrivate(QObject *parent = nullptr);
  ~FramelessHelperPrivate() override;

  bool isCaptionClassName(const char *name);

 public:
  QHash<QWidget *, FramelessWidgetData *> m_widgetDataHash;
  QList<QString> m_captionClassNameList;
  bool m_bWidgetResizable{true};
  bool m_bWidgetMovable{true};
};

QX_FRAMELESS_END_NAMESPACE

#endif // FRAMELESSHELPERPRIVATE_H
