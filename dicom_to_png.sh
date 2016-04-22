#!/bin/sh
for patient in `ls -d */`
do
	cd "$patient"
	mkdir _PATH_"${patient%%/}"
	for i in `ls -d */`
	do
		cd "$i"
		mkdir _PATH_"$patient""${i%%/}"
		for j in `ls -d */`
		do
			cd "$j"
			mkdir _PATH_"$patient""$i""${j%%/}"
			for k in `ls -a *.*`
			do
				dcmj2pnm "$k" _PATH_"$patient""$i""$j"`echo "$k" | cut -d '.' -f1`.png +on +Wi 1
			done
			cd ..
		done
		cd ..
	done
	cd ..
done
