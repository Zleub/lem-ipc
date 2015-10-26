max=50
for (( i=1; i <= $max; ++i ))
do
#    sleep 0.2
    ./bin/lem-ipc -t $* &
done
