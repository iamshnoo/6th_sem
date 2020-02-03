- MACBOOK IP : 192.168.1.8
```
(base) mymacpro:~ anjishnu$ ifconfig en0 <br>
en0: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500 <br>
	options=400<CHANNEL_IO> <br>
	ether f8:ff:c2:29:25:f2 <br>
	inet6 fe80::877:e095:cbc6:63bb%en0 prefixlen 64 secured scopeid 0x6 <br>
	inet 192.168.1.8 netmask 0xffffff00 broadcast 192.168.1.255 <br>
	nd6 options=201<PERFORMNUD,DAD> <br>
	media: autoselect <br>
	status: active <br>
```
---
```
(base) mymacpro:~ anjishnu$ dig www.google.com

; <<>> DiG 9.10.6 <<>> www.google.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 64421
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 4, ADDITIONAL: 9

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;www.google.com.			IN	A

;; ANSWER SECTION:
www.google.COM.		123	IN	A	172.217.166.228

;; AUTHORITY SECTION:
google.COM.		51295	IN	NS	ns3.google.com.
google.COM.		51295	IN	NS	ns2.google.com.
google.COM.		51295	IN	NS	ns4.google.com.
google.COM.		51295	IN	NS	ns1.google.com.

;; ADDITIONAL SECTION:
ns1.google.COM.		62724	IN	A	216.239.32.10
ns2.google.COM.		51297	IN	A	216.239.34.10
ns3.google.COM.		51297	IN	A	216.239.36.10
ns4.google.COM.		51297	IN	A	216.239.38.10
ns1.google.COM.		51297	IN	AAAA	2001:4860:4802:32::a
ns2.google.COM.		63569	IN	AAAA	2001:4860:4802:34::a
ns3.google.COM.		136651	IN	AAAA	2001:4860:4802:36::a
ns4.google.COM.		51297	IN	AAAA	2001:4860:4802:38::a

;; Query time: 9 msec
;; SERVER: 203.163.229.8#53(203.163.229.8)
;; WHEN: Fri Jan 31 20:55:17 IST 2020
;; MSG SIZE  rcvd: 337
```
---
```
(base) mymacpro:~ anjishnu$ arp -a
? (192.168.1.4) at f8:ff:c2:29:25:f2 on en0 ifscope permanent [ethernet]
? (192.168.1.6) at 18:19:d6:f9:3a:5b on en0 ifscope [ethernet]
? (192.168.1.254) at 8c:e1:17:b3:60:6e on en0 ifscope [ethernet]
? (192.168.1.255) at ff:ff:ff:ff:ff:ff on en0 ifscope [ethernet]
? (224.0.0.251) at 1:0:5e:0:0:fb on en0 ifscope permanent [ethernet]
? (239.255.255.250) at 1:0:5e:7f:ff:fa on en0 ifscope permanent [ethernet]
```
---
```

```