#include <QDir>
#include <QLocale>
#include <QUrl>
#include <QTranslator>
#include <QMessageBox>

#include "application.h"
#include "mainwindow.h"

using namespace ImageViewer;

static QString getRootPath()
{
    // Figure out root:  Up one from 'bin' or 'MacOs'
    QDir rootDir = QCoreApplication::applicationDirPath();
    rootDir.cdUp();
    return rootDir.canonicalPath();
}

static inline QString getDefaultTranslationsPath()
{
    const QString rootDirPath = getRootPath();
    // Build path
    QString result = rootDirPath;
#if defined Q_OS_MACX
    result += QLatin1Char('/');
    result += QLatin1String("Resources");
    result += QLatin1Char('/');
    result += QLatin1String("Translations");
#elif defined Q_OS_WIN
    result += QLatin1Char('/');
    result += QLatin1String("resources");
    result += QLatin1Char('/');
    result += QLatin1String("translations");
#elif defined Q_OS_UNIX
    // not Mac UNIXes
    result += QLatin1Char('/');
    result += QLatin1String("share");
    result += QLatin1Char('/');
    result += qApp->applicationName();
    result += QLatin1Char('/');
    result += QLatin1String("translations");
#endif
    return result;
}

static void loadTranslations()
{
    QString translationsPath = getDefaultTranslationsPath();
    QTranslator *qtTranslator = new QTranslator(qApp);
    qtTranslator->load("qt_" + QLocale::system().name(),
                      translationsPath);
    qApp->installTranslator(qtTranslator);

    QTranslator *libTranslator = new QTranslator(qApp);
    libTranslator->load("imageviewer_app" + QLocale::system().name(), translationsPath);
    qApp->installTranslator(libTranslator);

    QTranslator *appTranslator = new QTranslator(qApp);
    appTranslator->load("imageviewer" + QLocale::system().name(), translationsPath);
    qApp->installTranslator(appTranslator);
}

int main(int argc, char *argv[])
{
    Application app("ImageViewer", argc, argv);

    QStringList arguments = app.arguments();
    arguments[0] = QDir::currentPath();

#if QT_VERSION < 0x050000
    if (app.isRunning()) {
        app.sendMessage(arguments.join("\n"));
        return 0;
    }
#endif

    loadTranslations();

    app.loadSettings();
    app.restoreSession();

    app.handleArguments(arguments);

    return app.exec();
}
