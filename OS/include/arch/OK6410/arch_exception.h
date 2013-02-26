#ifndef	__EXCEPTION__
#define	__EXCEPTION__


#define	VIC0_BASE					0x71200000
#define	VIC1_BASE					0x71300000

#define	VIC_IRQ_STATUS_OFFSET		0x0
#define	VIC_FIQ_STATUS_OFFSET		0x4
#define VIC_RAW_INTR_OFFSET			0x8
#define	VIC_INT_SELECT_OFFSET		0xc
#define	VIC_INT_ENABLE_OFFSET		0x10
#define VIC_INT_ENCLEAR_OFFSET		0x14
#define	VIC_SOFT_INT_OFFSET			0x18
#define	VIC_SOFT_INT_CLEAR_OFFSET	0x1c
#define	VIC_PROTECTION_OFFSET		0x20
#define	VIC_SW_PRIO_MASK_OFFSET		0x24
#define	VIC_PRIO_DAISY_OFFSET		0x28

#define	VIC0_VECT_ADDR_BASE			(VIC0_BASE+0x100)
#define VIC1_VECT_ADDR_BASE			(VIC1_BASE+0x100)

#define VIC0_VECT_ADDR(x)			(VIC0_VECT_ADDR_BASE + x * 4)
#define VIC1_VECT_ADDR(x)			(VIC1_VECT_ADDR_BASE + x * 4)

#define VIC0_VECT_PRIO_BASE			(VIC0_BASE + 0x200)
#define VIC1_VECT_PRIO_BASE			(VIC1_BASE + 0x200)

#define VIC0_VECT_PRIO(x)			(VIC0_VECT_PRIO_BASE + x * 4)
#define VIC1_VECT_PRIO(x)			(VIC1_VECT_PRIO_BASE + x * 4)


#define VIC0_ADDR					(VIC0_BASE + 0xf00)
#define	VIC1_ADDR					(VIC1_BASE + 0xf00)



/* VIC0 */
/* include eint0 - 3*/
#define INT_EINT0					0
/* include eint4 - 11 */
#define INT_EINT1					1
#define	INT_RTC_TIC					2
#define INT_CAMIF_C					3
#define INT_CAMIF_P					4
#define INT_I2C1					5
/* include i2s0, i2s1, i2sv40 */
#define	INT_I2S01V40				6
#define	INT_3D						8
#define INT_POST0					9
#define INT_POTATOR					10
#define INT_2D						11
#define INT_TVENC					12
#define INT_SCALER					13
#define INT_BATF					14
#define INT_JPEG					15
#define INT_MFC						16
#define INT_SDMA0					17
#define INT_SDMA1					18
#define INT_ARM_DMAERR				19
#define INT_ARM_DMA					20
#define INT_ARM_DMAS				21
#define INT_KEYPAD					22
#define INT_TIMER0					23
#define INT_TIMER1					24
#define INT_TIMER2					25
#define INT_WDT						26
#define INT_TIMER3					27
#define INT_TIMER4					28
#define INT_LCD0					29
#define INT_LCD1					30
#define INT_LCD2					31


/* VIC1 */


/* include eint 12 - 19 */
#define INT_EINT2					32
/* include eint 20 - 27 */
#define INT_EINT3					33	
#define INT_PCM0					34
#define INT_PCM1					35
#define INT_AC97					36
#define INT_UART0					37
#define INT_UART1					38
#define INT_UART2					39
#define INT_UART3					40
#define INT_DMA0					41
#define INT_DMA1					42
#define INT_ONENAND0				43
#define INT_ONENAND1				44
#define INT_NFC						45
#define INT_CFC						46
#define INT_UHOST					47
#define INT_SPI0					48
#define	INT_SPI1_HSMMC2				49
#define INT_I2C0					50
#define INT_HSITX					51
#define INT_HSIRX					52
/* include eint group 1 ~ 9 */
#define INT_EINT4					53
#define INT_MSM						54
#define INT_HOSTIF					55
#define INT_HSMMC0					56
#define INT_HSMMC1					57
#define INT_OTG						58
#define INT_IRDA					59
#define INT_RTC_ALARM				60
#define INT_SEC						61
#define INT_PENDUP					62
#define INT_ADC						63

void unexception_abort(unsigned long sp, int kind, unsigned long pc);

void swi(void);
void irq_exception(int num);
void fiq_exception(void);
void vic_init(void);
int irq_request(int num, void(*isr_func)(void));
void irq_unmask(int num);
void irq_ack_mask(int num);
void irq_free(int num);
int find_vic_num(void);
void ret_from_irq(void);
void irq_bootomhalf(void);




extern void (*isr[])(void);


#endif
