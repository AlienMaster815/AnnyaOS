#include "DrsdCore.h"

static DRSD_DISPLAY_MODE DrsdDMTSpecificationModes[] = {
    {DEFINE_DRSD_MODE("640x350", DRSD_MODE_TYPE_DRIVER, 31500, 640, 672, 736, 832, 0, 350, 382, 385, 445, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("640x400", DRSD_MODE_TYPE_DRIVER, 31500, 640, 672, 736, 832, 0, 400, 401, 404, 445, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("720x400", DRSD_MODE_TYPE_DRIVER, 35500, 720, 756, 828, 936, 0, 400, 401, 404, 446, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("640x480", DRSD_MODE_TYPE_DRIVER, 25175, 640, 656, 752, 800, 0, 480, 490, 492, 525, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("640x480", DRSD_MODE_TYPE_DRIVER, 31500, 640, 664, 704, 832, 0, 480, 489, 492, 520, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("640x480", DRSD_MODE_TYPE_DRIVER, 31500, 640, 656, 720, 840, 0, 480, 481, 484, 500, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("640x480", DRSD_MODE_TYPE_DRIVER, 36000, 640, 696, 752, 832, 0, 480, 481, 484, 509, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 36000, 800, 824, 896, 1024, 0, 600, 601, 603, 625, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 40000, 800, 840, 968, 1056, 0, 600, 601, 605, 628, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 50000, 800, 856, 976, 1040, 0, 600, 637, 643, 666, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 49500, 800, 816, 896, 1056, 0, 600, 601, 604, 625, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 56250, 800, 832, 896, 1048, 0, 600, 601, 604, 631, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("800x600", DRSD_MODE_TYPE_DRIVER, 73250, 800, 848, 880, 960, 0, 600, 603, 607, 636, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("848x480", DRSD_MODE_TYPE_DRIVER, 33750, 848, 864, 976, 1088, 0, 480, 486, 494, 517, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1024x768i", DRSD_MODE_TYPE_DRIVER, 44900, 1024, 1032, 1208, 1264, 0, 768, 768, 776, 817, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH | DDM_FLAG_INTERLACED)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 65000, 1024, 1048, 1184, 1344, 0, 768, 771, 777, 806, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 75000, 1024, 1048, 1184, 1328, 0, 768, 771, 777, 806, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 78750, 1024, 1040, 1136, 1312, 0, 768, 769, 772, 800, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 78750, 1024, 1040, 1136, 1312, 0, 768, 769, 772, 800, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 94500, 1024, 1072, 1168, 1376, 0, 768, 769, 772, 808, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1024x768", DRSD_MODE_TYPE_DRIVER, 115500, 1024, 1072, 1104, 1184, 0, 768, 771, 775, 813, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1152x864", DRSD_MODE_TYPE_DRIVER, 108000, 1152, 1216, 1344, 1600, 0, 864, 865, 868, 900, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x720", DRSD_MODE_TYPE_DRIVER, 74250, 1280, 1390, 1430, 1650, 0, 720, 725, 730, 750, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x768", DRSD_MODE_TYPE_DRIVER, 68250, 1280, 1328, 1360, 1440, 0, 768, 771, 778, 790, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1280x768", DRSD_MODE_TYPE_DRIVER, 79500, 1280, 1344, 1472, 1664, 0, 768, 771, 778, 798, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x768", DRSD_MODE_TYPE_DRIVER, 102250, 1280, 1360, 1488, 1696, 0, 768, 771, 778, 805, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x768", DRSD_MODE_TYPE_DRIVER, 117500, 1280, 1360, 1496, 1712, 0, 768, 771, 778, 809, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x768", DRSD_MODE_TYPE_DRIVER, 140250, 1280, 1328, 1360, 1440, 0, 768, 771, 778, 813, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1280x800", DRSD_MODE_TYPE_DRIVER, 71000, 1280, 1328, 1360, 1440, 0, 800, 803, 809, 823, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1280x800", DRSD_MODE_TYPE_DRIVER, 83500, 1280, 1352, 1480, 1680, 0, 800, 803, 809, 831, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x800", DRSD_MODE_TYPE_DRIVER, 106500, 1280, 1360, 1488, 1696, 0, 800, 803, 809, 838, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x800", DRSD_MODE_TYPE_DRIVER, 122500, 1280, 1360, 1496, 1712, 0, 800, 803, 809, 843, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x800", DRSD_MODE_TYPE_DRIVER, 146250, 1280, 1328, 1360, 1440, 0, 800, 803, 809, 847, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1280x960", DRSD_MODE_TYPE_DRIVER, 108000, 1280, 1376, 1488, 1800, 0, 960, 961, 964, 1000, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x960", DRSD_MODE_TYPE_DRIVER, 148500, 1280, 1344, 1504, 1728, 0, 960, 961, 964, 1011, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x960", DRSD_MODE_TYPE_DRIVER, 175500, 1280, 1328, 1360, 1440, 0, 960, 963, 967, 1017, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1280x1024", DRSD_MODE_TYPE_DRIVER, 108000, 1280, 1328, 1440, 1688, 0, 1024, 1025, 1028, 1066, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x1024", DRSD_MODE_TYPE_DRIVER, 135000, 1280, 1296, 1440, 1688, 0, 1024, 1025, 1028, 1066, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x1024", DRSD_MODE_TYPE_DRIVER, 157500, 1280, 1344, 1504, 1728, 0, 1024, 1025, 1028, 1072, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1280x1024", DRSD_MODE_TYPE_DRIVER, 187250, 1280, 1328, 1360, 1440, 0, 1024, 1027, 1034, 1084, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1360x768", DRSD_MODE_TYPE_DRIVER, 85500, 1360, 1424, 1536, 1792, 0, 768, 771, 777, 795, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1360x768", DRSD_MODE_TYPE_DRIVER, 148250, 1360, 1408, 1440, 1520, 0, 768, 771, 776, 813, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1366x768", DRSD_MODE_TYPE_DRIVER, 85500, 1366, 1436, 1579, 1792, 0, 768, 771, 774, 798, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1366x768", DRSD_MODE_TYPE_DRIVER, 72000, 1366, 1380, 1436, 1500, 0, 768, 769, 772, 800, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1400x1050", DRSD_MODE_TYPE_DRIVER, 101000, 1400, 1448, 1480, 1560, 0, 1050, 1053, 1057, 1080, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1400x1050", DRSD_MODE_TYPE_DRIVER, 121750, 1400, 1488, 1632, 1864, 0, 1050, 1053, 1057, 1089, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1400x1050", DRSD_MODE_TYPE_DRIVER, 156000, 1400, 1504, 1648, 1896, 0, 1050, 1053, 1057, 1099, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1400x1050", DRSD_MODE_TYPE_DRIVER, 179500, 1400, 1504, 1656, 1912, 0, 1050, 1053, 1057, 1105, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1400x1050", DRSD_MODE_TYPE_DRIVER, 208000, 1400, 1448, 1480, 1560, 0, 1050, 1053, 1057, 1112, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1440x900", DRSD_MODE_TYPE_DRIVER, 88750, 1440, 1488, 1520, 1600, 0, 900, 903, 909, 926, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1440x900", DRSD_MODE_TYPE_DRIVER, 106500, 1440, 1520, 1672, 1904, 0, 900, 903, 909, 934, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1440x900", DRSD_MODE_TYPE_DRIVER, 136750, 1440, 1536, 1688, 1936, 0, 900, 903, 909, 942, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1440x900", DRSD_MODE_TYPE_DRIVER, 157000, 1440, 1544, 1696, 1952, 0, 900, 903, 909, 948, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1440x900", DRSD_MODE_TYPE_DRIVER, 182750, 1440, 1488, 1520, 1600, 0, 900, 903, 909, 953, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1600x900", DRSD_MODE_TYPE_DRIVER, 108000, 1600, 1624, 1704, 1800, 0, 900, 901, 904, 1000, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 162000, 1600, 1664, 1856, 2160, 0, 1200, 1201, 1204, 1250, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 175500, 1600, 1664, 1856, 2160, 0, 1200, 1201, 1204, 1250, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 189000, 1600, 1664, 1856, 2160, 0, 1200, 1201, 1204, 1250, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 202500, 1600, 1664, 1856, 2160, 0, 1200, 1201, 1204, 1250, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 229500, 1600, 1664, 1856, 2160, 0, 1200, 1201, 1204, 1250, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1600x1200", DRSD_MODE_TYPE_DRIVER, 268250, 1600, 1648, 1680, 1760, 0, 1200, 1203, 1207, 1271, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1680x1050", DRSD_MODE_TYPE_DRIVER, 119000, 1680, 1728, 1760, 1840, 0, 1050, 1053, 1059, 1080, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1680x1050", DRSD_MODE_TYPE_DRIVER, 146250, 1680, 1784, 1960, 2240, 0, 1050, 1053, 1059, 1089, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1680x1050", DRSD_MODE_TYPE_DRIVER, 187000, 1680, 1800, 1976, 2272, 0, 1050, 1053, 1059, 1099, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1680x1050", DRSD_MODE_TYPE_DRIVER, 214750, 1680, 1808, 1984, 2288, 0, 1050, 1053, 1059, 1105, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1680x1050", DRSD_MODE_TYPE_DRIVER, 245500, 1680, 1728, 1760, 1840, 0, 1050, 1053, 1059, 1112, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1792x1344", DRSD_MODE_TYPE_DRIVER, 204750, 1792, 1920, 2120, 2448, 0, 1344, 1345, 1348, 1394, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1792x1344", DRSD_MODE_TYPE_DRIVER, 261000, 1792, 1888, 2104, 2456, 0, 1344, 1345, 1348, 1417, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1792x1344", DRSD_MODE_TYPE_DRIVER, 333250, 1792, 1840, 1872, 1952, 0, 1344, 1347, 1351, 1423, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1856x1392", DRSD_MODE_TYPE_DRIVER, 218250, 1856, 1952, 2176, 2528, 0, 1392, 1393, 1396, 1439, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1856x1392", DRSD_MODE_TYPE_DRIVER, 288000, 1856, 1984, 2208, 2560, 0, 1392, 1393, 1396, 1500, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1856x1392", DRSD_MODE_TYPE_DRIVER, 356500, 1856, 1904, 1936, 2016, 0, 1392, 1395, 1399, 1474, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1920x1080", DRSD_MODE_TYPE_DRIVER, 148500, 1920, 2008, 2052, 2200, 0, 1080, 1084, 1089, 1125, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1920x1200", DRSD_MODE_TYPE_DRIVER, 154000, 1920, 1968, 2000, 2080, 0, 1200, 1203, 1209, 1235, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1920x1200", DRSD_MODE_TYPE_DRIVER, 193250, 1920, 2056, 2256, 2592, 0, 1200, 1203, 1209, 1245, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1920x1200", DRSD_MODE_TYPE_DRIVER, 245250, 1920, 2056, 2264, 2608, 0, 1200, 1203, 1209, 1255, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1920x1200", DRSD_MODE_TYPE_DRIVER, 281250, 1920, 2064, 2272, 2624, 0, 1200, 1203, 1209, 1262, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1920x1200", DRSD_MODE_TYPE_DRIVER, 317000, 1920, 1968, 2000, 2080, 0, 1200, 1203, 1209, 1271, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("1920x1440", DRSD_MODE_TYPE_DRIVER, 234000, 1920, 2048, 2256, 2600, 0, 1440, 1441, 1444, 1500, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1920x1440", DRSD_MODE_TYPE_DRIVER, 297000, 1920, 2064, 2288, 2640, 0, 1440, 1441, 1444, 1500, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("1920x1440", DRSD_MODE_TYPE_DRIVER, 380500, 1920, 1968, 2000, 2080, 0, 1440, 1443, 1447, 1525, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("2048x1152", DRSD_MODE_TYPE_DRIVER, 162000, 2048, 2074, 2154, 2250, 0, 1152, 1153, 1156, 1200, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("2560x1600", DRSD_MODE_TYPE_DRIVER, 268500, 2650, 2608, 2640, 2720, 0, 1600, 1603, 1609, 1646, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("2560x1600", DRSD_MODE_TYPE_DRIVER, 348500, 2650, 2752, 3032, 3504, 0, 1600, 1603, 1609, 1658, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("2560x1600", DRSD_MODE_TYPE_DRIVER, 443250, 2650, 2768, 3048, 3536, 0, 1600, 1603, 1609, 1682, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("2560x1600", DRSD_MODE_TYPE_DRIVER, 505250, 2650, 2768, 3048, 3536, 0, 1600, 1603, 1609, 1682, 0, DDM_FLAG_HSYNC_ACTIVE_LOW | DDM_FLAG_VSYNC_ACTIVE_HIGH)},
    {DEFINE_DRSD_MODE("2560x1600", DRSD_MODE_TYPE_DRIVER, 552750, 2650, 2608, 2640, 2720, 0, 1600, 1603, 1609, 1694, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("4096x2160", DRSD_MODE_TYPE_DRIVER, 556744, 4096, 4104, 4136, 4176, 0, 2160, 2208, 2216, 2222, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    {DEFINE_DRSD_MODE("4096x2160", DRSD_MODE_TYPE_DRIVER, 556188, 4096, 4104, 4136, 4176, 0, 2160, 2208, 2216, 2222, 0, DDM_FLAG_HSYNC_ACTIVE_HIGH | DDM_FLAG_VSYNC_ACTIVE_LOW)},
    0,
};

PDRSD_DISPLAY_MODE DrsdForkMode(PDRSD_DEVICE Device, PDRSD_DISPLAY_MODE DispMode);
void DrsdAddProbedDisplayModeToConnector(PDRSD_CONNECTOR Connector, PDRSD_DISPLAY_MODE Mope);


static const EDID_QUIRK EdidQuirkList[] = {
    {DEFINE_EDID_QUIRK('A', 'C', 'R',  44358, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('A', 'P', 'I', 0x7602, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('A', 'E', 'O', 0x0000, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('B', 'N', 'Q', 0x78D6, FORCE_8BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('B', 'O', 'E', 0x078B, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('C', 'P', 'T', 0x17df, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'D', 'C', 0x3652, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('B', 'O', 'E', 0x0771, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('M', 'A', 'X', 1516, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('M', 'A', 'X', 0x77e, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('E', 'P', 'I', 59264, CLOCK_TOO_HIGH_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('E', 'P', 'I', 8232, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('F', 'C', 'M', 13600, PREFER_LARGE_75HZ_EDID_QUIRK | DETAILED_CM_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('G', 'S', 'M', 0x5bbf, CAP_DSC_15BPP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('G', 'S', 'M', 0x5b9a, CAP_DSC_15BPP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('L', 'G', 'D', 764, FORCE_10BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('L', 'P', 'L', 0, DETAILED_USE_MAXIMUM_SIZE_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('L', 'P', 'L', 0x2a00, DETAILED_USE_MAXIMUM_SIZE_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'A', 'M', 541, DETAILED_SYNC_PP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'A', 'M', 596, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'A', 'M', 638, PREFER_LARGE_60HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'N', 'Y', 0x2541, FORCE_12BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'S', 'C', 5020, FORCE_REDUCED_BLANKING_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('M', 'E', 'D', 0x7b8, PREFER_LARGE_75HZ_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'D', 'C', 18514, FORCE_6BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'E', 'C', 0xd033, FORCE_8BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('E', 'T', 'R', 13896, FORCE_8BPC_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91A8, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B0, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B1, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B2, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B3, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B4, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B5, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B6, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B7, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B8, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91B9, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BA, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BB, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BC, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BD, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BE, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('V', 'L', 'V', 0x91BF, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('H', 'V', 'R', 0xAA01, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('H', 'V', 'R', 0xAA02, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('O', 'V', 'R', 0x0001, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('O', 'V', 'R', 0x0003, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('O', 'V', 'R', 0x0004, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('O', 'V', 'R', 0x0012, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('A', 'C', 'R', 0x7fCE, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('L', 'E', 'N', 0x0408, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('F', 'U', 'J', 0x1970, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('D', 'E', 'L', 0x7fCE, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'E', 'C', 0x144A, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('A', 'U', 'S', 0xC102, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'N', 'Y', 0x0704, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'E', 'N', 0x1019, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('S', 'V', 'R', 0x1019, NON_DESKTOP_EDID_QUIRK)},
    {DEFINE_EDID_QUIRK('A', 'U', 'O', 0x1111, NON_DESKTOP_EDID_QUIRK)},
    0x00,
};

uint32_t DrsdGetPanelIdentification(PDRSD_EDID_TRACKER Edid){
    PINTEL_STANDARD_EDID IntelEdid = Edid->EdidBase;
    if(Edid->EdidTotalSize < 128){
        return 0x00;
    }
    return (uint32_t)(IntelEdid->Manufacturer[0] << 24 | IntelEdid->Manufacturer[0] << 16 | GET_EDID_PRODUCT_IDENTIFICATION(IntelEdid));
}

bool DrsdEdidMatch(PDRSD_EDID_TRACKER Edid, PDRSD_EDID_IDENTIFICATION EdidID){
    if((!Edid) || (DrsdGetPanelIdentification(Edid) != EdidID->PannelIdentification)){
        return false;
    }

    //TODO: Match the name to the ID

    return true;
}

size_t EdidGetQuirks(PDRSD_EDID_TRACKER Edid){
    PEDID_QUIRK Tmp = (PEDID_QUIRK)EdidQuirkList;
    for(size_t i = 0 ; Tmp[i].QuirkID ; i++){
        if(DrsdEdidMatch(Edid, &Tmp[i].Identification)){
            return Tmp[i].QuirkID;
        }
    }
    return 0x00;
}

size_t DrsdAddModesNoEDID(
    PDRSD_CONNECTOR Connector, 
    int32_t Width, 
    int32_t Height
){
    size_t Result = 0;
    UNUSED PDRSD_DISPLAY_MODE Tmp;
    UNUSED PDRSD_DISPLAY_MODE NewProbedMode;
    for(size_t i = 0; DrsdDMTSpecificationModes[i].ModeName; i++){
        Tmp = &DrsdDMTSpecificationModes[i];

        if((Width) && (Height)){
            if((Tmp->HorizontalDisplay > Width) || (Tmp->VirticalDisplay > Height)){
                continue;
            }

            if(DrsdModeVfresh(Tmp) > 61){
                continue;
            }            

            NewProbedMode = DrsdForkMode(Connector->Device, Tmp);
            if(NewProbedMode){
                DrsdAddProbedDisplayModeToConnector(Connector, NewProbedMode);
                Result++;
            }
        }
    }
    return Result;
}

static PDRSD_EDID_TRACKER GlobalTrack = 0x00;

PDRSD_EDID_TRACKER DrsdEdidCreateObject(PINTEL_STANDARD_EDID Edid){
    PDRSD_EDID_TRACKER NewTrack = GlobalTrack;

    if(!GlobalTrack){
        GlobalTrack = LouKeMallocType(DRSD_EDID_TRACKER, KERNEL_GENERIC_MEMORY);
        GlobalTrack->EdidBase = Edid;
        GlobalTrack->EdidTotalSize = sizeof(INTEL_STANDARD_EDID);
        return GlobalTrack;
    }   
    while(NewTrack->Peers.NextHeader){
        NewTrack = (PDRSD_EDID_TRACKER)NewTrack->Peers.NextHeader;
    }
    NewTrack->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_EDID_TRACKER, KERNEL_GENERIC_MEMORY);;\
    return (PDRSD_EDID_TRACKER)NewTrack->Peers.NextHeader;
}