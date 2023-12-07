- 打开powershell或者命令行，安装wsl：
```
wsl --install
```


- 然后安装anaconda或者其他python环境管理系统，如装anaconda具体参考：
https://blog.csdn.net/m0_63834988/article/details/131867701
（方法2似乎确实比较方便）


- 重新打开wsl 为graphscope创建虚拟环境：
```
conda create -n graphscopeEnv python=3.9 // graphscope要求的python版本是3.9
conda activate graphscopeEnv
pip install graphscope
```


- 在pycharm或vscode中重新选择解释器，尝试运行 import graphscope as gs
  如果用vscode的话，需要安装wsl扩展，具体可参考 https://blog.csdn.net/qq_37354286/article/details/128245475



# Tugraph

https://www.tugraph.org/download 选择ubuntu版本下载到wsl里面
文件名字应该叫tugraph-4.0.1-1.x86_64.deb
在这个文件的路径下运行
```
sudo dpkg -i tugraph-4.0.1-1.x86_64.deb
```
然后参照 https://tugraph-db.readthedocs.io/en/latest/5.developer-manual/2.running/1.compile.html 运行
```
$ git clone --recursive https://github.com/TuGraph-family/tugraph-db.git
$ cd tugraph-db
$ deps/build_deps.sh
$ mkdir build && cd build
$ cmake .. -DOURSYSTEM=centos -DENABLE_PREDOWNLOAD_DEPENDS_PACKAGE=1
$ make
$ make package
```