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

            // Response messages textarea element
            var messages = document.getElementById("messages");

            // Send an xhttp response message to server and listen for the response
            function doxhttp(method, node, response) {
                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        messages.value += "\n" + this.responseText;
                    }
                };
        
                // Get client password setting
                var password = document.getElementById("password");

                xhttp.open("GET", node+"?pwd="+password.value+response, true);
                xhttp.send();

            }

            /*******************************************************************************/
            // The following generator functions originally from: 
            //   https://stackoverflow.com/questions/6878761/javascript-how-to-create-random-longitude-and-latitudes            
            /*******************************************************************************/

            // LATITUDE -90 to +90
            function genLatitude() {
                var num = (Math.random()*90).toFixed(6);
                var posorneg = Math.floor(Math.random());
                if (posorneg == 0) {
                    num = num * -1;
                }
                return num;
            }

            // LONGITUDE -180 to + 180
            function genLongitude() {
                var num = (Math.random()*180).toFixed(6);
                var posorneg = Math.floor(Math.random());
                if (posorneg == 0) {
                    num = num * -1;
                }
                return num;
            }

            // HEADING 0 to +359
            function genHeading() {
                return (Math.random()*360).toFixed(0);
            }

            /*******************************************************************************/

            // Browser geolocation successful, send coordinates back to robot
            function geosuccess(position) {
                var latitude  = position.coords.latitude;
                var longitude = position.coords.longitude;
                var heading = position.coords.heading;

                messages.value += "\nLat: ${latitude} °, Lon: ${longitude} °, Hed: ${heading}";

                doxhttp("GET", "location", "&lat="+latitude+"&lon="+longitude+"&hed="+heading);
            }

            // Browser geolocation unsuccessful...
            function geoerror() {
                messages.value += "\nUnable to get the client location...";
            }

            function dogeolocation() {
                if (!document.getElementById("fakegps").value) {
                    // Attempt to get actual GPS coordinates from browser
                    if (!navigator.geolocation) {
                        messages.value += "\nGeolocation is not supported by your browser...";
                    } else {
                        messages.value += "\nLocating...";
                        navigator.geolocation.getCurrentPosition(geosuccess, geoerror);
                    }
                } else {
                    // Generate and send some fake coordinate values
                    messages.value += "\n(FAKE) Locating...";

                    geosuccess({
                        coords: {
                            latitude: genLatitude(),
                            longitude: genLongitude(),
                            heading: genHeading()
                        }
                    });
                }
            }

            // Geolocate every {interval}
            setInterval(dogeolocation, geolocInterval);

            // Periodically get a set message from the robot and display it
            setInterval(function() {
                doxhttp("GET", "getmessage");
            }, messageCheckInterval);

            // If the user presses the E-STOP button, send request to robot
            function estop() {
                doxhttp("GET", "estop");
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
                    <input id="fakegps" type="checkbox" name="sendfakegps" checked>
                    <label for="sendfakegps">Send Fake GPS Coords?</label>                    
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