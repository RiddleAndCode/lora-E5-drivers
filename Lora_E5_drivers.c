//
// Created by firat on 14.07.21.


#include <string.h>
#include "Lora_E5_drivers.h"

extern lora_status lora_e5_read(char *response_buffer, size_t buff_size);

extern lora_status lora_e5_write(char *cmd);

static lora_status send_cmd_and_get_response(char *cmd, char *response, size_t len) {
    lora_status status = ERROR;
    status = lora_e5_write(cmd);
    if (status != OK) {
        return status;
    }
    status = lora_e5_read(response, len);
    return status;
}

static lora_status check_response(char *received_response, char *expected_response) {
    lora_status status = OK;
    size_t response_len = strlen(expected_response);
    if (response_len == strlen(received_response)) {
        for (int i = 0; i < response_len; ++i) {
            if (expected_response[i] != 'x' && expected_response[i] != received_response[i]) {
                status = UNEXPECTED_RESPONSE;
            }

        }
    }
    else{
        status = UNEXPECTED_RESPONSE;
    }
    return status;
}

lora_status check_modem_connectivity() {
    char receive_buffer[30];
    send_cmd_and_get_response("AT\r\n",receive_buffer,sizeof(receive_buffer));
}

lora_status get_DevAddr(char *DevAddr, size_t buf_len) {
    lora_status status = ERROR;
    status = send_cmd_and_get_response("AT+ID=DevAddr\r\n", DevAddr, buf_len);
    if (status != OK) {
        return status;
    }
    return check_response(DevAddr,"+ID: DevAddr, xx:xx:xx:xx");

}

lora_status get_DevEui(char *DevEui, size_t buf_len) {
    lora_status status = ERROR;
    status = send_cmd_and_get_response("AT+ID=DevEui\r\n", DevEui, buf_len);
    if (status != OK) {
        return status;
    }
    return check_response(DevEui,"+ID: DevEui, xx:xx:xx:xx:xx:xx:xx:xx");
}

lora_status get_AppEui(char *AppEui, size_t buf_len) {
    lora_status status = ERROR;
    status = send_cmd_and_get_response("AT+ID=AppEui\r\n", AppEui, buf_len);
    if (status != OK) {
        return status;
    }
    return check_response(AppEui,"+ID: AppEui, xx:xx:xx:xx:xx:xx:xx:xx");
}

lora_status set_DevAddr(char *DevAddr) {
    lora_status status = ERROR;
    char command_buffer[30];
    char response_buffer[30];
    snprintf(command_buffer, sizeof(command_buffer), "%s%s\r\n", "AT+ID=DevAddr, ", DevAddr);
    status = send_cmd_and_get_response(command_buffer, response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+ID=DevAddr, xx:xx:xx:xx");
}

lora_status set_DevEui(char *DevEui) {
    lora_status status = ERROR;
    char command_buffer[30];
    char response_buffer[30];
    snprintf(command_buffer, sizeof(command_buffer), "%s%s\r\n", "AT+ID=DevEui, ", DevEui);
    status = send_cmd_and_get_response(command_buffer, response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+ID=DevEui, xx:xx:xx:xx:xx:xx:xx:xx");

}

lora_status set_AppEui(char *AppEui) {
    lora_status status = ERROR;
    char command_buffer[30];
    char response_buffer[30];
    snprintf(command_buffer, sizeof(command_buffer), "%s%s\r\n", "AT+ID=AppEui, ", AppEui);
    status = send_cmd_and_get_response(command_buffer, response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+ID=AppEui, xx:xx:xx:xx:xx:xx:xx:xx");

}

lora_status set_AppKey(char *AppKey) {
    lora_status status = ERROR;
    char command_buffer[30];
    char response_buffer[30];
    snprintf(command_buffer, sizeof(command_buffer), "%s%s\r\n", "AT+ID=AppKey, ", AppKey);
    status = send_cmd_and_get_response(command_buffer, response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+KEY: APPKEY xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

}


lora_status set_EU_DR(){
    lora_status status = ERROR;
    char response_buffer[30];
    status = send_cmd_and_get_response("AT+DR=EU868\r\n", response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+DR: EU868");
}

lora_status set_EU_CH(){
    lora_status status = ERROR;
    char response_buffer[30];
    status = send_cmd_and_get_response("AT+CH=NUM,0-2\r\n", response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+CH=NUM,0-2");

}

lora_status set_OTAA(){
    lora_status status = ERROR;
    char response_buffer[30];
    status = send_cmd_and_get_response("AT+MODE=LWOTAA\r\n", response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    return check_response(response_buffer, "+MODE=LWOTAA");

}

lora_status join_request(){
    lora_status status = ERROR;
    char response_buffer[100];
    status = send_cmd_and_get_response("AT+JOIN\r\n", response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    printf("%s\n",response_buffer);
    return check_response(response_buffer, "Rx: +JOIN: Start\n"
                                           "+JOIN: NORMAL\n"
                                           "+JOIN: Network joined\n"
                                           "+JOIN: NetID xxxxxx DevAddr xx:xx:xx:xx\n"
                                           "+JOIN: Done");

}

lora_status send_hex_string(char * hex_str){
    lora_status status = ERROR;
    char command_buffer[250];
    char response_buffer[50];
    snprintf(command_buffer, sizeof(command_buffer), "%s%s\r\n", "AT+MSGHEX=", hex_str);
    status = send_cmd_and_get_response(command_buffer, response_buffer, sizeof(response_buffer));
    if (status != OK) {
        return status;
    }
    status = lora_e5_read(response_buffer,50);


    return status;

}