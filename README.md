angeljuice
==========

AngelJuice is a standalone scripting IDE host that aims to easy fast application prototyping.


Welcome to AngelJuice IDE source files !
========================================

Actually to compile AngelJuice you'll need to download the libraries is built around.
The only external dependancy is JUCE, all the other libraries are self contained.

You have to:

    1. go to http://www.rawmaterialsoftware.com/juce/ and download juce library 1.44
    2. unpack it in a directory we call "projects"
    3. unpack the angeljuice sources in the same directory so you'll have this tree:
        projects
            \-----juce
            \-----angeljuice

Now if you are on Linux:

    4. go to the JUCE linux build directory and compile JUCE:
        > cd ~/projects/juce/build/linux/
        > make CONFIG=Release
    5. once finished compiling, just go into angeljuice linux build directory and build:
        > cd ~/projects/angeljuice/build/linux/
        > make CONFIG=Release
    6. then you should have an executable "angeljuice" in that directory

    PS. remember that JUCE is built around
            "freetype" (libfreetype.so),
            "pthread" (libpthread.so),
            "X11" (libX11.so),
            "GL" (libGL.so),
            "GLU" (libGLU.so),
            "rt" (librt.so),            
            "Xinerama" (libXinerama.so),
            "asound (libasound.so)"
        so if you don't have one of the current libraries, your distro will have for sure,
        do an install, and restart from 4 or 5 (depends on the errors you have, compiling
        or linking ones). Anyway if something goes wrong and you can't compile angeljuice
        for some reasons, mainly it's not my mistake...
    

Otherwise, if you are on Win32:

    4. Open VisualC++ 6 (or 2003/2005/Express)
    5. Navigate in "angeljuice/build/vc6" and open "angeljuice.dsw"
    6. Hit compile for JUCE first, then ANGELJUICE
    7. Right click on the solution explorer and add "angeljuice/build/vcexpress/angeljuice.vcproj"
    8. Hit compile solution from menu

    PS. if something goes wrong don't blame me... probably teacher didn't told you to
        download PSDK !


With this version, you can find in "angeljuice/build/codeblocks" the angeljuice project
for codeblocks ide !


If you modify something cool in AngelJuice sources, please let me know (kunitoki@gmail.com) !


Regards,
 kRAkEn/gORe
