//
// Created by firat on 14.07.21.
//

#ifndef SERIAL_READ_LORA_E5_DRIVERS_H
#define SERIAL_READ_LORA_E5_DRIVERS_H
#include <stdio.h>

enum E5_status{
    OK, UNEXPECTED_RESPONSE,WRITE_FAILED,READ_FAILED, ERROR
};
typedef enum E5_status lora_status;

lora_status check_modem_connectivity(); //AT
lora_status get_DevAddr(char * DevAddr, size_t buf_len);
lora_status get_DevEui(char * DevEui, size_t buf_len);
lora_status get_AppEui(char * AppEui, size_t buf_len);

lora_status set_DevAddr(char * DevAddr);
lora_status set_DevEui(char * DevEui);
lora_status set_AppEui(char * AppEui);
lora_status set_AppKey(char * AppKey);

lora_status send_unconfirmed_msg(char * devEUI); //dont forget the /0


#endif //SERIAL_READ_LORA_E5_DRIVERS_H
