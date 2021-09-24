import sys
import xml.etree.ElementTree as ET
import json
import io
import argparse
import os
import struct
import shutil

try:
  to_unicode = unicode
except NameError:
  to_unicode = str

class GrowingList(list):
    def __setitem__(self, index, value):
        if index >= len(self):
            self.extend([None]*(index + 1 - len(self)))
        list.__setitem__(self, index, value)

class ParamHp:
  name = ""
  def __init__(self):
    self.addr = [-1, -1, -1, -1]

class ParamLp:
  name = ""
  def __init__(self):
    self.addr = [-1, -1, -1, -1]

class ParamShelv:
  name = ""
  addr = -1

class ParamPeq:
  name = ""
  addr = -1

class ParamPeqBank:
  name = ""
  def __init__(self):
    self.addr = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1]

class ParamPhase:
  name = ""
  addr = -1

class ParamDelay:
  name = ""
  addr = -1

class ParamGain:
  name = ""
  addr = -1

class ParamFir:
  name = ""
  addr = -1
  len = 0

class ParamXO:
  hpname = ""
  lpname = ""
  def __init__(self):
    self.hpaddr = [-1, -1, -1, -1]
    self.lpaddr = [-1, -1, -1, -1]

ninputs = 0

parser = argparse.ArgumentParser()
parser.add_argument("input", help="SigmaStudio project file")
parser.add_argument("plugin", help="Name of plugin")
parser.add_argument('--gui', help="Path to html gui", type=str)

# Read arguments from the command line
args = parser.parse_args()

# Check for --input
if args.input:
  print("SigmaStudio project file: %s" % args.input)
  path_sigmastudioproject = args.input
if args.plugin:
  print("Name of plugin: %s" % args.plugin)
  nameplugin = args.plugin

split_path = path_sigmastudioproject.rsplit("\\",1)
filename = os.path.basename(split_path[0])
projectname = filename.split(".")[0]
projectdir = os.path.dirname(path_sigmastudioproject)

#--- Read TxBuffer file
print("Reading " + projectdir + "/TxBuffer_IC_1.dat")
if not os.path.exists(projectdir + "/TxBuffer_IC_1.dat"):
  print("Could not find file TxBuffer_IC_1.dat in project directory")
  exit()
txbuffer = bytearray()
with open(projectdir + "/TxBuffer_IC_1.dat") as fp:
  line = fp.readline()
  while line:
    strlst = line.split(",")
    for ii in range(0, len(strlst)):
      str_ = strlst[ii].strip()
      if str_.startswith('0x'):
        txbuffer += bytearray.fromhex(str_[2:])
    line = fp.readline()

#--- Read NumBytes file
print("Reading " + projectdir + "/NumBytes_IC_1.dat")
if not os.path.exists(projectdir + "/NumBytes_IC_1.dat"):
  print("Could not find file NumBytes_IC_1.dat in project directory")
  exit()
numbytes = []
with open(projectdir + "/NumBytes_IC_1.dat") as fp:
  line = fp.readline()
  while line:
    strlst = line.split(",")
    numbytes.append(int(strlst[0].strip()))
    line = fp.readline()

#--- Create output directory
try:
  if os.path.exists(projectname) != True:
    os.mkdir(projectname)
except OSError:
  print("Creation of output directory %s failed" % projectname)

#--- Write dsp.fw
print("Writing DSP firmware")
with open(projectname + "/dsp.fw", 'wb') as file:
  idx = 0
  for ii in range(0, len(numbytes)):
    file.write(bytearray(struct.pack("!I", numbytes[ii])))
    for nn in range(0,numbytes[ii]):
      file.write(bytearray(struct.pack("!B", txbuffer[idx])))
      idx = idx + 1
    
#--- Reading project xml file
print("Reading " + projectdir + "/" + projectname + ".xml")

tree = ET.parse(projectdir + "/" + projectname + ".xml")
root = tree.getroot()

spdifoutmux_channel = []
spdifoutmux_channel.append(GrowingList())
spdifoutmux_channel.append(GrowingList())
spdifoutmux_port = [0, 0]

lshelv = []
hshelv = []
peq = []
peqbank = []
hp = []
lp = []
phase = []
dly = []
gain = []
xohp = []
xolp = []
fir = []

# --- Count inputs
for module in root.findall('IC/Module'):
  cellname = module.find('CellName')

  if cellname.text.startswith('InputSelect'):
    strlist = cellname.text.split('_',2)
    if len(strlist) > 2:
      if "Analog" in strlist[2]:
        ninputs = ninputs + 1

inputselect_analog = []
for ii in range(0,ninputs):
  inputselect_analog.append(GrowingList())

inputselect_spdif = []
for ii in range(0,ninputs):
  inputselect_spdif.append(GrowingList())

inputselect_uac2 = []
for ii in range(0,ninputs):
  inputselect_uac2.append(GrowingList())

inputselect_exp = []
for ii in range(0,ninputs):
  inputselect_exp.append(GrowingList())

inputselect_port = []
for ii in range(0,ninputs):
  inputselect_port.append(GrowingList())

for module in root.findall('IC/Module'):
  cellname = module.find('CellName')

  if cellname.text.startswith('InputSelect'):
    strlist = cellname.text.split('_',2)
    if len(strlist) > 2:
      if "Analog" in strlist[2]:
        idx = int(strlist[1].split('.',1)[0])
        modparam = module.find('Algorithm/ModuleParameter')
        inputselect_analog[idx-1][0] = int(modparam.find('Address').text)
      elif "SPDIF" in strlist[2]:
        idx = int(strlist[1].split('.',1)[0])
        modparam = module.find('Algorithm/ModuleParameter')
        inputselect_spdif[idx-1][0] = int(modparam.find('Address').text)
      elif "UAC" in strlist[2]:
        idx = int(strlist[1].split('.',1)[0])
        modparam = module.find('Algorithm/ModuleParameter')
        inputselect_uac2[idx-1][0] = int(modparam.find('Address').text)
      elif "Exp" in strlist[2]:
        idx = int(strlist[1].split('.',1)[0])
        modparam = module.find('Algorithm/ModuleParameter')
        inputselect_exp[idx-1][0] = int(modparam.find('Address').text)
    elif len(strlist) > 1:
      idx = int(strlist[1].split('.',1)[0])
      modparam = module.find('Algorithm/ModuleParameter')
      inputselect_port[idx-1][0] = int(modparam.find('Address').text)

  elif cellname.text.startswith('SpdifOutMux'):
    strlist = cellname.text.split('_')
    if len(strlist) > 2:
      if "Analog" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][0] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][0] = int(modparam.find('Address').text)
      elif "UAC2" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][1] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][1] = int(modparam.find('Address').text)
      elif "Exp" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][2] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][2] = int(modparam.find('Address').text)
      elif "ESP32" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][3] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][3] = int(modparam.find('Address').text)
      elif "SPDIF" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][4] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][4] = int(modparam.find('Address').text)
      elif "Out" in strlist[1]:
        modparam = module.find('Algorithm/ModuleParameter')
        if "Left" in strlist[2]:
          spdifoutmux_channel[0][5] = int(modparam.find('Address').text)
        elif "Right" in strlist[2]:
          spdifoutmux_channel[1][5] = int(modparam.find('Address').text)
    else:
      modparam = module.find('Algorithm/ModuleParameter')
      if "Left" in strlist[1]:
        spdifoutmux_port[0] = int(modparam.find('Address').text)
      elif "Right" in strlist[1]:
        spdifoutmux_port[1] = int(modparam.find('Address').text)

  # --- HP blocks
  elif cellname.text.lower().startswith('plugin.hp'):
    name = cellname.text.split(':',1)[0]
    idx = -1
    nn = int(cellname.text.split(':',1)[1]) - 1
    for m in range(0,len(hp)):
      if hp[m].name == name:
        idx = m
    if idx == -1:
      newHp = ParamHp()
      hp.append(newHp)
      idx = len(hp) - 1
    hp[idx].name = name
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        hp[idx].addr[nn] = int(modparam.find('Address').text)

  # --- LP blocks
  elif cellname.text.lower().startswith('plugin.lp'):
    name = cellname.text.split(':',1)[0]
    idx = -1
    nn = int(cellname.text.split(':',1)[1]) - 1
    for m in range(0,len(lp)):
      if lp[m].name == name:
        idx = m
    if idx == -1:
      newLp = ParamLp()
      lp.append(newLp)
      idx = len(lp) - 1
    lp[idx].name = name
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        lp[idx].addr[nn] = int(modparam.find('Address').text)

  # --- LowShelv blocks 
  elif cellname.text.lower().startswith('plugin.lowshelv'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        newLShelv = ParamShelv()
        newLShelv.addr = int(modparam.find('Address').text)
        newLShelv.name = cellname.text
        lshelv.append(newLShelv)

  # --- HighShelv blocks
  elif cellname.text.lower().startswith('plugin.highshelv'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        newHShelv = ParamShelv()
        newHShelv.addr = int(modparam.find('Address').text)
        newHShelv.name = cellname.text
        hshelv.append(newHShelv)
  
  # --- PEQ banks
  elif cellname.text.lower().startswith('plugin.peqbank'):
    newPeqBank = ParamPeqBank()
    newPeqBank.name = cellname.text
    idx = 0
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        if idx < 10:
          newPeqBank.addr[idx] = int(modparam.find('Address').text)
        else:
          print("[ERROR] Not more then 8 PEQs per bank allowed.")
        idx = idx + 1
    peqbank.append(newPeqBank)

  # --- PEQ blocks
  elif cellname.text.lower().startswith('plugin.peq'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        newPeq = ParamPeq()
        newPeq.addr = int(modparam.find('Address').text)
        newPeq.name = cellname.text
        peq.append(newPeq)

  # --- Phase blocks
  elif cellname.text.lower().startswith('plugin.phase'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        newPhase = ParamPhase()
        newPhase.addr = int(modparam.find('Address').text)
        newPhase.name = cellname.text
        phase.append(newPhase)

  # --- Delay blocks
  elif cellname.text.lower().startswith('plugin.delay'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "delay" in modname:
        newDelay = ParamDelay()
        newDelay.addr = int(modparam.find('Address').text)
        newDelay.name = cellname.text
        dly.append(newDelay)

  # --- Gain blocks
  elif cellname.text.lower().startswith('plugin.gain'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "target" in modname:
        newGain = ParamGain()
        newGain.addr = int(modparam.find('Address').text)
        newGain.name = cellname.text
        gain.append(newGain)

  # --- FIR blocks
  elif cellname.text.lower().startswith('plugin.fir'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "fircoeff" in modname:
        newFir = ParamFir()
        newFir.addr = int(modparam.find('Address').text)
        newFir.len = int(modparam.find('Size').text) / 4
        newFir.name = cellname.text
        fir.append(newFir)

  # --- XO-HP blocks
  elif cellname.text.lower().startswith('plugin.xohp'):
    print("[TODO] XO-HP not implemented")
    #name = cellname.text.split(':',1)[0]
    #idx = -1
    #nn = int(cellname.text.split(':',1)[1]) - 1
    #for m in range(0,len(xohp)):
    #  if xohp[m].name == name:
    #    idx = m
    #if idx == -1:
    #  newXoHp = ParamHp()
    #  xohp.append(newXoHp)
    #  idx = len(xohp) - 1
    #xohp[idx].name = name
    #for modparam in module.findall('Algorithm/ModuleParameter'):
    #  modname = modparam.find('Name').text
    #  if "B2" in modname:
    #    xohp[idx].addr[nn] = int(modparam.find('Address').text)

  # --- XO-LP blocks
  elif cellname.text.lower().startswith('plugin.xolp'):
    print("[TODO] XO-LP not implemented")
    #name = cellname.text.split(':',1)[0]
    #idx = -1
    #nn = int(cellname.text.split(':',1)[1]) - 1
    #for m in range(0,len(xolp)):
    #  if xolp[m].name == name:
    #    idx = m
    #if idx == -1:
    #  newXoLp = ParamLp()
    #  xolp.append(newXoLp)
    #  idx = len(xolp) - 1
    #xolp[idx].name = name
    #for modparam in module.findall('Algorithm/ModuleParameter'):
    #  modname = modparam.find('Name').text
    #  if "B2" in modname:
    #    xolp[idx].addr[nn] = int(modparam.find('Address').text)

  elif cellname.text.startswith('BypassVolPoti'):
    modparam = module.find('Algorithm/ModuleParameter')
    vpot = int(modparam.find('Address').text)

  elif cellname.text.startswith('MasterVolume'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "target" in modname:
        mastervol = int(modparam.find('Address').text)

  elif cellname.text.lower().startswith('plugin.'):
    print("[WARNING] Unkown dsp block in plugin: " + cellname.text)

inputselect_analog_t = GrowingList()
idx = 0
for m in range(0,len(inputselect_analog)):
  for n in range(0,len(inputselect_analog[m])):
    inputselect_analog_t[idx] = inputselect_analog[m][n]
    idx = idx+1

inputselect_spdif_t = GrowingList()
idx = 0
for m in range(0,len(inputselect_spdif)):
  for n in range(0,len(inputselect_spdif[m])):
    inputselect_spdif_t[idx] = inputselect_spdif[m][n]
    idx = idx+1

inputselect_uac2_t = GrowingList()
idx = 0
for m in range(0,len(inputselect_uac2)):
  for n in range(0,len(inputselect_uac2[m])):
    inputselect_uac2_t[idx] = inputselect_uac2[m][n]
    idx = idx+1

inputselect_exp_t = GrowingList()
idx = 0
for m in range(0,len(inputselect_exp)):
  for n in range(0,len(inputselect_exp[m])):
    inputselect_exp_t[idx] = inputselect_exp[m][n]
    idx = idx+1

inputselect_port_t = GrowingList()
idx = 0
for m in range(0,len(inputselect_port)):
  for n in range(0,len(inputselect_port[m])):
    inputselect_port_t[idx] = inputselect_port[m][n]
    idx = idx+1

spdifoutmux_channel_t = GrowingList()
idx = 0
for m in range(0,len(spdifoutmux_channel)):
  for n in range(0,len(spdifoutmux_channel[m])):
    spdifoutmux_channel_t[idx] = spdifoutmux_channel[m][n]
    idx = idx+1
spdifoutmux_channel_t.append(spdifoutmux_port[0])
spdifoutmux_channel_t.append(spdifoutmux_port[1])


# HP addresses
hp_t = GrowingList()
idx = 0
for m in range(0,len(hp)):
  for n in range(0, 4):
    if hp[m].addr[n] != -1:
      hp_t[idx] = hp[m].addr[n]
      idx = idx+1

# LP addresses
lp_t = GrowingList()
idx = 0
for m in range(0,len(lp)):
  for n in range(0, 4):
    if lp[m].addr[n] != -1:
      lp_t[idx] = lp[m].addr[n]
      idx = idx+1

# LowShelv addresses
lshelv_t = GrowingList()
for m in range(0,len(lshelv)):
  lshelv_t[m] = lshelv[m].addr

# HighShelv addresses
hshelv_t = GrowingList()
for m in range(0,len(hshelv)):
  hshelv_t[m] = hshelv[m].addr

# PEQ bank addresses
peq_t = GrowingList()
idx = 0
for m in range(0,len(peqbank)):
  for n in range(0, len(peqbank[m].addr)):
    if peqbank[m].addr[n] != -1:
      peq_t[idx] = peqbank[m].addr[n]
      idx = idx+1

# PEQ addresses
# peq_t = GrowingList()
for m in range(0,len(peq)):
  peq_t[len(peqbank) + m] = peq[m].addr

# Phase addresses
phase_t = GrowingList()
for m in range(0,len(phase)):
  phase_t[m] = phase[m].addr

# Delay addresses
dly_t = GrowingList()
for m in range(0,len(dly)):
  dly_t[m] = dly[m].addr

# Gain address
gain_t = GrowingList()
for m in range(0,len(gain)):
  gain_t[m] = gain[m].addr

# FIR addresses + lengths
fir_t = GrowingList()
firlen_t = GrowingList()
for m in range(0,len(fir)):
  fir_t[m] = fir[m].addr
  firlen_t[m] = fir[m].len

# XO-HP addresses
xohp_t = GrowingList()
idx = 0
for m in range(0,len(xohp)):
  for n in range(0, 4):
    xohp_t[idx] = xohp[m].addr[n]
    idx = idx+1

# XO-LP addresses
xolp_t = GrowingList()
idx = 0
for m in range(0,len(xolp)):
  for n in range(0, 4):
    xolp_t[idx] = xolp[m].addr[n]
    idx = idx+1

nhp = len(hp_t)/4
nlp = len(lp_t)/4
nxolp = len(xolp_t)/4
nxohp = len(xohp_t)/4
nxo = nxohp
if nxo != nxolp:
  print('[ERROR] Counts of XO_LP and XO_HP do not match.' )

nlshelv = len(lshelv_t)
nhshelv = len(hshelv_t)
npeq = len(peq_t)
nphase = len(phase_t)
ndly = len(dly_t)
ngain = len(gain_t)
nfir = len(fir_t)

#--- Write plugin.ini
print("Writing plugin.ini")
print("[TODO] Check max. number of blocks");
data = {"name":nameplugin,
        "ninputs":ninputs,
        "nhp":nhp,
        "nlshelv":nlshelv,
        "npeq":npeq,
        "nhshelv":nhshelv,
        "nphase":nphase,
        "nlp":nlp,
        "ndly":ndly,
        "ngain":ngain,
        "nxo":nxo,
        "nfir":nfir,
        "analog":inputselect_analog_t,
        "spdif":inputselect_spdif_t,
        "uac":inputselect_uac2_t,
        "exp":inputselect_exp_t,
        "port":inputselect_port_t,
        "spdifout":spdifoutmux_channel_t,
        "hp":hp_t,
        "lshelv":lshelv_t,
        "peq":peq_t,
        "hshelv":hshelv_t,
        "lp":lp_t,
        "phase":phase_t,
        "dly":dly_t,
        "gain":gain_t,
        "xohp":xohp_t,
        "xolp":xolp_t,
        "fir":fir_t,
        "firlen":firlen_t,
        "vpot":vpot,
        "master":mastervol }

with io.open(projectname + "/plugin.ini", 'w', encoding='utf8') as outfile:
  str_ = json.dumps(data,
                    indent=0, sort_keys=False,
                    separators=(',', ': '), ensure_ascii=False)
  outfile.write(to_unicode(str_))

#--- Writing chnames.txt
print("Writing chnames.txt")
with open(projectname + "/chnames.txt", 'w') as file:
  for ii in range(0,ninputs):
    file.write("Channel " + str(ii + 1) + "\n")
  for ii in range(0,ninputs):
    file.write("Out " + str(ii + 1) + "\n")

#--- Copy aurora.jgz
print("Copying aurora.jgz")
shutil.copy2("../WEBAPP/js/aurora.jgz", "./" + projectname + "/aurora.jgz")

#--- Copy stylesheet
print("Copying dark.css")
shutil.copy2("../WEBAPP/css/dark.css", "./" + projectname + "/dark.css")

if args.gui:
  #--- Copy custom GUI html
  print("Copying custom dsp.html")
  print(args.gui)

  with open(args.gui, 'r') as f:
    dsphtml = str(f.read())

    #--- replace LP names
    for m in range(0,len(lp)):
      dsphtml = dsphtml.replace("openLP('" + lp[m].name.split('.',1)[1] + "')", "openLP(" + str(m) + ")")

    #--- replace HP names
    for m in range(0,len(hp)):
      dsphtml = dsphtml.replace("openHP('" + hp[m].name.split('.',1)[1] + "')", "openHP(" + str(m) + ")")

    # --- LowShelv blocks 
    for m in range(0,len(lshelv)):
      dsphtml = dsphtml.replace("openLShelv('" + lshelv[m].name.split('.',1)[1] + "')", "openLShelv(" + str(m) + ")")

    # --- HighShelv blocks
    for m in range(0,len(hshelv)):
      dsphtml = dsphtml.replace("openHShelv('" + hshelv[m].name.split('.',1)[1] + "')", "openHShelv(" + str(m) + ")")

    # --- PEQ banks
    for m in range(0,len(peqbank)):
      dsphtml = dsphtml.replace("openPeqBank('" + peqbank[m].name.split('.',1)[1] + "')", "openPeqBank(" + str(m) + ")")

    # --- PEQ blocks
    for m in range(0,len(peq)):
      dsphtml = dsphtml.replace("openPEQ('" + peq[m].name.split('.',1)[1] + "')", "openPEQ(" + str(len(peqbank) + m) + ")")
    
    # --- Phase blocks
    for m in range(0,len(phase)):
      dsphtml = dsphtml.replace("openPhase('" + phase[m].name.split('.',1)[1] + "')", "openPhase(" + str(m) + ")")

    # --- Delay blocks
    for m in range(0,len(dly)):
      dsphtml = dsphtml.replace("openDelay('" + dly[m].name.split('.',1)[1] + "')", "openDelay(" + str(m) + ")")

    # --- Gain blocks
    for m in range(0,len(gain)):
      dsphtml = dsphtml.replace("openGain('" + gain[m].name.split('.',1)[1] + "')", "openGain(" + str(m) + ")")

    # --- FIR blocks
    for m in range(0,len(fir)):
      dsphtml = dsphtml.replace("openFIR('" + fir[m].name.split('.',1)[1] + "')", "openFIR(" + str(m) + ")")

    # --- XO-HP blocks
    print("[TODO] Correct handling of XO blocks")

    # --- XO-LP blocks
  
  with open("./" + projectname + "/dsp.html", "w") as f1:
    f1.write(dsphtml)

else:
  #--- Copy GUI template
  print("Copying template dsp.html")
  shutil.copy2("../WEBAPP/template/dsp.html", "./" + projectname + "/dsp.html")