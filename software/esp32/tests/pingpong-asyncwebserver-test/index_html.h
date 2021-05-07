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
            var counter = 0;

            function ping() {
                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("message").innerHTML = this.responseText;
                    }
                };

                if (++counter > 10) counter = 10;

                document.getElementById("count").innerHTML = counter;

                xhttp.open("GET", "ping?count="+counter, true);
                xhttp.send();
            }
            
            function pong() {
                var xhttp = new XMLHttpRequest();

                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("message").innerHTML = this.responseText;
                    }
                };

                if (--counter < 1) counter = 1;

                document.getElementById("count").innerHTML = counter;

                xhttp.open("GET", "pong?count="+counter, true);
                xhttp.send();
            }
        </script>        
    </head>
    <body>
        <div>
            <center>
                <h1>PingPong</h1>
                <h1>Async Web Server Test</h1>
            </center>
            <div>
                <h2>Response: <span id="message"></span></h2>
            </div>
            <div>
                <h2>Count: <span id="count"></span></h2>
            </div>
            <div>
                <button class="button" onclick="ping()">Ping!</button>
                <button class="button" onclick="pong()">Pong!</button>
            </div>
        </div>
    </body>
</html>
)=====";