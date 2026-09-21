#include <iostream>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {
    int sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    
    if (sock_raw < 0) {
        std::cerr << "Erro ao criar o socket. Certifica-te de que executas como root!\n";
        return 1;
    }

    unsigned char buffer[65536];
    std::cout << "A escutar pacotes de rede... Pressiona Ctrl+C para parar.\n\n";

    while (true) {
        int data_size = recvfrom(sock_raw, buffer, 65536, 0, nullptr, nullptr);
        
        if (data_size < 0) {
            std::cerr << "Erro ao ler pacotes (recvfrom falhou)\n";
            break;
        }

        std::cout << "Pacote capturado com sucesso! Tamanho: " << data_size << " bytes\n";
    }

    close(sock_raw);
    return 0;
}