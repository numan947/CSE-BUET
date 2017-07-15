#!/bin/sh

cd .
outputFile="multi_random_802_15_4.out"

tclFile="802_15_4_udp.tcl"
traceFile="multi_radio_802_15_4_random.tr"
awkFile="rule_wireless_udp.awk"


start=20
end=100

# graph files
thrGraph="802_15_4_throughput.txt"
delayGraph="802_15_4_delay.txt"
deliveryRatioGraph="802_15_4_deliveryGraph.txt"
dropRatioGraph="802_15_4_dropGraph.txt"
energyGraph="802_15_4_energyGraph.txt"
thrPs="802_15_4_throughput.ps"
delayPs="802_15_4_delay.ps"
deliveryPs="802_15_4_delivery.ps"
dropPs="802_15_4_drop.ps"
energyPs="802_15_4_energy.ps"
nodesPsWireless="802_15_4_nodesPsWireless.ps"
flowsPsWireless="802_15_4_flowsPsWireless.ps"
ppsPsWireless="802_15_4_ppsPsWireless.ps"
coveragePsWireless="802_15_4_coveragePsWireless.ps"


#pckt_size=64
flowStart=10
flowEnd=50
standardFlow=$((($flowStart+$flowEnd)/2))
pckt_per_sec_start=100
pckt_per_sec_end=500
coverage_start=2
coverage_end=5
coverage_mid=3
#pckt_interval=[expr 1 / $pckt_per_sec]
#echo "INERVAL: $pckt_interval"

#routing=DSDV

#time_sim=10

#iteration=$(printf %.0f $iteration_float);
consRow=4
def_node_num=30

vary=node

node=$start
b="0 0.0"
space=" "
newline="\n"
printf "TitleText: Throughput Vs Num of Nodes\nYUnitText: Throughput\nXUnitText: Num of Nodes\n\"\"\n0 0.0\n" > $thrGraph
printf "TitleText: delay Vs Num of Nodes\nYUnitText: delay\nXUnitText: Num of Nodes\n\"\"\n0 0.0\n" > $delayGraph
printf "TitleText: Delivery Ratio Vs Num of Nodes\nYUnitText: Delivery Ratio\nXUnitText: Num of Nodes\n\"\"\n0 0.0\n" > $deliveryRatioGraph
printf "TitleText: Drop Ratio Vs Num of Nodes\nYUnitText: Drop Ratio\nXUnitText: Num of Nodes\n\"\"\n0 0.0\n" > $dropRatioGraph
printf "TitleText: Energy Vs Num of Nodes\nYUnitText: Energy\nXUnitText: Num of Nodes\n\"\"\n0 0.0\n" > $energyGraph
while [ $node -le $end ]
do
	row=5
	col=$node
	ns $tclFile $row $col $standardFlow $pckt_per_sec_start $coverage_mid

	awk -f $awkFile $traceFile > $outputFile 
	
	l=0

	while read line
	do
		l=$(($l+1))
		echo $line
		if ([ "$l" = "1" ]);then
			echo $node $space $line >> $vary$thrGraph			
		elif ([ "$l" = "2" ]);then
			echo $node $space $line >> $vary$delayGraph			
		elif ([ "$l" = "3" ]);then
			echo $node $space $line >> $vary$deliveryRatioGraph
		elif ([ "$l" = "4" ]);then
			echo $node $space $line >> $vary$dropRatioGraph
		elif ([ "$l" = "5" ]);then
			echo $node $space $line >> $vary$energyGraph
		fi
	done < $outputFile
	
	node=$(($node+20))

done

# xgraph -device ps -o $deliveryPs $deliveryRatioGraph
# xgraph -device ps -o $dropPs $dropRatioGraph
# xgraph -device ps -o $energyPs $energyGraph
# xgraph -device ps -o $thrPs $thrGraph
# xgraph -device ps -o $delayPs $delayGraph
# gs -dBATCH -dNOPAUSE -q -sDEVICE=ps2write -sOutputFile=$nodesPsWireless $deliveryPs $dropPs $energyPs $thrPs $delayPs 
# xdg-open $nodesPsWireless &

printf "TitleText: Throughput Vs Packet per Sec\nYUnitText: Throughput\nXUnitText: Packet per Sec\n\"\"\n0 0.0\n" > $thrGraph
printf "TitleText: delay Vs Packet per Sec\nYUnitText: delay\nXUnitText: Packet per Sec\n\"\"\n0 0.0\n" > $delayGraph
printf "TitleText: Delivery Ratio Vs Packet per Sec\nYUnitText: Delivery Ratio\nXUnitText: Packet per Sec\n\"\"\n0 0.0\n" > $deliveryRatioGraph
printf "TitleText: Drop Ratio Vs Packet per Sec\nYUnitText: Drop Ratio\nXUnitText: Packet per Sec\n\"\"\n0 0.0\n" > $dropRatioGraph
printf "TitleText: Energy Vs Packet per Sec\nYUnitText: Energy\nXUnitText: Packet per Sec\n\"\"\n0 0.0\n" > $energyGraph

vary=packet_per_sec

pcktRate=$pckt_per_sec_start
while [ $pcktRate -le $pckt_per_sec_end ]
do
	ns $tclFile $consRow $def_node_num $standardFlow $pcktRate $coverage_mid

	awk -f $awkFile $traceFile > $outputFile 
	l=0

	while read line
	do
		l=$(($l+1))
		echo $line
		if ([ "$l" = "1" ]);then
			echo $pcktRate $space $line >> $vary$thrGraph			
		elif ([ "$l" = "2" ]);then
			echo $pcktRate $space $line >> $vary$delayGraph			
		elif ([ "$l" = "3" ]);then
			echo $pcktRate $space $line >> $vary$deliveryRatioGraph
		elif ([ "$l" = "4" ]);then
			echo $pcktRate $space $line >> $vary$dropRatioGraph
		elif ([ "$l" = "5" ]);then
			echo $pcktRate $space $line >> $vary$energyGraph
		fi
	done < $outputFile

	pcktRate=$(($pcktRate+100))
done

# xgraph -device ps -o $deliveryPs $deliveryRatioGraph
# xgraph -device ps -o $dropPs $dropRatioGraph
# xgraph -device ps -o $energyPs $energyGraph
# xgraph -device ps -o $thrPs $thrGraph
# xgraph -device ps -o $delayPs $delayGraph
# gs -dBATCH -dNOPAUSE -q -sDEVICE=ps2write -sOutputFile=$ppsPsWireless $deliveryPs $dropPs $energyPs $thrPs $delayPs 
# xdg-open $ppsPsWireless &

printf "TitleText: Throughput Vs Coverage Area\nYUnitText: Throughput\nXUnitText: Coverage Area\n\"\"\n0 0.0\n" > $thrGraph
printf "TitleText: delay Vs Coverage Area\nYUnitText: delay\nXUnitText: Coverage Area\n\"\"\n0 0.0\n" > $delayGraph
printf "TitleText: Delivery Ratio Vs Coverage Area\nYUnitText: Delivery Ratio\nXUnitText: Coverage Area\n\"\"\n0 0.0\n" > $deliveryRatioGraph
printf "TitleText: Drop Ratio Vs Coverage Area\nYUnitText: Drop Ratio\nXUnitText: Coverage Area\n\"\"\n0 0.0\n" > $dropRatioGraph
printf "TitleText: Energy Vs Coverage Area\nYUnitText: Energy\nXUnitText: Coverage Area\n\"\"\n0 0.0\n" > $energyGraph

vary=coverage

coverage=$coverage_start
while [ $coverage -le $coverage_end ]
do
	ns $tclFile $consRow $def_node_num $standardFlow $pckt_per_sec_start $coverage

	awk -f $awkFile $traceFile > $outputFile 
	l=0

	while read line
	do
		l=$(($l+1))
		echo $line
		if ([ "$l" = "1" ]);then
			echo $coverage $space $line >> $vary$thrGraph			
		elif ([ "$l" = "2" ]);then
			echo $coverage $space $line >> $vary$delayGraph			
		elif ([ "$l" = "3" ]);then
			echo $coverage $space $line >> $vary$deliveryRatioGraph
		elif ([ "$l" = "4" ]);then
			echo $coverage $space $line >> $vary$dropRatioGraph
		elif ([ "$l" = "5" ]);then
			echo $coverage $space $line >> $vary$energyGraph
		fi
	done < $outputFile

	coverage=$(($coverage+1))
done
# xgraph -device ps -o $deliveryPs $deliveryRatioGraph
# xgraph -device ps -o $dropPs $dropRatioGraph
# xgraph -device ps -o $energyPs $energyGraph
# xgraph -device ps -o $thrPs $thrGraph
# xgraph -device ps -o $delayPs $delayGraph
# gs -dBATCH -dNOPAUSE -q -sDEVICE=ps2write -sOutputFile=$coveragePsWireless $deliveryPs $dropPs $energyPs $thrPs $delayPs 
# xdg-open $coveragePsWireless &

printf "TitleText: Throughput Vs Num of Flows\nYUnitText: Throughput\nXUnitText: Num of Flows\n\"\"\n0 0.0\n" > $thrGraph
printf "TitleText: delay Vs Num of Flows\nYUnitText: delay\nXUnitText: Num of Flows\n\"\"\n0 0.0\n" > $delayGraph
printf "TitleText: Delivery Ratio Vs Num of Flows\nYUnitText: Delivery Ratio\nXUnitText: Num of Flows\n\"\"\n0 0.0\n" > $deliveryRatioGraph
printf "TitleText: Drop Ratio Vs Num of Flows\nYUnitText: Drop Ratio\nXUnitText: Num of Flows\n\"\"\n0 0.0\n" > $dropRatioGraph
printf "TitleText: Energy Vs Num of Flows\nYUnitText: Energy\nXUnitText: Num of Flows\n\"\"\n0 0.0\n" > $energyGraph

vary=numflow

numflow=$flowStart
while [ $numflow -le $flowEnd ]
do
	ns $tclFile $consRow $def_node_num $numflow 100 3

	awk -f $awkFile $traceFile > $outputFile 
	l=0

	while read line
	do
		l=$(($l+1))
		echo $line
		if ([ "$l" = "1" ]);then
			echo $numflow $space $line >> $vary$thrGraph			
		elif ([ "$l" = "2" ]);then
			echo $numflow $space $line >> $vary$delayGraph			
		elif ([ "$l" = "3" ]);then
			echo $numflow $space $line >> $vary$deliveryRatioGraph
		elif ([ "$l" = "4" ]);then
			echo $numflow $space $line >> $vary$dropRatioGraph
		elif ([ "$l" = "5" ]);then
			echo $numflow $space $line >> $vary$energyGraph
		fi
	done < $outputFile
	

	numflow=$(($numflow+10))

done

# xgraph -device ps -o $deliveryPs $deliveryRatioGraph
# xgraph -device ps -o $dropPs $dropRatioGraph
# xgraph -device ps -o $energyPs $energyGraph
# xgraph -device ps -o $thrPs $thrGraph
# xgraph -device ps -o $delayPs $delayGraph
# gs -dBATCH -dNOPAUSE -q -sDEVICE=ps2write -sOutputFile=$flowsPsWireless $deliveryPs $dropPs $energyPs $thrPs $delayPs 
# xdg-open $flowsPsWireless
