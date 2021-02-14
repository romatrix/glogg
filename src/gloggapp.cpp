/*
 * Copyright (C) 2017 Nicolas Bonnefon and other contributors
 *
 * This file is part of glogg.
 *
 * glogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gloggapp.h"

#include <QFileOpenEvent>
#include <iostream>
#include <QDialog>

#ifdef __APPLE__
bool GloggApp::event( QEvent *event )
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
        emit loadFile( openEvent->file() );
    }

    return QApplication::event(event);
}
#endif

bool GloggApp::notify(QObject *o, QEvent *e)
{
    if(o->inherits("QDialog") and e->type() == QEvent::Type::Close){
        //cout << "show: " <<  << "\n";
        QDialog* dlg = ((QDialog*)o);
        //dlg->setWindowTitle("Tada");
        mw_->onHideDialog(dlg->windowTitle().toStdString());
    }
    return QApplication::notify(o, e);
}
