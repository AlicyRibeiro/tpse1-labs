#ifndef _CLOCK_MODULE_REGISTERS_
#define _CLOCK_MODULE_REGISTERS_

//#include "playPong.h"

#pragma region CLOCK MODULE REGISTERS
// _SOC_AM33XX_H_
#pragma region L4_WKUP Peripheral Memory Map
#define CM_PER                          (SOC_CM_PER_REGS)      // (0x44E00000u) end 0x44E0_03FF 1KB Clock Module Peripheral Registers
#define CM_WKUP                         (SOC_CM_WKUP_REGS)     // (0x44E00400u) end 0x44E0_04FF 256 Bytes Clock Module Wakeup Registers
#define CM_DPLL                         (SOC_CM_DPLL_REGS)     // (0x44E00500u) end 0x44E0_05FF 256 Bytes Clock Module PLL Registers
#define CM_MPU                          (SOC_CM_MPU_REGS)      // (0x44E00600u) end 0x44E0_06FF 256 Bytes Clock Module MPU Registers
#define CM_DEVICE                       (SOC_CM_DEVICE_REGS)   // (0x44E00700u) end 0x44E0_07FF 256 Bytes Clock Module Device Registers
#define CM_RTC                          (SOC_CM_RTC_REGS)      // (0x44E00800u) end 0x44E0_08FF 256 Bytes Clock Module RTC Registers
#define CM_GFX                          (SOC_CM_GFX_REGS)      // (0x44E00900u) end 0x44E0_09FF 256 Bytes Clock Module Graphics Controller Registers
#define CM_CEFUSE                       (SOC_CM_CEFUSE_REGS)   // (0x44E00A00u) end 0x44E0_0AFF 256 Bytes Clock Module Efuse Registers
#pragma endregion L4_WKUP Peripheral Memory Map

// CM_PER REGISTER
#define CM_PER_L4LS_CLKSTCTRL           (0x0u)
#define CM_PER_L3S_CLKSTCTRL            (0x4u)
#define CM_PER_L3_CLKSTCTRL             (0xCu)
#define CM_PER_CPGMAC0_CLKCTRL          (0x14u)
#define CM_PER_LCDC_CLKCTRL             (0x18u)
#define CM_PER_USB0_CLKCTRL             (0x1Cu)
#define CM_PER_TPTC0_CLKCTRL            (0x24u)
#define CM_PER_EMIF_CLKCTRL             (0x28u)
#define CM_PER_OCMCRAM_CLKCTRL          (0x2Cu)
#define CM_PER_GPMC_CLKCTRL             (0x30u)
#define CM_PER_MCASP0_CLKCTRL           (0x34u)
#define CM_PER_UART5_CLKCTRL            (0x38u)
#define CM_PER_MMC0_CLKCTRL             (0x3Cu)
#define CM_PER_ELM_CLKCTRL              (0x40u)
#define CM_PER_I2C2_CLKCTRL             (0x44u)
#define CM_PER_I2C1_CLKCTRL             (0x48u)
#define CM_PER_SPI0_CLKCTRL             (0x4Cu)
#define CM_PER_SPI1_CLKCTRL             (0x50u)
#define CM_PER_L4LS_CLKCTRL             (0x60u)
#define CM_PER_L4FW_CLKCTRL             (0x64u)
#define CM_PER_MCASP1_CLKCTRL           (0x68u)
#define CM_PER_UART1_CLKCTRL            (0x6Cu)
#define CM_PER_UART2_CLKCTRL            (0x70u)
#define CM_PER_UART3_CLKCTRL            (0x74u)
#define CM_PER_UART4_CLKCTRL            (0x78u)
#define CM_PER_TIMER7_CLKCTRL           (0x7Cu)
#define CM_PER_TIMER2_CLKCTRL           (0x80u)
#define CM_PER_TIMER3_CLKCTRL           (0x84u)
#define CM_PER_TIMER4_CLKCTRL           (0x88u)
#define CM_PER_GPIO1_CLKCTRL            (0xACu)
#define CM_PER_GPIO2_CLKCTRL            (0xB0u)
#define CM_PER_GPIO3_CLKCTRL            (0xB4u)
#define CM_PER_TPCC_CLKCTRL             (0xBCu)
#define CM_PER_DCAN0_CLKCTRL            (0xC0u)
#define CM_PER_DCAN1_CLKCTRL            (0xC4u)
#define CM_PER_EPWMSS1_CLKCTRL          (0xCCu) 
#define CM_PER_EPWMSS0_CLKCTRL          (0xD4u) 
#define CM_PER_EPWMSS2_CLKCTRL          (0xD8u) 
#define CM_PER_L3_INSTR_CLKCTRL         (0xDCu) 
#define CM_PER_L3_CLKCTRL               (0xE0u) 
#define CM_PER_IEEE5000_CLKCTRL         (0xE4u)
#define CM_PER_PRU_ICSS_CLKCTRL         (0xE8u)
// Substituido #define CM_PER_PRUSS_CLKCTRL            (0xE8u) 
#define CM_PER_TIMER5_CLKCTRL           (0xECu) 
#define CM_PER_TIMER6_CLKCTRL           (0xF0u) 
#define CM_PER_MMC1_CLKCTRL             (0xF4u) 
#define CM_PER_MMC2_CLKCTRL             (0xF8u) 
#define CM_PER_TPTC1_CLKCTRL            (0xFCu) 
#define CM_PER_TPTC2_CLKCTRL            (0x100u) 
#define CM_PER_SPINLOCK_CLKCTRL         (0x10Cu) 
#define CM_PER_MAILBOX0_CLKCTRL         (0x110u) 
#define CM_PER_L4HS_CLKSTCTRL           (0x11Cu) 
#define CM_PER_L4HS_CLKCTRL             (0x120u) 
#define CM_PER_OCPWP_L3_CLKSTCTRL       (0x12Cu)
#define CM_PER_OCPWP_CLKCTRL            (0x130U)
#define CM_PER_PRU_ICSS_CLKSTCTRL       (0x140U)
// Substituido #define CM_PER_PRUSS_CLKSTCTRL          (0x140u) 
#define CM_PER_CPSW_CLKSTCTRL           (0x144u) 
#define CM_PER_LCDC_CLKSTCTRL           (0x148u) 
#define CM_PER_CLKDIV32K_CLKCTRL        (0x14Cu) 
#define CM_PER_CLK_24MHZ_CLKSTCTRL      (0x150u) 

// CM_WKUP Registers
#define CM_WKUP_CLKSTCTRL               (0x0u) 
#define CM_WKUP_CONTROL_CLKCTRL         (0x4u) 
#define CM_WKUP_GPIO0_CLKCTRL           (0x8u) 
#define CM_WKUP_L4WKUP_CLKCTRL          (0xCu) 
#define CM_WKUP_TIMER0_CLKCTRL          (0x10u) 
#define CM_WKUP_DEBUGSS_CLKCTRL         (0x14u) 
#define CM_L3_AON_CLKSTCTRL             (0x18u) 
#define CM_AUTOIDLE_DPLL_MPU            (0x1Cu) 
#define CM_IDLEST_DPLL_MPU              (0x20u) 
#define CM_SSC_DELTAMSTEP_DPLL_MPU      (0x24u) 
#define CM_SSC_MODFREQDIV_DPLL_MPU      (0x28u) 
#define CM_CLKSEL_DPLL_MPU              (0x2Cu) 
#define CM_AUTOIDLE_DPLL_DDR            (0x30u) 
#define CM_IDLEST_DPLL_DDR              (0x34u) 
#define CM_SSC_DELTAMSTEP_DPLL_DDR      (0x38u) 
#define CM_SSC_MODFREQDIV_DPLL_DDR      (0x3Cu) 
#define CM_CLKSEL_DPLL_DDR              (0x40u) 
#define CM_AUTOIDLE_DPLL_DISP           (0x44u) 
#define CM_IDLEST_DPLL_DISP             (0x48u) 
#define CM_SSC_DELTAMSTEP_DPLL_DISP     (0x4Cu) 
#define CM_SSC_MODFREQDIV_DPLL_DISP     (0x50u) 
#define CM_CLKSEL_DPLL_DISP             (0x54u) 
#define CM_AUTOIDLE_DPLL_CORE           (0x58u) 
#define CM_IDLEST_DPLL_CORE             (0x5Cu) 
#define CM_SSC_DELTAMSTEP_DPLL_CORE     (0x60u) 
#define CM_SSC_MODFREQDIV_DPLL_CORE     (0x64u) 
#define CM_CLKSEL_DPLL_CORE             (0x68u) 
#define CM_AUTOIDLE_DPLL_PER            (0x6Cu) 
#define CM_IDLEST_DPLL_PER              (0x70u) 
#define CM_SSC_DELTAMSTEP_DPLL_PER      (0x74u) 
#define CM_SSC_MODFREQDIV_DPLL_PER      (0x78u) 
#define CM_CLKDCOLDO_DPLL_PER           (0x7Cu) 
#define CM_DIV_M4_DPLL_CORE             (0x80u) 
#define CM_DIV_M5_DPLL_CORE             (0x84u) 
#define CM_CLKMODE_DPLL_MPU             (0x88u) 
#define CM_CLKMODE_DPLL_PER             (0x8Cu) 
#define CM_CLKMODE_DPLL_CORE            (0x90u) 
#define CM_CLKMODE_DPLL_DDR             (0x94u) 
#define CM_CLKMODE_DPLL_DISP            (0x98u) 
#define CM_CLKSEL_DPLL_PERIPH           (0x9Cu) 
#define CM_DIV_M2_DPLL_DDR              (0xA0u) 
#define CM_DIV_M2_DPLL_DISP             (0xA4u) 
#define CM_DIV_M2_DPLL_MPU              (0xA8u) 
#define CM_DIV_M2_DPLL_PER              (0xACu) 
#define CM_WKUP_WKUP_M3_CLKCTRL         (0xB0u) 
#define CM_WKUP_UART0_CLKCTRL           (0xB4u) 
#define CM_WKUP_I2C0_CLKCTRL            (0xB8u) 
#define CM_WKUP_ADC_TSC_CLKCTRL         (0xBCu) 
#define CM_WKUP_SMARTREFLEX0_CLKCTRL    (0xC0u) 
#define CM_WKUP_TIMER1_CLKCTRL          (0xC4u) 
#define CM_WKUP_SMARTREFLEX1            (0xC8u) 
#define CM_L4_WKUP_AON_CLKSTCTRL        (0xCCu) 
#define CM_WKUP_WDT1_CLKCTRL            (0xD4u) 
#define CM_DIV_M6_DPLL_CORE             (0xD8u) 

// CM_DPLL Registers
#define CLKSEL_TIMER7_CLK               (0x4u)
#define CLKSEL_TIMER2_CLK               (0x8u)
#define CLKSEL_TIMER3_CLK               (0xCu)
#define CLKSEL_TIMER4_CLK               (0x10u)
#define CM_MAC_CLKSEL                   (0x14u)
#define CLKSEL_TIMER5_CLK               (0x18u)
#define CLKSEL_TIMER6_CLK               (0x1Cu)
#define CM_CPTS_RFT_CLKSEL              (0x20u)
#define CLKSEL_TIMER1MS_CLK             (0x28u)
#define CLKSEL_GFX_FCLK                 (0x2Cu)
#define CLKSEL_PRU_ICSS_OCP_CLK         (0x30u)
#define CLKSEL_LCDC_PIXEL_CLK           (0x34u)
#define CLKSEL_WDT1_CLK                 (0x38u)
#define CLKSEL_GPIO0_DBCLK              (0x3Cu)

// CM_MPU Registers
#define CM_MPU_CLKSTCTRL                (0x0u)
#define CM_MPU_MPU_CLKCTRL              (0x4u)

// CM_DEVICE Register
#define CM_CLKOUT_CTRL                  (0x0u)

// CM_RTC Registers
#define CM_RTC_RTC_CLKCTRL              (0x0u)
#define CM_RTC_CLKSTCTRL                (0x4u)

// CM_GFX Registers
#define CM_GFX_L3_CLKSTCTRL             (0x0u)
#define CM_GFX_GFX_CLKCTRL              (0x4u)
#define CM_GFX_L4LS_GFX_CLKSTCTR        (0xCu)
#define CM_GFX_MMUCFG_CLKCTRL           (0x10u)
#define CM_GFX_MMUDATA_CLKCTRL          (0x14u)

// CM_CEFUSE Registers
#define CM_CEFUSE_CLKSTCTRL             (0x0u)
#define CM_CEFUSE_CEFUSE_CLKCTRL        (0x20u)

#pragma endregion CLOCK MODULE REGISTERS

/**
 * @brief Clock Modules Registers & their coresponding offsets from their domainx: TRM 8.1.12
 **/
typedef enum verify_clock_module_registers{
   // CKM_PER zone
   CLKM_PER_L4LS_CLKSTCTRL      = CM_PER_L4LS_CLKSTCTRL,
   CLKM_PER_L3S_CLKSTCTRL       = CM_PER_L3S_CLKSTCTRL,
   // Inexistente CKM_PER_L4FW_CLKSTCTRL      = 0x008,CKM_PER_L4FW_CLKSTCTRL
   CLKM_PER_L3_CLKSTCTRL        = CM_PER_L3_CLKSTCTRL,//0x00C,
   CLKM_PER_CPGMAC0_CLKCTRL     = CM_PER_CPGMAC0_CLKCTRL,//0x014,
   CLKM_PER_LCDC_CLKCTRL        = CM_PER_LCDC_CLKCTRL,//0x018,
   CLKM_PER_USB0_CLKCTRL        = CM_PER_USB0_CLKCTRL,//0x01C,
   CLKM_PER_TPTC0_CLKCTRL       = CM_PER_TPTC0_CLKCTRL,//0x024,
   CLKM_PER_EMIF_CLKCTRL        = CM_PER_EMIF_CLKCTRL,//0x028,
   CLKM_PER_OCMCRAM_CLKCTRL     = CM_PER_OCMCRAM_CLKCTRL,//0x02C,
   CLKM_PER_GPMC_CLKCTRL        = CM_PER_GPMC_CLKCTRL,//0x030,
   CLKM_PER_MCASP0_CLKCTRL      = CM_PER_MCASP0_CLKCTRL,//0x034,
   CLKM_PER_UART5_CLKCTRL       = CM_PER_UART5_CLKCTRL,//0x038,
   CLKM_PER_MMC0_CLKCTRL        = CM_PER_MMC0_CLKCTRL,//0x03C,
   CLKM_PER_ELM_CLKCTRL         = CM_PER_ELM_CLKCTRL,//0x040,
   CLKM_PER_I2C2_CLKCTRL        = CM_PER_I2C2_CLKCTRL,//0x044,
   CLKM_PER_I2C1_CLKCTRL        = CM_PER_I2C1_CLKCTRL,//0x048,
   CLKM_PER_SPI0_CLKCTRL        = CM_PER_SPI0_CLKCTRL,//0x04C,
   CLKM_PER_SPI1_CLKCTRL        = CM_PER_SPI1_CLKCTRL,//0x050,
   CLKM_PER_L4LS_CLKCTRL        = CM_PER_L4LS_CLKCTRL,//0x060,
   CLKM_PER_L4FW_CLKCTRL        = CM_PER_L4FW_CLKCTRL,//0x064,
   CLKM_PER_MCASP1_CLKCTRL      = CM_PER_MCASP1_CLKCTRL,//0x068,
   CLKM_PER_UART1_CLKCTRL       = CM_PER_UART1_CLKCTRL,//0x06C,
   CLKM_PER_UART2_CLKCTRL       = CM_PER_UART2_CLKCTRL,//0x070,
   CLKM_PER_UART3_CLKCTRL       = CM_PER_UART3_CLKCTRL,//0x074,
   CLKM_PER_UART4_CLKCTRL       = CM_PER_UART4_CLKCTRL,//0x078,
   CLKM_PER_TIMER7_CLKCTRL      = CM_PER_TIMER7_CLKCTRL,//0x07C,
   CLKM_PER_TIMER2_CLKCTRL      = CM_PER_TIMER2_CLKCTRL,//0x080,
   CLKM_PER_TIMER3_CLKCTRL      = CM_PER_TIMER3_CLKCTRL,//0x084,
   CLKM_PER_TIMER4_CLKCTRL      = CM_PER_TIMER4_CLKCTRL,//0x088,
   CLKM_PER_GPIO1_CLKCTRL       = CM_PER_GPIO1_CLKCTRL,//0x0AC,
   CLKM_PER_GPIO2_CLKCTRL       = CM_PER_GPIO2_CLKCTRL,//0x0B0,
   CLKM_PER_GPIO3_CLKCTRL       = CM_PER_GPIO3_CLKCTRL,//0x0B4,
   CLKM_PER_TPCC_CLKCTRL        = CM_PER_TPCC_CLKCTRL,//0x0BC,
   CLKM_PER_DCAN0_CLKCTRL       = CM_PER_DCAN0_CLKCTRL,//0x0C0,
   CLKM_PER_DCAN1_CLKCTRL       = CM_PER_DCAN1_CLKCTRL,//0x0C4,
   CLKM_PER_EPWMSS1_CLKCTRL     = CM_PER_EPWMSS1_CLKCTRL,//0x0CC,
   // Inexistente CKM_PER_EMIF_FW_CLKCTRL     = CM_PER_EMIF_FW_CLKCTRL,//0x0D0,
   CLKM_PER_EPWMSS0_CLKCTRL     = CM_PER_EPWMSS0_CLKCTRL,//0x0D4,
   CLKM_PER_EPWMSS2_CLKCTRL     = CM_PER_EPWMSS2_CLKCTRL,//0x0D8,
   CLKM_PER_L3_INSTR_CLKCTRL    = CM_PER_L3_INSTR_CLKCTRL,//0x0DC,
   CLKM_PER_L3_CLKCTRL          = CM_PER_L3_CLKCTRL,//0x0E0,
   CLKM_PER_IEEE5000_CLKCTRL    = CM_PER_IEEE5000_CLKCTRL,//0x0E4,
   CLKM_PER_PRU_ICSS_CLKCTRL    = CM_PER_PRU_ICSS_CLKCTRL,//0x0E8,
   CLKM_PER_TIMER5_CLKCTRL      = CM_PER_TIMER5_CLKCTRL,//0x0EC,
   CLKM_PER_TIMER6_CLKCTRL      = CM_PER_TIMER6_CLKCTRL,//0x0F0,
   CLKM_PER_MMC1_CLKCTRL        = CM_PER_MMC1_CLKCTRL,//0x0F4,
   CLKM_PER_MMC2_CLKCTRL        = CM_PER_MMC2_CLKCTRL,//0x0F8,
   CLKM_PER_TPTC1_CLKCTRL       = CM_PER_TPTC1_CLKCTRL,//0x0FC,
   CLKM_PER_TPTC2_CLKCTRL       = CM_PER_TPTC2_CLKCTRL,//0x100,
   CLKM_PER_SPINLOCK_CLKCTRL    = CM_PER_SPINLOCK_CLKCTRL,//0x10C,
   CLKM_PER_MAILBOX0_CLKCTRL    = CM_PER_MAILBOX0_CLKCTRL,//0x110,
   CLKM_PER_L4HS_CLKSTCTRL      = CM_PER_L4HS_CLKSTCTRL,//0x11C,
   CLKM_PER_L4HS_CLKCTRL        = CM_PER_L4HS_CLKCTRL,//0x120,
   CLKM_PER_OCPWP_L3_CLKSTCTRL  = CM_PER_OCPWP_L3_CLKSTCTRL,//0x12C,
   CLKM_PER_OCPWP_CLKCTRL       = CM_PER_OCPWP_CLKCTRL,//0x130,
   CLKM_PER_PRU_ICSS_CLKSTCTRL  = CM_PER_PRU_ICSS_CLKSTCTRL,//0x140,
   CLKM_PER_CPSW_CLKSTCTRL      = CM_PER_CPSW_CLKSTCTRL,//0x144,
   CLKM_PER_LCDC_CLKSTCTRL      = CM_PER_LCDC_CLKSTCTRL,//0x148,
   CLKM_PER_CLKDIV32K_CLKCTRL   = CM_PER_CLKDIV32K_CLKCTRL,//0x14C,
   CLKM_PER_CLK_24MHZ_CLKSTCTRL = CM_PER_CLK_24MHZ_CLKSTCTRL,//0x150,
   // CKM_WKUP zone
   CLKM_WKUP_CLKSTCTRL            = 0x00,
   CLKM_WKUP_CONTROL_CLKCTRL      = 0x04,
   CLKM_WKUP_GPIO0_CLKCTRL        = 0x08,
   CLKM_WKUP_L4WKUP_CLKCTRL       = 0x0C,
   CLKM_WKUP_TIMER0_CLKCTRL       = 0x10,
   CLKM_WKUP_DEBUGSS_CLKCTRL      = 0x14,
   CLKM_L3_AON_CLKSTCTRL          = 0x18,
   CLKM_AUTOIDLE_DPLL_MPU         = 0x1C,
   CLKM_IDLEST_DPLL_MPU           = 0x20,
   CLKM_SSC_DELTAMSTEP_DPLL_MPU   = 0x24,
   CLKM_SSC_MODFREQDIV_DPLL_MPU   = 0x28,
   CLKM_CLKSEL_DPLL_MPU           = 0x2C,
   CLKM_AUTOIDLE_DPLL_DDR         = 0x30,
   CLKM_IDLEST_DPLL_DDR           = 0x34,
   CLKM_SSC_DELTAMSTEP_DPLL_DDR   = 0x38,
   CLKM_SSC_MODFREQDIV_DPLL_DDR   = 0x3C,
   CLKM_CLKSEL_DPLL_DDR           = 0x40,
   CLKM_AUTOIDLE_DPLL_DISP        = 0x44,
   CLKM_IDLEST_DPLL_DISP          = 0x48,
   CLKM_SSC_DELTAMSTEP_DPLL_DISP  = 0x4C,
   CLKM_SSC_MODFREQDIV_DPLL_DISP  = 0x50,
   CLKM_CLKSEL_DPLL_DISP          = 0x54,
   CLKM_AUTOIDLE_DPLL_CORE        = 0x58,
   CLKM_IDLEST_DPLL_CORE          = 0x5C,
   CLKM_SSC_DELTAMSTEP_DPLL_CORE  = 0x60,
   CLKM_SSC_MODFREQDIV_DPLL_CORE  = 0x64,
   CLKM_CLKSEL_DPLL_CORE          = 0x68,
   CLKM_AUTOIDLE_DPLL_PER         = 0x6C,
   CLKM_IDLEST_DPLL_PER           = 0x70,
   CLKM_SSC_DELTAMSTEP_DPLL_PER   = 0x74,
   CLKM_SSC_MODFREQDIV_DPLL_PER   = 0x78,
   CLKM_CLKDCOLDO_DPLL_PER        = 0x7C,
   CLKM_DIV_M4_DPLL_CORE          = 0x80,
   CLKM_DIV_M5_DPLL_CORE          = 0x84,
   CLKM_CLKMODE_DPLL_MPU          = 0x88,
   CLKM_CLKMODE_DPLL_PER          = 0x8C,
   CLKM_CLKMODE_DPLL_CORE         = 0x90,
   CLKM_CLKMODE_DPLL_DDR          = 0x94,
   CLKM_CLKMODE_DPLL_DISP         = 0x98,
   CLKM_CLKSEL_DPLL_PERIPH        = 0x9C,
   CLKM_DIV_M2_DPLL_DDR           = 0xA0,
   CLKM_DIV_M2_DPLL_DISP          = 0xA4,
   CLKM_DIV_M2_DPLL_MPU           = 0xA8,
   CLKM_DIV_M2_DPLL_PER           = 0xAC,
   CLKM_WKUP_WKUP_M3_CLKCTRL      = 0xB0,
   CLKM_WKUP_UART0_CLKCTRL        = 0xB4,
   CLKM_WKUP_I2C0_CLKCTRL         = 0xB8,
   CLKM_WKUP_ADC_TSC_CLKCTRL      = 0xBC,
   CLKM_WKUP_SMARTREFLEX0_CLKCTRL = 0xC0,
   CLKM_WKUP_TIMER1_CLKCTRL       = 0xC4,
   CLKM_WKUP_SMARTREFLEX1_CLKCTRL = 0xC8,
   CLKM_L4_WKUP_AON_CLKSTCTRL     = 0xCC,
   CLKM_WKUP_WDT1_CLKCTRL         = 0xD4,
   CLKM_DIV_M6_DPLL_CORE          = 0xD8
}CLK_MODULE_REG;

/**
 * @brief Clock Modules Domaines bases: TRM 2.1
 **/
typedef enum
{
   CLKM_PER     = CM_PER,
   CLKM_WKUP    = CM_WKUP,
   CLKM_DPLL    = CM_DPLL,
   CLKM_MPU     = CM_MPU,
   CLKM_DEVICE  = CM_DEVICE,
   CLKM_RTC     = CM_RTC,
   CLKM_GFX     = CM_GFX,
   CLKM_CEFUSE  = CM_CEFUSE
}CLK_MODULE;

/**
 * @fn void CLKM_setCLKModuleRegister(CLK_MODULE_t module, CLKM_MODULE_REG reg, uint32_t value)
 * @brief               Set the clock register to a certain value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to set value.
 * @param[in]  value    Value to set register to.
 * @return              void
 **/
void ckmSetCLKModuleRegister(CLK_MODULE module, CLK_MODULE_REG reg, unsigned int value);
/**
 * @fn uint32_t CLKM_getCLKModuleRegister(CLK_MODULE_t module, CLKM_MODULE_REG reg)
 * @brief               Get the clock register value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to get the value from.
 * @return              value of the clock register.
 **/
unsigned int ckmGetCLKModuleRegister(CLK_MODULE module, CLK_MODULE_REG reg);
void ckmVerifySetCLKModuleRegister(CLK_MODULE module, CLK_MODULE_REG reg, unsigned int value);

#endif