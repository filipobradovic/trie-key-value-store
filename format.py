import os

for path, subdirs, files in os.walk("./src"):
  for name in files:
    s = name.split(".")
    if len(s) == 2 and (s[1] == "cpp" or s[1] == "h"):
      print("FORMAT: " + os.path.join(path, name))
      os.system("clang-format " + os.path.join(path, name))
      os.system("clang-format -i " + os.path.join(path, name))

for path, subdirs, files in os.walk("./tests"):
  for name in files:
    s = name.split(".")
    if len(s) == 2 and (s[1] == "cpp" or s[1] == "h"):
      print("FORMAT: " + os.path.join(path, name))
      os.system("clang-format " + os.path.join(path, name))
      os.system("clang-format -i " + os.path.join(path, name))
