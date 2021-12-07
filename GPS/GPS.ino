#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>
//#include "Peripherals/Pin_Initialization.h"
//#include "Peripherals/Watchdog_Initialization.h"
//#include "Peripherals/ADC_Initialization.h"
//#include "Peripherals/Display_Initialization.h"
//#include <xdc/std.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <xdc/runtime/System.h>
//#include <xdc/runtime/Error.h>

/* Power header files */
//#include <ti/drivers/Power.h>
//#include <ti/drivers/power/PowerCC26XX.h>
//#include "Board.h"


UART_Handle uart;
UART_Params uartParams;
char input[512] = {0};
int numBytes;
int bytesRead = 0;
int bytes_read = 0;
void Serial_RxDataCallback(UART_Handle handle, void *buffer, size_t size)
{
    bytesRead = size;
    bytes_read = size;
}

void setup() {
//  Board_initGeneral();
//  PIN_init(pinTable);

  /* Setup peripherals and semaphores */
//  clockSetup();
//  semaphoreSetup();
//  pinSetup();
    
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  
  UART_init(); 
  // put your setup code here, to run once:
//  UART_Params_init(&uartParams);
//  uartParams.writeDataMode = UART_DATA_BINARY;
//  uartParams.readDataMode = UART_DATA_BINARY;
//  uartParams.readReturnMode = UART_RETURN_FULL;
//  uartParams.readEcho = UART_ECHO_OFF;
//  uartParams.baudRate = 9600;
//
//  uartParams.readMode       = UART_MODE_CALLBACK;
//  uartParams.readCallback   = &Serial_RxDataCallback;
//  uart = UART_open(0,&uartParams);
//
//  if (uart == NULL) {
//    while(1){
//    Serial.println("error");
//    digitalWrite(GREEN_LED,LOW);
//    digitalWrite(RED_LED,HIGH);
//    }
//  }
//  else {
//    digitalWrite(GREEN_LED,HIGH);
//  }

}

void loop() {
  UART_init(); 
  // put your main code here, to run repeatedly: 
  /*UART_Params_init(&uartParams);
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 9600;

  uartParams.readMode       = UART_MODE_CALLBACK;
  uartParams.readCallback   = &Serial_RxDataCallback;
  */
  uart = UART_open(0,&uartParams);
  
  UART_control(uart,UARTCC26XX_CMD_RETURN_PARTIAL_ENABLE,NULL);
  bool gotdata = false;

  while (!(gotdata & (bytesRead==72))) {
    UART_control(uart,UARTCC26XX_CMD_RX_FIFO_FLUSH,NULL);
    numBytes = UART_read(uart,&input,sizeof(input));
    gotdata = true;
  }

  UART_write(uart, &input, 72);
  UART_control(uart, UARTCC26XX_CMD_RX_FIFO_FLUSH, NULL);

  UART_readCancel(uart);
  UART_writeCancel(uart);
  UART_close(uart);
  Serial.begin(9600);

 if ( numBytes) {
    digitalWrite(GREEN_LED, LOW);
  }
  
//  for (int i =0 ; i<352; i++) {
//    Serial.print(input[0] );
//  }
  Serial.println("bytes read: ");
  //Serial.print(numBytes);


  Serial.end();

//  PIN_setOutputValue(pinHandle, 8, 0);
//  PIN_setOutputValue(pinHandle, Board_PIN_LED0,0);
//  PIN_setOutputValue(pinHandle, Board_PIN_LED1,0);

  
}
