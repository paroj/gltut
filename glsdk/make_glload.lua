local lfs = require "lfs"


lfs.chdir("glloadgen")
os.execute("lua MakeAllExts.lua allgl.txt -spec=gl")
os.execute("lua MakeAllExts.lua allglx.txt -spec=glX")
os.execute("lua MakeAllExts.lua allwgl.txt -spec=wgl")

os.execute("lua LoadGen.lua ../glload/d -spec=gl -version=4.4 -profile=compatibility -extfile=allgl.txt -style=glload")
os.execute("lua LoadGen.lua ../glload/d -spec=glX -extfile=allglx.txt -style=glload")
os.execute("lua LoadGen.lua ../glload/d -spec=wgl -extfile=allwgl.txt -style=glload")
