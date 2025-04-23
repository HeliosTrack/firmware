#include "TelemetryBME688.h"
#include "ReplyModule.h"
#include "MeshService.h"
#include "configuration.h"
#include "main.h"

#include <assert.h>

// Ne redéclare pas bmeReader ici ! Il est défini dans getDataBME68x.cpp

meshtastic_MeshPacket *TelemetryBME688::allocReply()
{
    assert(currentRequest); // always should be non-null

#ifdef DEBUG_PORT
    auto req = *currentRequest;
    auto &p = req.decoded;
    LOG_INFO("Received message from=0x%0x, id=%d, msg=%.*s", req.from, req.id, p.payload.size, p.payload.bytes);
#endif

    screen->print("Send reply\n");

    std::string data = bmeReader.getAllSensorData();
    const char *replyStr = data.c_str();

    auto reply = allocDataPacket();
    reply->decoded.payload.size = strlen(replyStr);
    memcpy(reply->decoded.payload.bytes, replyStr, reply->decoded.payload.size);

    return reply;
}

void TelemetryBME688::sendTelemetry()
{
    LOG_INFO("Sending telemetry message...");                                      

    std::string data = bmeReader.getAllSensorData();
    const char *message = data.c_str();

    auto packet = this->allocDataPacket();

    packet->decoded.portnum = meshtastic_PortNum_TEXT_MESSAGE_APP;

    packet->decoded.payload.size = strlen(message);
    memcpy(packet->decoded.payload.bytes, message, packet->decoded.payload.size);

    service->sendToMesh(packet);
}
