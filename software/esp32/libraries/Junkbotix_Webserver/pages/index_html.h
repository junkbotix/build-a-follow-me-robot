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
            #messages {
                width: 99%;
                max-width: 99%;
            } 
        </style>
        <script>
            // NOTE: This script is incomplete...USE AT YOUR OWN RISK

            // Client e-stopped flag
            var isEstopped = false;

            // Geolocation interval period in milliseconds
            var geolocPeriod = 5000; 

            // Message checking interval period in milliseconds
            var messageCheckPeriod = 2500;

            // Add a message to textarea element, scroll to bottom
            function addMessage(message) {
                document.getElementById("messages").value += "\n" + message;
                messages.scrollTop = messages.scrollHeight;
            }

            // Send an xhttp response message to server and listen for the response
            function doxhttp(method = "GET", node = "", response = "") {
                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    // Send response messages to textarea element
                    if (this.readyState == 4 && this.status == 200) {
                        addMessage(this.responseText);
                    }
                };
        
                // Get client password setting
                var password = document.getElementById("password").value;

                xhttp.open(method, node+"?pwd="+password+response, true);
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
            function geoSuccess(position) {
                var latitude  = position.coords.latitude;
                var longitude = position.coords.longitude;
                var heading = position.coords.heading;

                // Send to messages textarea element°
                addMessage("Loc: "+latitude+", "+longitude+" ["+heading+"]");

                doxhttp("GET", "location", "&lat="+latitude+"&lon="+longitude+"&hed="+heading);
            }

            // Browser geolocation unsuccessful...
            function geoError() {
                // Send to messages textarea element
                addMessage("Unable to get the client location...");
            }

            function doGeolocation() {

                if (!document.getElementById("fakegps").value) {
                    // Attempt to get actual GPS coordinates from browser
                    if (!navigator.geolocation) {
                        addMessage("Geolocation is not supported by your browser...");
                    } else {
                        addMessage("Locating...");
                        navigator.geolocation.getCurrentPosition(geoSuccess, geoError);
                    }
                } else {
                    // Generate and send some simulated coordinate values
                    addMessage("[S] Locating...");

                    geoSuccess({
                        coords: {
                            latitude: genLatitude(),
                            longitude: genLongitude(),
                            heading: genHeading()
                        }
                    });
                }                
            }
        
            var intervalCount = 0;

            var clientInterval = setInterval(function() {
                if (intervalCount == messageCheckPeriod) {
                    // Periodically get message from the robot and display it
                    doxhttp("GET", "getmessage");
                } else if (intervalCount == geolocPeriod) {
                    // Geolocate
                    if (!isEstopped) doGeolocation();
                    intervalCount = 0;
                }

                intervalCount += 100;
            }, 100);

            // If the user presses the E-STOP button, send request to robot
            function estop() {
                doxhttp("GET", "estop");
                isEstopped = true;
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
                <textarea id="messages" rows=15></textarea>
            </div>
        </div>
    </body>
</html>
)=====";