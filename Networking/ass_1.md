### Assignment 1

## Anjishnu Mukherjee B05-511017020 (510517086)

- 1a. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ifconfig**

        ```
        eth0: flags=4419<UP,BROADCAST,RUNNING,PROMISC,MULTICAST>  mtu 1500
        inet 157.245.240.68  netmask 255.255.240.0  broadcast 157.245.255.255
        inet6 fe80::6cb5:9ff:fe98:23a3  prefixlen 64  scopeid 0x20<link>
        ether 6e:b5:09:98:23:a3  txqueuelen 1000  (Ethernet)
        RX packets 456235  bytes 139315738 (139.3 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 491898  bytes 73484410 (73.4 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
        ```

        The value next to inet is the IPv4 address of the machine,
        i.e. 157.245.240.68

  1b. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# ping 8.8.8.8**

        ```
        8.8.8.8 ping statistics
        10 packets transmitted, 10 received, 0% packet loss, time 9011ms
        rtt min/avg/max/mdev = 0.797/0.907/1.432/0.178 ms
        ```

  1c. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# dig www.google.com**

        IP address of www.google.com : 172.217.3.100

        **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# dig www.google.com**

        IP address of local DNS server of IIEST (www.iiests.ac.in) : 14.139.223.183

1d. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# traceroute www.google.com**

        Number of hops = 8
        IP a network gateway of subnet = 157.245.240.254 (1st hop's IPv4 address)

1e. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# arp -an** (arp -a will print which one is gateway)

        MAC address of the device that is performing as network gateway : 157.245.240.1

1f. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# nslookup www.google.com**

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

1g. **root@ubuntu-s-1vcpu-1gb-nyc1-01:~# netstat -l**

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
