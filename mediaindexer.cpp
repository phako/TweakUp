#include "mediaindexer.h"

MediaIndexer::MediaIndexer(QObject *parent)
    : QObject(parent)
    , m_timer()
    , m_progress(0.0)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(onTimer()));
}

void MediaIndexer::run() {
    m_timer.setInterval(750);
    m_timer.start();
}

void MediaIndexer::onTimer()
{
    m_progress += 0.1;
    if (m_progress < 1) {
        emit progress(m_progress);
    } else {
        m_progress = 1.0;
        emit progress(m_progress);
        emit done();
    }
}
