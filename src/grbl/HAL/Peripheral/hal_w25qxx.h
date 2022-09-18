#ifndef __hal_w25qxx_h__
#define __hal_w25qxx_h__


#include "../grbl_config.h"

#ifdef HAS_W25Qxx

    #include "../../../main.h"
    #define USE_FATFS
    #ifdef USE_FATFS
        #define W25QXX_FS_PATH              "0:"
    #endif /* USE_FATFS */


    // Flash choose
    // EF
    #define  sFLASH_ID_X16  0x3015        /* W25X16  */ 
    #define  sFLASH_ID_16   0x4015        /* W25Q16  */
    #define  sFLASH_ID_64   0X4017        /* W25Q64  */
    #define  sFLASH_ID_128  0X4018        /* W25Q128 */
    #define  sFLASH_ID_256  0X4019        /* W25Q256 */  

    #define sFLAHS_SPI_MODE                 0
    #define sFLASH_QSPI_MODE                1

    #define SPI_FLASH_SectorSize            512
    #define SPI_FLASH_PageSize              256
    #define SPI_FLASH_PerWritePageSize      256

    // Flash cmd
    #define W25X_WriteEnable		        0x06 
    #define W25X_WriteDisable		        0x04 
    #define W25X_ReadStatusReg		        0x05 
    #define W25X_ReadStatusReg2		        0x35 
    #define W25X_ReadStatusReg3		        0x15
    #define W25X_WriteStatusReg		        0x01 
    #define W25X_WriteStatusReg2		    0x31 
    #define W25X_WriteStatusReg3		    0x11
    #define W25X_ReadData			        0x03 
    #define W25X_FastReadData		        0x0B 
    #define W25X_FastReadDual		        0x3B 
    #define W25X_PageProgram		        0x02 
    #define W25X_BlockErase			        0xD8 
    #define W25X_SectorErase		        0x20 
    #define W25X_ChipErase			        0xC7
    #define W25X_PowerDown			        0xB9 
    #define W25X_ReleasePowerDown	        0xAB 
    #define W25X_DeviceID			        0xAB 
    #define W25X_ManufactDeviceID   	    0x90 
    #define W25X_JedecDeviceID		        0x9F 
    #define W25X_Enter4ByteMode		        0xB7
    #define W25X_ReadStatusRegister3        0x15

    #define WIP_Flag                        0x01  /* Write In Progress (WIP) flag */
    #define Dummy_Byte                      0xFF


    typedef struct{

        uint32_t flash_id;                  /* Flash ID */ 
        uint32_t flash_man;                 /* Flash Man */ 
        uint32_t flash_size;                
        uint32_t flash_delay_time;
        uint8_t  flash_mode;
        uint8_t  flash_state;               /* check if flash can't read, use for FATFS */ 
        uint8_t  addr_size;

        /* Base Func */
        void (*w25qxxSpiGpioInit)(void);                     /* 初始化GPIO的函数，包含GPIO复用 */
        void (*w25qxxSpiInit)(void);                          /* 初始化SPI外设 */
        uint8_t (*w25qxxSpiReadWriteByte)(uint8_t );        /* SPI读写函数 */
        bool (*w25qxxIsTransFinish)(void);                   /* 判断是否传输完成 */
        void (*w25qxxEnableTrans)(void);    
        void (*w25qxxDisableTrans)(void);

    }NFLASH_t;
    extern NFLASH_t sFlash;


    void w25qxxSpiRegiest();
    void w25qxxSpiInit(NFLASH_t *nFlash);                           

    void w25qxxInit(NFLASH_t *nFlash);
    uint32_t w25qxxRead_ID(NFLASH_t *nFlash);
    uint16_t w25qxxReadWriteByte(NFLASH_t *nFlash, uint16_t wdata);

    void w25qxxEnterFlashMode(NFLASH_t *nFlash);
    void w25qxxSectorErase(NFLASH_t *nFlash, uint32_t SectorAddr);
    void w25qxxBlockErase(NFLASH_t *nFlash, uint32_t BlockAddr);
    void w25qxxChipErase(NFLASH_t *nFlash);
    void w25qxxBufferWrite(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
    void w25qxxBufferRead(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
    void w25qxxTest();
    #ifdef USE_FATFS
        bool w25qxx_fs_init(void);
        void get_w25qxx_fafts_info(void);
    #endif /* USE_FATFS */

#endif /* HAS_W25Qxx */

#endif /* __hal_w25qxx_h__ */
