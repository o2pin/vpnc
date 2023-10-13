Documentation available at [davidepucci.it/doc/vpnc](https://davidepucci.it/doc/vpnc).
vpnc without xauth, only psk auth 
aggessive mode

not ready yet...

Build   
(Ubuntu 22.04)
    
    apt install -y libgcrypt20-dev
    cd ./vpnc
    make -s

Usage: ./bin/vpnc [--version] [--print-config] [--help] [--long-help] [options] [config files]

    ./bin/vpnc --debug 3  ./src/vpnc.conf


```conf
# example vpnc configuration file
# see vpnc --long-help for details

#Interface name tun0
#IKE DH Group dh2
#Perfect Forward Secrecy nopfs

# You may replace this script with something better
#Script /etc/vpnc/vpnc-script
# Enable this option for NAT traversal
#UDP Encapsulate

IPSec gateway 172.17.90.2 
IPSec ID 172.17.90.2
IPSec secret 123456
IKE Authmode psk
#Xauth username <username>
#Xauth password <password>
```
