#define _KERNEL_MODULE_
#ifndef _XHCI_PORTS_H
#define _XHCI_PORTS_H
#include <LouDDK.h>

#define XHCI_PORT_DEVICE_CONNECTED                  (1)
#define XHCI_PORT_ENABLED                           (1 << 1)
#define XHCI_PORT_OVER_CURRENT_CONDITION            (1 << 3)
#define XHCI_PORT_RESET_SIGNAL                      (1 << 4)
#define XHCI_PORT_PORT_LINK_STATE_MASK              (0x0F << 5)
#define XHCI_DEVICE_U0                              (0b1 << 5)
#define XHCI_DEVICE_U1                              (0x01 << 5)
#define XHCI_DEVICE_U2                              (0x02 << 5)
#define XHCI_DEVICE_U3                              (0x03 << 5)
#define XHCI_DEVICE_DISABLED                        (0x04 << 5)
#define XHCI_DEVICE_RXDETECT                        (0x05 << 5)
#define XHCI_DEVICE_INACTIVE                        (0x06 << 5)
#define XHCI_DEVICE_POLLING                         (0x07 << 5)
#define XHCI_DEVICE_RECOVERY                        (0x08 << 5)
#define XHCI_DEVICE_HOT_RESET                       (0x09 << 5)
#define XHCI_DEVICE_COMP_MODE                       (0x0A << 5)
#define XHCI_DEVICE_TEST_MODE                       (0x0B << 5)
#define XHCI_DEVICE_RESUME                          (0x0F << 5)

#define XHCI_PORT_POWER                             (1 << 9)

#define XHCI_DEVICE_SPEED_MASK                      (0x0F << 10)
#define XHCI_DEVICE_FS                              (0x01 << 10)
#define XHCI_DEVICE_LS                              (0x02 << 10)
#define XHCI_DEVICE_HS                              (0x03 << 10)
#define XHCI_DEVICE_SS                              (0x04 << 10)
#define XHCI_DEVICE_SSP                             (0x05 << 10)

#define XHCI_DEVICE_UNDEFINED_SPEED(Port)           (((Port) & XHCI_DEVICE_SPEED_MASK) == 0)
#define XHCI_DEVICE_FULL_SPEED(Port)                (((Port) & XHCI_DEVICE_SPEED_MASK) == XHCI_DEVICE_FS)
#define XHCI_DEVICE_LOW_SPEED(Port)                 (((Port) & XHCI_DEVICE_SPEED_MASK) == XHCI_DEVICE_LS)
#define XHCI_DEVICE_HIGH_SPEED(Port)                (((Port) & XHCI_DEVICE_SPEED_MASK) == XHCI_DEVICE_HS)
#define XHCI_DEVICE_SUPER_SPEED(Port)               (((Port) & XHCI_DEVICE_SPEED_MASK) == XHCI_DEVICE_SS)
#define XHCI_DEVICE_SUPER_SPEED_PLUS(Port)          (((Port) & XHCI_DEVICE_SPEED_MASK) == XHCI_DEVICE_SSP)
#define XHCI_DEVICE_SUPER_SPEED_ANY(Port)           (((Port) & XHCI_DEVICE_SPEED_MASK) >= XHCI_DEVICE_SS)
#define XHCI_DEVICE_PORT_SPEED(Port)                (((Port) >> 10) & 0x0F)

#define XHCI_SLOT_SPEED_FS                          (XHCI_DEVICE_FS << 10)
#define XHCI_SLOT_SPEED_LS                          (XHCI_DEVICE_LS << 10)
#define XHCI_SLOT_SPEED_HS                          (XHCI_DEVICE_HS << 10)
#define XHCI_SLOT_SPEED_SS                          (XHCI_DEVICE_SS << 10)
#define XHCI_SLOT_SPEED_SSP                         (XHCI_DEVICE_SSP << 10)

#define XHCI_PORT_LED_OFF                           (0)
#define XHCI_PORT_LED_AMBER                         (1 << 14)
#define XHCI_PORT_LED_GREEN                         (2 << 14)
#define XHCI_PORT_LED_MASK                          (3 << 14)

#define XHCI_PORT_LINK_STROBE                       (1 << 16)
#define XHCI_PORT_CONNECT_STATUS_CHANGE             (1 << 17)
#define XHCI_PORT_PORT_ENABLE_CHANGE                (1 << 18)
#define XHCI_PORT_WARM_RESET_CHANGE                 (1 << 19)
#define XHCI_PORT_OVER_CURRENT_CHANGE               (1 << 20)
#define XHCI_PORT_RESET_CHANGE                      (1 << 21)
#define XHCI_PORT_LINK_STATUS_CHANGE                (1 << 22)
#define XHCI_PORT_CONFIGURATION_ERROR_CHANGE        (1 << 23)
#define XHCI_PORT_CHANGE_MASK                       (XHCI_PORT_CONNECT_STATUS_CHANGE | XHCI_PORT_PORT_ENABLE_CHANGE | XHCI_PORT_WARM_RESET_CHANGE | XHCI_PORT_OVER_CURRENT_CHANGE | XHCI_PORT_RESET_CHANGE | XHCI_PORT_LINK_STATUS_CHANGE | XHCI_PORT_CONFIGURATION_ERROR_CHANGE)

#define XHCI_PORT_COLD_ATTACH_STATUS                (1 << 24)
#define XHCI_PORT_WAKE_ON_CONNECT_ENABLE            (1 << 25)
#define XHCI_PORT_WAKE_ON_DISCONNECT_ENABLE         (1 << 26)
#define XHCI_PORT_WAKE_ON_OVER_CURRENT_ENABLE       (1 << 27)
#define XHCI_PORT_DEVICE_REMOVE                     (1 << 30)
#define XHCI_PORT_WARM_RESET                        (1 << 31)

#define XHCI_PORT_U1_TIMEOUT(Port)                  ((Port) & 0xFF)
#define XHCI_PORT_U1_TIMEOUT_MASK                   0xFF
#define XHCI_PORT_U2_TIMEOUT(Port)                  (((Port) & 0xFF) << 8)
#define XHCI_PORT_U2_TIMEOUT_MASK                   (0xFF << 8)

#define XHCI_PORT_L1S_MASK                          7
#define XHCI_PORT_L1S_SUCCESS                       1
#define XHCI_PORT_RWE                               (1 << 3)
#define XHCI_PORT_HIRD(Port)                        (((Port) & 0x0F) << 4)
#define XHCI_PORT_HIRD_MASK                         (0x0F << 4)
#define XHCI_PORT_L1DS_MASK                         (0xFF << 8)
#define XHCI_PORT_L1DS(Port)                        (((Port) & 0xFF) << 8)
#define XHCI_PORT_HLE                               (1 << 16)
#define XHCI_PORT_TEST_MODE_SHIFT                   28

#define XHCI_PORT_RX_LANES(Port)                    (((Port) >> 16) & 0x0F)
#define XHCI_PORT_TX_LANES(Port)                    (((Port) >> 20) & 0x0F)

#define XHCI_PORT_HIRDM(Port)                       ((Port) & 0x03)
#define XHCI_PORT_L1_TIMEOUT(Port)                  (((Port) & 0xFF) << 2)
#define XHCI_PORT_BESLD(Port)                       (((Port) & 0x0F) << 10)

#define XHCI_L1_TIMEOUT                             1 //itos actually 512 microseconds

#define XHCI_DEFAULT_BESL                           4

#define XHCI_PORT_POLLING_LFPS_TIME                 36

#endif