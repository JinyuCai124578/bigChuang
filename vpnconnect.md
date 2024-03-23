Step0：参考 https://docs.ecnu.edu.cn/vpn/use_vpn/windows.html 下载华师大vpn
- 华师大账号：10222140459  
- 密码：Yoyo0207
- vpn 站点的域名：vpn-ct.ecnu.edu.cn

Step1：在本地执行以下命令建立隧道（<lport>: 替换为你本地任意的空闲端口）
（注：该命令建议在wsl或Mac Terminal中执行）
```
ssh -N -f -L 29001:127.0.0.1:2900 gateway@59.78.194.63 -p 2304
（密码：gateway）
```
Step2：在本地连接ssh隧道 (此时你可以自由的使用各种客户端建立ssh连接，包括但不限于cmd、xshell、putty等)
```
ssh root@localhost -p 29001
（默认密码：1234）