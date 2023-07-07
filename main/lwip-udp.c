#include "lwip-udp.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"

#include "platform-defs.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#define TAG "lwip-udp"

/**
 * @brief 
 * 84.237.104.128:4200
 * @see https://github.com/goertzenator/lwip/blob/master/contrib-1.4.0/apps/socket_examples/socket_examples.c
 */
void checkUDP() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = PP_HTONS(CONFIG_UDP_SOCK_PORT);
    addr.sin_addr.s_addr = inet_addr(CONFIG_SOCK_TARGET_HOST);

    int socket = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    // nonblocking 1
    uint32_t opt = 1;
    int ret = lwip_ioctl(socket, FIONBIO, &opt);
    LWIP_ASSERT("ret == 0", ret == 0);

    // nonblocking 2
    /*
    opt = lwip_fcntl(socket, F_GETFL, 0);
    opt |= O_NONBLOCK;
    ret = lwip_fcntl(socket, F_SETFL, opt);
    */

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt (socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

    uint32_t seqno = 0;
    char txbuf[16];
    while(true) {
        int txlen  = sprintf(txbuf, "%lu\n", seqno);
        ret = sendto(socket, txbuf, txlen, 0, (struct sockaddr *) &addr, sizeof(addr));
        if (ret < 0) {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            continue;
        }
        seqno++;
    }
    ret = lwip_close(socket);
    LWIP_ASSERT("lwip_close == 0", ret == 0);
}

void lwpInit() {
    ESP_ERROR_CHECK(esp_netif_init());
//    ESP_ERROR_CHECK(esp_event_loop_create_default());
}
