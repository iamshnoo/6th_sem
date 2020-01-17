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

        Number of hops = 8

2c.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -r results_without_n.pcap**

        Number of hops = 8

2e. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# arp -an** (arp -a will print which one is gateway)

        MAC address of the device that is performing as network gateway : 157.245.240.1

2f. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# nslookup www.google.com**

        ```
        Server:         127.0.0.53
        Address:        127.0.0.53#53
        Non-authoritative answer:
        Name:   www.google.com
        Address: 172.217.3.100
        Name:   www.google.com
        Address: 2607:f8b0:4006:800::2004
        ```

        Thus, IP Address of www.google.com is 172.217.3.100
        Doing reverse domain lookup.

      **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# nslookup 172.217.3.100**

        100.3.217.172.in-addr.arpa      name = lga34s18-in-f4.1e100.net.

2g. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# netstat -l**

        ```
        Active Internet connections (only servers):

        Proto Recv-Q Send-Q Local Address           Foreign Address         State
        tcp        0      0 localhost:domain        0.0.0.0:*               LISTEN
        tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN
        tcp6       0      0 [::]:ssh                [::]:*                  LISTEN
        udp        0      0 localhost:domain        0.0.0.0:*
        raw6       0      0 [::]:ipv6-icmp          [::]:*                  7

        Active UNIX domain sockets (only servers):

        Proto RefCnt Flags       Type       State         I-Node   Path
        unix  2      [ ACC ]     SEQPACKET  LISTENING     11620    /run/udev/control
        unix  2      [ ACC ]     STREAM     LISTENING     1076464  /run/user/0/systemd/private
        ...
        ```

        The active Internet connections are tcp, tcp6, udp, raw6.

2h. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        ```
        8.8.8.8 ping statistics
        10 packets transmitted, 10 received, 0% packet loss, time 9011ms
        rtt min/avg/max/mdev = 0.797/0.907/1.432/0.178 ms
        ```

2i. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        ```
        8.8.8.8 ping statistics
        10 packets transmitted, 10 received, 0% packet loss, time 9011ms
        rtt min/avg/max/mdev = 0.797/0.907/1.432/0.178 ms
        ```

2j. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        ```
        8.8.8.8 ping statistics
        10 packets transmitted, 10 received, 0% packet loss, time 9011ms
        rtt min/avg/max/mdev = 0.797/0.907/1.432/0.178 ms
        ```

2k. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        ```
        8.8.8.8 ping statistics
        10 packets transmitted, 10 received, 0% packet loss, time 9011ms
        rtt min/avg/max/mdev = 0.797/0.907/1.432/0.178 ms
        ```
