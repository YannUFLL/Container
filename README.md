# ft_container

Here is a 3-container implementation of the STL. Vector, Map and Stack.

To generate a binary using the standard library, use the command 
```
make std
```

else use 
```
make ft 
``` 

Use make if you dont want recompile with the header files. 
```
make
```

You can activate the a slow mode by editing the test.hpp in test/ and change the SLOW value to 1. You can also change manually the lib used by the same way.

Use
```
make ft && ./ft.out > ft.txt  
make std && ./std.out > std.txt
diff std.txt ft.txt 
```
to compare the two binary output.