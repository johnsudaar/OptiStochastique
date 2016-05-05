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
    ["Asnieres", "Asnières",11],
    ["Valence", "Valence",12],
    ["Roanne", "Roanne",13],
    ["Evry", "Evry",14],
    ["Strasbourg", "Strasbourg",15],
    ["Avignon", "Avignon",16],
    ["Wasquehal", "Wasquehal",17],
    ["Marseille", "Marseille",18],
]

var modifying = false;
var distMatrix = [];
var geocoder;
var curTeam;
var nextAction;
var recapMap;
var resultMap;
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
                console.log("Geolocalisation done");
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
    nextAction = computeDistances2;
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

function placeMarkers(map, use_team){
    if(! map.markers){
        map.markers = [];
    }

    for(var marker in map.markers){
        map.markers[marker].setMap(null);
        console.log("marker removed !");
    }

    map.markers = [];

    if(! use_team){
        for(team in teamList){
            var marker = new google.maps.Marker({
                position: {lat:teamList[team][3][0], lng:teamList[team][3][1]},
                map: map,
                title: teamList[team][0]
              });
            map.markers.push(marker);
        }
    } else {
        for(i in results[0]){
            var team = teamList[results[0][i]];
            var marker = new google.maps.Marker({
                position: {lat:team[3][0], lng:team[3][1]},
                map: map,
                icon: "assets/pictures/star-blue.png",
                title: team[0]
              });
            map.markers.push(marker);
        }

        for(i in results[1]){
            var team = teamList[results[1][i]];
            var marker = new google.maps.Marker({
                position: {lat:team[3][0], lng:team[3][1]},
                map: map,
                icon: "assets/pictures/star-red.png",
                title: team[0]
            });
            map.markers.push(marker);
        }
    }
}

function buildMap(container, map, use_team){
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

    placeMarkers(map,use_team);
    return map;
}

function buildRecapView2(){
    if(firstRun){
        firstRun = false;
        computeDistances2();

        showPane("recap");
    }

    recapMap = buildMap("#recap-map", recapMap, false);
    $("#recap-table").html("");
    for(var pos = 1; pos <= teamList.length; pos++){
        $("#recap-table").append("<tr><td>"+pos+"</td><td>"+teamInPos(pos)[0]+"</td><td>"+teamInPos(pos)[1]+"</td></tr>");
    }
}

function updateRanks(pos) {
    var rank = teamList[pos][2];

    for(team in teamList) {
        if (teamList[team][2] > rank) {
            teamList[team][2] = teamList[team][2] - 1;
        }
    }
}

function modifyTr(tr) {
    var tds = tr.find("td");
    var rank = $(tds[0]).text();
    var nom = $(tds[1]).text();
    var lieu = $(tds[2]).text();

    $(tds[1]).html("<input type='text' id='nom-team-"+rank+"' class='form-control-2' value='"+nom+"'>");
    $(tds[2]).html("<input id='adresse-autocomplete-"+rank+"' type='text' class='form-control-2' value='"+lieu+"'>");
    $(tds[3]).html("<button id='modify-"+rank+"' class='btn btn-form btn-default'>Modifier</button><button id='modify-not-"+rank+"' class='btn btn-form btn-default'>Annuler</button>");

    var c = new google.maps.places.Autocomplete($("#adresse-autocomplete-"+rank)[0]);
    $("#modify-"+rank).click(function(){
        if ($("#nom-team-"+rank).val() === "") {
            if ($("#adresse-autocomplete-"+rank).val() === "") {
                toastr.error("Il faut remplir le nom et le lieu de l'équipe");
            }
            else {
                toastr.error("Il faut remplir le nom de l'équipe");
            }
        }
        else if ($("#adresse-autocomplete-"+rank).val() === "") {
            toastr.error("Il faut remplir le lieu de l'équipe");
        }
        else {
            for(team in teamList) {
                if (teamList[team][2] == rank) {

                    teamList[team][0] = $("#nom-team-"+rank).val();
                    teamList[team][1] = $("#adresse-autocomplete-"+rank).val();
                }
            }
            modifying = false;
            initDistMatrix();
            computeDistances();
            buildTeamView();
        }
    });
    $("#modify-not-"+rank).click(function(){
        modifying = false;
        buildTeamView();
    });

}

function upTeam(pos) {
    var rank = teamList[pos][2];

    if (rank != 0) {
        for(team in teamList) {
            if (teamList[team][2] == rank-1) {
                teamList[team][2] = rank;
            }
        }
        teamList[pos][2] = rank - 1;
    }
}

function downTeam(pos) {
    var rank = teamList[pos][2];

    if (rank != teamList.length) {
        for(team in teamList) {
            if (teamList[team][2] == rank+1) {
                teamList[team][2] = rank;
            }
        }
        teamList[pos][2] = rank + 1;
    }
}

function buildTeamView(){
    $("#team-table").html("");

    for(team in teamList){
        $("#team-table").append("<tr><td>"+teamList[team][2]+"</td><td>"+teamList[team][0]+"</td><td>"+teamList[team][1]+"</td><td><a class='icon icon-trash icon-link delete-team' id='"+team+"'></a><a class='icon icon-pencil icon-link modify-team'></a><a id='"+team+"' class='icon icon-up-dir icon-link up-team'></a><a id='"+team+"' class='icon icon-down-dir icon-link down-team'></a></td></tr>");
    }

    $(".delete-team").click(function(event){
        updateRanks(event.target.id);
        teamList.splice(event.target.id,1);
        initDistMatrix();
        computeDistances();
        rebuildView();
    });
    $(".modify-team").click(function(event){
        if (! modifying) {
            modifying = true;
            var tr = $(event.target).parent().parent();
            modifyTr(tr);
        }
        else {
            toastr.error("Vous ne pouvez faire qu'une modification à la fois");
        }
    });
    $(".up-team").click(function(event){
        upTeam(event.target.id);
        initDistMatrix();
        computeDistances();
        rebuildView();
    });
    $(".down-team").click(function(event){
        downTeam(event.target.id);
        initDistMatrix();
        computeDistances();
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
        recapMap = buildMap("#result-map", resultMap, true);
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

function createTeam() {
    if ($("#nom-team").val() === "") {
        if ($("#adresse-autocomplete").val() === "") {
            toastr.error("Il faut remplir le nom et le lieu de l'équipe");
        }
        else {
            toastr.error("Il faut remplir le nom de l'équipe");
        }
    }
    else if ($("#adresse-autocomplete").val() === "") {
        toastr.error("Il faut remplir le lieu de l'équipe");
    }
    else {
        teamList.push([$("#nom-team").val(), $("#adresse-autocomplete").val(), teamList.length + 1]);
        $("#nom-team").val("");
        $("#adresse-autocomplete").val("");
        initDistMatrix();
        computeDistances();
        buildTeamView();
    }
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

    autocomplete_center = new google.maps.places.Autocomplete($("#adresse-autocomplete")[0]);

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
        if(!firstRun) {
            buildRecapView();
            showPane("recap");
        }
        else {
            toastr.error("Vous devez attendre la fin du chargement pour y accéder");
        }
    });

    $("#dist-link").click(function(){
        if(!firstRun) {
            buildMatrixView();
            showPane("dist");
        }
        else {
            toastr.error("Vous devez attendre la fin du chargement pour y accéder");
        }
    });

    $("#team-link").click(function(){
        if(!firstRun) {
            buildTeamView();
            showPane("team");
        }
        else {
            toastr.error("Vous devez attendre la fin du chargement pour y accéder");
        }
    });

    $("#results-link").click(function(){
        if(!firstRun) {
            showPane("results");
            buildResultsView();
        }
        else {
            toastr.error("Vous devez attendre la fin du chargement pour y accéder");
        }
    });

    $("#recomputeMatrix").click(computeDistances);

    $("#launch-calc").click(launch);

    $("#button-new-team").click(createTeam);

    $("#recap-map").height($(window).height()-100);

    $("#result-map").height($(window).height()-100);

    $( window ).resize(function() {
        $("#recap-map").height($(window).height()-100);
    });

    $( window ).resize(function() {
        $("#result-map").height($(window).height()-100);
    });
});
