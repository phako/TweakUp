#ifndef MEDIAINDEXER_H
#define MEDIAINDEXER_H

#include <QObject>
#include <QTimer>

class MediaIndexer : public QObject
{
    Q_OBJECT
public:
    explicit MediaIndexer(QObject *parent = 0);
    
signals:
    void progress(qreal currentProgress);
    void done();

public slots:
    void run();
    void onTimer();
private:
    QTimer m_timer;
    qreal m_progress;
};

#endif // MEDIAINDEXER_H
