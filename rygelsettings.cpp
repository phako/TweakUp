#include "rygelsettings.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QtDBus>
#include <QStringList>

RygelSettings::RygelSettings(QObject *parent)
    : QObject(parent)
    , m_settings(0)
    , m_available(false)
{
    QFile binary(QLatin1String("/usr/bin/rygel"));
    m_available = binary.exists();

    try {
        m_settings = new KeyFile(QLatin1String("rygel.conf"));
    } catch (GerrorException &e) {
        qWarning() << e.what();
        m_available = false;
    }
}

RygelSettings::~RygelSettings()
{
    if (m_settings != 0) {
        delete m_settings;
    }
}

bool RygelSettings::available()
{
    return m_available;
}

QString RygelSettings::friendlyName() const
{
    return m_settings->getString("title", QLatin1String("Media on @DEVICE@"), "Tracker");
}

void RygelSettings::setFriendlyName(const QString& friendlyName)
{
    m_settings->setString("title", friendlyName, "Tracker");
    emit friendlyNameChanged();
}

bool RygelSettings::strictSharing() const
{
    return m_settings->getBool("strict-sharing", true, "Tracker");
}

void RygelSettings::setStrictSharing(bool enable)
{
    m_settings->setBool("strict-sharing", enable, "Tracker");
    emit friendlyNameChanged();
}

bool RygelSettings::allowUpload() const
{
    return m_settings->getBool("allow-upload", true);
}

void RygelSettings::setAllowUpload(bool enable)
{
    m_settings->setBool("allow-upload", enable);
    emit allowUploadChanged();
}

bool RygelSettings::allowRemoveUpload() const
{
    return m_settings->getBool("allow-deletion", true);
}

void RygelSettings::setAllowRemoveUpload(bool enable)
{
    m_settings->setBool("allow-deletion", enable);
    emit allowRemoveUploadChanged();
}

bool RygelSettings::lpcmTranscoding() const
{
    return m_settings->getBool("enable-lpcm-transcoder", true);
}

void RygelSettings::setLPCMTranscoding(bool enable)
{
    m_settings->setBool("enable-lpcm-transcoder", enable);
    emit lpcmTranscodingChanged();
}

void RygelSettings::sync()
{
    m_settings->sync();
}
