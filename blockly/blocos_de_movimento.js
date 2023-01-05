Blockly.Blocks["movimentos"] = {
  init: function () {
    this.appendValueInput("red")
      .setCheck(null)
      .appendField("movimento")
      .appendField(
        new Blockly.FieldDropdown([
          ["frente", "frente"],
          ["ré", "ré"],
          ["esquerda", "esquerda"],
          ["direita", "direita"],
        ]),
        "movimento"
      );
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(225);
    this.setTooltip("");
    this.setHelpUrl("");
  },
};

Blockly.JavaScript["movimentos"] = function (block) {
  var dropdown_movimento = block.getFieldValue("movimento");
  var value_red = Blockly.JavaScript.valueToCode(
    block,
    "red",
    Blockly.JavaScript.ORDER_ATOMIC
  );
  // TODO: Assemble JavaScript into code variable.
  var code = "testando 123";
  return code;
};
