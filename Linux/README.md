# Hooks 
The execution of a compiled binary can be examined or entirely changed if we compile a shared libary that contains functions with the same names, and then  
use `LD_PRELOAD` to have this library loaded as an environment variable for the executable. Take a really basic example below. 

![babies_first_hook](https://github.com/cas1m1r/EDU/blob/main/Linux/hooked.gif?raw=true)

## Introduction to Hooks
Here is a really simple function, saved as badlogin.c. It checks if the user has provided (as an argument input) a string which matches a harcoded password. 
In this case a reverse engineer would easily be able to reverse the program to see the string, but that would be done with "static analysis". That's a process 
where you examine the file itself, piecing together what the code will do or looking for things like this hardcoded string. Here we can simply run our vulnerable 
program with our sneaky library loaded and have the strcmp call simply print the values being compared:
```
$ LD_PRELOAD=./hook.so ./login HAH!
=== Checking Your Credentials ===
[strcmp : HAH!,	0x53c2e7]
	~| A C C E S S  D E N I E D |~
```

```
$ LD_PRELOAD=./hook.so ./login 0x53c2e7
=== Checking Your Credentials ===
[strcmp : 0x53c2e7,	0x53c2e7]
	*** ACCESS GRANTED ***
```

## Running real applications
By intercepting `strlen()` calls for example, I can wait to see the `Untitled Document 1` string to come through (for the window title) and change the pointer to reference and entirely different string!


![hooked](https://raw.githubusercontent.com/cas1m1r/EDU/main/System/hooked.gif)

Okay, kinda nifty but it's not really that interesting. What about modifying something that affects how the user can actual run the program? Could we hook a library and add a change to say... prevent a key phrase from bring written in gedit? **Yes we can :D**.

![firstrule](https://raw.githubusercontent.com/cas1m1r/EDU/main/System/Hooks/ruleone.gif)

Thats pretty funny actually. But it definitely causes errors in the application, and it's not exactly subtle. Can we utilize this same small foothold into an application to say, completely change the user experience. For example, I like dark mode and light themes burn my eyeballs. Could I prevent the user from choosing  a light theme? **Turns out you can do that too :D**. 

By intercepting the `strlen()` call and checking for any of the names of known light themes, we can replace the string in that buffer *with existing theme file names* and the light mode options simply do not appear in the options when we run gedit using LD_PRELOAD with our special library!

![savetheretina](https://raw.githubusercontent.com/cas1m1r/EDU/main/System/Hooks/darkmode.gif)


It's not just gedit, the same trick can make the gnome-calculator much less reliable. Admittedly though, this has limited effect besides a few parlor tricks. To really change behavior of an application or probe it as it runs further, we'll probably have to get our hooks in deeper... But this was a fun start.

![badmath](https://raw.githubusercontent.com/cas1m1r/EDU/main/System/Hooks/Applications/badcalc.gif)

## Rootkits
Another way people hook low level system operations is the "rootkit". I took a look at some of this code and tried to piece something together for myself. This small kernel module adds a "hidden" argument that will give a user root (demonstrated below). 

![backdoor](https://raw.githubusercontent.com/cas1m1r/EDU/main/System/Hooks/godemode.gif)

