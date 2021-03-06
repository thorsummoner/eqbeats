"use strict";
document.addEventListener("DOMContentLoaded", function(){
    var els = Array.from(document.querySelectorAll('[data-nojs]'));
    for(var el of els){
        el.parentElement.removeChild(el);
    }

    var result = document.querySelector('.result');
    if(result){
        if(result.dataset['result'] != "finished"){
            window.setTimeout(checkStatus, 1000);
            var spinner = document.createElement("div");
            spinner.classList.add("spinner");
            result.appendChild(spinner);
        }
    }

    function checkStatus(){
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "jobstatus", true);
        xhr.addEventListener("loadend", function(){
            if(xhr.status != 200)
                return window.setTimeout(checkStatus, 4000);
            var response = JSON.parse(xhr.response)
            if(response.status == "finished"){
                result.innerHTML = "";
                var a = document.createElement("a");
                a.href = response.result;
                a.appendChild(document.createTextNode("Download your archive ("+response.meta.size+"B)"));
                result.appendChild(a);
            }
            else if(response.status == "failed"){
                result.removeChild(spinner);
                result.appendChild(document.createTextNode("Something went awry! "));
                var retry = document.createElement("a");
                retry.href = "clear";
                retry.appendChild(document.createTextNode("Retry?"));
                result.appendChild(retry);
            }
            else {
                window.setTimeout(checkStatus, 700);
            }
        });
        xhr.send();
    }
});
