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
    size_t response_len = strlen(expected_response);
    if (response_len == strlen(received_response)) {
        for (int i = 0; i < response_len; ++i) {
            if (expected_response[i] != 'x' && expected_response[i] != received_response[i]) {
                return UNEXPECTED_RESPONSE;
            }

        }
    }
    return OK;
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