const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style type="text/css">
            .button {
                font-size: 24pt;
                font-weight: bold;
                width: 100%;
                margin-bottom: 1em;
            }
        </style>
        <script>
            // NOTE: This script is untested currently...USE AT OWN RISK

            // Geolocation interval in milliseconds
            var geolocInterval = 5000; 

            // Message checking interval in milliseconds
            var messageCheckInterval = 2500;

            // Client password
            var password = document.getElementById("password");

            // Response messages textarea element
            var messages = document.getElementById("messages");

            // Browser geolocation successful, send coordinates back to robot
            function geosuccess(position) {
                var latitude  = position.coords.latitude;
                var longitude = position.coords.longitude;
                var heading = position.coords.heading;

                messages.value += "\nLat: ${latitude} °, Lon: ${longitude} °, Hed: ${heading}";

                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        messages.value += "\n" + this.responseText;
                    }
                };

                xhttp.open("GET", "location?pwd="+password.value+"&lat="+latitude+"&lon="+longitude+"&hed="+heading, true);
                xhttp.send();
            }

            // Browser geolocation unsuccessful...
            function geoerror() {
                messages.value += "\nUnable to get the client location...";
            }

            // Check to see if browser can use geolocation
            if (!navigator.geolocation) {
                messages.value += "\nGeolocation is not supported by your browser...";
            } else {
                // If it can, geolocate every {interval}
                setInterval(function() {
                    messages.value += "\nLocating...";
                    navigator.geolocation.getCurrentPosition(geosuccess, geoerror);
                }, geolocInterval);

                // Periodically get a set message from the robot and display it
                setInterval(function() {
                    var xhttp = new XMLHttpRequest();

                    xhttp.onreadystatechange = function() {
                        if (this.readyState == 4 && this.status == 200) {
                            if (this.responseText != "") {
                                messages.value += "\n" + this.responseText;
                            }
                        }
                    };

                    xhttp.open("GET", "getmessage", true);

                    xhttp.send();
                }, messageCheckInterval);
            }

            // If the user presses the E-STOP button, send request to robot
            function estop() {
                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        messages.value += "\n" + this.responseText;
                    }
                };

                xhttp.open("GET", "estop?pwd="+password.value, true);

                xhttp.send();
            }
        </script>        
    </head>
    <body>
        <div>
            <center>
                <h2>Junkbotix</h2>
                <h2>Follow Me Robot Client</h2>
                <div>
                    <label for="pwd">Password:</label>
                    <input id="password" name="pwd" type="text" />
                </div>
                <div>
                    <button class="button" onclick="estop()">!!! E-STOP !!!</button>
                </div>
            </center>
            <div>
                <textarea id="messages" rows=40 cols=80 autofocus></textarea>
            </div>
        </div>
    </body>
</html>
)=====";