#include <QDebug>

#include "focuseventfilter.h"
#include "rygelsettings.h"

FocusEventFilter::FocusEventFilter(RygelSettings *settings, QObject *parent)
  : QObject(parent)
  , m_settings(settings)
{
}

bool FocusEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusOut) {
        m_settings->restart();
    }

    return QObject::eventFilter(obj, event);
}
