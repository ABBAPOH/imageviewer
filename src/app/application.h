#ifndef APPLICATION_H
#define APPLICATION_H

#include <qglobal.h>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <qtsingleapplication.h>
#endif

namespace ImageViewer {

#if QT_VERSION >= 0x050000
class Application : public QApplication
#else
class Application : public QtSingleApplication
#endif
{
    Q_OBJECT
public:
    explicit Application(const QString &id, int &argc, char **argv);

    void handleArguments(const QStringList &arguments);

    bool restoreSession();
    void storeSession();

    void loadSettings();
    void saveSettings();

protected slots:
    void handleMessage(const QString &message);
    void onAboutToQuit();

protected:
    bool notify(QObject *object, QEvent *event);

    QByteArray saveSession() const;
    bool restoreSession(const QByteArray &state);
};

} // namespace ImageViewer

#endif // APPLICATION_H
