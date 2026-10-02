#include <iostream>
#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <cstring>

// Function called when libpcap captures a packet
void processar_pacote(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) {
    struct ether_header *eth_header = (struct ether_header *) buffer;
    if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) { // Not an IP packet
        return;
    }

    // Analyses the IP header
    const u_char *ip_header_ptr = buffer + sizeof(struct ether_header);
    struct ip *ip_header = (struct ip *)ip_header_ptr;
    int ip_header_length = ip_header->ip_hl * 4;

    if (ip_header->ip_p != IPPROTO_TCP) { // Not a TCP packet
        return;
    }

    // Analyses the TCP header
    const u_char *tcp_header_ptr = ip_header_ptr + ip_header_length;
    struct tcphdr *tcp_header = (struct tcphdr *)tcp_header_ptr;
    int tcp_header_length = tcp_header->doff * 4;

    // Calculates where the actual HTTP data begins
    const u_char *payload = tcp_header_ptr + tcp_header_length;
    int payload_length = ntohs(ip_header->ip_len) - (ip_header_length + tcp_header_length);

    // If there is payload data, print it
    if (payload_length > 0) {
        std::cout << "\n=== Novo Pacote HTTP Intercetado ===" << std::endl;
        std::cout << "Origem: " << inet_ntoa(ip_header->ip_src) << ":" << ntohs(tcp_header->source) << std::endl;
        std::cout << "Destino: " << inet_ntoa(ip_header->ip_dst) << ":" << ntohs(tcp_header->dest) << std::endl;
        std::cout << "Tamanho do Payload: " << payload_length << " bytes\n" << std::endl;

        // Iterate through the payload bytes and print readable ASCII characters
        for (int i = 0; i < payload_length; i++) {
            if (isprint(payload[i]) || payload[i] == '\n' || payload[i] == '\r') {
                std::cout << payload[i];
            } else {
                std::cout << "."; // Replace non-printable bytes with dots
            }
        }
        std::cout << "\n====================================\n";
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    
    const char *interface = "eth0"; // Change this to your network interface

    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Erro ao abrir dispositivo " << interface << ": " << errbuf << std::endl;
        return 1;
    }

    // Compile and apply a filter to capture only port 80
    struct bpf_program fp;
    const char *filter_exp = "tcp port 80";
    bpf_u_int32 net = 0;

    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        std::cerr << "Erro ao compilar o filtro: " << pcap_geterr(handle) << std::endl;
        return 1;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        std::cerr << "Erro ao aplicar o filtro: " << pcap_geterr(handle) << std::endl;
        return 1;
    }

    std::cout << "A escutar tráfego HTTP na interface " << interface << "..." << std::endl;

    // Capture packets indefinitely
    pcap_loop(handle, 0, processar_pacote, nullptr);

    pcap_close(handle);
    return 0;
}