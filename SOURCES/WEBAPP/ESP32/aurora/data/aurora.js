
function getConfig(){
  fetch("/config").then (function (response) {
    return response.json();
  }).then (function (data) {  
    document.getElementById("aid").value = data.aid;
    if(data.vpot==1) document.getElementById("vpot").checked=true;
    else document.getElementById("vpot").checked=false;
    document.getElementById("adcsum").value=data.adcsum;
  }).catch (function (error) {console.log(error);});
}

function sendConfig(){
  var data={};
  data.aid=document.getElementById("aid").value;
  data.vpot=document.getElementById("vpot").checked;
  data.adcsum=document.getElementById("adcsum").value;
  fetch("/config",{method:"POST",headers:{"Content-Type": "application/json"},body:JSON.stringify(data)})
  .then(function(result) {
  hideAddon();
  if(data.aid==0) document.getElementById("addon_none").style.display = "block";
  else if(data.aid==1) document.getElementById("addon_a").style.display = "block";
  else if(data.aid==2) document.getElementById("addon_b").style.display = "block";
  else if(data.aid==3) document.getElementById("addon_c").style.display = "block";
  else if(data.aid==4) document.getElementById("addon_d").style.display = "block";
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
    document.getElementById("ip").innerHTML="Local WiFi IP: "+cfg.ip;
    var p=cfg.pre;
    document.getElementById("pre0").style.backgroundColor = "#101010";
    document.getElementById("pre1").style.backgroundColor = "#101010";
    document.getElementById("pre2").style.backgroundColor = "#101010";
    document.getElementById("pre3").style.backgroundColor = "#101010";
    document.getElementById("pre"+p).style.backgroundColor = "#73EC6F";
    if(cfg.aid==0) document.getElementById('addon_none').style.display = "block";
    else if(cfg.aid==1) document.getElementById('addon_a').style.display = "block";
    else if(cfg.aid==2)
    {
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
    return fetch("/spdifout");
  }).then(function(response){
    return response.json();
  }).then(function(data){
    document.getElementById("spdifleft").value=data.spdifleft;
    document.getElementById("spdifright").value=data.spdifright;
    return fetch("/allinputs");
  }).then(function(response){
    return response.json();
  }).then(function(data){
    document.getElementById("chn0").value=data.in0;
    document.getElementById("chn1").value=data.in1;
    document.getElementById("chn2").value=data.in2;
    document.getElementById("chn3").value=data.in3;
    document.getElementById("chn4").value=data.in4;
    document.getElementById("chn5").value=data.in5;
    document.getElementById("chn6").value=data.in6;
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
  }).catch(function(err){console.log(err);
  });
}