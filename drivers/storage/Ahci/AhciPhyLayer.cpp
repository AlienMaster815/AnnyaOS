#define _KERNEL_MODULE_

/*
 * This software is provided under the GNU General Public License (GPL) v2.
 * Copyright (C) 2025 Tyler Grenier.
 *
 * The following kernel module is based on a combination of publicly available 
 * specifications, OS development resources, and various vendor documentation, 
 * including but not limited to:
 * - AHCI Specification
 * - OSDev.org materials
 * - Linux kernel documentation
 * - BSD kernel documentation
 * - Microsoft, NVIDIA, and Advanced Micro Devices (AMD) documentation
 *
 * DISCLAIMER:
 * Due to the nature of proprietary information and potential leaks, the sources 
 * of certain information will not be disclosed **nor shall they be provided.** 
 * Any possibly leaked information, if present, is used **strictly for compatibility 
 * purposes and not with any malicious intent.** If you require additional information 
 * regarding this driver, please obtain it from the **respective hardware or documentation owner.**
 *
 * This software is provided "as is," without any warranty of any kind, express or 
 * implied, including but not limited to the implied warranties of merchantability, 
 * fitness for a particular purpose, and non-infringement. In no event shall the author
 * be liable for any direct, indirect, incidental, special, exemplary, or consequential 
 * damages arising from the use of this software.
 *
 * MODULE FILES:
 * - AhciMod.h
 * - Ahci.cpp
 * - Ahci-Vt8251.cpp
 * - AhciLib.cpp
 * - Ahci-P5wdh.cpp
 * - Ahci-Avn.cpp
 * - AhciPowerManagement.cpp
 * - AhciPhyLayer.cpp
 *
 * LICENSE:
 * This module is licensed under the GNU General Public License v2 (GPLv2).
 * You may obtain a copy of the GPLv2 at:
 * https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */