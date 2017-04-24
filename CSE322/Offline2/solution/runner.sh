
xterm -title "Router1" -hold -e ./a.out 192.168.10.1 topo1.txt &

xterm -title "Router2" -hold -e ./a.out 192.168.10.2 topo1.txt &

xterm -title "Router3" -hold -e ./a.out 192.168.10.3 topo1.txt &

xterm -title "Router4" -hold -e ./a.out 192.168.10.4 topo1.txt &

# xterm -title "Router5" -hold -e ./a.out 192.168.10.5 topo1.txt &

# xterm -title "Router6" -hold -e ./a.out 192.168.10.6 topo1.txt &

xterm -title "Driver" -hold -e python driver.py topo1.txt