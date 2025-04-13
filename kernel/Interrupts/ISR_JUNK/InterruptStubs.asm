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
global ISR201
global ISR202
global ISR203
global ISR204
global ISR205
global ISR206
global ISR207
global ISR208
global ISR209
global ISR210
global ISR211
global ISR212
global ISR213
global ISR214
global ISR215
global ISR216
global ISR217
global ISR218
global ISR219
global ISR220
global ISR221
global ISR222
global ISR223
global ISR224
global ISR225
global ISR226
global ISR227
global ISR228
global ISR229
global ISR230
global ISR231
global ISR232
global ISR233
global ISR234
global ISR235
global ISR236
global ISR237
global ISR238
global ISR239
global ISR240
global ISR241
global ISR242
global ISR243
global ISR244
global ISR245
global ISR246
global ISR247
global ISR248
global ISR249
global ISR250
global ISR251
global ISR252
global ISR253
global ISR254
global ISR255

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
	pusha
	push 0
	jmp HANDLE_FUNCTION

ISR1:
	pusha
	push 1
	jmp HANDLE_FUNCTION

ISR2:
	pusha
	push 2
	jmp HANDLE_FUNCTION

ISR3:
	pusha
	push 3
	jmp HANDLE_FUNCTION

ISR4:
	pusha
	push 4
	jmp HANDLE_FUNCTION


ISR5:
	pusha
	push 5
	jmp HANDLE_FUNCTION

ISR6:
	pusha
	push 6
	jmp HANDLE_FUNCTION

ISR7:
	pusha
	push 7
	jmp HANDLE_FUNCTION


ISR8:
	pusha
	push 8
	jmp HANDLE_FUNCTION

ISR9:
	pusha
	push 9
	jmp HANDLE_FUNCTION

ISR10:
	pusha
	push 10
	jmp HANDLE_FUNCTION

ISR11:
	pusha
	push 11
	jmp HANDLE_FUNCTION

ISR12:
	pusha
	push 12
	jmp HANDLE_FUNCTION

ISR13:
	pusha 
	push 13
	jmp HANDLE_FUNCTION

ISR14:
	pusha 
	push 14
	jmp HANDLE_FUNCTION

ISR15:
	pusha
	push 15
	jmp HANDLE_FUNCTION

ISR16:
	pusha
	push 16
	jmp HANDLE_FUNCTION

ISR17:
	pusha
	push 17
	jmp HANDLE_FUNCTION

ISR18:
	pusha 
	push 18
	jmp HANDLE_FUNCTION

ISR19:
	pusha
	push 19
	jmp HANDLE_FUNCTION

ISR20:
	pusha
	push 20
	jmp HANDLE_FUNCTION

ISR21:
	pusha
	push 21
	jmp HANDLE_FUNCTION

ISR22
	pusha
	push 22
	jmp HANDLE_FUNCTION

ISR23:
	pusha
	push 23
	jmp HANDLE_FUNCTION

ISR24:
	pusha
	push 24
	jmp HANDLE_FUNCTION

ISR25:
	pusha
	push 25
	jmp  HANDLE_FUNCTION

ISR26:
	pusha
	push 26
	jmp HANDLE_FUNCTION

ISR27:
	pusha
	push 27
	jmp HANDLE_FUNCTION

ISR28:
	pusha
	push 28
	jmp HANDLE_FUNCTION

ISR29:
	pusha
	push 29
	jmp HANDLE_FUNCTION

ISR30:
	pusha
	push 30
	jmp HANDLE_FUNCTION
	
ISR31:
	pusha
	push 31
	jmp HANDLE_FUNCTION

ISR32:
	pusha
	mov rcx, rsp
	call UpdateThreadManager  
	mov rsp, rax 
	popa                                                                                              
	iretq

ISR33
	pusha
	push 33
	jmp HANDLE_FUNCTION

ISR34:
	pusha
	push 34
	jmp HANDLE_FUNCTION

ISR35:
	pusha
	push 35
	jmp HANDLE_FUNCTION

ISR36:
	pusha
	push 36
	jmp HANDLE_FUNCTION

ISR37:
	pusha
	push 37
	jmp HANDLE_FUNCTION

ISR38:
	pusha
	push 38
	jmp HANDLE_FUNCTION

ISR39:
	pusha
	push 39
	jmp HANDLE_FUNCTION

ISR40:
	pusha
	push 40
	jmp HANDLE_FUNCTION

ISR41:
	pusha
	push 41
	jmp HANDLE_FUNCTION

ISR42:
	pusha
	push 42
	jmp HANDLE_FUNCTION

ISR43:
	pusha
	push 43
	jmp HANDLE_FUNCTION

ISR44:
	pusha
	push 44
	jmp HANDLE_FUNCTION

ISR45:
	pusha
	push 45
	jmp HANDLE_FUNCTION
	
ISR46:
	pusha
	push 46
	jmp HANDLE_FUNCTION

ISR47:
	pusha
	push 47
	jmp HANDLE_FUNCTION

ISR48:
	pusha
	push 48
	jmp HANDLE_FUNCTION

ISR49:
	pusha
	push 49
	jmp HANDLE_FUNCTION

ISR50: 
	pusha
	push 50
	jmp HANDLE_FUNCTION

ISR51:
	pusha
	push 51
	jmp HANDLE_FUNCTION

ISR52:
	pusha:
	push 52
	jmp HANDLE_FUNCTION

ISR53:
	pusha
	push 53
	jmp HANDLE_FUNCTION

ISR54:
	pusha
	push 54
	jmp HANDLE_FUNCTION

ISR55:
	pusha
	push 55
	jmp HANDLE_FUNCTION

ISR56:
	pusha 
	push 56
	jmp HANDLE_FUNCTION

ISR57:
	pusha
	push 57
	jmp HANDLE_FUNCTION

ISR58:
	pusha
	push 58
	jmp HANDLE_FUNCTION

ISR59:
	pusha
	push 59
	jmp HANDLE_FUNCTION

ISR60:
	pusha 
	push 60
	jmp HANDLE_FUNCTION

ISR61:
	pusha
	push 61
	jmp HANDLE_FUNCTION

ISR62:
	pusha
	push 62
	jmp HANDLE_FUNCTION

ISR63:
	pusha
	push 63
	jmp HANDLE_FUNCTION

ISR64:
	pusha
	push 64
	jmp HANDLE_FUNCTION

ISR65:
	pusha
	push 65
	jmp HANDLE_FUNCTION

ISR66:
	pusha
	push 66
	jmp HANDLE_FUNCTION

ISR67:
	pusha
	push 67
	jmp HANDLE_FUNCTION

ISR68:
	pusha 
	push 68
	jmp HANDLE_FUNCTION

ISR69:
	pusha
	push 69
	jmp HANDLE_FUNCTION

ISR70:
	pusha 
	push 70
	jmp HANDLE_FUNCTION

ISR71:
	pusha
	push 71
	jmp HANDLE_FUNCTION

ISR72:
	pusha
	push 72
	jmp HANDLE_FUNCTION

ISR73:
	pusha
	push 73
	jmp HANDLE_FUNCTION

ISR74:
	pusha
	push 74
	jmp HANDLE_FUNCTION

ISR75:
	pusha
	push 75
	jmp HANDLE_FUNCTION

ISR76:
	pusha
	push 76
	jmp HANDLE_FUNCTION

ISR77:
	pusha
	push 77
	jmp HANDLE_FUNCTION

ISR78:
	pusha 
	push 78
	jmp HANDLE_FUNCTION

ISR79: 
	pusha
	push 79
	jmp HANDLE_FUNCTION
	
ISR80:
	pusha
	push 80
	jmp HANDLE_FUNCTION

ISR81:
	pusha 
	push 81
	jmp HANDLE_FUNCTION

ISR82:
	pusha
	push 82
	jmp HANDLE_FUNCTION

ISR83:
	pusha
	push 83
	jmp HANDLE_FUNCTION

ISR84:
	pusha
	push 84
	jmp HANDLE_FUNCTION

ISR85:
	pusha
	push 85
	jmp HANDLE_FUNCTION

ISR86:
	pusha
	push 86
	jmp HANDLE_FUNCTION

ISR87:
	pusha
	push 87
	jmp HANDLE_FUNCTION

ISR88:
	pusha
	push 88
	jmp HANDLE_FUNCTION

ISR89:
	pusha
	push 89
	jmp HANDLE_FUNCTION

ISR90:
	pusha
	push 90
	jmp HANDLE_FUNCTION

ISR91:
	pusha
	push 91
	jmp HANDLE_FUNCTION

ISR92:
	pusha
	push 92
	jmp HANDLE_FUNCTION

ISR93:
	pusha
	push 93
	jmp HANDLE_FUNCTION

ISR94:
	pusha
	push 94
	jmp HANDLE_FUNCTION

ISR95:
	pusha
	push 95
	jmp HANDLE_FUNCTION

ISR96:
	pusha
	push 96
	jmp HANDLE_FUNCTION

ISR97:
	pusha
	push 97
	jmp HANDLE_FUNCTION

ISR98:
	pusha 
	push 98
	jmp HANDLE_FUNCTION

ISR99:
	pusha
	push 99
	jmp HANDLE_FUNCTION

ISR100:
	pusha 
	push 100
	jmp HANDLE_FUNCTION

ISR101:
	pusha
	push 101
	jmp HANDLE_FUNCTION

ISR102:
	pusha
	push 102
	jmp HANDLE_FUNCTION

ISR103:
	pusha
	push 103
	jmp HANDLE_FUNCTION

ISR104:
	pusha
	push 104
	jmp HANDLE_FUNCTION

ISR105:
	pusha
	push 105
	jmp HANDLE_FUNCTION

ISR106:
	pusha
	push 106
	jmp HANDLE_FUNCTION

ISR107:
	pusha
	push 107
	jmp HANDLE_FUNCTION

ISR108:
	pusha
	push 108
	jmp HANDLE_FUNCTION

ISR109:
	pusha 
	push 109
	jmp HANDLE_FUNCTION

ISR110:
	pusha
	push 110
	jmp HANDLE_FUNCTION

ISR111:
	pusha
	push 111
	jmp HANDLE_FUNCTION

ISR112:
	pusha
	push 112
	jmp HANDLE_FUNCTION

ISR113:
	pusha
	push 113
	jmp HANDLE_FUNCTION

ISR114:
	pusha
	push 114
	jmp HANDLE_FUNCTION

ISR115:
	pusha
	push 115
	jmp HANDLE_FUNCTION

ISR116:
	pusha
	push 116
	jmp HANDLE_FUNCTION

ISR117:
	pusha
	push 117
	jmp HANDLE_FUNCTION

ISR118:
	pusha
	push 118
	jmp HANDLE_FUNCTION

ISR119:
	pusha
	push 119
	jmp HANDLE_FUNCTION

ISR120:
	pusha
	push 120
	jmp HANDLE_FUNCTION


ISR121:
	pusha
	push 121
	jmp HANDLE_FUNCTION

ISR122:
	pusha
	push 122
	jmp HANDLE_FUNCTION

ISR123:
	pusha
	push 123
	jmp HANDLE_FUNCTION

ISR124:
	pusha
	push 124
	jmp HANDLE_FUNCTION

ISR125:
	pusha
	push 125
	jmp HANDLE_FUNCTION

ISR126:
	pusha
	push 126
	jmp HANDLE_FUNCTION

ISR127:
	pusha
	push 127
	jmp HANDLE_FUNCTION

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
	pusha
	push 130
	jmp HANDLE_FUNCTION

ISR131:
	pusha 
	push 131
	jmp HANDLE_FUNCTION

ISR132:
	pusha
	push 132
	jmp HANDLE_FUNCTION

ISR133:
	pusha
	push 133
	jmp HANDLE_FUNCTION

ISR134:
	pusha
	push 134
	jmp HANDLE_FUNCTION

ISR135:
	pusha
	push 135
	jmp HANDLE_FUNCTION

ISR136:
	pusha
	push 136
	jmp HANDLE_FUNCTION

ISR137:
	pusha
	push 137
	jmp HANDLE_FUNCTION

ISR138:
	pusha
	push 138
	jmp HANDLE_FUNCTION

ISR139:
	pusha
	push 139
	jmp HANDLE_FUNCTION

ISR140:
	pusha
	push 140
	jmp HANDLE_FUNCTION

ISR141:
	pusha
	jmp HANDLE_FUNCTION

ISR142:
	pusha
	push 142
	jmp HANDLE_FUNCTION

ISR143:
	pusha
	push 143
	jmp HANDLE_FUNCTION

ISR144:
	pusha
	push 144
	jmp HANDLE_FUNCTION

ISR145:
	pusha
	push 145
	jmp HANDLE_FUNCTION

ISR146:
	pusha
	push 146
	jmp HANDLE_FUNCTION

ISR147:
	pusha
	push 147
	jmp HANDLE_FUNCTION

ISR148:
	pusha
	push 148
	jmp HANDLE_FUNCTION

ISR149:
	pusha
	push 149
	jmp HANDLE_FUNCTION

ISR150:
	pusha
	push 150
	jmp HANDLE_FUNCTION

ISR151:
	pusha
	push 151
	jmp HANDLE_FUNCTION

ISR152:
	pusha
	push 152
	jmp HANDLE_FUNCTION

ISR153:
	pusha
	push 153
	jmp HANDLE_FUNCTION

ISR154:
	pusha
	push 154
	jmp HANDLE_FUNCTION

ISR155:
	pusha
	push 155
	jmp HANDLE_FUNCTION

ISR156:
	pusha
	push 156
	jmp HANDLE_FUNCTION

ISR157:
	pusha
	push 157
	jmp HANDLE_FUNCTION

ISR158:
	pusha
	push 158
	jmp HANDLE_FUNCTION

ISR159:
	pusha
	push 159
	jmp HANDLE_FUNCTION

ISR160:
	pusha
	push 160
	jmp HANDLE_FUNCTION

ISR161:
	pusha
	push 161
	jmp HANDLE_FUNCTION

ISR162:
	pusha
	push 162
	jmp HANDLE_FUNCTION

ISR163:
	pusha
	push 163
	jmp HANDLE_FUNCTION

ISR164:
	pusha
	push 164
	jmp HANDLE_FUNCTION

ISR165:
	pusha
	push 165
	jmp HANDLE_FUNCTION

ISR166:
	pusha
	push 166
	jmp HANDLE_FUNCTION

ISR167:
	pusha
	push 167
	jmp HANDLE_FUNCTION

ISR168:
	pusha
	push 168
	jmp HANDLE_FUNCTION

ISR169:
	pusha
	push 169
	jmp HANDLE_FUNCTION

ISR170:
	pusha
	push 170
	jmp HANDLE_FUNCTION

ISR171:
	pusha
	push 171
	jmp HANDLE_FUNCTION

ISR172:
	pusha
	push 172
	jmp HANDLE_FUNCTION

ISR173:
	pusha
	push 173
	jmp HANDLE_FUNCTION

ISR174:
	pusha
	push 174
	jmp HANDLE_FUNCTION

ISR175:
	pusha
	push 175
	jmp HANDLE_FUNCTION

ISR176:
	pusha
	push 176
	jmp HANDLE_FUNCTION

ISR177:
	pusha
	push 177
	jmp HANDLE_FUNCTION

ISR178:
	pusha
	push 178
	jmp HANDLE_FUNCTION

ISR179:
	pusha
	push 179
	jmp HANDLE_FUNCTION

ISR180:
	pusha
	push 180
	jmp HANDLE_FUNCTION

ISR181:
	pusha
	push 181
	jmp HANDLE_FUNCTION

ISR182:
	pusha
	push 182
	jmp HANDLE_FUNCTION

ISR183:
	pusha
	push 183
	jmp HANDLE_FUNCTION

ISR184:
	pusha
	push 184
	jmp HANDLE_FUNCTION

ISR185:
	pusha
	push 185
	jmp HANDLE_FUNCTION

ISR186:
	pusha
	push 186
	jmp HANDLE_FUNCTION

ISR187:
	pusha
	push 187
	jmp HANDLE_FUNCTION

ISR188:
	pusha
	push 188
	jmp HANDLE_FUNCTION

ISR189:
	pusha
	push 189
	jmp HANDLE_FUNCTION

ISR190:
	pusha
	push 190
	jmp HANDLE_FUNCTION

ISR191:
	pusha
	push 191
	jmp HANDLE_FUNCTION

ISR192:
	pusha
	push 192
	jmp HANDLE_FUNCTION

ISR193:
	pusha
	push 193
	jmp HANDLE_FUNCTION

ISR194:
	pusha
	push 194
	jmp HANDLE_FUNCTION

ISR195:
	pusha
	push 195
	jmp HANDLE_FUNCTION

ISR196:
	pusha
	push 196
	jmp HANDLE_FUNCTION

ISR197:
	pusha
	push 197
	jmp HANDLE_FUNCTION

ISR198:
	pusha
	push 198
	jmp HANDLE_FUNCTION

ISR199:
	pusha
	push 199
	jmp HANDLE_FUNCTION

ISR200:
	pusha
	push 200
	jmp HANDLE_FUNCTION

ISR201:
	pusha
	push 201
	jmp HANDLE_FUNCTION

ISR202:
	pusha
	push 202
	jmp HANDLE_FUNCTION

ISR203:
	pusha
	push 203
	jmp HANDLE_FUNCTION

ISR204:
	pusha
	push 204
	jmp HANDLE_FUNCTION

ISR205:
	pusha
	push 205
	jmp HANDLE_FUNCTION

ISR206:
	pusha
	push 206
	jmp HANDLE_FUNCTION

ISR207:
	pusha
	push 207
	jmp HANDLE_FUNCTION

ISR208:
	pusha
	push 208
	jmp HANDLE_FUNCTION

ISR209:
	pusha
	push 209
	jmp HANDLE_FUNCTION

ISR210:
	pusha
	push 210
	jmp HANDLE_FUNCTION

ISR211:
	pusha
	push 211
	jmp HANDLE_FUNCTION

ISR212:
	pusha
	push 212
	jmp HANDLE_FUNCTION

ISR213:
	pusha
	push 213
	jmp HANDLE_FUNCTION

ISR214:
	pusha
	push 214
	jmp HANDLE_FUNCTION

ISR215:
	pusha
	push 215
	jmp HANDLE_FUNCTION

ISR216:
	pusha
	push 216
	jmp HANDLE_FUNCTION

ISR217:
	pusha
	push 217
	jmp HANDLE_FUNCTION

ISR218:
	pusha
	push 218
	jmp HANDLE_FUNCTION

ISR219:
	pusha
	push 219
	jmp HANDLE_FUNCTION

ISR220:
	pusha
	push 220
	jmp HANDLE_FUNCTION

ISR221:
	pusha
	push 221
	jmp HANDLE_FUNCTION

ISR222:
	pusha
	push 222
	jmp HANDLE_FUNCTION

ISR223:
	pusha
	push 223
	jmp HANDLE_FUNCTION

ISR224:
	pusha
	push 224
	jmp HANDLE_FUNCTION

ISR225:
	pusha
	push 225
	jmp HANDLE_FUNCTION

ISR226:
	pusha
	push 226
	jmp HANDLE_FUNCTION

ISR227:
	pusha
	push 227
	jmp HANDLE_FUNCTION

ISR228:
	pusha
	push 228
	jmp HANDLE_FUNCTION

ISR229:
	pusha
	push 229
	jmp HANDLE_FUNCTION

ISR230:
	pusha
	push 230
	jmp HANDLE_FUNCTION

ISR231:
	pusha
	push 231
	jmp HANDLE_FUNCTION

ISR232:
	pusha
	push 232
	jmp HANDLE_FUNCTION

ISR233:
	pusha
	push 233
	jmp HANDLE_FUNCTION

ISR234:
	pusha
	push 234
	jmp HANDLE_FUNCTION

ISR235:
	pusha
	push 235
	jmp HANDLE_FUNCTION

ISR236:
	pusha
	push 236
	jmp HANDLE_FUNCTION

ISR237:
	pusha
	push 237
	jmp HANDLE_FUNCTION

ISR238:
	pusha
	push 238
	jmp HANDLE_FUNCTION

ISR239:
	pusha
	push 239
	jmp HANDLE_FUNCTION

ISR240:
	pusha
	push 240
	jmp HANDLE_FUNCTION

ISR241:
	pusha
	push 241
	jmp HANDLE_FUNCTION

ISR242:
	pusha
	push 242
	jmp HANDLE_FUNCTION

ISR243:
	pusha
	push 243
	jmp HANDLE_FUNCTION

ISR244:
	pusha
	push 244
	jmp HANDLE_FUNCTION

ISR245:
	pusha
	push 245
	jmp HANDLE_FUNCTION

ISR246:
	pusha
	push 246
	jmp HANDLE_FUNCTION

ISR247:
	pusha
	push 247
	jmp HANDLE_FUNCTION

ISR248:
	pusha
	push 248
	jmp HANDLE_FUNCTION

ISR249:
	pusha
	push 249
	jmp HANDLE_FUNCTION

ISR250:
	pusha
	push 250
	jmp HANDLE_FUNCTION

ISR251:
	pusha
	push 251
	jmp HANDLE_FUNCTION

ISR252:
	pusha
	push 252
	jmp HANDLE_FUNCTION

ISR253:
	pusha
	push 253
	jmp HANDLE_FUNCTION

ISR254:
	pusha
	push 254
	jmp HANDLE_FUNCTION

ISR255:
	pusha
	push 255

HANDLE_FUNCTION:
	Handle
	popa
	iretq
