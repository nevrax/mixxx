#ifndef ENGINEFILTEBESSEL4_H
#define ENGINEFILTEBESSEL4_H

#include "engine/enginefilteriir.h"

class EngineFilterBessel4Low : public EngineFilterIIR<4, IIR_LP> {
    Q_OBJECT
  public:
    EngineFilterBessel4Low(int sampleRate, double freqCorner1);
    void setFrequencyCorners(int sampleRate, double freqCorner1);
};

class EngineFilterBessel4Band : public EngineFilterIIR<8, IIR_BP> {
    Q_OBJECT
  public:
    EngineFilterBessel4Band(int sampleRate, double freqCorner1,
            double freqCorner2);
    void setFrequencyCorners(int sampleRate, double freqCorner1,
            double freqCorner2);
};

class EngineFilterBessel4High : public EngineFilterIIR<4, IIR_HP> {
    Q_OBJECT
  public:
    EngineFilterBessel4High(int sampleRate, double freqCorner1);
    void setFrequencyCorners(int sampleRate, double freqCorner1);
};

#endif // ENGINEFILTEBESSEL4_H
