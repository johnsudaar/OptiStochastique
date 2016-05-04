var teamList =  [
    ["Toulouse", "Toulouse",1],
    ["Chambery", "Chambery",2],
    ["Cergy", "Cergy",3],
    ["Meudon", "Meudon",4],
    ["Annecy", "Annecy",5],
    ["Limoges", "Limoges",6],
    ["Amnéville", "Amnéville",7],
    ["Francais volants", "Paris",8],
    ["Clermont", "Clermont-Ferrand",9],
    ["Villard", "Villard-de-Lans",10],
    ["Asnieres", "asnieres sur seine",11],
    ["Valence", "Valence",12],
    ["Roanne", "Roanne",13],
    ["Evry", "Evry",14],
    ["Strasbourg", "Strasbourg",15],
    ["Avignon", "Avignon",16],
    ["Wasquehal", "Wasquehal",17],
    ["Marseille", "Marseille",18],
]

var distMatrix = [];
var geocoder;
var curTeam;
var nextAction;
var recapMap;
var results = null;
var firstRun = true;
var coeff_slider;

var rad = function(x) {
    return x * Math.PI / 180;
};

var getDistance = function(lat1,lng1, lat2, lng2) {
    var R = 6378137; // Earth’s mean radius in meter
    var dLat = rad(lat2 - lat1);
    var dLong = rad(lng2 - lng1);
    var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
        Math.cos(rad(lat1)) * Math.cos(rad(lat2)) *
        Math.sin(dLong / 2) * Math.sin(dLong / 2);
    var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
    var d = R * c;
    return d; // returns the distance in meter
};

function initDistMatrix(){
    for(team=0; team < teamList.length; team++){
        distMatrix[team] = [];
        for(team2=0; team2 < teamList.length; team2++){
            if(team == team2){
                distMatrix[team][team2] = 0;
            } else {
                distMatrix[team][team2] = team+team2;
            }
        }
    }
}

function computeDistances2(){
    for(team in teamList){
        for(team2 in teamList){
            distMatrix[team][team2]  = getDistance(teamList[team][3][0], teamList[team][3][1], teamList[team2][3][0], teamList[team2][3][1])
        }
    }
    buildMatrixView();
}

function teamInPos(pos){
    for(team in teamList){
        if(teamList[team][2] == pos){
            return teamList[team];
        }
    }

    return null;
}

function launchGeoLoc(){
    if(curTeam >= teamList.length){
        console.log("Done")
        nextAction();
    } else if(! teamList[curTeam][3]){
        console.log("Geocoding")
        geocoder.geocode({
            'address': teamList[curTeam][1]
        }, function(results, status) {
            if(status === google.maps.GeocoderStatus.OVER_QUERY_LIMIT){
                setTimeout(launchGeoLoc,200);
            } else {
                var lat=results[0].geometry.location.lat();
                var lng=results[0].geometry.location.lng();
                teamList[curTeam][3] = [lat,lng];
                curTeam ++;
                setTimeout(launchGeoLoc,100);
            }
        });
    } else {
        console.log("Do not geoloc");
        curTeam ++;
        launchGeoLoc();
    }
}

function computeDistances(){
    curTeam = 0;
    nextAction = computeDistances2();
    launchGeoLoc();
}

function showPane(pane){
    $(".c-pane").hide();
    $(".nav-group-item").removeClass("active");
    $("."+pane).show();
    $("#"+pane+"-link").addClass("active");
}

function rebuildView(){
    buildRecapView();
    buildTeamView();
    buildMatrixView();
}

function buildRecapView(){
    curTeam = 0;
    nextAction = buildRecapView2;
    launchGeoLoc();

}

function placeMarkers(map){
    if(! map.markers){
        map.markers = [];
    }

    for(var marker in map.markers){
        map.markers[marker].setMap(null);
        console.log("marker removed !");
    }

    map.markers = [];

    for(team in teamList){
        var marker = new google.maps.Marker({
            position: {lat:teamList[team][3][0], lng:teamList[team][3][1]},
            map: map,
            title: teamList[team][0]
          });
        map.markers.push(marker);
    }
}

function buildMap(container, map){
    var bounds = new google.maps.LatLngBounds();
    for(team in teamList) {
        bounds.extend(new google.maps.LatLng(teamList[team][3][0],teamList[team][3][1]));
    }
    if(teamList.length == 0){
        bounds.extend(new google.maps.LatLng(48.5839200,7.7455300));
    }

    var center = bounds.getCenter();
    var mapOptions = {
        center:center,
        zoom:13
    }

    if(!map){
        map = new google.maps.Map($(container)[0],mapOptions);
        if(teamList.length >= 2){
            map.fitBounds(bounds);
            map.panToBounds(bounds);
        }
    }

    placeMarkers(map);
    return map;
}

function buildRecapView2(){
    if(firstRun){
        firstRun = false;
        computeDistances2();
        showPane("recap");
    }

    recapMap = buildMap("#recap-map", recapMap);
    $("#recap-table").html("");
    for(var pos = 1; pos <= teamList.length; pos++){
        $("#recap-table").append("<tr><td>"+pos+"</td><td>"+teamInPos(pos)[0]+"</td><td>"+teamInPos(pos)[1]+"</td></tr>");
    }
}

function buildTeamView(){
    $("#team-table").html("");
    for(team in teamList){
        $("#team-table").append("<tr><td>"+teamList[team][2]+"</td><td>"+teamList[team][0]+"</td><td>"+teamList[team][1]+"</td><td><a class='icon icon-trash icon-link delete-team' id='"+team+"'></a><a class='icon icon-pencil icon-link'></a></td></tr>");
    }
    $(".delete-team").click(function(event){
        teamList.splice(event.target.id,1);
        rebuildView();
    });
}

function showResults(teamA, teamB){
    results = [teamA, teamB];
    showPane("results");
    buildResultsView();
}

function buildResultsView(){
    if(results === null){
        $(".results-failed").show();
        $(".results-ok").hide();
    } else {
        $(".results-failed").hide();
        $(".results-ok").show();
        $("#teama-table").html("");
        $("#teamb-table").html("");
        for(i in results[0]){
            team=teamList[results[0][i]]
            $("#teama-table").append("<tr><td>"+team[2]+"</td><td>"+team[0]+"</td><td>"+team[1]+"</td></tr>");
        }
        for(i in results[1]){
            team=teamList[results[1][i]]
            $("#teamb-table").append("<tr><td>"+team[2]+"</td><td>"+team[0]+"</td><td>"+team[1]+"</td></tr>");
        }
    }
}

function buildMatrixView(){
    str="<thead><tr><th>Team</th>"
    for(team in teamList){
        str+="<th>"+teamList[team][0]+"</th>"
    }
    str+="</tr></thead><tbody>"

    for(team in teamList){
        str+="<tr><td>"+teamList[team][0]+"</td>"
        for(team2 in teamList){
            str+="<td>"+Math.floor(distMatrix[team][team2]/1000)+"</td>"
        }
        str+="</tr>"
    }
    $("#matrix-table").html(str+"</tbody>");
}

function launch(){
    classement = [];
    for(var i = 0; i < teamList.length; i++){
        classement[i] = teamList[i][2];
    }
    window.connector.compute(classement, distMatrix, coeff_slider.noUiSlider.get());
    showPane("loading");
}

$( window ).load(function() {
    geocoder = new google.maps.Geocoder();

    initDistMatrix();

    rebuildView();

    coeff_slider = document.getElementById('coeff-slider');

    noUiSlider.create(coeff_slider, {
        start: 0,
        range: {
            'min': [ 0 ],
            'max': [ 100000 ]
        },
        pips: {
            mode: 'positions',
            values: [0,100000],
            density: 4,
            format: {
                to: function ( value ) {
                    return value === 0 ? "Distance" : "Classement";
                },
                from: function ( value ) {
                    return value === 0 ? "Distance" : "Classement";
                }
            },
            stepped: true
        }
    });

    showPane("loading");
    $("#recap-link").click(function(){
        buildRecapView();
        showPane("recap");
    });

    $("#dist-link").click(function(){
        buildMatrixView();
        showPane("dist");
    });

    $("#team-link").click(function(){
        buildTeamView();
        showPane("team");
    });

    $("#results-link").click(function(){
        showPane("results");
        buildResultsView();
    });

    $("#recomputeMatrix").click(computeDistances);

    $("#launch-calc").click(launch);
});
