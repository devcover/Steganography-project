# What is this?

It is a school project from Federal University of Rio Grande do Norte (UFRN, in portuguese).

We have to make a program that is called steg. Steg of steganography, that basically consists of hidding information on images.

The technic i will be using is the Least Significant Bit.

obs: I'm still developing it, so everything below here about the project its what's still going to have.

---

# How to use the program?


Open it in the terminal with these parameters:  
* -e for entering encript mode. by default the program is in decript mode;
* -i <\input-file> what is your input file;
* -f <\format> <\name> what will be your output file.

for ex, I want to hide some caracters of secret.txt in an .bmp image:
```
./steg -e -i secret.txt -f bmp image.bmp
```
or, if I want to extract them :
```
./steg -i image.bmp -f txt secret.txt
```

I found the -f <\format> argument unnecessary, but it is in the project requirement ¯\\\_(ツ)_/¯

---

# What this code consists of?

It has two libraries:
* image.h
* DEncode.h

The first one is responsible for reading images from disk and storing it on ram and also writting them back on disk.  
The second one is responsible for encoding or decoding the desired information on the image stored in ram through the image function.

Also it has a main that is responsible for getting these two little libraries, the arguments and making an functional program.

---

# May I use your code?

Yes. I would be glad if this code has whatever utility to someone :)

UNLESS YOU'RE FROM MY CLASS AND WANTS TO COPY IT!!  
but in this case, i don't really care. just don't say that this code is yours lol

---

### Some (quite) important notes
* This readme was builten before the development itself. So, it'll have changes throughout the development of the program. Building it first will help me to be guided;

* My objective in putting this in github is to have an easy way to edit and store my code. Also, putting stuff here will help me get familiarized with this tool;

* I'm only making this readme because this project is public. i would make it private so classmates don't copy it. but i don't think i should worry about it :)


