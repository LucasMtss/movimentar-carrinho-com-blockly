const button = document.querySelector("#executar-movimentos");
button.addEventListener("click", executarMovimentos);

function onFirstComment(event) {
  if (
    event.type == Blockly.Events.BLOCK_CHANGE &&
    event.element == "comment" &&
    !event.oldValue &&
    event.newValue
  ) {
    alert("Congratulations on creating your first comment!");
    workspace.removeChangeListener(onFirstComment);
  }
}
workspace.addChangeListener(onFirstComment);

function update(event) {
  Blockly.JavaScript.INFINITE_LOOP_TRAP = null;
  var code = new String(Blockly.JavaScript.workspaceToCode(workspace));
  if (code != "") {
    mostrar = code;
    document.getElementById("codigogerado").innerHTML = mostrar;
    cleanThanUp();
  }
}

function cleanThanUp() {
  var list = document.getElementById("im");
  while (list?.hasChildNodes()) {
    list.removeChild(list?.childNodes[0]);
  }
  updateGraph();
}

function updateGraph() {
  if (mostrar != "nada aqui") {
    var viz = new Viz();
    viz
      .renderSVGElement(mostrar)
      .then(function (element) {
        document.getElementById("im").appendChild(element);
      })
      .catch((error) => {
        // Create a new Viz instance (@see Caveats page for more info)
        viz = new Viz();

        // Possibly display the error
        console.error(error);
      });
  }
}
workspace.addChangeListener(update);

var req = new XMLHttpRequest();

function executarMovimentos() {
  const blocks = document.getElementsByClassName("blocklyDropdownText");
  const moviments = [];
  for (let item of blocks) {
    moviments.push(item.textContent.split(" ")[0]);
  }
  moviments.pop();

  req.open("POST", "http://127.0.0.1:5000/api/movimentos");

  req.setRequestHeader("Accept", "application/json");
  req.setRequestHeader("Content-Type", "application/json");

  const data = moviments.map((moviment) => {
    return {
      movimento: moviment,
    };
  });
  console.log(JSON.stringify(data));

  req.send(`{"movimentos": ${JSON.stringify(data)}}`);
}
