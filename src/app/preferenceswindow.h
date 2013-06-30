#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QtCore/qglobal.h>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace ImageViewer {

class PreferencesWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PreferencesWindow(QWidget *parent = 0);
};

} // namespace ImageViewer

#endif // PREFERENCESWINDOW_H
