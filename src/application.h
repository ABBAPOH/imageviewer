#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv, int flags = ApplicationFlags);

    bool notify(QObject *object, QEvent *event);
};

#endif // APPLICATION_H