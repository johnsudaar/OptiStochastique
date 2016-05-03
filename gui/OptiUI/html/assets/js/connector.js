$( window ).load(function() {
    serverURL = "ws://localhost:1337";

    console.log("Connection au serveur : "+serverURL);

    var socket = new WebSocket(serverURL);

    socket.onclose = function(){

    }

    socket.onerror = function(){

    }

    socket.onopen = function(){
        console.log("Connécté ! Mise en place des channels.");
        chan = new QWebChannel(socket, function(channel) {
            window.connector = channel.objects.connector;

            connector.sendResults.connect(function(i){
                console.log(i);
            });

            connector.compute(10);
        });
    };
});
