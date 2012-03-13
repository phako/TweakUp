/*
    This file is part of TweakUp.

    Copyright (C) 2012 Jens Georg <mail+tweakup@jensge.org>

    TweakUp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TweakUp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TweakUp.  If not, see <http://www.gnu.org/licenses/>.
*/

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
