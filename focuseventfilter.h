#ifndef FOCUSEVENTFILTER_H
#define FOCUSEVENTFILTER_H

#include <QObject>
#include <QEvent>

class RygelSettings;

class FocusEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit FocusEventFilter(RygelSettings *settings, QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    RygelSettings *m_settings;
    
};

#endif // FOCUSEVENTFILTER_H
