### Assignment 2

## Anjishnu Mukherjee B05-511017020 (510517086)

| Relevant flags | Corresponding tcpdump functionality                                                                     |
| :------------: | :------------------------------------------------------------------------------------------------------ |
|       -D       | Display available interfaces.                                                                           |
|       -n       | Don't convert addresses (i.e., host addresses, port numbers, etc.) to names.                            |
|    -c count    | Exit after receving count number of packets. (Here, count = 20)                                         |
|    -w file     | Write the raw packets to file rather than parsing and printing them out.                                |
|                | They can later be printed with the -r option. (Here, file = "results_with_n.pcap")                      |
|    -r file     | Read packets from file (which was created with the -w option or by other tools that                     |
|                | write pcap or pcapng files).                                                                            |
|       -e       | Print the link-level header on each dump line. This can be used, for example,                           |
|                | to print MAC layer addresses for protocols such as Ethernet and IEEE 802.11.                            |
|  -i interface  | Listen on interface. If unspecified, tcpdump searches the system interface list                         |
|                | for the lowest numbered, configured up interface (excluding loopback),                                  |
|                | which may turn out to be, for example, ``eth0''.                                                        |
|      -ttt      | Print a delta (micro-second resolution) between current and previous line on each dump line.            |
|       -A       | Print packet information in Ascii format. Handy for capturing web pages.                                |
|   expression   | Selects which packets will be dumped. If no expression is given, all packets on the net will be dumped. |
|                | Otherwise,only packets for which expression is `true' will be dumped.                                   |
|                | For the expression syntax, see pcap-filter(7).                                                          |
|      host      | Capture packets from specific hosts.                                                                    |
|      src       | Capture packets from specific source.                                                                   |
|      dst       | Capture packets from specific destination.                                                              |
|    <[port]>    | Capture packets from specific port.                                                                     |

2a.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump --version**

        tcpdump version 4.9.2
        libpcap version 1.8.1
        OpenSSL 1.1.1  11 Sep 2018

2a.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -D**

        1.eth0 [Up, Running]
        2.any (Pseudo-device that captures on all interfaces) [Up, Running]
        3.lo [Up, Running, Loopback]
        4.nflog (Linux netfilter log (NFLOG) interface)
        5.nfqueue (Linux netfilter queue (NFQUEUE) interface)
        6.usbmon1 (USB bus number 1)

        There are thus 6 interfaces available.

2a.3. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ifconfig eth0 promisc**

        Switch the primary ethernet interface to promiscuous mode.

2b.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 20 -n -w results_with_n.pcap**

        Listen to the promiscuous mode interface of host with -n flag.

2b.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 20 -w results_without_n.pcap**

        Listen to the promiscuous mode interface of host without -n flag.

2c.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -r results_with_n.pcap**

        Read results_with_n.pcap file

2c.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -r results_without_n.pcap**

        Read results_without_n.pcap file

2c.3. **Identifying the different fields present in TCP/IP packets captured by tcpdump. :**

        1. Packet arrival time as per local clock
        2. Internet Protocol - IP for IPv4 and IP6 for IPv6
        3. Source IP address and port
        4. TCP flags
        5. Destination IP address and port
        6. Destination network layer protocol
        7. Packet length

2d. **Extract packet arrival time, source IP address, destination IP address and port**

        Considering the file results_with_n.pcap,
        we take any one entry in the file for demonstration.
        The result will show arrivial time, source IP address,
        destination IP address and port in the form of
        [arrivial time][source IP].[port]>[destination IP].[port]
        ----------------------------------------------------------------------------
        01:52:01.676462 IP ubuntu-s-1vcpu-1gb-nyc1-01.ssh > 115.96.128.146.50243 ...
        ----------------------------------------------------------------------------
        Thus, arrival time is 01:52:01.676462 relative to local clock.
        Source IP is ubuntu-s-1vcpu-1gb-nyc1-01 and port is ssh.
        Destination IP is 115.96.128.146 and port is 50243.
        The reason why source still displays a name and not a IP address
        is because I am using a cloud machine which implements some measures
        to ensure that -n flag doesn't reveal its IP address.

2e. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 1 -e**

        Extract source MAC address and destination MAC address using the -e flag.
        In the result, source MAC address and destination MAC address is shown
        in the form of [source MAC address] > [destination MAC address]
        -----------------------------------------------------------------------
        ... 6e:b5:09:98:23:a3 (oui Unknown) > 00:00:5e:00:01:6e (oui IANA) ...
        -----------------------------------------------------------------------
        MAC address of source is 6e:b5:09:98:23:a3
        MAC address of destination is 00:00:5e:00:01:6e

        Comparing with the output of question 2d, I have observed
        that the source IP is ubuntu-s-1vcpu-1gb-nyc1-01.ssh
        and destination IP is 115.96.128.146.50243.

2f. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 5 -ttt**

        ...
        00:00:00.000000 ...
        00:00:00.000058 ...
        00:00:00.000050 ...
        00:00:00.000038 ...
        00:00:00.001187 ...
        ...

        To get the inter-arrival times while capturing packets, I use the fact that the
        -ttt flag prints a delta (micro-second resolution) between current and previous
        line on each dump line. In the output displayed above, I have only included
        the first colum of the output corresponding to these deltas.

2g. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump host www.google.com -a**

        www.google.com needs to be opened in the browser window for this
        command to work. We need to run tcpdump first and then browse
        something on google.com to get network traffic.

2h.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -c 5 -i eth0 icmp**

        The tcpdump command to capture the packets associated with ping.
        TODO : Explain the different fields of each request and reply.

2h.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -i eth0 not icmp**

        The tcpdump command to capture the packets associated with wget.
        TODO : Explain the different fields of each request and reply.

2h.3. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump 'icmp[icmptype] != icmp-echo and icmp[icmptype] !=icmp-echoreply'**

        The tcpdump command to capture the packets associated with traceroute.
        TODO : Explain the different fields of each request and reply.

2i.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src IP addr and dst IP addr**

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as both source and destination.

2i.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src IP addr**

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as only source.

2i.3. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump dst IP addr**

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as only destination.

2j. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src IP addr and dst IP addr icmp and port 22**

       The tcpdump command that captures packets containing ICMP
       packets between two hosts with different IP addresses.

2k. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump**

        TODO : The tcpdump command to capture packets containing SSH request
               and reply between two specific IP addresses
               (hint: use port number 22 for SSH)
