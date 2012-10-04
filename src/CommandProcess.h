#ifndef COMMANDPROCESS_H
#define COMMANDPROCESS_H

#include <QProcess>
#include <QApplication>

#if defined(Q_OS_WIN)
#include <Windows.h>
#endif

#if defined(Q_OS_UNIX)
#include <unistd.h>
#define Sleep sleep
#endif

#include "Global.h"

class CommandProcess : public QProcess
{
    Q_OBJECT

    public :
        CommandProcess() : QProcess() { init(); }
        ~CommandProcess() { end(); }

        void init();
        void end();
        void restart() { end(); init(); }
        void write(const QString & command) { QIODevice::write(QString("%1\n").arg(command).toStdString().c_str()); }
        void waitForComputingFinished();
};

#endif // COMMANDPROCESS_H
