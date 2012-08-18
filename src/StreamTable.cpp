#include "StreamTable.h"

UrlLabel::UrlLabel(const QString & text): QLabel(URL_RICH_TEXT_TEMPLATE.arg(text))
{
    QObject::connect(this, SIGNAL(linkActivated(const QString &)),
                     this, SLOT(onLinkActivated(const QString &)));
}

void UrlLabel::onLinkActivated(const QString & url)
{
    QDesktopServices::openUrl(QUrl(url));
}

StreamTable::StreamTable(QWidget * parent) : QTableWidget(parent), showOfflinePages(false)
{
    setColumnCount(COLUMN_COUNT);
    setHorizontalHeaderLabels(TABLE_HEADER_LABELS);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader()->setMinimumSectionSize(MINIMUM_TABLE_SECTION_SIZE);
    verticalHeader()->setDefaultSectionSize(MINIMUM_TABLE_SECTION_SIZE);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

void StreamTable::buildTable(const StreamList & streams)
{
    streamsCache = streams;
    int rowIterator(0);
    StreamList shown;

    foreach(const Stream & stream, streams)
    {
        if(stream.online || showOfflinePages)
            shown << stream;
        _lastStates.insert(stream.url, stream.online);
    }

    setRowCount(shown.size());

    foreach(const Stream & stream, shown)
    {
        // Creating row items
        QTableWidgetItem * streamNameItem = new QTableWidgetItem(stream.name);

        UrlLabel * urlLabel = new UrlLabel(stream.url);

        QTableWidgetItem * statusItem = new QTableWidgetItem(stream.online ? ONLINE_STATE : OFFLINE_STATE);
        statusItem->setBackgroundColor(stream.online ? ONLINE_COLOR : OFFLINE_COLOR);

        StreamActionWidget * actionWidget = new StreamActionWidget(stream.qualities, stream.url, stream.name);
        QObject::connect(actionWidget, SIGNAL(watchClicked(const QString &, const QString &)),
                            this, SLOT(onWatchClicked(const QString &, const QString &)));
        QObject::connect(actionWidget, SIGNAL(chatClicked(const QString &, const QString &)),
                            this, SLOT(onChatClicked(const QString &, const QString &)));

        // Placing items
        setItem         (rowIterator, 0, streamNameItem);
        setCellWidget   (rowIterator, 1, urlLabel);
        setItem         (rowIterator, 2, statusItem);
        setCellWidget   (rowIterator, 3, actionWidget);
        rowIterator ++;
    }
}