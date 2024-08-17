#!/usr/bin/python3

import sys
import json

def validate(fname) -> bool:
  with open(fname, "r") as f:
    content = json.load(f)
    if False == content.__contains__("size"):
      print(fname + " has no key: size!")
      return False
    if False == content.__contains__("chain"):
      print(fname + " has no key: chain!")
      return False
    if len(content["chain"]) < 2:
      print(fname + " chain length < 2!")
      return False
    print("validate " + fname)
    print("size: " + str(content["size"]))
    print("start: " + content["chain"][0])
    print("end: " + content["chain"][-1])
    chain_set = set(content["chain"])
    if len(chain_set) < len(content["chain"]):
      duplicate = len(content["chain"]) - len(chain_set)
      print(fname + " has " + str(duplicate) + " duplicate!")
      return False
    for i in range(len(content["chain"]) - 1):
      if len(content["chain"][i]) < 1 or len(content["chain"][i+1]) < 1:
        print(fname + " " + content["chain"][i] + " or " + content["chain"][i+1] + " length invalid!")
        return False
      if content["chain"][i][-1] != content["chain"][i+1][0]:
        print(fname + " " + content["chain"][i] + " cannot be connected to " + content["chain"][i+1] + "!")
        return False
    return True

if __name__ == "__main__":
  path = "../data/output/"
  fname = sys.argv[1] if len(sys.argv) > 1 else "solution.json"
  if validate(path+fname):
    print("verification passed!")
  else:
    print("verification failed!")
