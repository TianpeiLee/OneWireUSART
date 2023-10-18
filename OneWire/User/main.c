// This should work conecting signal to pin D3 and ground to ground
/*
    This file is part of the BlHeliSuite interface solutions for AVR
    Copyright (C) 2014  by 4712
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    File: Arduino1Wire.c
    Author: 4712
*/
/*
 * Arduino1Wire.c //Method I in C
 *
 * Rev 1: Initial realease
 * Rev 1.1: Set ow pull up at startup

*/

//modified by TempersLee



/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *
 *Hardware connection: PD5 -- Rx
 *                     PD6 -- Tx
 *                     PC1 -- OneWire
 */

#include "debug.h"


#define SetOWout    {GPIOC->CFGLR &= ~(0xf<<4);GPIOC->CFGLR |= (0x3<<4);}
#define SetOWin     {GPIOC->CFGLR &= ~(0xf<<4); GPIOC->CFGLR |= (0x8<<4);}
#define SetOWlow    {GPIOC->BCR = 0x2;}
#define SetOWhigh   {GPIOC->BSHR = 0x2;}
#define IsOWhigh    (GPIOC->INDR & 0x2)
#define IsOWlow     (!(GPIOC->INDR & 0x2))

#define SetTxlow    {GPIOD->BCR = (1<<5);}
#define SetTxhigh   {GPIOD->BSHR = (1<<5);}
#define IsRXhigh    (GPIOD->INDR & (1<<6))
#define IsRxlow     (!(GPIOD->INDR & (1<<6)))


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);

    GPIOD->BSHR  = (1<<5);
    GPIOD->CFGLR &= ~(0xf<<20);    //PD5
    GPIOD->CFGLR |= (0x3<<20);     //输出

    GPIOD->BSHR = (1<<6);
    GPIOD->CFGLR &= ~(0xf<<24);    //PD6
    GPIOD->CFGLR |= (0x8<<24);     //上拉输入

    SetOWout;
    SetOWhigh;

    while(IsRXhigh);            //等待接收到数据开始

    while(1)
    {
        SetOWout;
        SetOWlow;  //收到0,设置OW=0
        SetTxlow;  //echo low to tx
        while(IsRxlow); //等待0

        SetOWhigh;   //设置ow=1

        SetOWin;    //设置为输入
        SetOWhigh;  //上拉


        while(IsRXhigh)
        {
            if(IsOWhigh) {SetTxhigh;}
            else {SetTxlow;}
        }

    }
}
