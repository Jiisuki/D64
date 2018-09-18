/** @file
 *  @brief 
 *
 *  Details for kexx_delay.s
 */

.global Delay_ticks

// r0 = time_ticks, r1 = count
Delay_ticks:
    mov r1, #1
kexx_dly_start:
    add r1, #3
    cmp r1, r0
    blt kexx_dly_start
kexx_dly_end:
    mov pc, lr

