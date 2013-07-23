#!/bin/bash

echo "Empezando test

"
for i in {1..10000}
do
	echo -n "test\n" | nc 127.0.0.1 3000
	echo "
i=$i
"
done
echo "
Test terminado
