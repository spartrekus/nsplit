
rm merge.dat ; ls -1 filen* | sort | while read -r i ; do              cat "$i" >> merge.dat ; done  


