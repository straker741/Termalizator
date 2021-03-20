window.onload = () => {
    document.getElementById("target").addEventListener("input", validateTarget, false);
    document.getElementById("target").addEventListener("blur", validateTarget, false);
    document.getElementById("target").addEventListener("change", () => {
        if (validateTarget()) {
            setTarget();
        }
    }, false);
    document.getElementById("power").addEventListener("click", setPower, false);

    setInterval(() => getData(), 1000);
};

function validateTarget() {
    var E_target = document.getElementById("target");
    if(isNaN(E_target.value) || E_target.value === "") {
        E_target.setAttribute("data-valid", "false");
        return false;
    }
    else {
        E_target.setAttribute("data-valid", "true");
        return true;
    }
}

function setPower() {
    var E_power = document.getElementById("power");
    var state = E_power.getAttribute("data-state") === "0" ? "1" : "0";
    E_power.setAttribute("data-state", "2");
    fetch(`/api/config?power=${state}`).then((response) => {
        if (response.ok) {
            E_power.setAttribute("data-state", state);
        }
        else {
            E_power.setAttribute("data-state", "0");
        }
    }).catch((e) => {
        console.log(e);
        E_power.setAttribute("data-state", "0");
    });
}

function setTarget() {
    var E_target = document.getElementById("target");
    var value = E_target.value === "" ? "0.0" : E_target.value;

    fetch(`/api/config?target=${value}`).catch((e) => {
        console.log(e);
    });
}

function getData() {
    var E_power = document.getElementById("power");
    var E_temp = document.getElementById("temp");
    var E_time = document.getElementById("time");
    var E_output = document.getElementById("output");

    fetch("/api/data").then((response) => {
        return response.json();
    }).then((data) => {
        console.log(data);
        var {power, temp, time} = data;
        E_power.setAttribute("data-state", power);
        E_temp.innerHTML = temp;
        E_time.innerHTML = new Date(time * 1000).toISOString().substr(11, 8);
        if (E_power.getAttribute("data-state") === "1") {
            E_output.setAttribute("data-display", "true");
        }
        else {
            E_output.setAttribute("data-display", "false");
        }
    }).catch((e) => {
        console.log(e);
    });
}