#pragma once

#include "SinglePortModule.h"
#include "getDataBME68x.h"

// Déclare que bmeReader est défini ailleurs
extern BME68xReader bmeReader;

class TelemetryBME688 : public SinglePortModule
{
public:
    /** Constructor - name is for debugging output */
    TelemetryBME688() : SinglePortModule("telemetry-bme688", meshtastic_PortNum_TEXT_MESSAGE_APP) {}

    void sendTelemetry();

    virtual ~TelemetryBME688() {} // Bonnes pratiques pour classe avec méthode virtuelle

protected:
    /** Traitement des réponses via allocReply */
    virtual meshtastic_MeshPacket *allocReply() override;
};
