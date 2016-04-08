ser:main.o c_socket.o server_management.o server_data.o command_process.o cjson.o string_int_transform.o mysql.o
	g++ -g -o $@ $^ -lpthread  -I/usr/include/mysql/ -L/usr/lib/mysql/ `mysql_config --cflags --libs`
main.o:main.cpp 
	g++ -g  -c $<
c_socket.o:c_socket.cpp
	g++ -g  -c $<
server_management.o:server_management.cpp 
	g++ -g  -c $<	
server_data.o:server_data.cpp
	g++ -g  -c $<
command_process.o:command_process.cpp
	g++ -g  -c $<
cjson.o:cjson.cpp
	g++ -g  -c $<
string_int_transform.o:string_int_transform.cpp
	g++ -g  -c $<
mysql.o:mysql.cpp
	g++ -g  -c $<
clean1:
	rm *.o
clean:
	rm *.o ser
