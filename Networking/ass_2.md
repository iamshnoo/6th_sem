### Assignment 2

## Anjishnu Mukherjee B05-511017020 (510517086)

2a.1 **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump --version**

        tcpdump version 4.9.2
        libpcap version 1.8.1
        OpenSSL 1.1.1  11 Sep 2018

2a.2 **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump --version**

        1.eth0 [Up, Running]
        2.any (Pseudo-device that captures on all interfaces) [Up, Running]
        3.lo [Up, Running, Loopback]
        4.nflog (Linux netfilter log (NFLOG) interface)
        5.nfqueue (Linux netfilter queue (NFQUEUE) interface)
        6.usbmon1 (USB bus number 1)

        There are 6 interfaces available.

2a.3 **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ifconfig eth0 promisc**

        Switch the ethernet interface to promiscuous mode.

2b.1 **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 20 -n -w results_with_n.pcap**

        Listen to the promiscuous mode interface of host with -n option.

        Role of -n flag:
        ----------------
         -n     Don't convert addresses (i.e., host addresses, port numbers, etc.) to names.

2b.2 **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 20 -w results_without_n.pcap**

        Listen to the promiscuous mode interface of host without -n option.

2c.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -r results_with_n.pcap**

2c.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -r results_without_n.pcap**
