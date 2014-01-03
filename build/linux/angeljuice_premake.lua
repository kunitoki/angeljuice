
project.name = "angeljuice"
project.bindir = "../../"
project.libdir = "../../"

project.configs = { "Debug", "Release" }

package = newpackage()
package.name = "angeljuice"
package.target = "angeljuice"
package.kind = "winexe"
package.language = "c++"
package.linkflags = { "static-runtime" }

package.objdir = "intermediate"
package.config["Debug"].objdir   = "intermediate/Debug"
package.config["Release"].objdir = "intermediate/Release"

package.config["Debug"].defines         = { "LINUX=1", "DEBUG=1", "_DEBUG=1" }
package.config["Debug"].buildoptions    = { "-O0 -ggdb -Wall" }

package.config["Release"].defines       = { "LINUX=1", "NDEBUG=1" }
package.config["Release"].buildoptions  = { "-O0 -ggdb -Wall" }

package.includepaths = {
    "../../src",
    "../../../juce",
    "/usr/include"
}

package.libpaths = {
    "../../../juce/bin",
    "/usr/lib/"
}

package.config["Debug"].links = {
    "freetype", "pthread", "X11", "GL", "GLU", "rt", "Xinerama", "asound", "juce_debug"
}

package.config["Release"].links = {
    "freetype", "pthread", "X11", "GL", "GLU", "rt", "Xinerama", "asound", "juce"
}

package.files = {
    matchrecursive (
        "../../src/*.cpp",
        "../../src/*.c",
        "../../src/*.h" )
}
