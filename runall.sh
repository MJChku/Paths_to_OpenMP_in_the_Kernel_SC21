ulimit -s unlimited
for filename in bin/*.[S,W,A-C];do
	./$filename
done
