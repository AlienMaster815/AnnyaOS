#include "usb.h"
#include "Ohci.h"
#include <Hal.h>

/*
Bit Stuffing Insertion of a “0” bit into a data stream to cause an electrical
transition on the data wires allowing a PLL to remain locked.
Buffer Storage used to compensate for a difference in data rates or time
of occurrence of events, when transmitting data from one
device to another.
Command A request made to a Universal Serial Bus (USB) device.
Cyclic Redundancy
Check (CRC)
A check performed on data to see if an error has occurred in
transmitting, reading, or writing the data. The result of a
CRC is typically stored or transmitted with the checked data.
The stored or transmitted result is compared to a CRC
calculated for the data to determine if an error has occurred.
Device A logical or physical entity that performs one or more functions.
The actual entity described depends on the context of the
reference. At the lowest level, device may refer to a single
hardware component, as in a memory device. At a higher
level, it may refer to a collection of hardware components
that perform a particular function, such as a Universal Serial
Bus (USB) interface device. At an even higher level, device
may refer to the function performed by an entity attached to
the USB; for example, a data/FAX modem device. Devices
may be physical, electrical, addressable, and logical. When
used as a nonspecific reference, a USB device is either a hub
or a function.
Device Address The address of a device on Universal Serial Bus (USB). The
Device Address is the Default Address when the USB device
is first powered or reset. Hubs and functions are assigned a
unique Device Address by USB configuration software.
Driver When referring to hardware, an I/O pad that drives an external
load. When referring to software, a program responsible for
interfacing to a hardware device; that is, a device driver.
ED See Endpoint Descriptor.
OpenHCI - Open Host Controller Interface Specification for USB
3
End of Frame
(EOF)
The end of a USB defined frame. There are several different
stages of EOF present in a frame.
Endpoint Address The combination of a Device Address and an Endpoint Number
on a Universal Serial Bus device.
Endpoint
Descriptor (ED)
A memory structure which describes information necessary for
the Host Controller to communicate (via Transfer
Descriptors) with a device Endpoint. An Endpoint Descriptor
includes a Transfer Descriptor pointer.
Endpoint Number A unique pipe endpoint on a Universal Serial Bus device.
EOF See End of Frame.
Frame A frame begins with a Start of Frame (SOF) token and is 1.0 ms
±0.25% in length.
Function A Universal Serial Bus device that provides a capability to the
host. For example, an ISDN connection, a digital
microphone, or speakers.
Handshake Packet Packet which acknowledges or rejects a specific condition.
HC See Host Controller.
HCCA See Host Controller Communication Area
HCD See Host Controller Driver.
HCDI See Host Controller Driver Interface.
HCI See Host Controller Interface.
Host Controller
(HC)
Hardware device which interfaces to the Host Controller Driver
(HCD) and the Universal Serial Bus (USB). The interface to
the HCD is defined by the OpenHCI Host Controller
Interface. The Host Controller processes data lists
constructed by the HCD for data transmission over the USB.
The Host Controller contains the Root Hub as well.
OpenHCI - Open Host Controller Interface Specification for USB
4
Host Controller
Communication
Area (HCCA)
A structure in shared main memory established by the Host
Controller Driver (HCD). This structure is used for
communication between the HCD and the Host Controller.
The HCD maintains a pointer to this structure in the Host
Controller.
Host Controller
Driver (HCD)
Software driver which interfaces to the Universal Serial Bus
Driver and the Host Controller. The interface to the Host
Controller is defined by the OpenHCI Host Controller
Interface.
Host Controller
Driver Interface
(HCDI)
Software interface between the Universal Serial Bus Driver and
the Host Controller Driver.
Host Controller
Interface (HCI)
Interface between the Host Controller Driver and the Host
Controller.
Hub A Universal Serial Bus device that provides additional
connections to the Universal Serial Bus.
Interrupt Request
(IRQ)
A hardware signal that allows a device to request attention from
a host. The host typically invokes an interrupt service routine
to handle the condition which caused the request.
IRQ See Interrupt Request.
Isochronous Data A continuous stream of data delivered at a steady rate.
LSb Least Significant Bit.
LSB Least Significant Byte.
MSb Most Significant Bit.
MSB Most Significant Byte.
OpenHCI The Open Host Controller Interface definition. This interface
describes the requirements for a Host Controller and a Host
Controller driver for the operation of a Universal Serial Bus.
Packet A bundle of data organized for transmission.
OpenHCI - Open Host Controller Interface Specification for USB
5
Peripheral
Component
Interconnect (PCI)
A 32- or 64-bit, processor-independent, expansion bus used on
personal computers.
Phase A token, data, or handshake packet; a transaction has three
phases.
Polling Asking multiple devices, one at a time, if they have any data to
transmit.
Polling Interval The period between consecutive requests for data input to a
Universal Serial Bus Endpoint.
POR See Power-On Reset.
Port Point of access to or from a system or circuit. For Universal
Serial Bus, the point where a Universal Serial Bus device is
attached.
Power-On Reset
(POR)
Restoring a storage device, register or memory to a
predetermined state when power is applied.
Queue A linked list of Transfer Descriptors.
Root Hub A Universal Serial Bus hub attached directly to the Host
Controller.
Start of Frame
(SOF)
Start of Frame (SOF). The beginning of a USB-defined frame.
The SOF is the first transaction in each frame. SOF allows
endpoints to identify the start of frame and synchronize
internal endpoint clocks to the host.
TD See Transfer Descriptor.
Time-out The detection of a lack of bus activity for some predetermined
interval.
Transfer Descriptor
(TD)
A memory structure which describes information necessary for
the Host Controller to transfer a block of data to or from a
device Endpoint.
Universal Serial Bus
(USB)
A collection of Universal Serial Bus devices including the
software and hardware that allow connections between
functions and the host.
*/


void InitializeOhciDevice(P_PCI_DEVICE_OBJECT PDEV){
    LouPrint("Initializing Ohci Devic\n");
    PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    POPEN_HOST_CONTROLLER OhciDevice = (POPEN_HOST_CONTROLLER)LouKeHalGetPciVirtualBaseAddress(CommonConfig, 0);

    LouPrint("OHCI Is At Address:%h\n", OhciDevice);


    //while(1);
}