/*******************************************************************************
* Copyright (C) 2017, Xiaohua Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Xiaohua Semiconductor Co.,Ltd ("XHSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with XHSC
* components. This software is licensed by XHSC to be adapted only
* for use in systems utilizing XHSC components. XHSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. XHSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* XHSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* XHSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file clk.h
 **
 ** Headerfile for CLK functions
 ** @link CLK Group Some description @endlink 
 **
 ** History:
 **   - 2017-05-02   Ronnie     First Version
 **
 ******************************************************************************/

#ifndef __CLK_H__
#define __CLK_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup ClkGroup Clock (CLK)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 ******************************************************************************/
#define CLK_RCH_VAL             (4*1000*1000)       ///< 内部高速时钟频率值
#define CLK_RCL_VAL             (38400)             ///< 内部低速时钟频率值
#define CLK_XTL_VAL             (32768)             ///< 外部低速时钟频率值
#ifndef CLK_XTH_VAL
#define CLK_XTH_VAL             (32*1000*1000)      ///< 外部高速时钟频率值默认值
#endif
/**
 *******************************************************************************
 ** \brief 时钟输入源类型
 ** \note
 ******************************************************************************/
typedef enum en_clk_source
{
    ClkRCH  = 0u,               ///< 内部高速时钟
    ClkXTH  = 1u,               ///< 外部高速时钟
    ClkRCL  = 2u,               ///< 内部低速时钟
    ClkXTL  = 3u,               ///< 外部低速时钟
}en_clk_source_t;

/**
 *******************************************************************************
 ** \brief 时钟分频系数
 ******************************************************************************/
typedef enum en_clk_div
{
    ClkDiv1 = 1,                ///< 不分频
    ClkDiv2 = 2,                ///< 2 分频
    ClkDiv4 = 4,                ///< 4 分频
    ClkDiv8 = 8,                ///< 8 分频
    ClkDiv16 = 16,              ///< 16 分频
    ClkDiv32 = 32,              ///< 32 分频
    ClkDiv64 = 64,              ///< 64 分频
    ClkDiv128 = 128,            ///< 128 分频
}en_clk_div_t;

/**
 *******************************************************************************
 ** \brief 时钟周期数
 ******************************************************************************/
typedef enum en_clk_cycle
{
    ClkCycle4,                  ///< 4 个周期数
    ClkCycle16,                 ///< 16 个周期数
    ClkCycle64,                 ///< 64 个周期数
    ClkCycle256,                ///< 256 个周期数
    ClkCycle1024,               ///< 1024 个周期数
    ClkCycle4096,               ///< 4096 个周期数
    ClkCycle16384,              ///< 16384 个周期数
}en_clk_cycle_t;

/**
 *******************************************************************************
 ** \brief 时钟频率值枚举
 ******************************************************************************/
typedef enum en_clk_freq
{
    ClkFreq32768,               ///< 32.8KHz
    ClkFreq38_4K,               ///< 38.4KHz
    ClkFreq4Mhz,                ///< 4MHz
    ClkFreq8Mhz,                ///< 8MHz
    ClkFreq16Mhz,               ///< 16MHz
    ClkFreq22_12Mhz,            ///< 22.12MHz
    ClkFreq24Mhz,               ///< 24MHz
}en_clk_freq_t;

/**
 *******************************************************************************
 ** \brief 时钟模块功能功能类型选择
 ******************************************************************************/
typedef enum en_clk_func
{
    ClkFuncWkupRCH,                     ///< 唤醒时使用RCH时钟
    ClkFuncXTHEn,                       ///< 使能外部高速时钟输入引脚
    ClkFuncXTLEn,                       ///< 使能外部低速速时钟输入引脚
    ClkFuncXTLAWSON,                    ///< 使能外部低速时钟始终开启
    ClkFuncFaultEn,                     ///< 使能时钟失效检测
    ClkFuncRtcLPWEn,                    ///< 使能RTC低功耗模式
    ClkFuncLockUpEn,                    ///< 只能代码失效重启
    ClkFuncRstPinIOEn,                  ///< reset脚设为IO
    ClkFuncSwdPinIOEn,                  ///< swd脚设为IO
}en_clk_func_t;

/**
 *******************************************************************************
 ** \brief 外设时钟门控开关类型枚举
 ******************************************************************************/
typedef enum en_clk_peripheral_gate
{
    ClkPeripheralUart0      = 0u,       ///< 串口0
    ClkPeripheralUart1      = 1u,       ///< 串口1
    ClkPeripheralLpUart     = 2u,       ///< 低功耗串口
    ClkPeripheralI2c        = 4u,       ///< I2C
    ClkPeripheralSpi        = 6u,       ///< SPI
    ClkPeripheralBt         = 8u,       ///< 基础时钟
    ClkPeripheralLpTim      = 9u,       ///< 低功耗时钟
    ClkPeripheralAdt        = 10u,      ///< 高级时钟
    ClkPeripheralPca        = 14u,      ///< 可编程计数阵列
    ClkPeripheralWdt        = 15u,      ///< 看门狗
    ClkPeripheralAdcBgr     = 16u,      ///< ADC
    ClkPeripheralVcLvd      = 17u,      ///< 电压比较和低电压检测
    ClkPeripheralRtc        = 20u,      ///< RTC
    ClkPeripheralClkTrim    = 21u,      ///< 时钟校准
    ClkPeripheralTick       = 24u,      ///< 系统定时器
    ClkPeripheralCrc        = 26u,      ///< CRC
    ClkPeripheralGpio       = 28u,      ///< GPIO
    ClkPeripheralFlash      = 31u,      ///< Flash
}en_clk_peripheral_gate_t;

/**
 *******************************************************************************
 ** \brief 时钟外设调试开关
 ** \note 开启后，当调试中断时，外设时钟仍然工作
 ******************************************************************************/
typedef enum
{
    ClkDBGTim0       = 0u,             ///<  时钟0
    ClkDBGTim1       = 1u,             ///<  时钟1
    ClkDBGTim2       = 2u,             ///<  时钟2
    ClkDBGLpTim      = 3u,             ///<  低功耗时钟
    ClkDBGTim4       = 4u,             ///<  时钟4
    ClkDBGTim5       = 5u,             ///<  时钟5 
    ClkDBGTim6       = 6u,             ///<  时钟6 
    ClkDBGTPca       = 7u,             ///<  可编程计数阵列
    ClkDBGTWdt       = 8u,             ///<  看门狗
    ClkDBGTRtc       = 9u,             ///<  RTC
    ClkDBGTTick      = 10u,            ///<  systick
}en_clk_debug_t;

/**
 *******************************************************************************
 ** \brief Systick配置
 ** \note 这个systick和ARM的systick功能一致，但这个systick可设定指定时钟源来计数
 ******************************************************************************/
typedef struct
{
    en_clk_source_t     enClk;      ///< 时钟源选择
                                    ///< XTL  -> XTL
                                    ///< RCL  -> 38.5k
                                    ///< RCH  -> hclk/8
                                    ///< XTH  -> XTH
    boolean_t           bNoRef;     ///< 使用系统时钟
                                    ///< TRUE  :  使用系统时钟HCLK 
                                    ///< FALSE :  使用enClk
    uint32_t            u32LoadVal; ///< 计数周期值
}stc_clk_systickcfg_t;

/**
 *******************************************************************************
 ** \brief 时钟初始化配置
 ******************************************************************************/
typedef struct
{
    en_clk_source_t enClkSrc;       ///< 时钟源选择
    en_clk_div_t    enHClkDiv;      ///< 系统时钟分频系数
    en_clk_div_t    enPClkDiv;      ///< 外设时钟分频系数
}stc_clk_config_t;

/**
 *******************************************************************************
 ** \brief XTL晶体振幅枚举类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xtl_amp
{
    SysctrlXtlAmp0 = 0x00,                ///< 最小振幅
    SysctrlXtlAmp1 = 0x01,                ///< 正常振幅
    SysctrlXtlAmp2 = 0x02,                ///< 较大振幅
    SysctrlXtlAmp3 = 0x03,                ///< 最大振幅
}en_clk_xtl_amp_t;


/**
 *******************************************************************************
 ** \brief XTL驱动能力类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xtl_driver
{
    SysctrlXtlDriver0 = 0x00,                ///< 最弱驱动能力
    SysctrlXtlDriver1 = 0x01,                ///< 弱驱动能力
    SysctrlXtlDriver2 = 0x02,                ///< 一般驱动能力
    SysctrlXtlDriver3 = 0x03,                ///< 最强驱动能力
}en_clk_xtl_driver_t;

/**
 *******************************************************************************
 ** \brief XTH频率值范围选择类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xth_freq
{
    SysctrlXthFreq4_8MHz   = 0x00,                ///< 4~8MHz
    SysctrlXthFreq8_16MHz  = 0x01,                ///< 8~16MHz
    SysctrlXthFreq16_24MHz = 0x02,                ///< 16~24MHz
    SysctrlXthFreq24_32MHz = 0x03,                ///< 24~32MHz
}en_clk_xth_freq_t;


/**
 *******************************************************************************
 ** \brief XTH驱动能力类型定义
 ******************************************************************************/
typedef enum en_sysctrl_xth_driver
{
    SysctrlXthDriver0 = 0x00,                ///< 最弱驱动能力
    SysctrlXthDriver1 = 0x01,                ///< 弱驱动能力
    SysctrlXthDriver2 = 0x02,                ///< 一般驱动能力
    SysctrlXthDriver3 = 0x03,                ///< 最强驱动能力
}en_clk_xth_driver_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 时钟初始化 / 去初始化
en_result_t Clk_Init(stc_clk_config_t *pstcCfg);
en_result_t Clk_DeInit(void);

///< 时钟基本功能设置
en_result_t Clk_Enable(en_clk_source_t enSource, boolean_t bFlag);
en_result_t Clk_SetSource(en_clk_source_t enSource);
boolean_t Clk_GetClkRdy(en_clk_source_t enSource);
en_result_t Clk_SetXTH_StableTime(en_clk_cycle_t enCycle);
en_result_t Clk_SetRCL_StableTime(en_clk_cycle_t enCycle);
en_result_t Clk_SetXTL_StableTime(en_clk_cycle_t enCycle);
en_result_t Clk_SetXTL_Driver(en_clk_xtl_amp_t enAmp, en_clk_xtl_driver_t enDriver);
en_result_t Clk_SetXTH_Driver(en_clk_xth_freq_t enFreq, en_clk_xth_driver_t enDriver);

///< 时钟源切换
en_result_t Clk_SwitchTo(en_clk_source_t enSource);

///< 时钟频率设定
en_result_t Clk_SetRCHFreq(en_clk_freq_t enVal);
en_result_t Clk_SetRCLFreq(en_clk_freq_t enVal);

///< 时钟分频设置
en_result_t Clk_SetHClkDiv(uint8_t u8Div);
en_result_t Clk_SetPClkDiv(uint8_t u8Div);

///< 获取时钟频率
uint32_t Clk_GetHClkFreq(void);
uint32_t Clk_GetPClkFreq(void);

///< 时钟外设门控开关
en_result_t Clk_SetPeripheralGate(en_clk_peripheral_gate_t enPeripheral,
                                  boolean_t bFlag);
boolean_t Clk_GetPeripheralGate(en_clk_peripheral_gate_t enPeripheral);


///< 时钟功能开关
en_result_t Clk_SetFunc(en_clk_func_t enFunc, boolean_t bFlag);

///< systick 配置
en_result_t Clk_SysTickConfig(stc_clk_systickcfg_t *pstcCfg);
en_result_t Clk_DebugClk(en_clk_debug_t enPeri, boolean_t bFlag);

en_result_t Clk_SetRTCAdjustClkFreq(uint32_t u32val);

//Systick SKEW 获取
boolean_t Clk_SysTickSkewGet(void);
//Systick CALIB 获取
uint32_t Clk_SysTickStcalibGet(void);
//@} // ClkGroup

#ifdef __cplusplus
#endif


#endif /* __CLK_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


