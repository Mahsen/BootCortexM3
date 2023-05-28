/************************************************** Description *******************************************************/
/*
    File : boot.cpp
    Programmer : Mohammad Lotfi
    Used : Using firmware update cortex M3
    Design Pattern : Singleton
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
#include <fstream>
#include "boot.hpp"
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
BOOT* BOOT::Instance = nullptr;
/************************************************** Functions *********************************************************/
bool BOOT::Check(string FileName) {

    fstream File;                   
    File.open(FileName, ios::in);
    if(File)
    {
        File.close(); 
        return true;
    }

    return false;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool BOOT::Execute(string FileName) {

    fstream File;

    File.open(FileName, ios::in);
    if(File)
    {
        char bytes[1024];
        File.seekg(0, ios::end);
        uint32_t Size = File.tellg();
        File.seekg(0, ios::beg);
        uint32_t Address = _AddressStart;

        for(uint32_t Length = 0; Length<Size;)
        {
            File.read(bytes, 1024);

            _Flash_PageErase(Address);
            _Flash_PageWrite(Address, bytes, 1024);

            Address += 1024;
            Length += 1024;	
        }

        File.close();
        return true;
    }

    return false;
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
