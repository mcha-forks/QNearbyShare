//
// Created by victor on 17/04/23.
//

#include <QTextStream>
#include "nearbypayload.h"

struct NearbyPayloadPrivate {
    bool isBytes;
    quint64 totalSize;

    QByteArray buffer;
    bool completed = false;
};

NearbyPayload::NearbyPayload(bool isBytes) {
    d = new NearbyPayloadPrivate();
    d->isBytes = isBytes;
}

NearbyPayload::~NearbyPayload() {
    delete d;
}

void NearbyPayload::loadChunk(quint64 offset, const QByteArray& body) {
    if (d->buffer.length() != offset) {
        // Stop!
        QTextStream(stderr) << "Nearby Payload offset jumped unexpectedly\n";
        return;
    }
    d->buffer.append(body);
}

void NearbyPayload::setCompleted() {
    d->completed = true;
}

QByteArray NearbyPayload::data() {
    return d->buffer;
}

bool NearbyPayload::completed() {
    return d->completed;
}

bool NearbyPayload::isBytes() {
    return d->isBytes;
}
