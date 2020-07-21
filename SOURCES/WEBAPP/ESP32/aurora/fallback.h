const char fallback_html[] = "<!DOCTYPE html>"
R"!^!(
<html>
<head>
<title>AURORA DSP</title>
</head>
<body>
<center>
<h1>Aurora DSP</h1>

<div id="plugin">
  <div>
    <table class="ptbl">
    <tr><td colspan="2" style="height:20px;padding-top:10px;">
    <table style="width:100%;">
    <tr><td class="headline">Upload Plugin</td></tr>
    </table>
    </td></tr>
    <tr><td>Please select the folder of the plugin.</td></tr>
    <tr><td><input type="file" id="picker" name="fileList" webkitdirectory mozdirectory multiple width="95%"></td></tr>
    <tr><td><div id="wait" style="display:none;">Please wait while uploading.</div></td></tr>
    <tr><td><div id="prg" style="border: 1px solid #73EC6F; background: #73EC6F; height:2px; width:0%;"></div></td></tr>
    </table>
  </div>
</div>

</center>

<script>
  let picker = document.getElementById('picker');
  picker.addEventListener('change', e => {
    var html,fw,css,plugin,aurorajs;
    for(let file of Array.from(e.target.files)){
      if(file.name=="dark.css")
        css = file;
      if(file.name=="dsp.fw")
        fw = file;
      if(file.name=="dsp.html")
        html = file;
      if(file.name=="plugin.ini")
        plugin = file;
      if(file.name=="aurora.jgz")
        aurorajs = file;
    }
    var prg=document.getElementById('prg');
		prg.style.width="5%";
    document.getElementById("wait").style.display="block";

    fetch("/upload?fname=dark.css",{method:'POST',headers:{},body:css})
    .then(function(response){
      prg.style.width="20%";
      return fetch("/upload?fname=dsp.fw",{method:'POST',headers:{},body:fw});})
    .then(function(response){
      prg.style.width="40%";
      return fetch("/upload?fname=dsp.html",{method:'POST',headers:{},body:html});})
    .then(function(response){
      prg.style.width="60%";
      return fetch("/upload?fname=plugin.ini",{method:'POST',headers:{},body:plugin});})
    .then(function(response){
      prg.style.width="80%";
      return fetch("/upload?fname=aurora.jgz",{method:'POST',headers:{},body:aurorajs});})
    .then(function(response){
      prg.style.width="100%";
      return response;})
    .then(function(response){
      alert("Success! Your plugin has been installed. Please reboot your DSP and reconnect to it.");
      document.getElementById("wait").style.display="none";
      return response;})
    .catch(function(err){alert( "Uploading your plugin failed: "+err);});
  });
</script>
</body>
</html>
)!^!";