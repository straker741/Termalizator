#ifndef _CONSTANTS_CPP_
#define _CONSTANTS_CPP_

#include <Arduino.h>

const char INDEX[] PROGMEM = "\
<!DOCTYPE html>\
<html>\
<head>\
<meta charset='utf-8'>\
<title>Termalizator</title>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<link rel='stylesheet' type='text/css' media='screen' href='main.css'>\
<script src='main.js'></script>\
</head>\
<body>\
<section class=\"page\">\
<h1>Termalizator</h1>\
<div class=\"tm-input with-border\">\
<label for=\"target\">&#x1F3AF;🌡️</label>\
<input type=\"text\" id=\"target\" name=\"target\" placeholder=\"50.125\" data-valid=\"true\" />\
<span>&#x274C;</span>\
</div>\
</section>\
<section class=\"page-divider\">\
<div class=\"page\">\
<div class=\"flex-group\">\
<span id=\"options\" class=\"tm-action-icon\" data-state=\"0\">\
<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 512 512\">\
<path d=\"M487.4 315.7l-42.6-24.6c4.3-23.2 4.3-47 0-70.2l42.6-24.6c4.9-2.8 7.1-8.6 5.5-14-11.1-35.6-30-67.8-54.7-94.6-3.8-4.1-10-5.1-14.8-2.3L380.8 110c-17.9-15.4-38.5-27.3-60.8-35.1V25.8c0-5.6-3.9-10.5-9.4-11.7-36.7-8.2-74.3-7.8-109.2 0-5.5 1.2-9.4 6.1-9.4 11.7V75c-22.2 7.9-42.8 19.8-60.8 35.1L88.7 85.5c-4.9-2.8-11-1.9-14.8 2.3-24.7 26.7-43.6 58.9-54.7 94.6-1.7 5.4.6 11.2 5.5 14L67.3 221c-4.3 23.2-4.3 47 0 70.2l-42.6 24.6c-4.9 2.8-7.1 8.6-5.5 14 11.1 35.6 30 67.8 54.7 94.6 3.8 4.1 10 5.1 14.8 2.3l42.6-24.6c17.9 15.4 38.5 27.3 60.8 35.1v49.2c0 5.6 3.9 10.5 9.4 11.7 36.7 8.2 74.3 7.8 109.2 0 5.5-1.2 9.4-6.1 9.4-11.7v-49.2c22.2-7.9 42.8-19.8 60.8-35.1l42.6 24.6c4.9 2.8 11 1.9 14.8-2.3 24.7-26.7 43.6-58.9 54.7-94.6 1.5-5.5-.7-11.3-5.6-14.1zM256 336c-44.1 0-80-35.9-80-80s35.9-80 80-80 80 35.9 80 80-35.9 80-80 80z\"/>\
</svg>\
</span>\
<span id=\"power\" class=\"tm-action-icon\" data-state=\"2\">\
<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 512 512\">\
<path d=\"M400 54.1c63 45 104 118.6 104 201.9 0 136.8-110.8 247.7-247.5 248C120 504.3 8.2 393 8 256.4 7.9 173.1 48.9 99.3 111.8 54.2c11.7-8.3 28-4.8 35 7.7L162.6 90c5.9 10.5 3.1 23.8-6.6 31-41.5 30.8-68 79.6-68 134.9-.1 92.3 74.5 168.1 168 168.1 91.6 0 168.6-74.2 168-169.1-.3-51.8-24.7-101.8-68.1-134-9.7-7.2-12.4-20.5-6.5-30.9l15.8-28.1c7-12.4 23.2-16.1 34.8-7.8zM296 264V24c0-13.3-10.7-24-24-24h-32c-13.3 0-24 10.7-24 24v240c0 13.3 10.7 24 24 24h32c13.3 0 24-10.7 24-24z\"></path>\
</svg>\
</span>\
</div>\
</div>\
</section>\
<section id=\"output\" class=\"page\" data-display=\"false\">\
<p>🌡️ <span id=\"temp\">00.000</span> &deg;C</p>\
<p>&#x23F0; <span id=\"time\">00:00:00</span></p>\
</section>\
</body>\
</html>\
";

const char CSS[] PROGMEM = "\
* {font-family: sans-serif;font-size: 32px;text-align: center;-webkit-box-sizing: border-box;box-sizing: border-box;overflow: hidden;color: #cacaca;background-color: #1e1e1e;-webkit-transition: all 0.25s;transition: all 0.25s;}\
body {padding: 0;margin: 0;}\
section {margin-bottom: 1em;}\
.page {width: 95%;max-width: 512px;margin-left: auto;margin-right: auto;}\
.page-divider {width: 100%;padding: 0.5em;background-color: #ffc840;}\
.page-divider * {background-color: #ffc840;}\
.with-border {border: 2px solid #ffc840;border-radius: 1em;}\
.flex-group {display: -webkit-box;display: -ms-flexbox;display: flex;-webkit-box-pack: space-evenly;-ms-flex-pack: space-evenly;justify-content: space-evenly;}\
.tm-input {display: -ms-grid;display: grid;-ms-grid-columns: 100px auto auto;grid-template-columns: 100px auto auto;}\
.tm-input > * {padding: 0.25em;}\
.tm-input label {background-color: #ffc840;}\
.tm-input input {width: 100%;border: none;outline: none;text-align: left;}\
@media(hover: hover) and (pointer: fine) {.tm-input input:hover, .tm-input input:focus {color: white;}}\
.tm-input > input[data-valid=\"true\"] + span {display: none;}\
.tm-input > input[data-valid=\"false\"] + span {display: block;}\
.tm-action-icon {height: 2em;width: 2em;cursor: pointer;border-radius: 1em;background-color: #1e1e1e;}\
.tm-action-icon > * {height: 100%;padding: 0.25em;background-color: inherit;}\
.tm-action-icon[data-state=\"2\"] > * {fill: #ffc840;}\
.tm-action-icon[data-state=\"1\"] > * {fill: #4caf50;}\
.tm-action-icon[data-state=\"0\"] > * {fill: #f44336;}\
@media(hover: hover) and (pointer: fine) {.tm-action-icon:hover > *,.tm-action-icon:focus > * {fill: #ffc840;}}\
[data-display=\"true\"] {display: block;}\
[data-display=\"false\"] {display: none;}\
";

const char JS[] PROGMEM = "\
window.onload = () => {\
document.getElementById(\"target\").addEventListener(\"input\", validateTarget, false);\
document.getElementById(\"target\").addEventListener(\"blur\", validateTarget, false);\
document.getElementById(\"target\").addEventListener(\"change\", () => {\
if (validateTarget()) {\
setTarget();\
}\
}, false);\
document.getElementById(\"power\").addEventListener(\"click\", setPower, false);\
setInterval(() => getData(), 1000);\
};\
function validateTarget() {\
var E_target = document.getElementById(\"target\");\
if(isNaN(E_target.value) || E_target.value === \"\") {\
E_target.setAttribute(\"data-valid\", \"false\");\
return false;\
}\
else {\
E_target.setAttribute(\"data-valid\", \"true\");\
return true;\
}\
}\
function setPower() {\
var E_power = document.getElementById(\"power\");\
var state = E_power.getAttribute(\"data-state\") === \"0\" ? \"1\" : \"0\";\
E_power.setAttribute(\"data-state\", \"2\");\
fetch(`/api/config?power=${state}`).then((response) => {\
if (response.ok) {\
E_power.setAttribute(\"data-state\", state);\
}\
else {\
E_power.setAttribute(\"data-state\", \"0\");\
}\
}).catch((e) => {\
console.log(e);\
E_power.setAttribute(\"data-state\", \"0\");\
});\
}\
function setTarget() {\
var E_target = document.getElementById(\"target\");\
var value = E_target.value === \"\" ? \"0.0\" : E_target.value;\
fetch(`/api/config?target=${value}`).catch((e) => {\
console.log(e);\
});\
}\
function getData() {\
var E_power = document.getElementById(\"power\");\
var E_temp = document.getElementById(\"temp\");\
var E_time = document.getElementById(\"time\");\
var E_output = document.getElementById(\"output\");\
fetch(\"/api/data\").then((response) => {\
return response.json();\
}).then((data) => {\
console.log(data);\
var {power, temp, time} = data;\
E_power.setAttribute(\"data-state\", power);\
E_temp.innerHTML = temp;\
E_time.innerHTML = new Date(time * 1000).toISOString().substr(11, 8);\
if (E_power.getAttribute(\"data-state\") === \"1\") {\
E_output.setAttribute(\"data-display\", \"true\");\
}\
else {\
E_output.setAttribute(\"data-display\", \"false\");\
}\
}).catch((e) => {\
console.log(e);\
});\
}";


#endif