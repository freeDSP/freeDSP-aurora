function getConfig(){
  fetch("/config").then (function (response) {return response.json();})
  .then (function (data) {  
    document.getElementById("aid").value = data.aid;
    if(data.vpot==1) document.getElementById("vpot").checked=true;
    else document.getElementById("vpot").checked=false;
    document.getElementById("adcsum").value=data.adcsum;})
  .catch (function (error) {console.log(error);});
}

function sendConfig(){
  var data={};
  data.aid=document.getElementById("aid").value;
  data.vpot=document.getElementById("vpot").checked;
  data.adcsum=document.getElementById("adcsum").value;
  fetch("/config",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(result) {
    if(document.getElementById('addon').innerHTML == "AddOn"){
      hideAddon();
      if(data.aid==0) document.getElementById("addon_none").style.display = "block";
      else if(data.aid==1) document.getElementById("addon_a").style.display = "block";
      else if(data.aid==2) document.getElementById("addon_b").style.display = "block";
      else if(data.aid==3) document.getElementById("addon_c").style.display = "block";
      else if(data.aid==4) document.getElementById("addon_d").style.display = "block";
    }
  }).catch (function(err){console.log(err);});
}

function sendSpdifOutMux(){
  var data={};
  data.spdifleft=document.getElementById("spdifleft").value;
  data.spdifright=document.getElementById("spdifright").value;
  fetch("/spdifout",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .catch (function(err){console.log(err);});
}

function onLoad(){
  hideAddon();
  fetch("/config").then(function(response){
    return response.json();
  }).then(function(cfg){  
    document.getElementById("fw").innerHTML="FW: "+cfg.fw;
    document.getElementById("plugin").innerHTML="Plugin: "+cfg.plugin;
    if(!(cfg.fw == cfg.plugin)) alert("Plugin does not match firmware version. Please upload an updated plugin.");
    document.getElementById("ip").innerHTML="Local WiFi IP: "+cfg.ip;
    var p=cfg.pre;
    document.getElementById("pre0").style.backgroundColor = "#101010";
    document.getElementById("pre1").style.backgroundColor = "#101010";
    document.getElementById("pre2").style.backgroundColor = "#101010";
    document.getElementById("pre3").style.backgroundColor = "#101010";
    document.getElementById("pre"+p).style.backgroundColor = "#73EC6F";
    if(cfg.vinputs == true){
      hideAddon();
      document.getElementById('addon').innerHTML = "";
    }
    else
    {
      document.getElementById('addon').innerHTML = "AddOn";
      if(cfg.aid==0) document.getElementById('addon_none').style.display = "block";
      else if(cfg.aid==1) document.getElementById('addon_a').style.display = "block";
      else if(cfg.aid==2){
        if(cfg.addcfg==0) document.getElementById("spdif_b").value="0x00";
        else if(cfg.addcfg==1) document.getElementById("spdif_b").value="0x01";
        else if(cfg.addcfg==2) document.getElementById("spdif_b").value="0x02";
        else if(cfg.addcfg==3) document.getElementById("spdif_b").value="0x03";
        else if(cfg.addcfg==4) document.getElementById("spdif_b").value="0x04";
        else if(cfg.addcfg==5) document.getElementById("spdif_b").value="0x05";
        else if(cfg.addcfg==6) document.getElementById("spdif_b").value="0x06";
        else if(cfg.addcfg==7) document.getElementById("spdif_b").value="0x07";
        document.getElementById('addon_b').style.display = "block";
      }
      else if(cfg.aid==3) document.getElementById('addon_c').style.display="block";
      else if(cfg.aid==4) document.getElementById('addon_d').style.display="block";
    }
    return fetch("/spdifout");
  }).then(function(response){
    return response.json();
  }).then(function(data){
    document.getElementById("spdifleft").value=data.spdifleft;
    document.getElementById("spdifright").value=data.spdifright;
    return fetch("/allinputs");
  }).then(function(response){return response.json();
  }).then(function(data){
    if(data.num>0)
    document.getElementById("chn0").value=data.in0;
    if(data.num>1)
    document.getElementById("chn1").value=data.in1;
    if(data.num>2)
    document.getElementById("chn2").value=data.in2;
    if(data.num>3)
    document.getElementById("chn3").value=data.in3;
    if(data.num>4)
    document.getElementById("chn4").value=data.in4;
    if(data.num>5)
    document.getElementById("chn5").value=data.in5;
    if(data.num>6)
    document.getElementById("chn6").value=data.in6;
    if(data.num>7)
    document.getElementById("chn7").value=data.in7;
    return fetch("/allbyp");
  }).then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.byp){
      if(data.byp[ii].val) document.getElementById(data.byp[ii].name).style="border-bottom-color:red;";
      else document.getElementById(data.byp[ii].name).style="";
    }
    return fetch("/allfc");
  }).then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.fc){
      document.getElementById(data.fc[ii].name).innerHTML=data.fc[ii].val;
    }
    getMVol();
    return fetch("/allnames");
  }).then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.inputs){document.getElementById("input"+ii).innerHTML=data.inputs[ii];}
    for(ii in data.outputs){document.getElementById("output"+ii).innerHTML=data.outputs[ii];}
    for(ii in data.presets){document.getElementById("pre"+ii).innerHTML=data.presets[ii];}
    if(data.sources.length > 0){
      document.getElementById("vinput").innerText = null;
      for(ii in data.sources){
        var option = document.createElement("option");
        option.value = ii;
        option.text = data.sources[ii];
        document.getElementById("vinput").appendChild(option);  
      }
      document.getElementById("vinput").value = data.selvinput;
    }
  }).catch(function(err){console.log(err);
  });
}

function switchPreset(p){
  var data={};
  data.pre=p;
  document.getElementById("msg").innerHTML="Switching preset, please wait...";
  document.getElementById("plzw").style.display="block";
  fetch("/preset",{method:"POST",headers:{
  "Content-Type": "application/json"},
  body:JSON.stringify(data)
  }).then(function(response){return fetch("/addoncfg");
  }).then(function(response){return response.json();
  }).then(function(cfg){
    if(document.getElementById("aid").value==2){
    if(cfg.addcfg==0) document.getElementById("spdif_b").value="0x00";
      else if(cfg.addcfg==1) document.getElementById("spdif_b").value="0x01";
      else if(cfg.addcfg==2) document.getElementById("spdif_b").value="0x02";
      else if(cfg.addcfg==3) document.getElementById("spdif_b").value="0x03";
      else if(cfg.addcfg==4) document.getElementById("spdif_b").value="0x04";
      else if(cfg.addcfg==5) document.getElementById("spdif_b").value="0x05";
      else if(cfg.addcfg==6) document.getElementById("spdif_b").value="0x06";
      else if(cfg.addcfg==7) document.getElementById("spdif_b").value="0x07";
    }
    return fetch("/spdifout");
  }).then(function(response){
    return response.json();
  }).then(function(data){
    document.getElementById("spdifleft").value=data.spdifleft;
    document.getElementById("spdifright").value=data.spdifright;
    return fetch("/allinputs");
  }).then(function(response){return response.json();
  }).then(function(data){
    if(data.num>0)
    document.getElementById("chn0").value=data.in0;
    if(data.num>1)
    document.getElementById("chn1").value=data.in1;
    if(data.num>2)
    document.getElementById("chn2").value=data.in2;
    if(data.num>3)
    document.getElementById("chn3").value=data.in3;
    if(data.num>4)
    document.getElementById("chn4").value=data.in4;
    if(data.num>5)
    document.getElementById("chn5").value=data.in5;
    if(data.num>6)
    document.getElementById("chn6").value=data.in6;
    if(data.num>7)
    document.getElementById("chn7").value=data.in7;
    return fetch("/allbyp");
  }).then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.byp){
      if(data.byp[ii].val) document.getElementById(data.byp[ii].name).style="border-bottom-color:red;";
      else document.getElementById(data.byp[ii].name).style="";
    }
    return fetch("/allfc");
  }).then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.fc){document.getElementById(data.fc[ii].name).innerHTML=data.fc[ii].val;}
    getMVol();
  }).then(function(response){document.getElementById("plzw").style.display="none";
  }).catch(function(error){console.log(error);});
  document.getElementById("pre0").style.backgroundColor = "#101010";
  document.getElementById("pre1").style.backgroundColor = "#101010";
  document.getElementById("pre2").style.backgroundColor = "#101010";
  document.getElementById("pre3").style.backgroundColor = "#101010";
  document.getElementById("pre"+p).style.backgroundColor = "#73EC6F";
}

function sendWifi(){
  var data={};
  data.ssid=document.getElementById("ssid").value;
  data.pwd=document.getElementById("pwd").value;
  fetch("/wifi",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(response){
    alert("Success! Your WiFi settings have been stored.");
    return response;})
  .catch(function(err){console.log(err);});
}

function sendPwdAP(){
  var data={};
  data.pwdap=document.getElementById("pwdap").value;
  data.apname=document.getElementById("apname").value;
  if((data.pwdap.length>7) || (data.pwdap.length==0)){
  fetch("/pwdap",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(response){
    alert("Success! The configuration of the access point has been stored.");
    return response;})
  .catch(function(err){console.log(err);});
  }
  else {
    alert("Please select a password with at least 8 characters.");
  }
}

function configDev(){document.getElementById("configDev").style.display = "block";getConfig();}

function configWifi(){document.getElementById("configWifi").style.display = "block";getWifiConfig();}

function getWifiConfig(){
  fetch("/wificonfig").then (function(response) {return response.json();})
  .then(function(data) {
    document.getElementById('ssid').value = data.ssid;
    document.getElementById('apname').value = data.apname;})
  .catch(function(error) {console.log(error);});
}

function hideAddon(){
  document.getElementById('addon_none').style.display = "none";
  document.getElementById('addon_a').style.display = "none";
  document.getElementById('addon_b').style.display = "none";
  //document.getElementById('addon_c').style.display = "none";
  document.getElementById('addon_d').style.display = "none";
}

function storePreset(){
  var data={};
  document.getElementById("msg").innerHTML="Storing preset, please wait...";
  document.getElementById("plzw").style.display="block";
  fetch("/store",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(response){
    alert("Success! Your preset has been stored.");
    return response;})
  .then(function(response){document.getElementById("plzw").style.display="none";})
  .catch(function(err){console.log(err);});
}

function changeSPDIF(id){
  var data={};
  data.len=3;
  data.i2c=["0x82", "0x01", document.getElementById(id).value];
  fetch("/addoncfg",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)});
}

function closeModal(id){
  document.getElementById(id).style.display = "none";
  if(id == 'peqbank') {
    while(document.getElementById('peqbank-userinput').children.length > 0)
      document.getElementById('peqbank-userinput').children[0].remove();
      document.getElementById('peqbank-dialog-content').style.width = '300px';
  }
  fetch("/allbyp")
  .then(function(response){
    return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.byp){
      if(data.byp[ii].val) document.getElementById(data.byp[ii].name).style="border-bottom-color:red;";
      else document.getElementById(data.byp[ii].name).style="";
    }
    return fetch("/allfc");
  }).then(function(response){return response.text();
  }).then(function(response){
    var data = JSON.parse(response);
    for(ii in data.fc){document.getElementById(data.fc[ii].name).innerHTML=data.fc[ii].val;}
  }).catch(function(err){console.log(err);});
}

function switchMute(){
  if(document.getElementById("mute").dataset.mute=="1"){
    document.getElementById("mute").style.backgroundColor="#FF0000";
    document.getElementById("mute").style.borderColor="#FF0000";
    document.getElementById("mute").style.color="#101010";
  }else{
    document.getElementById("mute").style.backgroundColor = "#101010";
    document.getElementById("mute").style.borderColor="#808080";
    document.getElementById("mute").style.color="#D0D0D0";
  }
}

function bypass(id){
  if(document.getElementById(id).dataset.bypass=="0")
    document.getElementById(id).dataset.bypass="1";
  else
    document.getElementById(id).dataset.bypass="0";
  switchBypass(id);
}

function switchBypass(id){
  if(document.getElementById(id).dataset.bypass=="1"){
    document.getElementById(id).style.backgroundColor="#FF0000";
    document.getElementById(id).style.borderColor="#FF0000";
    document.getElementById(id).style.color="#101010";
  }else{
    document.getElementById(id).style.backgroundColor = "#101010";
    document.getElementById(id).style.borderColor="#808080";
    document.getElementById(id).style.color="#D0D0D0";
  }
}

function postMVol(){
  var data={};
  data.vol=document.getElementById("mvol").value;
  fetch("/mvol",{method:"POST",headers:{
  "Content-Type": "application/json"},
  body:JSON.stringify(data)}).catch(function(error){console.log(error);});
}

function sendParam(btp){postJson(btp).catch(function(error){console.log(error);});}

function mute(){
  if(document.getElementById("mute").dataset.mute=="0")
    document.getElementById("mute").dataset.mute="1";
  else
    document.getElementById("mute").dataset.mute="0";
  switchMute();
  sendParam("gain");
}

function readFirFile(file){
  return new Promise((resolve, reject) => {
  var reader=new FileReader();
  reader.onload = function found(){resolve(reader.result);}
  reader.readAsText(file);
  })
}

function openHP(idx){
  document.getElementById("highPass").style.display = "block";
  fetch("/hp?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("highPass").dataset.idx=idx;
    document.getElementById("hp_fc").value=data.fc;
    document.getElementById("hp_typ").value=data.typ;
    document.getElementById("hp_bypass").dataset.bypass=data.bypass;
    switchBypass("hp_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openLShelv(idx){
  document.getElementById("lowShelv").style.display = "block";
  fetch("/lshelv?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("lowShelv").dataset.idx=idx;
    document.getElementById("ls_v").value=data.gain;
    document.getElementById("ls_fc").value=data.fc;
    document.getElementById("ls_s").value=data.slope;
    document.getElementById("ls_bypass").dataset.bypass=data.bypass;
    switchBypass("ls_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openPEQ(idx){
  document.getElementById("peq").style.display = "block";
  fetch("/peq?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data){
    document.getElementById("peq").dataset.idx=idx;
    document.getElementById("peq_v").value=data.gain;
    document.getElementById("peq_fc").value=data.fc;
    document.getElementById("peq_q").value=data.Q;
    document.getElementById("peq_bypass").dataset.bypass=data.bypass;
    switchBypass("peq_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openPeqBank(idx,len){
  fetch("/peqbank?idx="+idx).then (function (response) {
    return response.json();
  }).then (function(data) {
    document.getElementById('peqbank-dialog-content').style.width = 200 * data["fc"].length + 'px';
    document.getElementById('peqbank-dialog-content').style.maxWidth = '95%';
    var userinput = document.getElementById('peqbank-userinput');
    userinput.dataset.numbands = data["fc"].length;

    var startidx = 0;
    for(var mm = 0; mm < 2; mm++) {
      var tr = document.createElement('tr');

      ii = startidx;
      for(var nn = 0; nn < 5 && ii < data["fc"].length; nn++) {
        var td = document.createElement('td');
        td.innerHTML = ii + 1;
        ii++;
        td.colSpan = 3;
        tr.appendChild(td);
      }
      userinput.appendChild(tr);
      tr = document.createElement('tr');
      ii = startidx;
      for(var nn = 0; nn < 5 && ii < data["fc"].length; nn++) {
        var td = document.createElement('td');
        td.style.textAlign = 'right';
        td.style.width = '20px';
        td.innerHTML = 'fc';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.maxWidth = '120px';
        td.innerHTML = '<input type="number" id="peq_fc_' + ii + '" style="width:90%;" value="' + data["fc"][ii] + '" step="any" min="0" max="24000">';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.textAlign = 'left';
        td.style.width = '20px';
        td.innerHTML = 'Hz';
        tr.appendChild(td);
        ii++;
      }
      userinput.appendChild(tr);
      tr = document.createElement('tr');
      ii = startidx;
      for(var nn = 0; nn < 5 && ii < data["Q"].length; nn++) {
        var td = document.createElement('td');
        td.style.textAlign = 'right';
        td.style.width = '20px';
        td.id = "label_"+ii;
        td.innerHTML = 'Q';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.maxWidth = '120px';
        td.innerHTML = '<input type="number" id="peq_q_' + ii + '" style="width:90%;" value="' + data["Q"][ii] + '" step="any" min="0.1" max="100">';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.textAlign = 'left';
        td.style.width = '20px';
        td.innerHTML = '';
        tr.appendChild(td);
        ii++;
      }
      userinput.appendChild(tr);
      tr = document.createElement('tr');
      ii = startidx;
      for(var nn = 0; nn < 5 && ii < data["V0"].length; nn++) {
        var td = document.createElement('td');
        td.style.textAlign = 'right';
        td.style.width = '20px';
        td.innerHTML = 'V0';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.maxWidth = '120px';
        td.innerHTML = '<input type="number" id="peq_v0_' + ii + '" style="width:90%;" value="' + data["V0"][ii] + '" step="any" min="-100" max="100">';
        tr.appendChild(td);
        td = document.createElement('td');
        td.style.textAlign = 'left';
        td.style.width = '20px';
        td.innerHTML = 'dB';
        tr.appendChild(td);
        ii++;
      }
      userinput.appendChild(tr);
      tr = document.createElement('tr');
      ii = startidx;
      for(var nn = 0; nn < 5 && ii < data["bypass"].length; nn++) {
        var td = document.createElement('td');
        tr.appendChild(td);
        td = document.createElement('td');
        td.innerHTML = "<button class=\"send\" id='peq_bypass_" + ii + "' onclick=\"bypass('peq_bypass_" + ii + "')\" data-bypass=\"0\">Bypass</button>";
        tr.appendChild(td);
        td = document.createElement('td');
        tr.appendChild(td);
        ii++;
        startidx = ii;
      }
      userinput.appendChild(tr);
    }
    for(var ii = 0; ii < data["bypass"].length; ii++) {
      document.getElementById("peq_bypass_" + ii).dataset.bypass=data["bypass"][ii];
      switchBypass("peq_bypass_" + ii);
    }
    document.getElementById('peqbank-send').onclick = function(){setPeqBank(idx)};
    document.getElementById('peqbank-dialog-content').className = 'modal-content d_peq';
    document.getElementById('peqbank-title').innerHTML = 'Parametric EQ';
    document.getElementById('peqbank').style.display = 'block';
  }).catch (function (error){console.log(error);});
}


function setPeqBank(idx){
  var data = {};
  data.idx = idx;
  data.fc = [];
  data.Q = [];
  data.V0 = [];
  data.bypass = [];

  var numbands = document.getElementById('peqbank-userinput').dataset.numbands;
  for(var ii = 0; ii < numbands; ii++) {
    data.fc.push(parseFloat(document.getElementById('peq_fc_' + ii).value));
    data.Q.push(parseFloat(document.getElementById('peq_q_' + ii).value));
    data.V0.push(parseFloat(document.getElementById('peq_v0_' + ii).value));
    data.bypass.push(document.getElementById('peq_bypass_' + ii).dataset.bypass);
  }
  data.numbands = numbands;
  fetch("/peqbank",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .catch(function(err){console.log(err);});
}

function openHShelv(idx){
  document.getElementById("highShelv").style.display = "block";
  fetch("/hshelv?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("highShelv").dataset.idx=idx;
    document.getElementById("hs_v").value=data.gain;
    document.getElementById("hs_fc").value=data.fc;
    document.getElementById("hs_s").value=data.slope;
    document.getElementById("hs_bypass").dataset.bypass=data.bypass;
    switchBypass("hs_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openLP(idx){
  document.getElementById("lowPass").style.display = "block";
  fetch("/lp?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("lowPass").dataset.idx=idx;
    document.getElementById("lp_fc").value=data.fc;
    document.getElementById("lp_typ").value=data.typ;
    document.getElementById("lp_bypass").dataset.bypass=data.bypass;
    switchBypass("lp_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openPhase(idx){
  document.getElementById("phase").style.display = "block";
  fetch("/phase?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {  
    document.getElementById("phase").dataset.idx=idx;
    document.getElementById("ph_fc").value=data.fc;
    document.getElementById("ph_q").value=data.Q;
    if(data.inv==1) document.getElementById("ph_inv").checked=true;
    else document.getElementById("ph_inv").checked=false;
    document.getElementById("ph_bypass").dataset.bypass=data.bypass;
    switchBypass("ph_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openDelay(idx){
  document.getElementById("delay").style.display = "block";
  fetch("/delay?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {  
    document.getElementById("delay").dataset.idx=idx;
    document.getElementById("delayval").value=data.dly;
    document.getElementById("delay_bypass").dataset.bypass=data.bypass;
    switchBypass("delay_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openGain(idx){
  document.getElementById("gain").style.display = "block";
  fetch("/gain?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {  
    document.getElementById("gain").dataset.idx=idx;
    document.getElementById("gainval").value=data.gain;
    document.getElementById("mute").dataset.mute=data.mute;
    switchMute();
  }).catch (function (error){console.log(error);
  });
}

function openXO(idx){
  document.getElementById("crossOver").style.display = "block";
  fetch("/xo?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("crossOver").dataset.idx=idx;
    document.getElementById("xo_lp_fc").value=data.lp_fc;
    document.getElementById("xo_lp_typ").value=data.lp_typ;
    document.getElementById("xo_lp_bypass").dataset.bypass=data.lp_bypass;
    switchBypass("xo_lp_bypass");
    document.getElementById("xo_hp_fc").value=data.hp_fc;
    document.getElementById("xo_hp_typ").value=data.hp_typ;
    document.getElementById("xo_hp_bypass").dataset.bypass=data.hp_bypass;
    switchBypass("xo_hp_bypass");
  }).catch (function (error){console.log(error);
  });
}

function openFIR(idx){
  document.getElementById("fir").style.display = "block";
  document.getElementById('irfile').value="";
  fetch("/fir?idx="+idx).then (function (response) {
    return response.json();
  }).then (function (data) {
    document.getElementById("fir").dataset.idx=idx;
    document.getElementById("fir_bypass").dataset.bypass=data.bypass;
    switchBypass("fir_bypass");
  }).catch (function (error){console.log(error);
  });
}

function getMVol(){
  fetch("/mvol").then (function (response) {return response.json();})
  .then(function (data){  
    document.getElementById("mvol").value=data.vol;
  }).catch (function (error) {console.log(error);
  });
}

function getPreset(){
  fetch("/preset").then (function (response) {
    return response.json();
  }).then (function (data) {  
    switchPreset(data.pre);
  }).catch (function (error) {console.log(error);
  });
}

function postInputJson(id,idx){
  var data={};
  var elem = document.getElementById(id);
  var selected = elem.options[elem.selectedIndex];
  data.idx=idx;
  data.sel=document.getElementById(id).value;
  fetch("/input",{method:"POST",headers:{
  "Content-Type": "application/json"},
  body:JSON.stringify(data)}).catch(function(error){console.log(error);});
}

function postJson(btp){
  var data={};
  if(btp=="hp"){
    data.idx=document.getElementById("highPass").dataset.idx;
    data.fc=document.getElementById("hp_fc").value;
    data.typ=document.getElementById("hp_typ").value;
    data.bypass=document.getElementById("hp_bypass").dataset.bypass;
    return fetch("/hp",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="lshelv"){
    data.idx=document.getElementById("lowShelv").dataset.idx;
    data.gain=document.getElementById("ls_v").value;
    data.fc=document.getElementById("ls_fc").value;
    data.slope=document.getElementById("ls_s").value;
    data.bypass=document.getElementById("ls_bypass").dataset.bypass;
    return fetch("/lshelv",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="peq"){
    data.idx=document.getElementById("peq").dataset.idx;
    data.gain=document.getElementById("peq_v").value;
    data.fc=document.getElementById("peq_fc").value;
    data.Q=document.getElementById("peq_q").value;
    data.bypass=document.getElementById("peq_bypass").dataset.bypass;
    return fetch("/peq",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="hshelv"){
    data.idx=document.getElementById("highShelv").dataset.idx;
    data.gain=document.getElementById("hs_v").value;
    data.fc=document.getElementById("hs_fc").value;
    data.slope=document.getElementById("hs_s").value;
    data.bypass=document.getElementById("hs_bypass").dataset.bypass;
    return fetch("/hshelv",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="lp"){
    data.idx=document.getElementById("lowPass").dataset.idx;
    data.fc=document.getElementById("lp_fc").value;
    data.typ=document.getElementById("lp_typ").value;
    data.bypass=document.getElementById("lp_bypass").dataset.bypass;
    return fetch("/lp",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="phase"){
    data.idx=document.getElementById("phase").dataset.idx;
    data.fc=document.getElementById("ph_fc").value;
    data.Q=document.getElementById("ph_q").value;
    data.inv=document.getElementById("ph_inv").checked;
    data.bypass=document.getElementById("ph_bypass").dataset.bypass;
    return fetch("/phase",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="delay"){
    data.idx=document.getElementById("delay").dataset.idx;
    data.delay=document.getElementById("delayval").value;
    data.bypass=document.getElementById("delay_bypass").dataset.bypass;
    return fetch("/delay",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="gain"){
    data.idx=document.getElementById("gain").dataset.idx;
    data.gain=document.getElementById("gainval").value;
    data.mute=document.getElementById("mute").dataset.mute;
    return fetch("/gain",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="xo"){
    data.idx=document.getElementById("crossOver").dataset.idx;
    data.lp_fc=document.getElementById("xo_lp_fc").value;
    data.lp_typ=document.getElementById("xo_lp_typ").value;
    data.lp_bypass=document.getElementById("xo_lp_bypass").dataset.bypass;
    data.hp_fc=document.getElementById("xo_hp_fc").value;
    data.hp_typ=document.getElementById("xo_hp_typ").value;
    data.hp_bypass=document.getElementById("xo_hp_bypass").dataset.bypass;
    return fetch("/xo",{method:"POST",headers:{
    "Content-Type": "application/json"},
    body:JSON.stringify(data)});
  }
  else if(btp=="fir"){
    var idx=document.getElementById("fir").dataset.idx;
    var bypass=document.getElementById("fir_bypass").dataset.bypass;
    var taps = new Float32Array(20000);
    for(var k=0;k<20000;k++) taps[k]=0;
    document.getElementById("msg").innerHTML="Updating FIRs, please wait...";
    document.getElementById("plzw").style.display="block";
    if(document.getElementById("irfile").files.length>0){
      return new Promise((resolve, reject) => {
        var file=document.getElementById('irfile').files[0];
        readFirFile(file).then(function(result){
          var lines = result.split('\n');
          for(var ll=0; ll<lines.length; ll++){
            if(ll<20000){
              val = parseFloat(lines[ll]);
              if(!isNaN(val)){taps[ll]=val;}
            }
          }
        }).then(function(response){
          var fir = new Blob([taps], {type:'application/octet-binary'});
          return fetch("/fir?idx="+idx+"&bypass="+bypass,{method:'POST',headers:{},body:fir});
        }).then(function(response){
          document.getElementById("plzw").style.display = "none";
          resolve(response);
        });
      });
    }
    else
    {
      return new Promise((resolve, reject) => {
        taps[0]=1;
        var fir = new Blob([taps], {type:'application/octet-binary'});
        return fetch("/fir?idx="+idx+"&bypass="+bypass,{method:'POST',headers:{},body:fir});
      }).then(function(response){
        document.getElementById("plzw").style.display = "none";
        resolve(response);
      });
    }
  }
  else if(btp=="firbypass"){
    document.getElementById("plzw").style.display="block";
    data.idx=document.getElementById("fir").dataset.idx;
    data.bypass=document.getElementById("fir_bypass").dataset.bypass;

    return fetch("/firbypass",{method:"POST",headers:{
      "Content-Type": "application/json"},
      body:JSON.stringify(data)
    }).then(function(response){
      document.getElementById("plzw").style.display = "none";
    });
  }
}

function openPlugin(){document.getElementById("pluginupload").style.display = "block";}

function onStoreNames() {
  var data = {};
  data.inputs = [];
  data.outputs = [];
  data.presets = [];
  var numchannels = document.getElementById('audioinputs').dataset.numchannels;
  for(var ii = 0; ii < numchannels; ii++)
    data.inputs.push(document.getElementById('input' + ii).value);
  numchannels = document.getElementById('audiooutputs').dataset.numchannels;
  for(var ii = 0; ii < numchannels; ii++)
    data.outputs.push(document.getElementById('output' + ii).value);
  var numpresets = document.getElementById('presets').dataset.numpresets;
  for(var ii = 0; ii < numpresets; ii++)
    data.presets.push(document.getElementById('preset' + ii).value);
   
  fetch("/chnames",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
    .then(function(){window.location.href='/'})
    .catch(function(error){console.log(error);});
}

function onLoadInputRouting() {
  fetch("/inputrouting").then(function(response) {
    return response.json();
  }).then(function (data) {  
    var tbl = document.getElementById('inputrouting');
    tbl.dataset.numsources = data["numSourceNames"];
    tbl.dataset.numvirtualinputs = data["numInputs"];
    var id = 0;
    for(var mm = 0; mm < data["numSourceNames"]; mm++) {
      var tr = document.createElement('tr');
      var td = document.createElement('td');
      td.style.textAlign = 'left';
      var input = document.createElement("input");
      input.setAttribute('type', 'text');
      input.value = data["sourceNames"][mm];
      input.id = 'name_'+mm;
      td.appendChild(input);
      tr.appendChild(td);
      for(var nn = 0; nn < data["numInputs"]; nn++) {
        var td = document.createElement('td');
        td.style = 'min-width:80px';
        var sel = document.createElement('select');
        sel.id = 'sel_'+mm+'_'+nn;
        for(var ii = 0; ii < data["options"].length; ii++) {
          var opt = document.createElement('option');
          opt.value = ii;
          opt.text = data["options"][ii];
          sel.appendChild(opt);
        }
        sel.value = data["select"][mm][nn];
        id++;
        td.appendChild(sel);
        tr.appendChild(td);
      }
      tbl.appendChild(tr);
    }
  }).catch (function (error) {console.log(error);
  });
}

function onStoreInputRouting(){
  var data = {};
  var numSources = document.getElementById('inputrouting').dataset.numsources;
  var numVirtualInputs = document.getElementById('inputrouting').dataset.numvirtualinputs;
  data.select = [];
  data.sourceNames = [];
  for(var mm = 0; mm < numSources; mm++){
    data.sourceNames[mm] = document.getElementById('name_'+mm).value;
    data.select[mm] = [];
  }
  for(var mm = 0; mm < numSources; mm++){
    for(var nn = 0; nn < numVirtualInputs; nn++) data.select[mm][nn] = document.getElementById('sel_'+mm+'_'+nn).value;
  }
  fetch("/inputrouting",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(){window.location.href='/'})
  .catch(function(error){console.log(error);});
}

function selectVirtualInput(){
  var data = {};
  data.sel = document.getElementById('vinput').value;
  fetch("/vinput",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .catch(function(error){console.log(error);});
}
