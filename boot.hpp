#ifndef BOOT_HPP
#define BOOT_HPP
/************************************************** Description *******************************************************/
/*
    File : boot.hpp
    Programmer : Mohammad Lotfi
    Used : Using firmware update cortex M3
    Design Pattern : Singleton
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/5/28
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
#include<iostream>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<string>
#include<thread>
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/* Using std */
using namespace std;
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
class BOOT {
    private: 
        static BOOT *Instance;
        uint32_t _AddressStart;
        bool (*_Flash_PageErase)(uint32_t Address);
        bool (*_Flash_PageWrite)(uint32_t Address, char* Data, uint32_t Length); 
        BOOT();

    public: static BOOT* getInstance() {
        if(Instance == nullptr) {
            Instance = new BOOT();
        }
        return Instance;
    }
    bool Check(string FileName);
    bool Execute(string FileName);
    void Set_AddressStart(uint32_t AddressStart) {
        _AddressStart = AddressStart;
    }
    void Set_Flash_PageErase(bool (*Pointer)(uint32_t)) {
        _Flash_PageErase = Pointer;
    }
    void Set_Flash_PageWrite(bool (*Pointer)(uint32_t, char*, uint32_t)) {
        _Flash_PageWrite = Pointer;
    }
    void Set_Handler(uint32_t AddressStart, bool (*Flash_PageErase)(uint32_t), bool (*Flash_PageWrite)(uint32_t, char*, uint32_t)) {
        Set_AddressStart(AddressStart);
        Set_Flash_PageErase(Flash_PageErase);
        Set_Flash_PageWrite(Flash_PageWrite);
    }
};
/************************************************** Functions *********************************************************/
/*
    Nothing
*/
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
#endif