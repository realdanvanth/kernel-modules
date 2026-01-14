make 
sudo insmod hello.ko
sudo dmesg | tail
echo "---------------------------"
modinfo hello.ko
sudo rmmod hello
echo "---------------------------"
sudo dmesg | tail
