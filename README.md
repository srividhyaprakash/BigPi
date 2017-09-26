# BigPi
Computing the value of Pi to a million digits using the MPIR Library and Nonic algorithm "https://en.wikipedia.org/wiki/Borwein%27s_algorithm#Nonic_convergence".

The nonic algorithm increases the accuracy of the decimals of Pi by a factor of 9 on each successive iteration.

Installing the MPIR library.

The MPIR library is available as the source code. You need to download, compile and include the library.


I run Windows 8. But I installed it in VMware application which runs Ubuntu 14.04
here are the steps to do so.

1. Go to "http://mpir.org/downloads.html (Links to an external site.)".
2. Click and Download "MPIR 3.0.0 source bz2 
3. Navigate to the folder where you downloaded it and enter the command "tar -xvf <filename>"
4. You need to install dependencies "Yasm" and "m4". For this, type command "sudo apt-get install yasm" and then "sudo apt-get install m4". It might prompt for your password.
5. Once that is done, Navigate to the where you unzipped your MPIR 3.0.0 folder. Navigate inside and enter the command "./configure". 
6. Once that is done, Type "make"
7. Once that is done, Type "make check"
  8. Once that is done, Type "make install"
  
  This would have your MPIR library installed but for the library to be detected by the system, so that when you use it in a file, it compiles, run the command "sudo ldconfig"
  
  You have compiled and installed the library.
