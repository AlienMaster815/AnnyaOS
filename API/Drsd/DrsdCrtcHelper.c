#include "DrsdCore.h"

PDRSD_ENCODER
DrsdConnectorGetSingleEncoder(
    PDRSD_CONNECTOR Connector
){
    PDRSD_ENCODER Encoder;
    DrsdConnectorForEachPossibleEncoder(Connector, Encoder){
        return Encoder;
    }
    return 0x00;
}