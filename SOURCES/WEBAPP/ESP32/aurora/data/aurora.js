
function getConfig(){
  fetch("/config").then (function (response) {
    return response.json();
  }).then (function (data) {  
    document.getElementById("aid").value = data.aid;
    if(data.vpot==1) document.getElementById("vpot").checked=true;
    else document.getElementById("vpot").checked=false;
    document.getElementById("adcsum").value=data.adcsum;
    document.getElementById("spdifleft").value=data.spdifleft;
    document.getElementById("spdifright").value=data.spdifright;
    console.log(data);
  }).catch (function (error) {console.log(error);
  });
}

function sendConfig(){
  var data={};
  data.aid=document.getElementById("aid").value;
  data.vpot=document.getElementById("vpot").checked;
  data.adcsum=document.getElementById("adcsum").value;
  data.spdifleft=document.getElementById("spdifleft").value;
  data.spdifright=document.getElementById("spdifright").value;
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