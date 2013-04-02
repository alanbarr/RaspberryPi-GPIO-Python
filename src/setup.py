from distutils.command.build import build as DistutilsBuild
from distutils.core import setup, Extension
import os

gpioExtMod = Extension("gpyo",
                       library_dirs = ["C-Library/library"],
                       libraries = ["rpigpio"],
                       include_dirs = ["C-Library/include"],
                       sources = ["gpiomodule.c"])

class build(DistutilsBuild):
    def run(self):
        setupDir = os.getcwd()
        os.chdir("C-Library/src")
        os.system("make")
        os.chdir(setupDir)
        DistutilsBuild.run(self)

setup(name = "gpyo", 
      version = "0.1",  
      author = "Alan Barr",
      description = "A Python wrapper to control GPIO pins on the Raspberry Pi.",
      cmdclass = {"build" : build},
      ext_modules = [gpioExtMod],
      url= "https://github.com/alanbarr/RaspberryPi-GPyO",
      classifiers = [
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Programming Language :: Python :: 3.2"
      ]

      )
