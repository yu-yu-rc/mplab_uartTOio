/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC12F1822
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"


#define _XTAL_FREQ 32000000

void i2cByteWrite(char, char);
void i2cTxData(char);
void I2C_Initialize(void);
void pin_init(){
    IO_RA1_SetDigitalOutput();
    IO_RA2_SetDigitalOutput();
    IO_RA1_SetLow();
    IO_RA2_SetLow();
    __delay_ms(10);
}
void start(){
    IO_RA1_SetHigh();
    IO_RA2_SetLow();
    __delay_ms(1);
}

void end(){
    IO_RA1_SetLow();
    IO_RA2_SetLow();
    __delay_ms(1);
}
void send(int kaisu){
    start();
    IO_RA1_SetLow();
    for(int i = 0; i < kaisu; i++){
        IO_RA2_SetHigh();
        __delay_us(50);
        IO_RA2_SetLow();
        __delay_us(50);
    }
    end();
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    I2C_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();  
    uint8_t data = 4;

    while (1)
    {   
        send(data);
    }
}

//********************************************************************
// I2C 関連
//********************************************************************

void I2C_Initialize()
{
    ANSELA = 0x00;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    //SSP1STAT = 0x80;
    //SSP1CON1 = 0x28;
    //SSP1CON3 = 0x00;
    //SSP1ADD  = 0x4F;
    //SSP1CON1bits.SSPEN = 1;
}

//-------- ByteI2C送信
void i2cByteWrite(char addr, char data){
    SSP1IF = 0;
    SSP1CON2bits.SEN = 1;      // Start condition 開始
    while(SSP1IF == 0) {};   // Start condition 確認
    SSP1IF = 0;
    i2cTxData(addr);           // アドレス送信
    i2cTxData(data);   // データ送信
    SSP1IF = 0;
    SSP1CON2bits.PEN = 1;      // Stop condition 開始
    while(SSP1IF == 0) {};   // Stop condition 確認
    SSP1IF = 0;
}
//-------- Data送信
void i2cTxData(char data){
    SSP1IF = 0;       // 終了フラグクリア
    SSP1BUF = data;            // データセット
    while(SSP1IF == 0) {};// 送信終了待ち
    SSP1IF = 0;
}
/**
 End of File
*/