#include <iostream>
#include <string>
#include "flash.h"

/*
 * There is total 2^32 blocks.
 * One block has 32pages.
 * Every page has 8Bytes.
 *
 * You have a 8Bytes SRAM Buffer.
 *
 * */

const uint32_t PAGE_LIMIT = 32;

/*
 * mode					: Operation mode. Offered: read, write, erase.
 * blockNo				: Target block number.
 * fromPage [optional]	: Read/Write begin at which page (included).
 * toPage	[optional]	: Read/Write end at which page (included).
 * pattern	[optional]	: Write pattern.
 *
 */
void flashControl(
	std::string mode
	);

int main(int argc, char **argv){
	std::string mode = "read";
	//uint32_t blockNo = 10;
	//uint32_t fromPage = 4;
	//uint32_t toPage = 9;
	
	while(std::cin >> mode){
        flashControl(mode);
    }
	return 0;
}

void flashControl(std::string mode)
{
    uint32_t blockNo;
	uint32_t fromPage = 0;
	uint32_t toPage = 0;
    char pattern = 0x00;
    if(mode == "read")			// read
	{
		std::cin >> blockNo >> fromPage >> toPage;
        // Check page's range
		// No need to check < 0 because type is unsigned
		if(fromPage >= PAGE_LIMIT)
		{
			fprintf(stderr, "Variable frompage overflow!!\n");
			return;
		}
		if(toPage >= PAGE_LIMIT)
		{
			fprintf(stderr, "Variable toPage overflow!!\n");
			return;
		}
		if(fromPage > toPage)
		{
			// swap
			uint32_t temp = fromPage;
			fromPage = toPage;
			toPage = temp;
		}
		
		// read pages
		for(uint32_t page=fromPage; page<=toPage; page++)
		{
			printf(" Read dwBlock %d(0x%04Xh)\n", blockNo, blockNo);
            printf(" Read dwPage %d(0x%04Xh)\n", page, page);
            vFTL_PageRead(page, blockNo); // read 1 page
		}
	}
	else if(mode == "write")	// write
	{
		int tmp_int;
        std::cin >> blockNo >> fromPage >> toPage >> std::hex >> tmp_int >> std::dec;
        //std::cout << tmp_int << std::endl;
        pattern = tmp_int;
        // Check page's range
		// No need to check < 0 because type is unsigned
		if(fromPage >= PAGE_LIMIT)
		{
			fprintf(stderr, "Variable frompage overflow!!\n");
			return;
		}
		if(toPage >= PAGE_LIMIT)
		{
			fprintf(stderr, "Variable toPage overflow!!\n");
			return;
		}
		if(fromPage > toPage)
		{
			// swap
			uint32_t temp = fromPage;
			fromPage = toPage;
			toPage = temp;
		}
		
        //memset((byte *)(FLASH_MEM_BASE), bPATTERN, 128);
        //pSRamBuffer[0] = 0;
		
		// write pages
		for(uint32_t page=fromPage; page<=toPage; page++)
		{
			printf(" dwPage %d(0x%04Xh)\n", page, page);
            //pSRamBuffer[0] = page;
            vFTL_PageProgram(page, blockNo, pattern); // write 1 page
		}
	}
	else if(mode == "erase")	// erase
	{
		std::cin >> blockNo;
        bFTL_BlockErase(blockNo);
		fprintf(stdout, "Erase block %d complete.\n", blockNo);
	}
	else						// error
	{
		fprintf(stderr, "Operation %s is not offered!!\n", mode.c_str());
		return;
	}
}
