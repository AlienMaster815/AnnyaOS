#ifndef _DRSD_MODES_H
#define _DRSD_MODES_H

#include "DrsdCore.h"

extern "C" BOOL DrsdModeParseCommandLineForConnector(
    LOUSTR              ModeOption,
    PDRSD_CONNECTOR     Connector,
    PDRSD_CMDLINE_MODE  Mode
);

#endif