all:
	> output.log

	echo "TESTES PRA 1 PARAMETRO:\n" >> output.log

	echo "1_geral:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 1_geral.c cria_func.c
	./prog >> output.log 2>&1


	echo "\n\n"


	echo "TESTES PRA 2 PARAMETROs:\n" >> output.log

	echo "2_int_int:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 2_int_int.c cria_func.c
	./prog >> output.log 2>&1

	echo "2_int_ptr:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 2_int_ptr.c cria_func.c
	./prog >> output.log 2>&1

	echo "2_ptr_int:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 2_ptr_int.c cria_func.c
	./prog >> output.log 2>&1

	echo "2_ptr_ptr:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 2_ptr_ptr.c cria_func.c
	./prog >> output.log 2>&1
	

	echo "\n\n"


	echo "TESTES PRA 3 PARAMETROs:\n" >> output.log

	echo "3_main:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main1:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main1.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main2:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main2.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main3:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main3.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main4:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main4.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main5:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main5.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main6:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main6.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main7:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main7.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main8:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main8.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main9:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main9.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main10:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main10.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main11:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main11.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main12:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main12.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main13:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main13.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main14:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main14.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main15:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main15.c cria_func.c
	./prog >> output.log 2>&1

	echo "3_main16:" >> output.log
	gcc -Wall -Wa,--execstack -o prog 3_main16.c cria_func.c
	./prog >> output.log 2>&1
	
obj:
	gcc -c codmaquina.s
	objdump -d codmaquina.o > codmaquina.txt