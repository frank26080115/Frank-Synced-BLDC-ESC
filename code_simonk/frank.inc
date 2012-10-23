;***********************************************************
;* Frank's Custom ESC                                      *
;***********************************************************

.equ	F_CPU		= 16000000
.equ	USE_INT0	= 0
.equ	USE_I2C		= 1
.equ	USE_UART	= 1
.equ	USE_ICP		= 1

;*********************
; PORT definitions     *
;*********************
.equ	ApFET_port	= PORTD
.equ	ApFET		= 5	;o
.equ	AnFET_port	= PORTD
.equ	AnFET		= 7	;o
.equ	BpFET_port	= PORTB
.equ	BpFET		= 1	;o
.equ	BnFET_port	= PORTB
.equ	BnFET		= 2	;o
.equ	CpFET_port	= PORTD
.equ	CpFET		= 4	;o
.equ	CnFET_port	= PORTD
.equ	CnFET		= 3	;o

;* ADC inputs for BEMF
.equ	mux_a		= 1	; phase input
.equ	mux_b		= 0	; phase input
.equ	mux_c		= 7	; phase input

.equ	i2c_data	= 4	; ADC4/SDA
.equ	i2c_clk		= 5	; ADC5/SCL

.equ	c_comp		= 6	;i common comparator input (AIN0)
.equ	rcp_in		= 0	;i r/c pulse input

.equ	sj_addr_0_port	= PORTD;
.equ	sj_addr_0	= 1;
.equ	sj_addr_1_port	= PORTC;
.equ	sj_addr_1	= 3;
.equ	sj_addr_2_port	= PORTC;
.equ	sj_addr_2	= 2;

.equ	INIT_PB		= 0
.equ	DIR_PB		= (1<<BpFET)+(1<<BnFET)
.equ	INIT_PC		= 0
.equ	DIR_PC		= 0
.equ	INIT_PD		= 1
.equ	DIR_PD		= (1<<CpFET)+(1<<CnFET)+(1<<AnFET)+(1<<ApFET)

.MACRO comp_init
	in	@0, SFIOR
	sbr	@0, (1<<ACME)	; set Analog Comparator Multiplexer Enable
	out	SFIOR, @0
	cbi	ADCSRA, ADEN	; disable ADC
.ENDMACRO
.MACRO set_comp_phase_a
	ldi	@0, mux_a	; set comparator multiplexer to phase A
	out	ADMUX, @0
.ENDMACRO
.MACRO set_comp_phase_b
	ldi	@0, mux_b	; set comparator multiplexer to phase B
	out	ADMUX, @0
.ENDMACRO
.MACRO set_comp_phase_c
	ldi	@0, mux_c	; set comparator multiplexer to phase C
	out	ADMUX, @0
.ENDMACRO

.MACRO rcp_int_enable
	in	@0, TIMSK
	sbr	@0, (1<<TICIE1)	; enable icp1_int
	out	TIMSK, @0
.ENDMACRO
.MACRO rcp_int_disable
	in	@0, TIMSK
	cbr	@0, (1<<TICIE1)	; disable icp1_int
	out	TIMSK, @0
.ENDMACRO
.MACRO rcp_int_rising_edge
	ldi	@0, T1CLK
	out	TCCR1B, @0
.ENDMACRO
.MACRO rcp_int_falling_edge
	ldi	@0, T1CLK & ~(1<<ICES1)
	out	TCCR1B, @0
.ENDMACRO

.MACRO ApFET_on
	sbi	PORTD, ApFET
.ENDMACRO
.MACRO ApFET_off
	cbi	PORTD, ApFET
.ENDMACRO
.MACRO ApFET_on_reg
	sbr	@0, 1<<ApFET
.ENDMACRO
.MACRO ApFET_off_reg
	cbr	@0, 1<<ApFET
.ENDMACRO
.MACRO AnFET_on
	sbi	PORTD, AnFET
.ENDMACRO
.MACRO AnFET_off
	cbi	PORTD, AnFET
.ENDMACRO
.MACRO AnFET_on_reg
	sbr	@0, 1<<AnFET
.ENDMACRO
.MACRO AnFET_off_reg
	cbr	@0, 1<<AnFET
.ENDMACRO
.MACRO BpFET_on
	sbi	PORTB, BpFET
.ENDMACRO
.MACRO BpFET_off
	cbi	PORTB, BpFET
.ENDMACRO
.MACRO BpFET_on_reg
	sbr	@0, 1<<BpFET
.ENDMACRO
.MACRO BpFET_off_reg
	cbr	@0, 1<<BpFET
.ENDMACRO
.MACRO BnFET_on
	sbi	PORTB, BnFET
.ENDMACRO
.MACRO BnFET_off
	cbi	PORTB, BnFET
.ENDMACRO
.MACRO BnFET_on_reg
	sbr	@0, 1<<BnFET
.ENDMACRO
.MACRO BnFET_off_reg
	cbr	@0, 1<<BnFET
.ENDMACRO
.MACRO CpFET_on
	sbi	PORTD, CpFET
.ENDMACRO
.MACRO CpFET_off
	cbi	PORTD, CpFET
.ENDMACRO
.MACRO CpFET_on_reg
	sbr	@0, 1<<CpFET
.ENDMACRO
.MACRO CpFET_off_reg
	cbr	@0, 1<<CpFET
.ENDMACRO
.MACRO CnFET_on
	sbi	PORTD, CnFET
.ENDMACRO
.MACRO CnFET_off
	cbi	PORTD, CnFET
.ENDMACRO
.MACRO CnFET_on_reg
	sbr	@0, 1<<CnFET
.ENDMACRO
.MACRO CnFET_off_reg
	cbr	@0, 1<<CnFET
.ENDMACRO

.MACRO all_pFETs_off
	ApFET_off
	BpFET_off
	CpFET_off
.ENDMACRO
.MACRO all_nFETs_off
	AnFET_off
	BnFET_off
	CnFET_off
.ENDMACRO
.MACRO pFET_brake
	ApFET_on
	BpFET_on
	CpFET_on
.ENDMACRO
.MACRO nFET_brake
	AnFET_on
	BnFET_on
	CnFET_on
.ENDMACRO

.MACRO RED_on
.ENDMACRO
.MACRO RED_off
.ENDMACRO
.MACRO GRN_on
.ENDMACRO
.MACRO GRN_off
.ENDMACRO

.MACRO frank_read_addr
	; first setup internal pull-up resistors to read solder jumpers for addresses
	in	@0, sj_addr_0_port
	ori	@0, (1<<sj_addr_0)
	out	sj_addr_0_port, @0
	in	@0, sj_addr_1_port
	ori	@0, (1<<sj_addr_1)
	out	sj_addr_1_port, @0
	in	@0, sj_addr_2_port
	ori	@0, (1<<sj_addr_2)
	out	sj_addr_2_port, @0
	; small delay to settle signal
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	; even if we are not using I2C, we still need to load TWAR
	; because UART is modified to use it for MOTOR_ID
	ldi	@0, 0
	sbis	sj_addr_0_port, (1<<sj_addr_0)
	ori	@0, (1<<0)
	sbis	sj_addr_1_port, (1<<sj_addr_1)
	ori	@0, (1<<1)
	sbis	sj_addr_2_port, (1<<sj_addr_2)
	ori	@0, (1<<2)
	inc	@0 ; MOTOR_ID used to start with 1
	lsl	@0
	ldi	@1, I2C_ADDR
	add	@0, @1
	out	TWAR, @0
.ENDMACRO

.MACRO frank_load_motor_id
	in		@0, TWAR
	subi	@0, I2C_ADDR
	lsr		@0
.ENDMACRO