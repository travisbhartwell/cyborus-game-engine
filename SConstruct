import os

# Shared build parameters
CPPPATH = ["/usr/include/SDL",
           "/usr/include/lua5.1"]
CCFLAGS = ["-Wall"]
ARFLAGS = ["-r", "-s"]
SOURCE_DIR = "CGE"

release_env = Environment(CPPPATH = CPPPATH,
                          ARFLAGS = ARFLAGS,
                          CCFLAGS = CCFLAGS + ["-O2"])

debug_env = release_env.Clone()
debug_env.Replace(CCFLAGS=CCFLAGS + ["-g"])

for build in ['release', 'debug']:
    env = globals()[build + "_env"]
    build_dir = os.path.join("build", build)
    library = 'libcge-ubu64-' + build
    
    VariantDir(build_dir, SOURCE_DIR, duplicate=0)

    CGEFiles = \
        Glob(build_dir + "/*.cpp") + \
        Glob(build_dir + "/*.c")

    OpenALDir = os.path.join(build_dir, "OpenAL")
    OpenALFiles = Glob(OpenALDir + "/*.cpp")

    OpenGLDir = os.path.join(build_dir, "OpenGL")
    OpenGLFiles = \
        Glob(OpenGLDir + "/*.cpp") + \
        Glob(OpenGLDir + "/*.c")

    UIDir = os.path.join(build_dir, "UI")
    UIFiles = Glob(UIDir + "/*.cpp")

    LibraryFiles = \
        CGEFiles + \
        OpenALFiles + \
        OpenGLFiles + \
        UIFiles

    env.Library(library, LibraryFiles)

