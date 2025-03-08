[bits 64]



section .data

global InterruptCode
raxp dq 0
global InterruptNum
global InstructionPointer
global ThreadStart
global RSPPoint

InterruptMutex dq 0

InterruptNum db 0
InterruptCode dq 0
InstructionPointer dq 0

global SYSTEMCALL

SYSTEMCALL dq 0

savedRIP dq 0 

RSPPoint dq 0

section .bss

section .text
extern InterruptRouter
extern PIC_sendEOI
extern UpdateThreadManager
extern local_apic_send_eoi

FPU_ON dq 0
SSE_ON dq 0
AVX_OM dq 0

global TURN_FPU_ON

TURN_FPU_ON:
	mov rax, 1
	mov [FPU_ON], rax
	ret

%macro pusha 0	

	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8

	push rdi
	push rsi
	push rbp

	push rdx
	push rcx
	push rbx
	push rax

%endmacro

%macro popa 0

	pop rax
	pop rbx
	pop rcx
	pop rdx

	pop rbp
	pop rsi
	pop rdi

	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

%endmacro

;PIC_sendEOI(unsigned char irq)

%macro Handle 0
	pop rcx
	mov rdx, rsp
	call InterruptRouter
%endmacro

global ISR0
global ISR1
global ISR2
global ISR3
global ISR4
global ISR5
global ISR6
global ISR7
global ISR8
global ISR9
global ISR10
global ISR11
global ISR12
global ISR13
global ISR14
global ISR15
global ISR16
global ISR17
global ISR18
global ISR19
global ISR20
global ISR21
global ISR22
global ISR23
global ISR24
global ISR25
global ISR26
global ISR27
global ISR28
global ISR29
global ISR30
global ISR31



global ISR32
global ISR33
global ISR34
global ISR35
global ISR36
global ISR37
global ISR38
global ISR39
global ISR40
global ISR41
global ISR42
global ISR43
global ISR44
global ISR45
global ISR46
global ISR47
global ISR48
global ISR49
global ISR50

global ISR51
global ISR52
global ISR53
global ISR54
global ISR55
global ISR56
global ISR57
global ISR58
global ISR59
global ISR60
global ISR61
global ISR62
global ISR63
global ISR64
global ISR65
global ISR66
global ISR67
global ISR68
global ISR69
global ISR70
global ISR71
global ISR72
global ISR73
global ISR74
global ISR75
global ISR76
global ISR77
global ISR78
global ISR79
global ISR80
global ISR81
global ISR82
global ISR83
global ISR84
global ISR85
global ISR86
global ISR87
global ISR88
global ISR89
global ISR90
global ISR91
global ISR92
global ISR93
global ISR94
global ISR95
global ISR96
global ISR97
global ISR98
global ISR99
global ISR100
global ISR101
global ISR102
global ISR103
global ISR104
global ISR105
global ISR106
global ISR107
global ISR108
global ISR109
global ISR110
global ISR110
global ISR111
global ISR112
global ISR113
global ISR114
global ISR115
global ISR116
global ISR117
global ISR118
global ISR119
global ISR120
global ISR121
global ISR122
global ISR123
global ISR124
global ISR125
global ISR126
global ISR127
global ISR128
global ISR129
global ISR130
global ISR131
global ISR132
global ISR133
global ISR134
global ISR135
global ISR136
global ISR137
global ISR138
global ISR139
global ISR140
global ISR141
global ISR142
global ISR143
global ISR144
global ISR145
global ISR146
global ISR147
global ISR148
global ISR149
global ISR150
global ISR151
global ISR152
global ISR153
global ISR154
global ISR155
global ISR156
global ISR157
global ISR158
global ISR159
global ISR160
global ISR161
global ISR162
global ISR163
global ISR164
global ISR165
global ISR166
global ISR167
global ISR168
global ISR169
global ISR170
global ISR171
global ISR172
global ISR173
global ISR174
global ISR175
global ISR176
global ISR177
global ISR178
global ISR179
global ISR180
global ISR181
global ISR182
global ISR183
global ISR184
global ISR185
global ISR186
global ISR187
global ISR188
global ISR189
global ISR190
global ISR191
global ISR192
global ISR193
global ISR194
global ISR195
global ISR196
global ISR197
global ISR198
global ISR199
global ISR200

global HandleSwitch
global StoreContext 

global ContextLiftoff
extern RegisterLastKnownStackLocation
section .text
global getRsp

SaveNext dd 0

ContextLiftoff:
	pusha
	mov [rdx], rsp
	mov rsp, rcx;
    popa
	ret

ThreadStart:

	hlt

ISR0:
	;hlt
	pusha
	push 0
	mov [InterruptNum], ah
	Handle

ISR1:
	;hlt
	pusha
	push 1
	mov [InterruptNum], ah
	popa
	ret

ISR2:
	;hlt
	pusha
	push 2
	mov [InterruptNum], ah
	Handle

ISR3:
	;hlt
	pusha
	push 3
	mov [InterruptNum], ah
	Handle

ISR4:
	;hlt
	pusha
	push 4
	mov [InterruptNum], ah
	Handle

ISR5:
	;hlt
	pusha
	push 5
	mov [InterruptNum], ah
	Handle

ISR6:
	;hlt
	pusha
	push 6
	mov [InterruptNum], ah
	Handle

ISR7:
	;hlt
	pusha
	push 7
	mov [InterruptNum], ah
	Handle
	hlt
ISR8:
	;hlt
	pusha
	push 8
	mov [InterruptNum], ah
	Handle

ISR9:
	;hlt
	pusha
	push 9
	mov [InterruptNum], ah
	Handle

ISR10:
	;hlt
	pusha
	push 10
	mov [InterruptNum], ah
	Handle

ISR11:
	;hlt
	pusha
	push 11
	mov [InterruptNum], ah
	Handle

ISR12:
	;hlt
	pusha
	push 12
	mov [InterruptNum], ah
	Handle

ISR13:
	;GPF
	pusha
	push 13
	mov [InterruptNum], ah
	Handle
	popa
	iretq

ISR14:
	;hlt
	mov [raxp], rax
    pop rax
    mov [InterruptCode], rax
    xor rax, rax
    mov rax, [raxp]
    pusha
    push 14
    mov [InterruptNum], ah
    Handle
    popa
    iretq

ISR15:
	;hlt
	pusha
	push 15
	mov [InterruptNum], ah
	Handle

ISR16:
	;hlt
	pusha
	push 16
	mov [InterruptNum], ah
	Handle

ISR17:
	;hlt
	pusha
	push 17
	mov [InterruptNum], ah
	Handle

ISR18:
	;hlt
	pusha
	push 18
	mov [InterruptNum], ah
	Handle

ISR19:
	;hlt
	pusha
	push 19
	mov [InterruptNum], ah
	jmp Handle

ISR20:
	;hlt
	pusha
	push 20
	mov [InterruptNum], ah
	Handle

ISR21:
	;hlt
	pusha
	push 21
	mov [InterruptNum], ah
	Handle

ISR22:
	;hlt
	pusha
	push 22
	mov [InterruptNum], ah
	Handle

ISR23:
	;hlt
	pusha
	push 23
	mov [InterruptNum], ah
	Handle

ISR24:
	;hlt
	pusha
	push 24
	mov [InterruptNum], ah
	Handle

ISR25:
	;hlt
	pusha
	push 25
	mov [InterruptNum], ah
	Handle

ISR26:
	;hlt
	pusha
	push 26
	mov [InterruptNum], ah
	Handle

ISR27:
	;hlt
	pusha
	push 27
	mov [InterruptNum], ah
	Handle

ISR28:
	;hlt
	pusha
	push 28
	mov [InterruptNum], ah
	Handle

ISR29:
	;hlt
	pusha
	push 29
	mov [InterruptNum], ah
	Handle

ISR30:
	;hlt
	pusha
	push 30
	mov [InterruptNum], ah
	Handle

ISR31:
	;hlt
	pusha
	push 31
	mov [InterruptNum], ah
	Handle





ISR32:
	;hlt
	pusha
	mov rcx, rsp
	call UpdateThreadManager  
	mov rsp, rax 
	popa                                                                                              
	iretq

ISR33:
	;hlt
	pusha
	push 33
	mov [InterruptNum], ah
	Handle
	popa
	iretq

ISR34:
	;hlt
	pusha
	push 34
	mov [InterruptNum], ah
	Handle
	hlt

ISR35:
	;hlt
	pusha
	push 35
	mov [InterruptNum], ah
	Handle
	hlt

ISR36:
	;hlt
	pusha
	push 36
	mov [InterruptNum], ah
	Handle
	hlt

ISR37:
	;hlt
	pusha
	push 37
	mov [InterruptNum], ah
	Handle
	hlt

ISR38:
	;hlt
	pusha
	push 38
	mov [InterruptNum], ah
	Handle
	hlt

ISR39:
	;hlt
	pusha
	push 39
	mov [InterruptNum], ah
	Handle
	hlt

ISR40:
	;hlt
	pusha	
	push 40
	mov [InterruptNum], ah
	Handle
	hlt

ISR41:
	;hlt
	pusha
	push 41
	mov [InterruptNum], ah
	Handle
	hlt

ISR42:
	;hlt
	pusha
	push 42
	mov [InterruptNum], ah
	Handle
	hlt

ISR43:
	;hlt
	pusha	
	push 43
	mov [InterruptNum], ah
	Handle
	hlt

ISR44:
	;hlt
	pusha	
	push 44
	mov [InterruptNum], ah
	Handle
	popa
	iretq

ISR45:
	;hlt
	pusha
	push 45
	mov [InterruptNum], ah
	Handle
	hlt

ISR46:
	;hlt
	pusha
	push 46
	mov [InterruptNum], ah
	Handle
	hlt

ISR47:
	;hlt
	pusha
	push 47
	mov [InterruptNum], ah
	Handle
	hlt

ISR48:
	;hlt
	pusha
	push 48
	mov [InterruptNum], ah
	Handle
	hlt

ISR49:
	;hlt
	pusha
	push 49
	mov [InterruptNum], ah
	Handle
	hlt

ISR50:
	;hlt
	pusha
	push 50
	mov [InterruptNum], ah
	Handle
	hlt

ISR51:
	;hlt
	pusha
	push 51
	mov [InterruptNum], ah
	Handle
	hlt

ISR52:
	;hlt
	pusha
	push 52
	mov [InterruptNum], ah
	Handle
	hlt

ISR53:
	;hlt
	pusha
	push 53
	mov [InterruptNum], ah
	Handle
	hlt

ISR54:
	;hlt
	pusha
	push 54
	mov [InterruptNum], ah
	Handle
	hlt

ISR55:
	;hlt
	pusha
	push 55
	mov [InterruptNum], ah
	Handle
	hlt

ISR56:
	;hlt
	pusha
	push 56
	mov [InterruptNum], ah
	Handle
	hlt

ISR57:
	;hlt
	pusha
	push 57
	mov [InterruptNum], ah
	Handle
	hlt

ISR58:
	;hlt
	pusha
	push 58
	mov [InterruptNum], ah
	Handle
	hlt

ISR59:
	;hlt
	pusha
	push 59
	mov [InterruptNum], ah
	Handle
	hlt

ISR60:
	;hlt
	pusha
	push 60
	mov [InterruptNum], ah
	Handle
	hlt

ISR61:
	;hlt
	pusha
	push 61
	mov [InterruptNum], ah
	Handle
	hlt

ISR62:
	;hlt
	pusha
	push 62
	mov [InterruptNum], ah
	Handle
	hlt

ISR63:
	;hlt
	pusha
	push 63
	mov [InterruptNum], ah
	Handle
	hlt

ISR64:
	;hlt
	pusha
	push 64
	mov [InterruptNum], ah
	Handle
	hlt

ISR65:
	;hlt
	pusha
	push 65
	mov [InterruptNum], ah
	Handle
	hlt

ISR66:
	;hlt
	pusha
	push 66
	mov [InterruptNum], ah
	Handle
	hlt

ISR67:
	;hlt
	pusha
	push 67
	mov [InterruptNum], ah
	Handle
	hlt

ISR68:
	;hlt
	pusha
	push 68
	mov [InterruptNum], ah
	Handle
	hlt

ISR69:
	;hlt
	pusha
	push 69
	mov [InterruptNum], ah
	Handle
	hlt

ISR70:
	;hlt
	pusha
	push 70
	mov [InterruptNum], ah
	Handle
	hlt

ISR71:
	;hlt ;This is an issue
	pusha
	push 71
	mov [InterruptNum], ah
	Handle
	popa
	iretq

ISR72:
	;hlt
	pusha
	push 72
	mov [InterruptNum], ah
	Handle
	hlt

ISR73:
	;hlt
	pusha
	push 73
	mov [InterruptNum], ah
	Handle
	hlt

ISR74:
	;hlt
	pusha
	push 74
	mov [InterruptNum], ah
	Handle
	hlt

ISR75:
	;hlt
	pusha
	push 75
	mov [InterruptNum], ah
	Handle
	hlt

ISR76:
	;hlt
	pusha
	push 76
	mov [InterruptNum], ah
	Handle
	hlt

ISR77:
	;hlt
	pusha
	push 77
	mov [InterruptNum], ah
	Handle
	hlt

ISR78:
	;hlt
	pusha
	push 78
	mov [InterruptNum], ah
	Handle
	hlt

ISR79:
	;hlt
	pusha
	push 79
	mov [InterruptNum], ah
	Handle
	hlt

ISR80:
	;hlt
	pusha
	push 80
	mov [InterruptNum], ah
	Handle
	hlt

ISR81:
	;hlt
	pusha
	push 81
	mov [InterruptNum], ah
	Handle
	hlt

ISR82:
	;hlt
	pusha
	push 82
	mov [InterruptNum], ah
	Handle
	hlt

ISR83:
	;hlt
	pusha
	push 83
	mov [InterruptNum], ah
	Handle
	hlt

ISR84:
	;hlt
	pusha
	push 84
	mov [InterruptNum], ah
	Handle
	hlt

ISR85:
	;hlt
	pusha
	push 85
	mov [InterruptNum], ah
	Handle
	hlt

ISR86:
	;hlt
	pusha
	push 86
	mov [InterruptNum], ah
	Handle
	hlt

ISR87:
	;hlt
	pusha
	push 87
	mov [InterruptNum], ah
	Handle
	hlt

ISR88:
	;hlt
	pusha
	push 88
	mov [InterruptNum], ah
	Handle
	hlt

ISR89:
	;hlt
	pusha
	push 89
	mov [InterruptNum], ah
	Handle
	hlt

ISR90:
	;hlt
	pusha
	push 90
	mov [InterruptNum], ah
	Handle
	hlt

ISR91:
	;hlt
	pusha
	push 91
	mov [InterruptNum], ah
	Handle
	hlt

ISR92:
	;hlt
	pusha
	push 92
	mov [InterruptNum], ah
	Handle
	hlt

ISR93:
	;hlt
	pusha
	push 93
	mov [InterruptNum], ah
	Handle
	hlt

ISR94:
	;hlt
	pusha
	push 94
	mov [InterruptNum], ah
	Handle
	hlt

ISR95:
	;hlt
	pusha
	push 95
	mov [InterruptNum], ah
	Handle
	hlt

ISR96:
	;hlt
	pusha
	push 96
	mov [InterruptNum], ah
	Handle
	hlt

ISR97:
	;hlt
	pusha
	push 97
	mov [InterruptNum], ah
	Handle
	hlt

ISR98:
	;hlt
	pusha
	push 98
	mov [InterruptNum], ah
	Handle
	hlt

ISR99:
	;hlt
	pusha
	push 99
	mov [InterruptNum], ah
	Handle
	hlt

ISR100:
	;hlt
	pusha
	push 100
	mov [InterruptNum], ah
	Handle
	hlt

ISR101:
	;hlt
	pusha
	push 101
	mov [InterruptNum], ah
	Handle
	hlt

ISR102:
	;hlt
	pusha
	push 102
	mov [InterruptNum], ah
	Handle
	hlt

ISR103:
	;hlt
	pusha
	push 103
	mov [InterruptNum], ah
	Handle
	hlt

ISR104:
	;hlt
	pusha
	push 104
	mov [InterruptNum], ah
	Handle
	hlt

ISR105:
	;hlt
	pusha
	push 105
	mov [InterruptNum], ah
	Handle
	hlt

ISR106:
	;hlt
	pusha
	push 106
	mov [InterruptNum], ah
	Handle
	hlt

ISR107:
	;hlt
	pusha
	push 107
	mov [InterruptNum], ah
	Handle
	hlt

ISR108:
	;hlt
	pusha
	push 108
	mov [InterruptNum], ah
	Handle
	hlt

ISR109:
	;hlt
	pusha
	push 109
	mov [InterruptNum], ah
	Handle
	hlt

ISR110:
	;hlt
	pusha
	push 110
	mov [InterruptNum], ah
	Handle
	hlt

ISR111:
	;hlt
	pusha
	push 111
	mov [InterruptNum], ah
	Handle
	hlt

ISR112:
	;hlt
	pusha
	push 112
	mov [InterruptNum], ah
	Handle
	hlt

ISR113:
	;hlt
	pusha
	push 113
	mov [InterruptNum], ah
	Handle
	hlt

ISR114:
	;hlt
	pusha
	push 114
	mov [InterruptNum], ah
	Handle
	hlt

ISR115:
	;hlt
	pusha
	push 115
	mov [InterruptNum], ah
	Handle
	hlt

ISR116:
	;hlt
	pusha
	push 116
	mov [InterruptNum], ah
	Handle
	hlt

ISR117:
	;hlt
	pusha
	push 117
	mov [InterruptNum], ah
	Handle
	hlt

ISR118:
	;hlt
	pusha
	push 118
	mov [InterruptNum], ah
	Handle
	hlt

ISR119:
	;hlt
	pusha
	push 119
	mov [InterruptNum], ah
	Handle
	hlt

ISR120:
	;hlt
	pusha
	push 120
	mov [InterruptNum], ah
	Handle
	hlt

ISR121:
	;hlt
	pusha
	push 121
	mov [InterruptNum], ah
	Handle
	hlt

ISR122:
	;hlt
	pusha
	push 122
	mov [InterruptNum], ah
	Handle
	hlt

ISR123:
	;hlt
	pusha
	push 123
	mov [InterruptNum], ah
	Handle
	hlt

ISR124:
	;hlt
	pusha
	push 124
	mov [InterruptNum], ah
	Handle
	hlt

ISR125:
	;hlt
	pusha
	push 125
	mov [InterruptNum], ah
	Handle
	hlt

ISR126:
	;hlt
	pusha
	push 126
	mov [InterruptNum], ah
	Handle
	hlt

;Smp Interrupts
ISR127:
	;hlt
	pusha
	push 127
	mov [InterruptNum], ah
	Handle
	hlt

extern SYSCALLS

ISR128:
	pusha
	mov r9, rsp
	call SYSCALLS
	popa
	iretq

ISR129:
	pusha
	push rdx
	push rsi
	push rdi
	pop rcx
	pop rdx
	pop r8
	mov r9, rsp
	call SYSCALLS
	popa
	iretq

ISR130:
	;hlt
	pusha
	push 130
	mov [InterruptNum], ah
	Handle
	hlt

ISR131:
	;hlt
	pusha
	push 131
	mov [InterruptNum], ah
	Handle
	hlt

ISR132:
	;hlt
	pusha
	push 132
	mov [InterruptNum], ah
	Handle
	hlt

ISR133:
	;hlt
	pusha
	push 133
	mov [InterruptNum], ah
	Handle
	hlt

ISR134:
	;hlt
	pusha
	push 134
	mov [InterruptNum], ah
	Handle
	hlt

ISR135:
	;hlt
	pusha
	push 135
	mov [InterruptNum], ah
	Handle
	hlt

ISR136:
	;hlt
	pusha
	push 136
	mov [InterruptNum], ah
	Handle
	hlt

ISR137:
	;hlt
	pusha
	push 137
	mov [InterruptNum], ah
	Handle
	hlt

ISR138:
	;hlt
	pusha
	push 138
	mov [InterruptNum], ah
	Handle
	hlt

ISR139:
	;hlt
	pusha
	push 139
	mov [InterruptNum], ah
	Handle
	hlt

ISR140:
	;hlt
	pusha
	push 140
	mov [InterruptNum], ah
	Handle
	hlt

ISR141:
	;hlt
	pusha
	push 141
	mov [InterruptNum], ah
	Handle
	hlt

ISR142:
	;hlt
	pusha
	push 142
	mov [InterruptNum], ah
	Handle
	hlt

ISR143:
	;hlt
	pusha
	push 143
	mov [InterruptNum], ah
	Handle
	hlt

ISR144:
	;hlt
	pusha
	push 144
	mov [InterruptNum], ah
	Handle
	hlt

ISR145:
	;hlt 
	pusha
	push 145
	mov [InterruptNum], ah
	Handle
	hlt

ISR146:
	;hlt 
	pusha
	push 146
	mov [InterruptNum], ah
	Handle
	hlt

ISR147:
	;hlt 
	pusha
	push 147
	mov [InterruptNum], ah
	Handle
	hlt

ISR148:
	;hlt 
	pusha
	push 148
	mov [InterruptNum], ah
	Handle
	hlt

ISR149:
	;hlt 
	pusha
	push 149
	mov [InterruptNum], ah
	Handle
	hlt

ISR150:
	;hlt 
	pusha
	push 150
	mov [InterruptNum], ah
	Handle
	hlt

ISR151:
	;hlt 
	pusha
	push 151
	mov [InterruptNum], ah
	Handle
	hlt

ISR152:
	;hlt 
	pusha
	push 152
	mov [InterruptNum], ah
	Handle
	hlt

ISR153:
	;hlt 
	pusha
	push 153
	mov [InterruptNum], ah
	Handle
	hlt

ISR154:
	;hlt 
	pusha
	push 154
	mov [InterruptNum], ah
	Handle
	hlt

ISR155:
	;hlt 
	pusha
	push 155
	mov [InterruptNum], ah
	Handle
	hlt

ISR156:
	;hlt 
	pusha
	push 156
	mov [InterruptNum], ah
	Handle
	hlt

ISR157:
	;hlt 
	pusha
	push 157
	mov [InterruptNum], ah
	Handle
	hlt

ISR158:
;	hlt 
	pusha
	push 158
	mov [InterruptNum], ah
	Handle
	hlt

ISR159:
;	hlt 
	pusha
	push 159
	mov [InterruptNum], ah
	Handle
	hlt

ISR160:
;	hlt 
	pusha
	push 160
	mov [InterruptNum], ah
	Handle
	hlt

ISR161:
;	hlt 
	pusha
	push 161
	mov [InterruptNum], ah
	Handle
	hlt

ISR162:
;	hlt
	pusha
	push 162
	mov [InterruptNum], ah
	Handle
	hlt

ISR163:
;	hlt
	pusha
	push 163
	mov [InterruptNum], ah
	Handle
	hlt

ISR164:
;	hlt 
	pusha
	push 164
	mov [InterruptNum], ah
	Handle
	hlt

ISR165:
;	hlt 
	pusha
	push 165
	mov [InterruptNum], ah
	Handle
	hlt

ISR166:
;	hlt 
	pusha
	push 166
	mov [InterruptNum], ah
	Handle
	hlt

ISR167:
;	hlt 
	pusha
	push 167
	mov [InterruptNum], ah
	Handle
	hlt

ISR168:
;	hlt 
	pusha
	push 168
	mov [InterruptNum], ah
	Handle
	hlt

ISR169:
;	hlt 
	pusha
	push 169
	mov [InterruptNum], ah
	Handle
	hlt

ISR170:
;	hlt 
	pusha
	push 170
	mov [InterruptNum], ah
	Handle
	hlt

ISR171:
;	hlt 
	pusha
	push 171
	mov [InterruptNum], ah
	Handle
	hlt

ISR172:
;	hlt 
	pusha
	push 172
	mov [InterruptNum], ah
	Handle
	hlt

ISR173:
;	hlt 
	pusha
	push 173
	mov [InterruptNum], ah
	Handle
	hlt

ISR174:
;	hlt 
	pusha
	push 174
	mov [InterruptNum], ah
	Handle
	hlt

ISR175:
;	hlt 
	pusha
	push 175
	mov [InterruptNum], ah
	Handle
	hlt

ISR176:
;	hlt 
	pusha
	push 176
	mov [InterruptNum], ah
	Handle
	hlt

ISR177:
;	hlt 
	pusha
	push 177
	mov [InterruptNum], ah
	Handle
	hlt

ISR178:
;	hlt 
	pusha
	push 8
	mov [InterruptNum], ah
	Handle
	hlt

ISR179:
;	hlt 
	pusha
	push 179
	mov [InterruptNum], ah
	Handle
	hlt

ISR180:
;	hlt 
	pusha
	push 180
	mov [InterruptNum], ah
	Handle
	hlt

ISR181:
;	hlt 
	pusha
	push 181
	mov [InterruptNum], ah
	Handle
	hlt

ISR182:
;	hlt 
	pusha
	push 182
	mov [InterruptNum], ah
	Handle
	hlt

ISR183:
;	hlt 
	pusha
	push 183
	mov [InterruptNum], ah
	Handle
	hlt

ISR184:
;	hlt 
	pusha
	push 184
	mov [InterruptNum], ah
	Handle
	hlt

ISR185:
;	hlt 
	pusha
	push 185
	mov [InterruptNum], ah
	Handle
	hlt

ISR186:
;	hlt 
	pusha
	push 186
	mov [InterruptNum], ah
	Handle
	hlt

ISR187:
;	hlt 
	pusha
	push 187
	mov [InterruptNum], ah
	Handle
	hlt

ISR188:
;	hlt 
	pusha
	push 188
 	mov [InterruptNum], ah
	Handle
	hlt

ISR189:
;	hlt 
	pusha
	push 189
	mov [InterruptNum], ah
	Handle
	hlt

ISR190:
;	hlt 
	pusha
	push 190
	mov [InterruptNum], ah
	Handle
	hlt

ISR191:
;	hlt 
	pusha
	push 191
	mov [InterruptNum], ah
	Handle
	hlt

ISR192:
;	hlt
	pusha
	push 192
	mov [InterruptNum], ah
	Handle
	hlt

ISR193:
;	hlt 
	pusha
	push 193
	mov [InterruptNum], ah
	Handle
	hlt

ISR194:
;	hlt 
	pusha
	push 194
	mov [InterruptNum], ah
	Handle
	hlt

ISR195:
;	hlt 
	pusha
	push 195
	mov [InterruptNum], ah
	Handle
	hlt

ISR196:
;	hlt 
	pusha
	push 196
	mov [InterruptNum], ah
	Handle
	hlt

ISR197:
;	hlt 
	pusha
	push 197
	mov [InterruptNum], ah
	Handle
	hlt

ISR198:
;	hlt 
	pusha
	push 198
	mov [InterruptNum], ah
	Handle
	hlt

ISR199:
;	hlt 
	pusha
	push 199
	mov [InterruptNum], ah
	Handle
	hlt

ISR200:
;	hlt
	pusha
	push 200
	mov [InterruptNum], ah
	Handle
	hlt