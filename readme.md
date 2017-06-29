# What is this?

It is a school project from Federal University of Rio Grande do Norte (UFRN, in portuguese).

We have to make a program that is called steg. Steg from steganography, that basically consists in hidding information on images.

The technic used is the Least Significant Bit.

obs: It's still in developing phase.

---

# How to use the program?


Open it in the terminal with these parameters:  
* -e for entering encript mode;
* -i (input-file) input your file name;
* -f (format) (name) name of the output file.

for ex, I want to hide some caracters of secret.txt in an .bmp image:
```
./steg -e -i secret.txt -f bmp image.bmp
```
or, if I want to extract them :
```
./steg -d -o image.bmp -f txt secret.txt
```

---

# What this code consists of?

It has two libraries:
* image.h
* DEncode.h

The first one is responsible for reading images from disk and storing it on ram and also writting them back on disk.  
The second one is responsible for encoding or decoding the desired information on the image stored in ram.

Also it has a main that is responsible for getting these two libraries, the arguments and making the functional program.

---

# May I use your code/program freely?

Yes. I would be glad if this code has some utility to someone.

---
