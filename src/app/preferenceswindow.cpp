#include "preferenceswindow.h"

#if QT_VERSION >= 0x050000
#include <QtWidgets/QAction>
#include <QtWidgets/QVBoxLayout>
#else
#include <QtGui/QAction>
#include <QtGui/QVBoxLayout>
#endif

#include <ImageView/PreferencesWidget>

using namespace ImageViewer;

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new PreferencesWidget(this));
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QAction *closeAction = new QAction(this);
    closeAction->setShortcut(QKeySequence("Ctrl+W"));
    connect(closeAction, SIGNAL(triggered()), SLOT(close()));
    addAction(closeAction);

    setWindowIcon(QIcon(":/icons/qimageviewer.png"));
    setWindowTitle(tr("Preferences"));
}
