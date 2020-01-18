### Assignment 2

## Anjishnu Mukherjee B05-511017020 (510517086)

| Relevant flags | Corresponding tcpdump functionality                                                                       |
| :------------: | :-------------------------------------------------------------------------------------------------------- |
|       -D       | Display available interfaces.                                                                             |
|       -n       | Don't convert addresses (i.e., host addresses, port numbers, etc.) to names.                              |
|      -nn       | Stop Domain Name translation and lookups (Host names or port names).                                      |
|    -c count    | Exit after receving count number of packets. (Here, count = 20)                                           |
|    -w file     | Write the raw packets to file rather than parsing and printing them out.                                  |
|    -r file     | Read packets from file (which was created with the -w option)                                             |
|      -ttt      | Print a delta (micro-second resolution) between current and previous line on each dump line.              |
|       -A       | Print packet information in Ascii format. Handy for capturing web pages.                                  |
|      host      | Capture packets from specific hosts.                                                                      |
|      src       | Capture packets from specific source.                                                                     |
|      dst       | Capture packets from specific destination.                                                                |
|     [port]     | Capture packets from specific port.                                                                       |
|   -s snaplen   | Snarf snaplen bytes of data from each packet.Setting snaplen to 0 sets it to the default of 262144.       |
|                | Setting snaplen to 0 sets it to the default of 262144.                                                    |
|       -e       | Print the link-level header on each dump line. This can be used, for example,                             |
|                | to print MAC layer addresses for protocols such as Ethernet and IEEE 802.11.                              |
|  -i interface  | Listen on interface. If unspecified, tcpdump searches the system interface list                           |
|                | for the lowest numbered, configured up interface (excluding loopback), which may be, for eg, eth0.        |
|   expression   | Selects which packets will be dumped. If no expression is given, all packets on the net will be dumped.   |
|                | Otherwise, packets for which expression is true will be dumped.For expression syntax, see pcap-filter(7). |

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
        something on google.com to get network traffic. -a flag ensures output
        is in ASCII format.

        ...
        10:06:52.192177 IP laptop.43623 > del03s14-in-f4.1e100.net.443: UDP, length 1350
        10:06:52.248403 IP del03s14-in-f4.1e100.net.443 > laptop.43623: UDP, length 36
        10:06:52.289983 IP laptop.41812 > del03s14-in-f4.1e100.net.https: Flags [S],
        seq 2134581189, win 64240, options [mss 1460,sackOK,TS val 332749028 ecr 0,
        nop,wscale 7], length 0
        10:06:52.292514 IP del03s14-in-f4.1e100.net.443 > laptop.43623: UDP, length 1350
        10:06:52.292701 IP del03s14-in-f4.1e100.net.443 > laptop.43623: UDP, length 1350
        10:06:52.293929 IP laptop.43623 > del03s14-in-f4.1e100.net.443: UDP, length 36
        ...

2h. **The different fields of each request and reply for 2h.1.b, 2h.2.b and 2h.3.b**

        1. Packet arrival time as per local clock
        2. Internet Protocol - IP for IPv4 and IP6 for IPv6
        3. Source IP address and port
        4. TCP flags
        5. Destination IP address and port
        6. Destination network layer protocol
        7. Packet length

2h.1.a **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        We let ping run in one terminal.

2h.1.b **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -i eth0 -s 0 -v icmp**

        We run this tcpdump command to capture the packets associated with ping
        in a separate terminal and let tcpdump listen to traffic
        from traceroute. traceroute and ping both use icmp protocol.

        TODO : output

2h.2.a **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# wget https://wordpress.org/latest.zip**

        We let wget run in one terminal.

2h.2.b **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -i eth0 -s 0 -v**

        We run this tcpdump command to capture the packets associated with wget
        in a separate terminal and let tcpdump listen to traffic
        from traceroute.

        TODO : output

2h.3.a **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# traceroute www.google.com**

        We let traceroute run in one terminal.

2h.3.b **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump -i eth0 -s 0 -v icmp**

        We run this tcpdump command to capture the packets associated with traceroute
        in a separate terminal and let tcpdump listen to traffic
        from traceroute. traceroute and ping both use icmp protocol.

        14:52:58.866431 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33476 unreachable, length 36
        14:52:58.868865 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33475 unreachable, length 36
        14:52:58.869045 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33472 unreachable, length 36
        14:52:58.869058 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33470 unreachable, length 36
        14:52:58.870038 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33478 unreachable, length 36
        14:52:58.876254 IP del03s06-in-f4.1e100.net > Aspire-E5-575G: ICMP
        del03s06-in-f4.1e100.net udp port 33469 unreachable, length 36

2i.1. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src 10.0.2.15 and dst 172.217.161.2 -c 5**

        ...
        05:24:48.900354 IP 10.0.2.15.47184 > del03s10-in-f2.1e100.net.https: Flags [P.],
        seq 2280536235:2280536392, ack 3609503, win 64028, length 157
        05:24:49.004998 IP 10.0.2.15.47184 > del03s10-in-f2.1e100.net.https: Flags [.],
        ack 215, win 64028, length 0
        05:24:49.020467 IP 10.0.2.15.47184 > del03s10-in-f2.1e100.net.https: Flags [.],
        ack 285, win 64028, length 0
        05:24:49.021118 IP 10.0.2.15.47184 > del03s10-in-f2.1e100.net.https: Flags [P.],
        seq 157:196, ack 285, win 64028, length 39
        05:24:49.133872 IP 10.0.2.15.47186 > del03s10-in-f2.1e100.net.https: Flags [.],
        ack 232, win 64028, length 0
        ...

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as both source and destination.

        TODO : check correctness

2i.2. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src 10.0.2.15 -c 5**

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as only source.

        TODO : output

2i.3. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump dst 172.217.161.2 -c 5**

        The tcpdump command that captures packets containing TCP
        packets with a specific IP address as only destination.

        TODO : output

2j. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump icmp and src 192.168.43.33 and dst 172.217.27.206**

        14:39:39.608857 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 1, length 64
        14:39:40.610400 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 2, length 64
        14:39:41.611855 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 3, length 64
        14:39:42.613228 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 4, length 64
        14:39:43.614431 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 5, length 64
        14:39:44.615868 IP home > bom07s15-in-f14.1e100.net: ICMP echo request,
        id 14744, seq 6, length 64

        The tcpdump command that captures packets containing ICMP
        packets between two hosts with different IP addresses.

2k. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# tcpdump src 10.32.6.42 and dst 10.2.1.40 and port 22 -nn**

        ...
        14:26:07.482386 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [P.],
        seq 2685039579:2685039623, ack 2031964935, win 501,
        options [nop,nop,TS val 1856280474 ecr 1525261534], length 44
        14:26:07.488906 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [.], ack 45, win 501,
        options [nop,nop,TS val 1856280480 ecr 1525279262], length 0
        14:26:08.221618 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [P.], seq 44:80, ack 45,
        win 501, options [nop,nop,TS val 1856281213 ecr 1525279262], length 36
        14:26:08.227643 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [.], ack 81, win 501,
        options [nop,nop,TS val 1856281219 ecr 1525280001], length 0
        14:26:08.227881 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [.], ack 125, win 501,
        options [nop,nop,TS val 1856281219 ecr 1525280001], length 0
        14:26:08.229278 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [.], ack 301, win 501,
        options [nop,nop,TS val 1856281221 ecr 1525280003], length 0
        14:26:08.229503 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [P.], seq 80:116, ack 301,
        win 501, options [nop,nop,TS val 1856281221 ecr 1525280003], length 36
        14:26:08.229598 IP 10.32.6.42.53284 > 10.2.1.40.22: Flags [FP.], seq 116:176, ack 301,
        win 501, options [nop,nop,TS val 1856281221 ecr 1525280003], length 60
        ...

        The tcpdump command to capture packets containing SSH request
        and reply between two specific IP addresses
        (using port number 22 for SSH)
