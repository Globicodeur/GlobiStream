#ifndef STREAMTABLE_H
#define STREAMTABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

#include "StreamActionWidget.h"

static int COLUMN_COUNT(4); // Name | URL | Status | Actions
static QStringList TABLE_HEADER_LABELS(QStringList() << "Stream Name" << "URL" << "Status" << "Actions");

class UrlLabel : public QLabel
{
    Q_OBJECT

    public :
        UrlLabel();
        UrlLabel(const QString & text);
        ~UrlLabel() { }

    private slots :
        void onLinkActivated(const QString & url);
};

class StreamTable : public QTableWidget
{
    Q_OBJECT

    public :
        StreamTable(QWidget * parent = 0);
        ~StreamTable() { }

        void buildTable(const StreamList & streams);
        void rebuildTable() { buildTable(streamsCache); }
        void setShowOfflinePages(bool show) { showOfflinePages = show; }
        void setShowNonMonitoredPages(bool show) { showNonMonitoredPaged = show; }
        QMap <QString, int> lastStates() const { return _lastStates; }

    private slots :
        void onWatchClicked(const QString & url, const QString & quality) { emit watchClicked(url, quality); }
        void onChatClicked(const QString & url, const QString & name) { emit chatClicked(url, name); }

    signals :
        void watchClicked(const QString &, const QString &);
        void chatClicked(const QString &, const QString &);

    private :
        bool showOfflinePages;
        bool showNonMonitoredPaged;
        StreamList streamsCache;
        QMap <QString, int> _lastStates;
};
#endif // STREAMTABLE_H
