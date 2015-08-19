
## lush
Shell is a program that takes what you input on the keyboard and gives them to the OS to perform. The Linux OS have System Calls, but they should be called through GNU C Library. Shell can provide a convenient way to call the System Calls.

lush is a simple implemention of shell.

## Add more to lush
add DIY commands to builtin.c/h

## Compile
$ gcc main.c builtin.c -o lush

## Run
$ ./lush



##ref

[Advanced Programming in the UNIX Environment](http://www.apuebook.com/)

[starter](http://stephen-brennan.com/2015/01/16/write-a-shell-in-c/)

[getch()](https://gist.github.com/ionutvmi/5708845)


[handle backspace](http://stackoverflow.com/questions/5723935/echoing-a-backspace)

[handle arrow-key](http://stackoverflow.com/questions/10463201/getch-and-arrow-codes)


[key code](http://help.adobe.com/en_US/AS2LCR/Flash_10.0/help.html?content=00000520.html)
