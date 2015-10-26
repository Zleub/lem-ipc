max=50
for (( i=1; i <= $max; ++i )) do
sh saturation.sh 1 &
sh saturation.sh 2 &
sh saturation.sh 3 &
sh saturation.sh 4 &
sh saturation.sh 5 &
sleep 10
done
