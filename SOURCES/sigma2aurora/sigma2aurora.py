import sys
import xml.etree.ElementTree as ET
import json
import io
import argparse

try:
  to_unicode = unicode
except NameError:
  to_unicode = str

#print(str(sys.argv[1]))

class GrowingList(list):
    def __setitem__(self, index, value):
        if index >= len(self):
            self.extend([None]*(index + 1 - len(self)))
        list.__setitem__(self, index, value)

numchn = 8

parser = argparse.ArgumentParser()
parser.add_argument("input", help="Parameter XML file in SigmaStudio project folder")
parser.add_argument("numchains", help="Set number of dsp chains")
parser.add_argument("plugin", help="Name of plugin")

# Read arguments from the command line
args = parser.parse_args()

# Check for --input
if args.input:
  print(args.input)
  tree = ET.parse(args.input)
# Check for --numchains
if args.numchains:
  print("Number of DSP chains: %s" % args.numchains)
  numchn = int(args.numchains)
if args.plugin:
  print("Name of plugin: %s" % args.plugin)
  nameplugin = args.plugin

#tree = ET.parse(str(sys.argv[1]))
root = tree.getroot()


inputselect_analog = []
for ii in range(0,numchn):
  inputselect_analog.append(GrowingList())

inputselect_spdif = []
for ii in range(0,numchn):
  inputselect_spdif.append(GrowingList())

inputselect_uac2 = []
for ii in range(0,numchn):
  inputselect_uac2.append(GrowingList())

inputselect_exp = []
for ii in range(0,numchn):
  inputselect_exp.append(GrowingList())

inputselect_port = []
for ii in range(0,numchn):
  inputselect_port.append(GrowingList())

spdifoutmux_channel = []
spdifoutmux_channel.append(GrowingList())
spdifoutmux_channel.append(GrowingList())
spdifoutmux_port = [0, 0]

lshelv = []
for ii in range(0,numchn):
  lshelv.append(GrowingList())

hshelv = []
for ii in range(0,numchn):
  hshelv.append(GrowingList())

peq = []
for ii in range(0,numchn):
  peq.append(GrowingList())

hp = []
for ii in range(0,numchn):
  hp.append(GrowingList())

lp = []
for ii in range(0,numchn):
  lp.append(GrowingList())

phase = []
for ii in range(0,numchn):
  phase.append(GrowingList())

dly = []
for ii in range(0,numchn):
  dly.append(GrowingList())

gain = []
for ii in range(0,numchn):
  gain.append(GrowingList())

xohp = []
for ii in range(0,numchn):
  xohp.append(GrowingList())

xolp = []
for ii in range(0,numchn):
  xolp.append(GrowingList())

fir = []
for ii in range(0,numchn):
  fir.append(GrowingList())

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

  elif cellname.text.startswith('HP'):
    idx = int(cellname.text.split('_',1)[0].split("HP")[1])-1
    subidx = int(cellname.text.split('_',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        hp[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('Low Shelv'):
    idx = int(cellname.text.split(' ',2)[2])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        subidx = int(modname.split('_',1)[1])-1
        lshelv[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('Param EQ'):
    idx = int(cellname.text.split(' ',2)[2])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        subidx = int(modname.split('_',1)[1])-1
        peq[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('High Shelv'):
    idx = int(cellname.text.split(' ',2)[2])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        subidx = int(modname.split('_',1)[1])-1
        hshelv[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('LP'):
    idx = int(cellname.text.split('_',1)[0].split("LP")[1])-1
    subidx = int(cellname.text.split('_',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        lp[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('Phase'):
    idx = int(cellname.text.split(' ',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        subidx = int(modname.split('_',1)[1])-1
        phase[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('Delay'):
    idx = int(cellname.text.split(' ',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "delay" in modname:
        dly[idx][0] = int(modparam.find('Address').text)

  elif cellname.text.startswith('Gain'):
    idx = int(cellname.text.split(' ',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "target" in modname:
        gain[idx][0] = int(modparam.find('Address').text)

  elif cellname.text.startswith('FIR'):
    idx = int(cellname.text.split(' ',1)[1])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "fircoeff" in modname:
        fir[idx][0] = int(modparam.find('Address').text)

  elif cellname.text.startswith('XO_LP'):
    idx = int(cellname.text.split('_',2)[1].split("LP")[1])-1
    subidx = int(cellname.text.split('_',2)[2])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        xolp[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('XO_HP'):
    idx = int(cellname.text.split('_',2)[1].split("HP")[1])-1
    subidx = int(cellname.text.split('_',2)[2])-1
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "B2" in modname:
        xohp[idx][subidx] = int(modparam.find('Address').text)

  elif cellname.text.startswith('BypassVolPoti'):
    modparam = module.find('Algorithm/ModuleParameter')
    vpot = int(modparam.find('Address').text)

  elif cellname.text.startswith('MasterVolume'):
    for modparam in module.findall('Algorithm/ModuleParameter'):
      modname = modparam.find('Name').text
      if "target" in modname:
        mastervol = int(modparam.find('Address').text)


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

lshelv_t = GrowingList()
idx = 0
for m in range(0,len(lshelv)):
  for n in range(0,len(lshelv[m])):
    lshelv_t[idx] = lshelv[m][n]
    idx = idx+1

hshelv_t = GrowingList()
idx = 0
for m in range(0,len(hshelv)):
  for n in range(0,len(hshelv[m])):
    hshelv_t[idx] = hshelv[m][n]
    idx = idx+1

hp_t = GrowingList()
idx = 0
for m in range(0,len(hp)):
  for n in range(0,len(hp[m])):
    hp_t[idx] = hp[m][n]
    idx = idx+1

lp_t = GrowingList()
idx = 0
for m in range(0,len(lp)):
  for n in range(0,len(lp[m])):
    lp_t[idx] = lp[m][n]
    idx = idx+1

peq_t = GrowingList()
idx = 0
for m in range(0,len(peq)):
  for n in range(0,len(peq[m])):
    peq_t[idx] = peq[m][n]
    idx = idx+1

phase_t = GrowingList()
idx = 0
for m in range(0,len(phase)):
  for n in range(0,len(phase[m])):
    phase_t[idx] = phase[m][n]
    idx = idx+1

dly_t = GrowingList()
idx = 0
for m in range(0,len(dly)):
  for n in range(0,len(dly[m])):
    dly_t[idx] = dly[m][n]
    idx = idx+1

gain_t = GrowingList()
idx = 0
for m in range(0,len(gain)):
  for n in range(0,len(gain[m])):
    gain_t[idx] = gain[m][n]
    idx = idx+1

xohp_t = GrowingList()
idx = 0
for m in range(0,len(xohp)):
  for n in range(0,len(xohp[m])):
    xohp_t[idx] = xohp[m][n]
    idx = idx+1

xolp_t = GrowingList()
idx = 0
for m in range(0,len(xolp)):
  for n in range(0,len(xolp[m])):
    xolp_t[idx] = xolp[m][n]
    idx = idx+1

fir_t = GrowingList()
idx = 0
for m in range(0,len(fir)):
  for n in range(0,len(fir[m])):
    fir_t[idx] = fir[m][n]
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

data = {"name":nameplugin,
        "nchn":numchn,
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
        "vpot":vpot,
        "master":mastervol }

with io.open('plugin.ini', 'w', encoding='utf8') as outfile:
    str_ = json.dumps(data,
                      indent=0, sort_keys=False,
                      separators=(',', ': '), ensure_ascii=False)
    outfile.write(to_unicode(str_))
