const char webota_html[] = "<!DOCTYPE html>"
R"!^!(
<html>
<head>
<title>AURORA DSP</title>
</head>
<body>
<center>
<h1>Aurora DSP Firmware Update</h1>

<div id="plugin">
  <div>
    <table class="ptbl">
    <tr><td>Please select the new firmware.</td></tr>
    <tr><td><input type="file" id="picker" name="fileList" width="95%"></td></tr>
    <tr><td><div id="wait" style="display:none;">Please wait while uploading.</div></td></tr>
    </table>
  </div>
</div>

</center>

<script>
  let picker = document.getElementById('picker');
  picker.addEventListener('change', e => {

    var files = e.target.files;
    var fw = files[0];

    document.getElementById("wait").style.display="block";

    fetch("/update",{method:'POST',headers:{},body:fw})
    .then(function(response){
      alert("Success! Your firmware has been updated. Please reboot your DSP and reconnect to it.");
      document.getElementById("wait").style.display="none";
      return response;})
    .catch(function(err){alert( "Updateing your firmware failed: "+err);});
  });
</script>
</body>
</html>
)!^!";