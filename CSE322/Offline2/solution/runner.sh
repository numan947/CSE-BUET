
xterm -title "Router1" -hold -e ./a.out 192.168.10.1 topo2.txt &

xterm -title "Router2" -hold -e ./a.out 192.168.10.2 topo2.txt &

xterm -title "Router3" -hold -e ./a.out 192.168.10.3 topo2.txt &

xterm -title "Router4" -hold -e ./a.out 192.168.10.4 topo2.txt &

 xterm -title "Router5" -hold -e ./a.out 192.168.10.5 topo2.txt &

# xterm -title "Router6" -hold -e ./a.out 192.168.10.6 topo1.txt &

xterm -title "Driver" -hold -e python driver.py topo2.txt