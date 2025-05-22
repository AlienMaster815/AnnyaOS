#ifndef _RS600D_H
#define _RS600D_H

#define R_000070_MC_INDEX 0x000070
#define S_000070_MC_ADDRESS(x) (((x) & 0xFFFF) << 0)
#define G_000070_MC_ADDRESS(x) (((x) >> 0) & 0xFFFF)
#define S_000070_MC_INDEX_CITF_ARB0(x) (((x) & 0x01) << 21)

#define R_000074_MC_INDEX_DATA 0x000074
#define S_000074_MC_INDEX_WR_EN(x) (((x) >> 22) & 0x01)

#define R_000078_MC_INDEX 0x000078
#define S_000078_MC_INDEX_WR_EN(x) (((x) >> 0) & 0x01FF)


#define R_0028F8_MC_INDEX 0x28F8
#define S_0028F8_MC_ADDRESS(x) (((x) & 0x1FF) << 0)
#define C_0028F8_MC_ADDRESS 0xFFFFFE00
#define S_0028F8_MC_INDEX_WR_EN(x) (((x) & 0x01) << 9)
#define R_0028FC_MC_DATA                        0x28FC


#endif