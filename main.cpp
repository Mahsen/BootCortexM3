/************************************************** Description *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : Using firmware update cortex M3
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/5/25
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include <iostream>
#include "boot.hpp"
#include "stm32l1xx_flash.h"
/************************************************** Defineds **********************************************************/
#define MAIN_PROGRAM_ADDRESS_JUMP	0x08008000
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void __ASM MAIN_AsmJumpTo(uint32_t Address) {
	MOV LR, #0xFFFFFFFF    ;Reset Link Register
	LDR SP, [R0, #0]       ;Load new stack pointer address
	LDR PC, [R0, #4]       ;Load new program counter address
}
/*--------------------------------------------------------------------------------------------------------------------*/
void MAIN_JumpTo(uint32_t Address) {
	__disable_irq();
	SCB->VTOR = Address;
	__enable_irq();

	MAIN_AsmJumpTo(Address);
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool MAIN_Flash_PageErase(uint32_t Address) {
{
	FLASH_Status fs;
	FLASH_Unlock();

    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGAERR|FLASH_FLAG_WRPERR);
    fs = FLASH_ErasePage(Address);
    if(fs != FLASH_COMPLETE)
    {
        FLASH_Lock();
        return false;
    }

	FLASH_Lock();
	return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool MAIN_Flash_PageWrite(uint32_t Address, char* Data, uint32_t Length) {
{
	FLASH_Status fs;
	uint32_t *data2write = (uint32_t*)((void*)Data);

	while(Length)
	{
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGAERR|FLASH_FLAG_WRPERR);
		fs = FLASH_FastProgramWord(Address , *data2write);
		FLASH_Lock();
		data2write++;
		Address+=4;
		Length-=4;
		if(fs != FLASH_COMPLETE)
			return false;
	}

	FLASH->PECR |= FLASH_PECR_PRGLOCK;

	return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int main() {

    cout << "Start BOOT " << endl;

    BOOT *_BOOT = BOOT::getInstance();

    _BOOT->Set_Handler(MAIN_PROGRAM_ADDRESS_JUMP, MAIN_Flash_PageErase, MAIN_Flash_PageWrite);

    _BOOT->Check("BootFile.bin");
    _BOOT->Execute("BootFile.bin");

    cout << "Finish BOOT " << endl;

    MAIN_JumpTo(MAIN_PROGRAM_ADDRESS_JUMP);

    return 0;
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/