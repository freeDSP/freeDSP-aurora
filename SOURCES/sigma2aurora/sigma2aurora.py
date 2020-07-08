import sys
import xml.etree.ElementTree as ET
import json
import io

print(str(sys.argv[1]))

tree = ET.parse(str(sys.argv[1]))
root = tree.getroot()

hplist = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
lplist = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

for module in root.findall('IC/Module'):
  cellname = module.find('CellName')
  if cellname.text.startswith('HP'):
    print(cellname.tag, cellname.text)

    idx = int(cellname.text.split('_',1)[0].split("HP")[1])-1
    subidx = int(cellname.text.split('_',1)[1])-1

    for modparam in module.findall('Algorithm/ModuleParameter'):
      if "B2" in modparam.find('Name').text:
        hplist[(idx)*4+(subidx)] = int(modparam.find('Address').text)

  elif cellname.text.startswith('LP'):
    print(cellname.tag, cellname.text)

    idx = int(cellname.text.split('_',1)[0].split("LP")[1])-1
    subidx = int(cellname.text.split('_',1)[1])-1

    for modparam in module.findall('Algorithm/ModuleParameter'):
      if "B2" in modparam.find('Name').text:
        lplist[(idx)*4+(subidx)] = int(modparam.find('Address').text)

print(hplist)
print(lplist)