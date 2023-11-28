/* Alternate pin name */
PA_4_ALT1  = PA_4  | ALT1,
PA_4_ALT2  = PA_4  | ALT2,
PA_5_ALT1  = PA_5  | ALT1,
PA_5_ALT2  = PA_5  | ALT2,
PA_6_ALT1  = PA_6  | ALT1,
PA_6_ALT2  = PA_6  | ALT2,
PA_7_ALT1  = PA_7  | ALT1,
PA_7_ALT2  = PA_7  | ALT2,
PC_3_ALT1  = PC_3  | ALT1,
PC_3_ALT2  = PC_3  | ALT2,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PE_4,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PE_5,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PE_6,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PB_7,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = PB_8,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = PE_7,
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = PB_15,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = PF_2,
#endif

/* USB */
#ifdef USBCON
  USB_OTG_HS_DM   = PA_11,
  USB_OTG_HS_DP   = PA_12,
#endif