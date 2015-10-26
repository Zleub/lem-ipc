while (test 42) do
	./bin/lem-ipc -t 3 &
	./bin/lem-ipc -t 1 &
	./bin/lem-ipc -t 2 &
	sleep 1
done
