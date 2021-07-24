#ifndef FLASH_H
#define FLASH_H

#include <map>
#include <vector>
// LBA - 
extern char pSRamBuffer[8];
extern std::map<uint32_t, std::map<uint32_t,std::vector<char>>> flash;

void init_flash();

void bFTL_BlockErase(uint32_t blkn);

void vFTL_PageRead(uint32_t pagen, uint32_t blkn);

void vFTL_PageProgram(uint32_t pagen, uint32_t blkn, char pattern);

#endif
