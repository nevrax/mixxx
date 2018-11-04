#include <QtDebug>

#include "skin/skincontext.h"
#include "waveform/renderers/waveformmarkproperties.h"

#include "waveformmark.h"

WaveformMark::WaveformMark(const QString& group,
                           const QDomNode& node,
                           const SkinContext& context,
                           const WaveformSignalColors& signalColors)
        : m_iHotCue(kNoHotCue) {
    QString item = context.selectString(node, "Control");
    if (!item.isEmpty()) {
        m_pPointCos = std::make_unique<ControlProxy>(group, item);
        if (item.startsWith("hotcue_") && item.endsWith("_position")) {
            m_iHotCue = item.midRef(7, item.count() - 16).toInt() - 1;
        }
    }
    QString source = context.selectString(node, "Source");
    if (!source.isEmpty()) {
        m_pSourceCos = std::make_unique<ControlProxy>(group, source);
        m_pSourceCos->connectValueChanged(this, SLOT(slotCueSourceChanged()));
    }
    m_properties = WaveformMarkProperties(node, context, signalColors, m_iHotCue);
}

WaveformMark::WaveformMark(const QString& group,
                           const QDomNode& node,
                           const SkinContext& context,
                           const WaveformSignalColors& signalColors,
                           int hotCue)
        : m_iHotCue(hotCue) {
    if (hotCue >= 0) {
        QString item = "hotcue_" + QString::number(hotCue + 1) + "_position";
        m_pPointCos = std::make_unique<ControlProxy>(group, item);
    }
    QString source = context.selectString(node, "Source");
    if (!source.isEmpty()) {
        m_pSourceCos = std::make_unique<ControlProxy>(group, source);
        m_pSourceCos->connectValueChanged(this, SLOT(slotCueSourceChanged()));
    }
    m_properties = WaveformMarkProperties(node, context, signalColors, hotCue);
}


void WaveformMark::connectSamplePositionChanged(const QObject *obj, const char *slt) const {
    m_pPointCos->connectValueChanged(obj, slt, Qt::AutoConnection);
}

void WaveformMark::slotCueSourceChanged() {
    emit(sourceChanged(this));
}
